/**
 * @brief   GEL BOB Experiment #1
 * @verbose Move Blinky BOB across screen as simply as possible.
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
#include <graphics/gels.h>
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

struct Bob pacBob;
struct VSprite pacVSprite;

USHORT bmBlinky[] = 
{
	/* BITPLANE 0 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0618, /* 0000011000011000 */
	0x0F3C, /* 0000111100111100 */
	0x0C30, /* 0000110000110000 */
	0x0C30, /* 0000110000110000 */
	0x0618, /* 0000011000011000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	/* BITPLANE 1 */
	0x0000, /* 0000000000000000 */
	0x03C0, /* 0000001111000000 */
	0x0FF0, /* 0000111111110000 */
	0x1FF8, /* 0001111111111000 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3CF0, /* 0011110011110000 */
	0x7CF2, /* 0111110011110010 */
	0x7FFE, /* 0111111111111110 */
	0x7FFE, /* 0111111111111110 */
	0x7FFE, /* 0111111111111110 */
	0x7FFE, /* 0111111111111110 */
	0x7FFE, /* 0111111111111110 */
	0x6E76, /* 0110111001110110 */
	0x4662, /* 0100011001100010 */
	0x0000, /* 0000000000000000 */
	/* BITPLANE 2 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x030C, /* 0000001100001100 */
	0x030C, /* 0000001100001100 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
};

USHORT smBlinky[] = /* Shadow mask. */
{
	0x0000, /* 0000000000000000 */
	0x03C0, /* 0000001111000000 */
	0x0FF0, /* 0000111111110000 */
	0x1FF8, /* 0001111111111000 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x7FFE, /* 0111111111111110 */
	0x7FFE, /* 0111111111111110 */
	0x7FFE, /* 0111111111111110 */
	0x7FFE, /* 0111111111111110 */
	0x7FFE, /* 0111111111111110 */
	0x7FFE, /* 0111111111111110 */
	0x6E76, /* 0110111001110110 */
	0x4662, /* 0100011001100010 */
	0x0000, /* 0000000000000000 */
};

struct GelsInfo gelsInfo;
struct VSprite dummySpriteA, dummySpriteB;

WORD pacSaveBuffer[512];

GELBOBTask()
{
	int i=0;

	pacBob.BobVSprite = &pacVSprite;
	pacVSprite.VSBob = &pacBob;

	pacVSprite.Height = 16;      /* 16 lines          */
	pacVSprite.Width = 1;        /* 1 word, 16 pixels */
	pacVSprite.Depth = 3;        /* 8 colors          */
	pacVSprite.PlanePick = 0x07; /* 3 bitplanes       */
	pacVSprite.ImageData = bmBlinky;
	pacBob.ImageShadow = smBlinky;
	pacVSprite.X = 0;
	pacVSprite.Y = 100;
	pacBob.SaveBuffer = &pacSaveBuffer;
	pacBob.Flags = SAVEBACK | OVERLAY;
	pacVSprite.Flags = SAVEBACK | OVERLAY;

	InitGels(&dummySpriteA, &dummySpriteB, &gelsInfo);

	wPacMan->RPort->GelsInfo = &gelsInfo;

	AddBob(&pacBob, wPacMan->RPort);

	/* Optimize by sorting only once here */
	SortGList(wPacMan->RPort);

	for (i=0;i<240;i++)
	{
		pacVSprite.X++;
		DrawGList(wPacMan->RPort,&sPacMan->ViewPort);
		WaitTOF();
	}

	Wait(0); /* for godot. */
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

	task = CreateTask("gelbob.task",127,&GELBOBTask,1000);
	
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
