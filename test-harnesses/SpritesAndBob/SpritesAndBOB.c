/**
 * @brief   Sprites and BOB
 * @verbose Animate PAC-MAN and Ghosts on screen with maze
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
#include <graphics/sprite.h>
#include <intuition/intuition.h>

#include "font.h"
#include "MazeBorders.h"
#include "sprites.h"
#include "bobs.h"

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

extern struct MsgPort *CreatePort();
extern struct IORequest *CreateExtIO();
extern struct Task *CreateTask();

/** The Test Harness *******************************************************/

struct Screen *OpenScreen();
struct Window *OpenWindow();

struct Task *clydeTask, *blinkyTask, *pinkyTask, *inkyTask, *paccyTask;

struct Screen *sPacMan;
struct Window *wPacMan;

struct NewScreen nsPacMan = 
{
	0, 0,
	320, 200, 4,
	3, 0, /* 0, 1 */
	SPRITES,
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
	0xFA0,		/* 7: Dark Yellow (pale orange?) */
	0x00F,		/* 8: Light Green */
	0xFA0,		/* 9: Light Orange */
	0xFEF,		/* A: Pinky white */
	0xFCB,		/* B: Power Pellet */
	0x0FF,		/* C: Light Cyan */
	0xF00,		/* D: Light Red */
	0xF0F,		/* E: Light Magenta */
	0xFFF,		/* F: White */
};

struct SimpleSprite blinkySprite, pinkySprite, inkySprite, paccySprite;

struct Bob clydeBob;
struct VSprite clydeVSprite;

struct GelsInfo gelsInfo;
struct VSprite dummySpriteA, dummySpriteB;

WORD clydeSaveBuf[512];

int globalX=0;

PaccyTask()
{
	SHORT paccy_spr;

	int k, bx=0, by=84, i=0, frame=0;

	paccySprite.posctldata = paccy_right_0;
	paccySprite.height = 16;
	paccySprite.x = bx;
	paccySprite.y = by;

	paccy_spr = GetSprite(&paccySprite, 1);

	k = ((paccy_spr & 0x06) * 2) + 16;
	
	SetRGB4(&sPacMan->ViewPort, k+1, 0x0F, 0x0F, 0x00);
	SetRGB4(&sPacMan->ViewPort, k+2, 0x0F, 0x0F, 0x00);
	SetRGB4(&sPacMan->ViewPort, k+3, 0x0F, 0x0F, 0x00);

	for (i=0;i<240;i++)
	{
		UWORD *p;

		if (frame>2)
			frame=0;

		if (frame==0)
			p = paccy_right_0;
		else if (frame==1)
			p = paccy_right_1;
		else if (frame==2)
			p = paccy_right_2;

		ChangeSprite(&sPacMan->ViewPort,
				&paccySprite,
				p);

		MoveSprite(&sPacMan->ViewPort,
				&paccySprite,
				globalX,
				by);

		frame++;

		WaitTOF();
	}

	FreeSprite(paccy_spr);

	Wait(0);
}

BlinkyTask()
{
	SHORT blinky_spr;

	int k, bx=0, by=20, bi=0, frame=0;

	blinkySprite.posctldata = blinky_right_0;
	blinkySprite.height = 16;
	blinkySprite.x = bx;
	blinkySprite.y = by;

	blinky_spr = GetSprite(&blinkySprite, 2);

	k = ((blinky_spr & 0x06) * 2) + 16;

	SetRGB4(&sPacMan->ViewPort, k+1, 0x0F, 0x00, 0x00);
	SetRGB4(&sPacMan->ViewPort, k+2, 0x0F, 0x0F, 0x0F);
	SetRGB4(&sPacMan->ViewPort, k+3, 0x00, 0x00, 0x0F);

	for (bi=0;bi<240;bi++)
	{
		if (!(bi&3))
			frame = !frame;

		ChangeSprite(&sPacMan->ViewPort, 
				&blinkySprite, 
				frame ? &blinky_right_0 : &blinky_right_1);
		MoveSprite(&sPacMan->ViewPort, &blinkySprite, globalX++, by);
		WaitTOF();
	}

	FreeSprite(blinky_spr);

	Wait(0); /* ...for Godot. */
}

PinkyTask()
{
	SHORT pinky_spr;

	int k, bx=0, by=36, bi=0, frame=0;

	pinkySprite.posctldata = pinky_right_0;
	pinkySprite.height = 16;
	pinkySprite.x = bx;
	pinkySprite.y = by;

	pinky_spr = GetSprite(&pinkySprite, 4);

	k = ((pinky_spr & 0x06) * 2) + 16;

	SetRGB4(&sPacMan->ViewPort, k+1, 0x0F, 0x0B, 0x0F);
	SetRGB4(&sPacMan->ViewPort, k+2, 0x0F, 0x0F, 0x0F);
	SetRGB4(&sPacMan->ViewPort, k+3, 0x00, 0x00, 0x0F);

	for (bi=0;bi<240;bi++)
	{
		if (!(bi&3))
			frame = !frame;

		ChangeSprite(&sPacMan->ViewPort, 
				&pinkySprite, 
				frame ? &pinky_right_0 : &pinky_right_1);
		MoveSprite(&sPacMan->ViewPort, &pinkySprite, globalX, by);
		WaitTOF();
	}

	FreeSprite(pinky_spr);

	Wait(0); /* ...for Godot. */
}

InkyTask()
{
	SHORT inky_spr;

	int k, bx=0, by=52, bi=0, frame=0;

	inkySprite.posctldata = inky_right_0;
	inkySprite.height = 16;
	inkySprite.x = bx;
	inkySprite.y = by;

	inky_spr = GetSprite(&inkySprite, 6);

	k = ((inky_spr & 0x06) * 2) + 16;

	SetRGB4(&sPacMan->ViewPort, k+1, 0x00, 0x0F, 0x0F);
	SetRGB4(&sPacMan->ViewPort, k+2, 0x0F, 0x0F, 0x0F);
	SetRGB4(&sPacMan->ViewPort, k+3, 0x00, 0x00, 0x0F);

	for (bi=0;bi<240;bi++)
	{
		if (!(bi&3))
			frame = !frame;

		ChangeSprite(&sPacMan->ViewPort, 
				&inkySprite, 
				frame ? &inky_right_0 : &inky_right_1);
		MoveSprite(&sPacMan->ViewPort, &inkySprite, globalX, by);
		WaitTOF();
	}

	FreeSprite(inky_spr);

	Wait(0); /* ...for Godot. */
}

ClydeTask()
{
	int i=0;
	int frame=0;

	clydeBob.BobVSprite = &clydeVSprite;
	clydeVSprite.VSBob = &clydeBob;

	clydeVSprite.Height = 16;      /* 16 lines          */
	clydeVSprite.Width = 1;        /* 1 word, 16 pixels */
	clydeVSprite.Depth = 4;        /* 8 colors          */
	clydeVSprite.PlanePick = 0x0F; /* 3 bitplanes       */
	clydeVSprite.ImageData = bmClyde_r00;
	clydeBob.ImageShadow = smClyde_r00;
	clydeVSprite.X = 0;
	clydeVSprite.Y = 68;
	clydeBob.SaveBuffer = clydeSaveBuf;
	clydeBob.Flags = SAVEBACK | OVERLAY;
	clydeVSprite.Flags = SAVEBACK | OVERLAY;

	InitGels(&dummySpriteA, &dummySpriteB, &gelsInfo);

	wPacMan->RPort->GelsInfo = &gelsInfo;

	AddBob(&clydeBob, wPacMan->RPort);

	/* Optimize by sorting only once here */
	SortGList(wPacMan->RPort);

	for (i=0;i<240;i++)
	{
		if (!(i&3))
			frame = !frame;
	
		clydeVSprite.ImageData = frame ? bmClyde_r00 : bmClyde_r01;
		clydeBob.ImageShadow = frame ? smClyde_r00 : smClyde_r01;

		clydeVSprite.X = globalX;
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

	paccyTask  = CreateTask("paccy.task", 0,&PaccyTask, 1000);
	blinkyTask = CreateTask("blinky.task",0,&BlinkyTask,1000);
	pinkyTask  = CreateTask("pinky.task" ,0,&PinkyTask ,1000);
	inkyTask   = CreateTask("inky.task"  ,0,&InkyTask  ,1000);
	clydeTask  = CreateTask("clyde.task" ,0,&ClydeTask ,1000);
	
	Delay(600);
	
bye:
	if (paccyTask)
		DeleteTask(paccyTask);

	if (inkyTask)
		DeleteTask(inkyTask);

	if (pinkyTask)
		DeleteTask(pinkyTask);

	if (blinkyTask)
		DeleteTask(blinkyTask);

	if (clydeTask)
		DeleteTask(clydeTask);

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
