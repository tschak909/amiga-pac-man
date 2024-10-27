/**
 * @brief   Power Pellet Task
 * @verbose Blink the power pellet register using the timer device.
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

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

extern struct MsgPort *CreatePort();
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

SHORT bmPellet[] = 
{
	/* BITPLANE 0 */
	0x7800, /* 0111100000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0x7800, /* 0111100000000000 */
 
	/* BITPLANE 1 */
	0x7800, /* 0111100000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0x7800, /* 0111100000000000 */

	/* BITPLANE 3 */
	0x7800, /* 0111100000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0xFC00, /* 1111110000000000 */
	0x7800, /* 0111100000000000 */
};

struct Image iPellet = 
{
	0, 0,
	6, 6, 4,
	bmPellet,
	0x0B, 0x00
};

BlinkPelletWait()
{
	struct MsgPort *timerPort;
	struct timerequest *timerMsg;
	struct timeval tv;
	int error;

	/* Create the timer ************************************************/

	timerPort = CreatePort(0,0); /* Private port */

	if (!timerPort)
		return -1;

	timerMsg = (struct timerequest *)
		CreateExtIO(timerPort, sizeof(struct timerequest));

	if (!timerMsg)
	{
		DeletePort(timerPort);
		return FALSE;
	}

	error = OpenDevice(TIMERNAME, UNIT_VBLANK, timerMsg, 0);

	if (error)
	{
		if (timerMsg->tr_node.io_Message.mn_ReplyPort)
			DeletePort(timerMsg->tr_node.io_Message.mn_ReplyPort);
		CloseDevice(timerMsg);
		DeleteExtIO(timerMsg, sizeof(struct timerequest));
		return FALSE;
	}

	/* Set the timer to fire every BLINK microseconds *******************/

	tv.tv_secs = 0;
	tv.tv_micro = 100000;

	timerMsg->tr_node.io_Command = TR_ADDREQUEST;
	timerMsg->tr_time = &tv;
	
 	/* Do it. */
	DoIO(timerMsg);

	/* Tear down and close timer ****************************************/

	if (timerMsg->tr_node.io_Message.mn_ReplyPort)
		DeletePort(timerMsg->tr_node.io_Message.mn_ReplyPort);

	CloseDevice(timerMsg);

	/* DeleteExtIO will close the timerPort */
	DeleteExtIO(timerMsg, sizeof(struct timerequest));

	return TRUE;
}

/* The blink-on color, as blink-off is all zeroes. */

#define BLINK_R 0xF
#define BLINK_G 0xC
#define BLINK_B 0xB
#define BLINK_COLOR 0x0B

PowerPelletTask()
{
	BYTE bOnOff;

	bOnOff = 0;

	FOREVER /* RJ Mical'ism */
	{
		/* we only start task after screen is ready, so... */

		SetRGB4(&sPacMan->ViewPort,
			BLINK_COLOR,
			bOnOff ? BLINK_R : 0x00, 
			bOnOff ? BLINK_G : 0x00, 
			bOnOff ? BLINK_B : 0x00);
		
		bOnOff = !bOnOff;

		/* The DoIO will cause a Wait(), so no needless spinning */
		BlinkPelletWait();
	}
}

/* The Test Harness ******************************************************/

main()
{
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

	DrawImage(wPacMan->RPort,&iPellet,19,29);
	DrawImage(wPacMan->RPort,&iPellet,169,29);
	DrawImage(wPacMan->RPort,&iPellet,19,149);
	DrawImage(wPacMan->RPort,&iPellet,169,149);

	task = CreateTask("powerpellet.task",127,&PowerPelletTask,1000);
	
	Delay(600);
	
bye:
	if (task)
		DeleteTask(task);

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
