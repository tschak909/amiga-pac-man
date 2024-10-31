/**
 * @brief   Score Task
 * @verbose Each task manages a score for a player.
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see LICENSE for details.
 */

#include <exec/types.h>
#include <exec/nodes.h>
#include <exec/lists.h>
#include <exec/memory.h>
#include <exec/interrupts.h>
#include <exec/ports.h>
#include <exec/libraries.h>
#include <exec/tasks.h>
#include <exec/io.h>
#include <exec/devices.h>
#include <devices/timer.h>
#include <graphics/gfx.h>
#include <graphics/gfxbase.h>
#include <intuition/intuition.h>

#include "font.h"
#include "MazeBorders.h"

#define TEXT_HEIGHT		8
#define HEADER_HISCORE_X	232
#define HEADER_HISCORE_Y 	24
#define SCORE_HISCORE_Y 	HEADER_HISCORE_Y + TEXT_HEIGHT
#define HEADER_1UP_Y		48
#define SCORE_1UP_Y		HEADER_1UP_Y + TEXT_HEIGHT
#define HEADER_2UP_Y		72
#define SCORE_2UP_Y		HEADER_2UP_Y + TEXT_HEIGHT
#define SCORE_X			264

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

extern struct MsgPort *CreatePort();
extern struct MsgPort *FindPort();
extern struct IORequest *CreateExtIO();
extern struct Task *CreateTask();

/** The Test Harness *******************************************************/

struct Screen *OpenScreen();
struct Window *OpenWindow();

struct Task *task;

struct Screen *sPacMan;
struct Window *wPacMan;

struct NewScreen nsPacMan = 
{
	0, 0,
	320, 200, 4,
	3, 0, /* 0, 1 */
	NULL,
	CUSTOMSCREEN,
	NULL,
	"PAC-MAN(tm)",
	NULL
};

struct NewWindow nwPacMan = 
{
	0, 0,
	320, 200,
	0, 1,
	NULL,
	BORDERLESS|BACKDROP,
	NULL,
	NULL,
	"PAC-MAN(tm)",
	NULL,
	NULL,
	320,200,320,200,
	CUSTOMSCREEN
};

struct TextAttr taFont = {
	"Arcade8.font",
	8,
	FS_NORMAL,
	FPF_DESIGNED
};

USHORT colorTable[16] = 
{
	0x000,		/* 0: Black */
	0xFF0,		/* 1: Yellow */
	0xF00,		/* 2: Light Red */
	0xFFF,		/* 3: White */
	0x00F,		/* 4: Light Blue */
	0xF0F,		/* 5: Light Magenta */
	0x0FF,		/* 6: Light Cyan */
	0x770,		/* 7: Dark Yellow (pale orange?) */
	0x0F0,		/* 8: Light Green */
	0xFA0,		/* 9: Light Orange */
	0xFEF,		/* A: Pinky white */
	0xFCB,		/* B: Power Pellet */
	0x0FF,		/* C: Light Cyan */
	0xF00,		/* D: Light Red */
	0xF0F,		/* E: Light Magenta */
	0xFFF,		/* F: White */
};

struct ScoreMessage
{
	struct Message msg;
	int cmd;
	int playerno;
	char *score;
};

#define SCORE_CMD_RESET 0
#define SCORE_CMD_SET 1
#define SCORE_CMD_ADD 2
#define SCORE_CMD_STOP -1

/**
 * @brief Add digits in s to d, ignore blank spaces
 * @param s Source string, the # of points to add
 * @param d Dest string, the score to add to.
 */
void scoreTask_Add(s, d)
char *s, *d;
{
	int i=0;		/* Index */
	int carry=0;		/* Carry flag */

	for (i=7;i-- >0;)	/* Go from right to left <- */
	{
		char cs = s[i]; /* Grab current source char */
		char cd = d[i]; /* Grab current dest char   */

		if (carry)			/* last digit carried... */
		{
			if (cs < '0')		/* If source digit empty */
				cs = '0';	/* set to '0' 	         */
			if (cd < '0')           /* If dest digit empty   */
				cd = '0';       /* set to '0'            */
		}
		else				/* ...didn't carry       */
		{
			if (cs < '0')		/* If source digit empty */
				continue;	/* ignore and continue   */
		}

		/* Convert source/dest ASCII digits */
		cs -= '0';
		cd -= '0';

		/* Add the source digit and carry (if set) */
		cd += cs + carry;
		carry = 0; /* Clear carry for next round.  */

		if (cd > 9)		/* Digit overflowed */
		{
			carry = 1;	/* Set carry	    */
			cd -= 10;       /* Leave remainder  */
		}

		cd += '0';		/* Convert back to ASCII */
		d[i] = cd;		/* Place in destination. */
	}
}

/** 
 * @brief set the score d with string s
 * @param s The source (score to set as const)
 * @param d The destination (score char array)
 */
void scoreTask_Set(s, d)
char *s, *d;
{
	/* Yes, this is unrolled. ;) */
	d[0]=s[0];
	d[1]=s[1];
	d[2]=s[2];
	d[3]=s[3];
	d[4]=s[4];
	d[5]=s[5];
	d[6]=s[6];	
}

void scoreTask_Hiscore(s,d)
char *s, *d;
{
	int i=0;

	for (i=0; i<7; i++)
		if (s[i] > d[i])
		{
			scoreTask_Set(s,d);
			Move(wPacMan->RPort,SCORE_X,32);
			Text(wPacMan->RPort,d,7);
			break;
		}
}

/**
 * @brief Reset P1 and P2 scores
 * @param pointers to score1 and score2
 */
void scoreTask_Reset(s0, s1, s2)
char *s0, *s1, *s2;
{
	scoreTask_Set("     00",s1);
	scoreTask_Set("     00",s2);
	
	Move(wPacMan->RPort,HEADER_HISCORE_X,HEADER_HISCORE_Y);
	Text(wPacMan->RPort,"HIGH SCORE",10);
	Move(wPacMan->RPort,SCORE_X,SCORE_HISCORE_Y);
	Text(wPacMan->RPort,s0,7);
	Move(wPacMan->RPort,SCORE_X,HEADER_1UP_Y);
	Text(wPacMan->RPort,"   1UP ",7);
	Move(wPacMan->RPort,SCORE_X,SCORE_1UP_Y);
	Text(wPacMan->RPort,s1,7);
	Move(wPacMan->RPort,SCORE_X,HEADER_2UP_Y);
	Text(wPacMan->RPort,"   2UP ",7);
	Move(wPacMan->RPort,SCORE_X,SCORE_2UP_Y);
	Text(wPacMan->RPort,s2,7);
}

void scoreTask()
{
	struct MsgPort *taskPort;
	char score1[7], score2[7], hiscore[7], *score;

	int x,y;

	x=SCORE_X;

	Forbid();

	taskPort = CreatePort("score.port",0);

	if (!taskPort)
	{
		Permit();
		return;
	}
	
	Permit();

	FOREVER /* RJ Mical'ism */
	{
		struct ScoreMessage *msg;
		
		msg = (struct ScoreMessage *)WaitPort(taskPort);

		/* There are messages. Process them */

		while (msg = (struct ScoreMessage *)GetMsg(taskPort))
		{
			switch(msg->cmd)
			{
				case SCORE_CMD_RESET:
					scoreTask_Reset(hiscore,score1,score2);
					break;

				case SCORE_CMD_SET:
					if (msg->playerno==0)
						scoreTask_Set(msg->score,
								hiscore);
					else if (msg->playerno==1)
						scoreTask_Set(msg->score, 
								score1);
					else if (msg->playerno==2)
						scoreTask_Set(msg->score, 
								score2);
					break;
				case SCORE_CMD_ADD:
					if (msg->playerno==0)
						scoreTask_Add(msg->score,
								hiscore);
					else if (msg->playerno==1)
						scoreTask_Add(msg->score,
								score1);
					else if (msg->playerno==2)
						scoreTask_Add(msg->score,
								score2);
					break;
				case SCORE_CMD_STOP:
					goto score_stop;
			}

			/* Place the score */
			switch(msg->playerno)
			{
				case 0:
					score=&hiscore[0];
					y=SCORE_HISCORE_Y;
					break;
				case 1:
					score=&score1[0];
					y=SCORE_1UP_Y;
					break;
				case 2:
					score=&score2[0];
					y=SCORE_2UP_Y;
					break;
			}

			SetAPen(wPacMan->RPort,3);
			Move(wPacMan->RPort,SCORE_X,y);
			Text(wPacMan->RPort,score,7);

			scoreTask_Hiscore(score,hiscore);

			/* Free the memory for the message, we're done. */
			FreeMem(msg, sizeof(struct ScoreMessage));
		}

	}

score_stop:
	/* Drain the message port, and then delete it */
	while ((struct ScoreMessage *)GetMsg(taskPort));
	
	DeletePort(taskPort);

	DeleteTask(0); /* Bye. */
}

/* The Test Harness ******************************************************/

struct MsgPort *taskPort;

main()
{
	int i=0;
	struct ScoreMessage *resetMsg, *set1Msg, *set2Msg;

	GfxBase = (struct GfxBase *)
		OpenLibrary("graphics.library",0);

	if (!GfxBase)
		goto bye;

	IntuitionBase = (struct IntuitionBase *)
		OpenLibrary("intuition.library",0);

	if (!IntuitionBase)
		goto bye;

	FontInit_Arcade8();
	AddFont(&Arcade8Font);

	nsPacMan.Font = &taFont;
	
	sPacMan = OpenScreen(&nsPacMan);
	if (!sPacMan)
		goto bye;

	LoadRGB4(&sPacMan->ViewPort, colorTable, 16);

	nwPacMan.Screen = sPacMan;
	wPacMan = OpenWindow(&nwPacMan);
	if (!wPacMan)
		goto bye;

	SetRast(wPacMan->RPort,0);

	DrawBorder(wPacMan->RPort,&boMaze,0,7);

	task = CreateTask("score.task",0,scoreTask,1000);
	if (!task)
		goto bye;

	while (!taskPort)
		taskPort = FindPort("score.port");
	
	if (!taskPort)
		goto bye;

	resetMsg = (struct ScoreMessage *)
		AllocMem(sizeof(struct ScoreMessage), MEMF_PUBLIC|MEMF_CLEAR);

	if (!resetMsg)
		goto bye;

	resetMsg->msg.mn_Node.ln_Type = NT_MESSAGE;
	resetMsg->msg.mn_Length = sizeof(struct ScoreMessage);
	resetMsg->cmd = SCORE_CMD_RESET;
	PutMsg(taskPort, resetMsg);

	set1Msg = (struct ScoreMessage *)
		AllocMem(sizeof(struct ScoreMessage), MEMF_PUBLIC|MEMF_CLEAR);
	
	if (!set1Msg)
		goto bye;

	set1Msg->msg.mn_Node.ln_Type = NT_MESSAGE;
	set1Msg->msg.mn_Length = sizeof(struct ScoreMessage);
	set1Msg->cmd = SCORE_CMD_SET;
	set1Msg->playerno = 1;
	set1Msg->score = "     00";
	PutMsg(taskPort, set1Msg);

	set2Msg = (struct ScoreMessage *)
		AllocMem(sizeof(struct ScoreMessage), MEMF_PUBLIC|MEMF_CLEAR);
	
	if (!set2Msg)
		goto bye;
	
	set2Msg->msg.mn_Node.ln_Type = NT_MESSAGE;
	set2Msg->msg.mn_Length = sizeof(struct ScoreMessage);
	set2Msg->cmd = SCORE_CMD_SET;
	set2Msg->playerno = 2;
	set2Msg->score = "    400";
	PutMsg(taskPort, set2Msg);

	for (i=0; i<240; i++)
	{
		struct ScoreMessage *addMsg;
	
		addMsg = (struct ScoreMessage *)
			AllocMem(sizeof(struct ScoreMessage),
				MEMF_PUBLIC|MEMF_CLEAR);

		if (!addMsg)
			goto bye;	
	
		addMsg->msg.mn_Node.ln_Type = NT_MESSAGE;
		addMsg->msg.mn_Length = sizeof(struct ScoreMessage);
		addMsg->cmd = SCORE_CMD_ADD;
		addMsg->playerno = 1;
		addMsg->score = "     10";
		PutMsg(taskPort, addMsg);
		Delay(2);
	}

	Delay(100);
	
bye:
	if (task)
	{
		struct ScoreMessage stop;

		stop.msg.mn_Node.ln_Type = NT_MESSAGE;
		stop.msg.mn_Length = sizeof(struct ScoreMessage);
		stop.cmd = SCORE_CMD_STOP;
		PutMsg(taskPort, &stop);
		Delay(10);	
	}

	RemFont(&Arcade8Font);

	if (wPacMan)
		CloseWindow(wPacMan);

	if (sPacMan)
		CloseScreen(sPacMan);

	if (IntuitionBase)
		CloseLibrary(IntuitionBase);

	if (GfxBase)
		CloseLibrary(GfxBase);
}
