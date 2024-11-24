/**
 * @brief   Bitplane the ghosts
 * @verbose Demonstrate how bitplanes work pt 2
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see LICENSE for details.
 */

#include <exec/types.h>
#include <exec/memory.h>
#include <exec/exec.h>
#include <graphics/gfx.h>
#include <graphics/gfxbase.h>
#include <graphics/gfxmacros.h>
#include <intuition/intuition.h>

#include "font.h"
#include "Bobs.h"

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
	NULL,
	CUSTOMSCREEN,
	NULL,
	"ANATOMY OF A GHOST (BITPLANES)",
	NULL
};

struct NewWindow nwPacMan = 
{
	0, 12,
	320, 188,
	0, 1,
	CLOSEWINDOW,
	ACTIVATE|WINDOWCLOSE,
	NULL,
	NULL,
	"PRESS TO CLOSE",
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
	0xF80,		/* 7: Dark Yellow (pale orange?) */
	0x00F,		/* 8: Light Green */
	0xFA0,		/* 9: Light Orange */
	0x777,		/* A: Pinky white */
	0x00F,		/* B: Light Green */
	0x0FF,		/* C: Light Cyan */
	0xF00,		/* D: Light Red */
	0xF0F,		/* E: Light Magenta */
	0xFFF,		/* F: White */
};

struct Image iClyde = 
{
	0, 0,
	16, 16, 4,
	bmClyde_r00,
	0x0F, 0x00,
	NULL
};

struct Image iClyde2 = 
{
	0, 0,
	16, 16, 4,
	bmClyde_r01,
	0x0F, 0x00,
	NULL
};

drawPlanes(img,y)
struct Image *img;
SHORT y;
{
	SHORT oldDepth, oldPlanePick;
	UWORD *oldImageData;

	oldDepth = img->Depth;
	oldPlanePick = img->PlanePick;
	oldImageData = img->ImageData;

	if (oldPlanePick & 0x01)
	{
		img->Depth = 1;
		img->PlanePick = 0x1;
		DrawImage(wPacMan->RPort,img,32,y);
		img->ImageData += 16;
	}

	if (oldPlanePick & 0x02)
	{
		img->PlanePick = 0x02;
		DrawImage(wPacMan->RPort,img,64,y);
		img->ImageData += 16;
	}

	if (oldPlanePick & 0x04)
	{
		img->PlanePick = 0x04;
		DrawImage(wPacMan->RPort,img,96,y);
		img->ImageData += 16;
	}

	if (oldPlanePick & 0x08)
	{
		img->PlanePick = 0x08;
		DrawImage(wPacMan->RPort,img,128,y);
		img->ImageData += 16;
	}

	img->Depth = oldDepth;
	img->PlanePick = oldPlanePick;
	img->ImageData = oldImageData;
	DrawImage(wPacMan->RPort,img,160,y);
}

char *colorLegend="0123456789ABCDEF";

drawColors()
{
	int i;

	SetOPen(wPacMan->RPort, 0); /* Black border around color chips */

	for (i=0;i<16;i++)
	{
		SetAPen(wPacMan->RPort,i);
		RectFill(wPacMan->RPort,312-16,(i<<3)+12,320-16,((i<<3)+8)+12);
		Move(wPacMan->RPort,300-16,(i<<3)+12+7);
		Text(wPacMan->RPort,colorLegend++,1);
	}

}

#define LEGEND_Y 160

drawLegends()
{
	SetAPen(wPacMan->RPort,0x0F);

	Move(wPacMan->RPort,32,LEGEND_Y);
	Text(wPacMan->RPort,"0",1);
	Move(wPacMan->RPort,64,LEGEND_Y);
	Text(wPacMan->RPort,"1",1);
	Move(wPacMan->RPort,96,LEGEND_Y);
	Text(wPacMan->RPort,"2",1);
	Move(wPacMan->RPort,128,LEGEND_Y);
	Text(wPacMan->RPort,"3",1);
	Move(wPacMan->RPort,160,LEGEND_Y);
	Text(wPacMan->RPort,"ALL",3);

	Move(wPacMan->RPort,32,LEGEND_Y+8);
	Text(wPacMan->RPort,"1",1);
	Move(wPacMan->RPort,64,LEGEND_Y+8);
	Text(wPacMan->RPort,"2",1);
	Move(wPacMan->RPort,96,LEGEND_Y+8);
	Text(wPacMan->RPort,"4",1);
	Move(wPacMan->RPort,128,LEGEND_Y+8);
	Text(wPacMan->RPort,"8",1);
}

/**
 * The test harness.
 */
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

	/* Load playfield color palette */
	LoadRGB4(&sPacMan->ViewPort, colorTable, 16);

	/* Set our mouse (sprite 0 colors) */
	SetRGB4(&sPacMan->ViewPort,0x11,0x07,0x07,0x00);
	SetRGB4(&sPacMan->ViewPort,0x13,0x0F,0x0F,0x00);

	nwPacMan.Screen = sPacMan;
	wPacMan = OpenWindow(&nwPacMan);
	if (!wPacMan)
		goto bye;

	drawColors();
	drawLegends();

/*	drawPlanes(&iBlinky,32);
	drawPlanes(&iPinky,48);
	drawPlanes(&iInky,64); */
	drawPlanes(&iClyde2,64);
	drawPlanes(&iClyde,80);

	Wait(1<<wPacMan->UserPort->mp_SigBit);

bye:
	RemFont(&Arcade8Font);

	/* Intuition will drain the message port for us. */
	if (wPacMan)
		CloseWindow(wPacMan);

	if (sPacMan)
		CloseScreen(sPacMan);

	if (IntuitionBase)
		CloseLibrary(IntuitionBase);

	if (GfxBase)
		CloseLibrary(GfxBase);
}
