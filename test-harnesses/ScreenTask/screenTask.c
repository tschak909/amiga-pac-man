/**
 * @brief   the Screen Task
 * @verbose opens or closes the main screen based on message
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see LICENSE for details.
 */

#include <exec/types.h>
#include <exec/memory.h>
#include <exec/exec.h>
#include <graphics/gfx.h>
#include <graphics/gfxbase.h>
#include <intuition/intuition.h>

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

/** The Screen Task *************************************************/

#define PRIORITY 1
#define STACK_SIZE 4000

#define PORT_NAME "PMScreenTaskPort"
#define SCMD_OPEN 0
#define SCMD_CLOSE 1
#define SCMD_STOP 2
#define TASK_NAME "PMScreenTask"

struct Task *task_screenTask;
struct MsgPort *port_screenTask;

struct Screen *OpenScreen();

struct ScMessage
{
	struct Message msg;
	long command;
};

struct Screen *sPacMan;
struct NewScreen nsPacMan = 
{
	0, 0,
	320, 200, 4,	/* 320x200 16 colors */
	0, 1,
	NULL,
	CUSTOMSCREEN,
	NULL,	/* Change this later for font! */
	"PAC-MAN (tm)",
	NULL
};

/* Color Palette for nsPacMan */
UBYTE colorTable[16] = 
{
	0x000,
	0xFF0,
	0xF00,
	0xFFF,
	0x00F,
	0xF0F,
	0x0FF,
	0x770,
	0x0F0,
	0xFA0,
	0xFEF,
	0x0F0,
	0x0FF,
	0xF00,
	0xF0F,
	0xFFF
};

screenTask_OPEN()
{
	sPacMan = OpenScreen(&nsPacMan);
	if (!sPacMan)
		return 0;

	LoadRGB4(&sPacMan->ViewPort,colorTable,sizeof(colorTable));

	return 0;
}

screenTask_CLOSE()
{
	if (sPacMan)
		CloseScreen(sPacMan);
	
	return 0;
}

screenTask()
{
	struct ScMessage *smsg;

	UBYTE st_running = TRUE;
	port_screenTask = (struct MsgPort *)
		CreatePort(PORT_NAME,0L);

	if (!port_screenTask)
		goto godot;

	while (st_running)
	{
		WaitPort(port_screenTask);
		while(smsg = (struct ScreenMessage *)GetMsg(port_screenTask))
		{

			switch(smsg->command)
			{
				case SCMD_OPEN:
					screenTask_OPEN();
					break;
				case SCMD_CLOSE:
					screenTask_CLOSE();
					break;
				case SCMD_STOP:
					st_running=FALSE;
					break;
			}

			ReplyMsg((struct Message *)smsg);
		}
	};

/* We come down here when CMD_STOP */
godot:
	if (port_screenTask)
		DeletePort(port_screenTask);

	Wait(0L); /* Sit and spin forever until deleted. */
}

/** The Test Harness ************************************************/

struct MsgPort *FindPort();

test()
{
	struct MsgPort *port;
	struct MsgPort *replyPort;
	struct ScMessage *msg;

	task_screenTask = 
		(struct Task *)CreateTask(TASK_NAME,
						PRIORITY,
						screenTask,
						STACK_SIZE);

	if (!task_screenTask)
	{
		return FALSE;		
	}

	port = FindPort(PORT_NAME);
	if (!port)
	{
		return FALSE;
	}

	replyPort = (struct MsgPort *)CreatePort(0,0);

	msg = (struct ScMessage *)AllocMem(sizeof(struct ScMessage),
						MEMF_PUBLIC|MEMF_CLEAR);

	msg->msg.mn_Node.ln_Type = NT_MESSAGE;
	msg->msg.mn_Length = sizeof(struct ScMessage);
	msg->msg.mn_ReplyPort = replyPort;
	msg->command = SCMD_OPEN;

	PutMsg(port, msg);
	msg = (struct ScMessage *)GetMsg(replyPort);

	DisplayBeep(NULL);

	Delay(600);

	while(1);

	return TRUE;
}

done()
{
	if (IntuitionBase)
		CloseLibrary(IntuitionBase);

	if (GfxBase)
		CloseLibrary(GfxBase);

	return 0;
}

init()
{
	GfxBase = (struct GfxBase *)
		OpenLibrary("graphics.library",0);
	if (!GfxBase)
	{
		return FALSE;
	}

	IntuitionBase = (struct IntuitionBase *)
		OpenLibrary("intuition.library",0);
	if (!IntuitionBase)
	{
		return FALSE;
	}
	
	return TRUE;
}

main()
{
	if (!init())
	{
		done();
		return 1;
	}

	test();
	
	done();
}
