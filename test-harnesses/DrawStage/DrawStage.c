/**
 * @brief   Draw Stage Task
 * @verbose Draw Stage
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
#include "Fruits.h"
#include "StageMessage.h"

#define NUM_PLAYERS 2

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

WORD stage_x[7] = {192,208,224,240,256,272,288};
#define STAGE_Y 176
#define NUM_IMGS 7
struct Image stage_imgs[NUM_IMGS];

void stageTask_setup_imgs()
{
	int i=0;

	/* Exit if no window rastport */
	if (!wPacMan->RPort)
		return FALSE;

	/* Clear pointers to struct Images */
	for (i=0;i<7;i++)
		img[i] = NULL;

	/* Clear the stage fruit area */
	SetAPen(wPacMan->RPort,0);
	RectFill(wPacMan->RPort,stageX[0],STAGEY,stageX[6]+16,STAGEY+16);

	/* Set up pointers to images */
	switch(stage)
	for (i=0;i<NUM_IMGS;i++)
	{
		stage_imgs[i].LeftEdge = stage_x[i];
		stage_imgs[i].TopEdge = STAGE_Y;
		stage_imgs[i].Width = stage_imgs[i].Height = 16;
		stage_imgs[i].Depth = 3; /* 8 colors */
		stage_imgs[i].ImageData = bmEmpty;
		stage_imgs[i].PlanePick = 0x07;
		stage_imgs[i].PlaneOnOff = 0x00;
		stage_imgs[i].NextImage = 
			(i==NUM_IMGS-1 ? NULL : &stage_imgs[i+1]);
	}
}

void stageTask_clearImgs()
{
	int i=0;

	for (i=0;i<NUM_IMGS;i++)
		stage_imgs[i].ImageData = bmEmpty;	
}

void stageTask_Set(msg)
struct StageMessage *msg;
{
	stageTask_clearImgs();

	switch (msg->stageNo)
	{
		case 0:
			stage_imgs[6].ImageData = bmCherry;
			break;
		case 1:
			stage_imgs[6].ImageData = bmStrawberry;
			stage_imgs[5].ImageData = bmCherry;
			break;
		case 2:
			stage_imgs[6].ImageData = bmOrange;
			stage_imgs[5].ImageData = bmStrawberry;
			stage_imgs[4].ImageData = bmCherry;
			break;
		case 3:
			stage_imgs[6].ImageData = bmOrange;
			stage_imgs[5].ImageData = bmOrange;
			stage_imgs[4].ImageData = bmStrawberry;
			stage_imgs[3].ImageData = bmCherry;
			break;
		case 4:
			stage_imgs[6].ImageData = bmApple;
			stage_imgs[5].ImageData = bmOrange;
			stage_imgs[4].ImageData = bmOrange;
			stage_imgs[3].ImageData = bmStrawberry;
			stage_imgs[2].ImageData = bmCherry;
			break;
		case 5:
			stage_imgs[6].ImageData = bmApple;
			stage_imgs[5].ImageData = bmApple;
			stage_imgs[4].ImageData = bmOrange;
			stage_imgs[3].ImageData = bmOrange;
			stage_imgs[2].ImageData = bmStrawberry;
			stage_imgs[1].ImageData = bmCherry;
			break;
		case 6:
			stage_imgs[6].ImageData = bmMelon;
			stage_imgs[5].ImageData = bmApple;
			stage_imgs[4].ImageData = bmApple;
			stage_imgs[3].ImageData = bmOrange;
			stage_imgs[2].ImageData = bmOrange;
			stage_imgs[1].ImageData = bmStrawberry;
			stage_imgs[0].ImageData = bmCherry;
			break;
		case 7:
			stage_imgs[6].ImageData = bmMelon;
			stage_imgs[5].ImageData = bmMelon;
			stage_imgs[4].ImageData = bmApple;
			stage_imgs[3].ImageData = bmApple;
			stage_imgs[2].ImageData = bmOrange;
			stage_imgs[1].ImageData = bmOrange;
			stage_imgs[0].ImageData = bmStrawberry;
			break;
		case 8:
			stage_imgs[6].ImageData = bmGalaxian;
			stage_imgs[5].ImageData = bmMelon;
			stage_imgs[4].ImageData = bmMelon;
			stage_imgs[3].ImageData = bmApple;
			stage_imgs[2].ImageData = bmApple;
			stage_imgs[1].ImageData = bmOrange;
			stage_imgs[0].ImageData = bmOrange;
			break;
		case 9:
			stage_imgs[6].ImageData = bmGalaxian;
			stage_imgs[5].ImageData = bmGalaxian;
			stage_imgs[4].ImageData = bmMelon;
			stage_imgs[3].ImageData = bmMelon;
			stage_imgs[2].ImageData = bmApple;
			stage_imgs[1].ImageData = bmApple;
			stage_imgs[0].ImageData = bmOrange;
			break;
		case 10:
			stage_imgs[6].ImageData = bmBell;
			stage_imgs[5].ImageData = bmGalaxian;
			stage_imgs[4].ImageData = bmGalaxian;
			stage_imgs[3].ImageData = bmMelon;
			stage_imgs[2].ImageData = bmMelon;
			stage_imgs[1].ImageData = bmApple;
			stage_imgs[0].ImageData = bmApple;
			break;
		case 11:
			stage_imgs[6].ImageData = bmBell;
			stage_imgs[5].ImageData = bmBell;
			stage_imgs[4].ImageData = bmGalaxian;
			stage_imgs[3].ImageData = bmGalaxian;
			stage_imgs[2].ImageData = bmMelon;
			stage_imgs[1].ImageData = bmMelon;
			stage_imgs[0].ImageData = bmApple;
			break;
		case 12:
			stage_imgs[6].ImageData = bmKey;
			stage_imgs[5].ImageData = bmBell;
			stage_imgs[4].ImageData = bmBell;
			stage_imgs[3].ImageData = bmGalaxian;
			stage_imgs[2].ImageData = bmGalaxian;
			stage_imgs[1].ImageData = bmMelon;
			stage_imgs[0].ImageData = bmMelon;
			break;
		case 13:
			stage_imgs[6].ImageData = bmKey;
			stage_imgs[5].ImageData = bmKey;
			stage_imgs[4].ImageData = bmBell;
			stage_imgs[3].ImageData = bmBell;
			stage_imgs[2].ImageData = bmGalaxian;
			stage_imgs[1].ImageData = bmGalaxian;
			stage_imgs[0].ImageData = bmMelon;
			break;
		case 14:
			stage_imgs[6].ImageData = bmKey;
			stage_imgs[5].ImageData = bmKey;
			stage_imgs[4].ImageData = bmKey;
			stage_imgs[3].ImageData = bmBell;
			stage_imgs[2].ImageData = bmBell;
			stage_imgs[1].ImageData = bmGalaxian;
			stage_imgs[0].ImageData = bmGalaxian;
			break;
		case 15:
			stage_imgs[6].ImageData = bmKey;
			stage_imgs[5].ImageData = bmKey;
			stage_imgs[4].ImageData = bmKey;
			stage_imgs[3].ImageData = bmKey;
			stage_imgs[2].ImageData = bmBell;
			stage_imgs[1].ImageData = bmBell;
			stage_imgs[0].ImageData = bmGalaxian;
			break;
		case 16:
			stage_imgs[6].ImageData = bmKey;
			stage_imgs[5].ImageData = bmKey;
			stage_imgs[4].ImageData = bmKey;
			stage_imgs[3].ImageData = bmKey;
			stage_imgs[2].ImageData = bmKey;
			stage_imgs[1].ImageData = bmBell;
			stage_imgs[0].ImageData = bmBell;
			break;
		case 17:
			stage_imgs[6].ImageData = bmKey;
			stage_imgs[5].ImageData = bmKey;
			stage_imgs[4].ImageData = bmKey;
			stage_imgs[3].ImageData = bmKey;
			stage_imgs[2].ImageData = bmKey;
			stage_imgs[1].ImageData = bmKey;
			stage_imgs[0].ImageData = bmBell;
			break;
		default:
			stage_imgs[6].ImageData = bmKey;
			stage_imgs[5].ImageData = bmKey;
			stage_imgs[4].ImageData = bmKey;
			stage_imgs[3].ImageData = bmKey;
			stage_imgs[2].ImageData = bmKey;
			stage_imgs[1].ImageData = bmKey;
			stage_imgs[0].ImageData = bmKey;
	}

	/* And draw the stage images all at once. */
	/* DrawImage(wPacMan->RPort,&stage_imgs[0],0,0); */
}

void stageTask()
{
	struct MsgPort *taskPort = NULL;
	struct StageMessage *msg = NULL;

	stageTask_setup_imgs();
	
	Forbid();

	taskPort = CreatePort("stage.port", 0);

	if (!taskPort)
	{
		Permit();
		return;
	}

	Permit();

	DisplayBeep(NULL);

	FOREVER
	{
		msg = (struct StageMessage *)WaitPort(taskPort);

		while (msg = (struct StageMessage *)GetMsg(taskPort))
		{
			switch(msg->cmd)
			{
				case STAGE_CMD_SET:
					stageTask_Set(msg);
					break;
				case STAGE_CMD_STOP:
					goto stagetask_stop;
			}

			ReplyMsg(msg);
		}
	}

stagetask_stop:

	ReplyMsg(msg);

	while ((struct StageMessage *)GetMsg(taskPort));

	DeletePort(taskPort);

	DeleteTask(0);
}

/* The Test Harness ******************************************************/

main()
{
	struct MsgPort *replyPort = NULL;
	struct MsgPort *stagePort = NULL;

	int i=0;

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

	replyPort = CreatePort(0,0);
	if (!replyPort)
		goto bye;

	task = CreateTask("stage.task",0,stageTask,1000L);
	if (!task)
		goto bye;

	Wait(0);

	while (!stagePort)
		stagePort = FindPort("stage.port");

	DrawBorder(wPacMan->RPort,&boMaze,0,7);

	for (i=0;i<24;i++)
	{
		struct StageMessage msg;
		struct StageMessage *reply;

		msg.msg.mn_Node.ln_Type = NT_MESSAGE;
		msg.msg.mn_ReplyPort = replyPort;
		msg.msg.mn_Length = sizeof(struct StageMessage);
		msg.playerNo=1;
		msg.stageNo=i;
		msg.cmd=STAGE_CMD_SET;
		PutMsg(&msg);
		reply = (struct StageMessage *)WaitPort(replyPort);

		Delay(100);
	}

	Delay(600);
	
bye:
	if (task)
	{
		struct StageMessage msg;
		struct StageMessage *reply = NULL;

		msg.msg.mn_Node.ln_Type=NT_MESSAGE;
		msg.msg.mn_Length = sizeof(struct StageMessage);
		msg.msg.mn_ReplyPort = replyPort;
		msg.playerNo=0;
		msg.stageNo=0;
		msg.cmd = STAGE_CMD_STOP;
		PutMsg(&msg);
		reply = (struct StageMessage *)WaitPort(replyPort);
	}
	
	if (replyPort)
		DeletePort(replyPort);

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
