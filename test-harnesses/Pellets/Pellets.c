/**
 * @brief   Draw Pellets
 * @verbose Draw Pellets for the board
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
#include "Dots.h"

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

struct Image dots[256];

dots_setup()
{
	int i=0, d=0;

	for (i=0;i<sizeof(dotmap);i++)
	{
		if (dotmap[i]>0x02)
			continue;

		dots[d].LeftEdge = dot_x[i&0x1F];
		dots[d].TopEdge = dot_y[i>>5];
		dots[d].Width = dots[d].Height = 6;
		dots[d].Depth = 1;
	
		if (dotmap[i]==0x01)
		{
			dots[d].ImageData = &bmPellet[0];
		}
		else if (dotmap[i]==0x02)
		{
			dots[d].ImageData = &bmEnergizer[0];
		}

		dots[d].PlanePick = dots[d].PlaneOnOff = 0x0B;
		dots[d].NextImage = &dots[d+1];
		d++;
	}

	dots[d-1].NextImage = NULL;
}

dot_plot(d)
int d;
{
	struct Image *img = NULL;

	if (dotmap[d]<0xFC)
	{
		switch(dotmap[d])
		{
			case 0x01:
				img = &iPellet;
				break;
			case 0x02:
				img = &iEnergizer;
				break;
		}
	}

	DrawImage(wPacMan->RPort,img,dot_x[d&0x1F],dot_y[d>>5]);
}

dots_plot()
{
	int i;

	for (i=0;i<sizeof(dotmap);i++)
	{
		dot_plot(i);
	}
}

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

	dots_setup();

	DrawBorder(wPacMan->RPort,&boMaze,0,7);
	DrawImage(wPacMan->RPort,&dots[0],0,0);

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
