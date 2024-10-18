/**
 * @brief   Animate PAC-MAN sprite
 * @verbose Using the GELs system
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
#include <intuition/intuition.h>

#include "font.h"

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

/** The Test Harness *******************************************************/

struct Screen *OpenScreen();
struct Window *OpenWindow();

struct Screen *sPacMan;
struct Window *wPacMan;

struct NewScreen nsPacMan = 
{
	0, 0,
	320, 200, 4,
	0, 1,
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

USHORT colorTable[] = 
{
	0x000,		/* 0: Black */
	0xFF0,		/* 1: Yellow */
	0xF00,		/* 2: Light Red */
	0xFFF,		/* 3: White */
	0x00F,		/* 4: Light Blue */
	0xF0F,		/* 5: Light Magenta */
	0x0FF,		/* 6: Light Cyan */
	0xF80,		/* 7: Dark Yellow (pale orange?) */
	0x0F0,		/* 8: Light Green */
	0xFA0,		/* 9: Light Orange */
	0xFEF,		/* A: Pinky white */
	0x0F0,		/* B: Light Green */
	0x0FF,		/* C: Light Cyan */
	0xF00,		/* D: Light Red */
	0xF0F,		/* E: Light Magenta */
	0xFFF,		/* F: White */
};

/** 
 * Sprite bitmaps
 */
UWORD pacman_right_0[] = 
{
	0, 0,
	0x0000, 0x0000, /* 0000000000000000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x1FC0, 0x0000, /* 0001111111000000 */
	0x3F80, 0x0000, /* 0011111110000000 */
	0x3F00, 0x0000, /* 0011111100000000 */
	0x7E00, 0x0000, /* 0111111000000000 */
	0x7C00, 0x0000, /* 0111110000000000 */
	0x7800, 0x0000, /* 0111100000000000 */
	0x7C00, 0x0000, /* 0111110000000000 */
	0x7E00, 0x0000, /* 0111111000000000 */
	0x3F00, 0x0000, /* 0011111100000000 */
	0x3F80, 0x0000, /* 0011111110000000 */
	0x1FC0, 0x0000, /* 0001111111000000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0, 0
};

UWORD pacman_right_1[] = 
{
	0, 0,
	0x0000, 0x0000, /* 0000000000000000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x1FF0, 0x0000, /* 0001111111110000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x7FE0, 0x0000, /* 0111111111100000 */
	0x7F00, 0x0000, /* 0111111100000000 */
	0x7800, 0x0000, /* 0111100000000000 */
	0x7F00, 0x0000, /* 0111111100000000 */
	0x7FE0, 0x0000, /* 0111111111100000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x1FF0, 0x0000, /* 0001111111110000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0, 0
};

UWORD pacman_right_2[]=
{
	0, 0,
	0x0000, 0x0000, /* 0000000000000000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x1FF0, 0x0000, /* 0001111111110000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x7FFC, 0x0000, /* 0111111111111100 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x3FF8, 0x0000, /* 0011111111111000 */
	0x1FF0, 0x0000, /* 0001111111110000 */
	0x07C0, 0x0000, /* 0000011111000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0x0000, 0x0000, /* 0000000000000000 */
	0, 0,
};
struct SimpleSprite pacSprite =
{
	pacman_right_0,
	16,
	64,64,
	1
};

/**
 * The test harness, display PAC-MAN chomping his mouth, facing right.
 */
main()
{
	SHORT spr, k, i, x;

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

	spr = GetSprite(&pacSprite, -1);
	k = ((spr & 0x06)*2)+16;

	SetRGB4(&sPacMan->ViewPort,k+1,0x0F,0x0F,0x00);
	SetRGB4(&sPacMan->ViewPort,k+2,0x0F,0x0F,0x00);
	SetRGB4(&sPacMan->ViewPort,k+3,0x0F,0x0F,0x00);
	SetRGB4(&sPacMan->ViewPort,k+4,0x0F,0x0F,0x00);

	/* Set initial X position */
	x=0;

	for (i=0;i<128;i++)
	{
		ChangeSprite(&sPacMan->ViewPort,&pacSprite,&pacman_right_0);
		MoveSprite(&sPacMan->ViewPort,&pacSprite,x++,100);
		WaitTOF();
		ChangeSprite(&sPacMan->ViewPort,&pacSprite,&pacman_right_1);
		MoveSprite(&sPacMan->ViewPort,&pacSprite,x++,100);
		WaitTOF();
		ChangeSprite(&sPacMan->ViewPort,&pacSprite,&pacman_right_2);
		MoveSprite(&sPacMan->ViewPort,&pacSprite,x++,100);
		WaitTOF();
	}
	
	MoveSprite(&sPacMan->ViewPort,&pacSprite,64,100);

	Delay(600); 

bye:
	if (spr>0)
		FreeSprite(spr);

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
