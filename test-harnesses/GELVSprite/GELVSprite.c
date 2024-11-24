/**
 * @brief   PAC-MAN as VSprite
 * @verbose Work out using VSprite GELs.
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see LICENSE for details.
 */

#include <exec/types.h>
#include <exec/memory.h>
#include <exec/exec.h>
#include <graphics/gfx.h>
#include <graphics/gfxbase.h>
#include <graphics/sprite.h>
#include <graphics/gels.h>
#include <intuition/intuition.h>
#include <hardware/custom.h>
#include <hardware/dmabits.h>

#include "MazeBorders.h"
#include "Sprites.h"
#include "font.h"

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

extern struct Task *CreateTask();

/** The Test Harness *******************************************************/

struct Screen *OpenScreen();
struct Window *OpenWindow();

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
	ACTIVATE|BORDERLESS|BACKDROP,
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
	0x0F0,		/* B: Light Green */
	0x0FF,		/* C: Light Cyan */
	0xF00,		/* D: Light Red */
	0xF0F,		/* E: Light Magenta */
	0xFFF,		/* F: White */
};

struct VSprite paccyVSprite, blinkyVSprite, pinkyVSprite, inkyVSprite;
struct VSprite clydeVSprite;

struct GelsInfo gelsInfo;
struct VSprite dummySpriteA, dummySpriteB;

void PaccyAdd()
{
	paccyVSprite.Height = 16;
	paccyVSprite.SprColors = paccyColors;
	paccyVSprite.ImageData = paccy_right_0;
	paccyVSprite.Flags = VSPRITE;
	paccyVSprite.Depth = 2;
	paccyVSprite.Width = 1;
	paccyVSprite.PlanePick = 0x0F;

	paccyVSprite.X = 64;
	paccyVSprite.Y = 64;

	AddVSprite(&paccyVSprite, wPacMan->RPort);
}
void BlinkyAdd()
{
	blinkyVSprite.Height = 16;
	blinkyVSprite.SprColors = blinkyColors;
	blinkyVSprite.ImageData = blinky_right_0;
	blinkyVSprite.Flags = VSPRITE;
	blinkyVSprite.Depth = 2;
	blinkyVSprite.Width = 1;
	blinkyVSprite.PlanePick = 0x0F;

	blinkyVSprite.X = 80;
	blinkyVSprite.Y = 64;

	AddVSprite(&blinkyVSprite, wPacMan->RPort);
}

void PinkyAdd()
{
	pinkyVSprite.Height = 16;
	pinkyVSprite.SprColors = pinkyColors;
	pinkyVSprite.ImageData = pinky_right_0;
	pinkyVSprite.Flags = VSPRITE;
	pinkyVSprite.Depth = 2;
	pinkyVSprite.Width = 1;
	pinkyVSprite.PlanePick = 0x0F;

	pinkyVSprite.X = 96;
	pinkyVSprite.Y = 64;

	AddVSprite(&pinkyVSprite, wPacMan->RPort);
}

void InkyAdd()
{
	inkyVSprite.Height = 16;
	inkyVSprite.SprColors = inkyColors;
	inkyVSprite.ImageData = inky_right_0;
	inkyVSprite.Flags = VSPRITE;
	inkyVSprite.Depth = 2;
	inkyVSprite.Width = 1;
	inkyVSprite.PlanePick = 0x0F;

	inkyVSprite.X = 112;
	inkyVSprite.Y = 64;

	AddVSprite(&inkyVSprite, wPacMan->RPort);
}

void ClydeAdd()
{
	clydeVSprite.Height = 16;
	clydeVSprite.SprColors = clydeColors;
	clydeVSprite.ImageData = clyde_right_0;
	clydeVSprite.Flags = VSPRITE;
	clydeVSprite.Depth = 2;
	clydeVSprite.Width = 1;
	clydeVSprite.PlanePick = 0x0F;

	clydeVSprite.X = 128;
	clydeVSprite.Y = 128;

	AddVSprite(&clydeVSprite, wPacMan->RPort);
}

main()
{
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

	nwPacMan.Screen = sPacMan;

	wPacMan = OpenWindow(&nwPacMan);
	if (!wPacMan)
		goto bye;

	LoadRGB4(&sPacMan->ViewPort, colorTable, 16);

	InitGels(&dummySpriteA, &dummySpriteB, &gelsInfo);
	wPacMan->RPort->GelsInfo = &gelsInfo;

	/* draw maze */
	DrawBorder(wPacMan->RPort,&boMaze,0,7);
	
	PaccyAdd();
        BlinkyAdd();
	PinkyAdd();
	InkyAdd();
	ClydeAdd();

	for (i=0;i<256;i++)
	{
		paccyVSprite.X++;
		blinkyVSprite.X++;
		pinkyVSprite.X++;
		inkyVSprite.X++;
		clydeVSprite.X++;
		DrawGList(wPacMan->RPort,ViewPortAddress(wPacMan));
		RethinkDisplay();
		WaitTOF();
	}
	Delay(600);

bye:
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
