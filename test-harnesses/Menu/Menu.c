/**
 * @brief   Menu
 * @verbose Implement the menu bar
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

struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

extern struct MsgPort *CreatePort();
extern struct MsgPort *FindPort();
extern struct IORequest *CreateExtIO();
extern struct Task *CreateTask();

/** The Test Harness *******************************************************/

#define MENU_GAME 0
#define ITEM_1P_START 0
#define ITEM_2P_START 1
#define ITEM_SEPERATOR 2
#define ITEM_QUIT 3

#define MENU_STAGE 1
#define ITEM_CHERRY 0
#define ITEM_STRAWBERRY 1
#define ITEM_ORANGE 2
#define ITEM_APPLE 3
#define ITEM_MELON 4
#define ITEM_GALAXIAN 5
#define ITEM_BELL 6
#define ITEM_KEY 7

struct Screen *OpenScreen();
struct Window *OpenWindow();

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
	MENUPICK,
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

struct MenuItem miKey = 
{
	NULL,
	48, 16, 16, 16,
	ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&iKey,
	NULL,
	NULL,
	NULL,
	NULL
};

struct MenuItem miBell = 
{
	&miKey,
	32, 16, 16, 16,
	ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&iBell,
	NULL,
	NULL,
	NULL,
	NULL
};

struct MenuItem miGalaxian = 
{
	&miBell,
	16, 16, 16, 16,
	ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&iGalaxian,
	NULL,
	NULL,
	NULL,
	NULL
};

struct MenuItem miMelon = 
{
	&miGalaxian,
	0, 16, 16, 16,
	ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&iMelon,
	NULL,
	NULL,
	NULL,
	NULL
};

struct MenuItem miApple = 
{
	&miMelon,
	48, 0, 16, 16,
	ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&iApple,
	NULL,
	NULL,
	NULL,
	NULL
};

struct MenuItem miOrange = 
{
	&miApple,
	32, 0, 16, 16,
	ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&iOrange,
	NULL,
	NULL,
	NULL,
	NULL
};

struct MenuItem miStrawberry = 
{
	&miOrange,
	16, 0, 16, 16,
	ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&iStrawberry,
	NULL,
	NULL,
	NULL,
	NULL
};

struct MenuItem miCherry = 
{
	&miStrawberry,
	0, 0, 16, 16,
	ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&iCherry,
	NULL,
	NULL,
	NULL,
	NULL
};

struct Menu mnuStage = 
{
	NULL,
	66, 0, 66, 12,
	MENUENABLED,
	"STAGE",
	&miCherry
};

struct IntuiText itQuit = 
{
	0, 1,	
	JAM1,
	0, 0,
	NULL,
	"QUIT",
	NULL
};

struct MenuItem miQuit = 
{
	NULL,
	0, 24, 64, 8,
	ITEMTEXT|ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&itQuit,
	NULL,
	NULL,
	NULL,
	NULL
};

struct IntuiText itSeperator = 
{
	0, 1,	
	JAM1,
	0, 0,
	NULL,
	"--------",
	NULL
};

struct MenuItem miSeperator = 
{
	&miQuit,
	0, 16, 64, 8,
	ITEMTEXT,
	0,
	(APTR)&itSeperator,
	NULL,
	NULL,
	NULL,
	NULL
};

struct IntuiText it2PStart = 
{
	0, 1,	
	JAM1,
	0, 0,
	NULL,
	"2P START",
	NULL
};

struct MenuItem mi2PStart = 
{
	&miSeperator,
	0, 8, 64, 8,
	ITEMTEXT|ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&it2PStart,
	NULL,
	NULL,
	NULL,
	NULL
};

struct IntuiText it1PStart = 
{
	0, 1,	
	JAM1,
	0, 0,
	NULL,
	"1P START",
	NULL
};

struct MenuItem mi1PStart = 
{
	&mi2PStart,
	0, 0, 64, 8,
	ITEMTEXT|ITEMENABLED|HIGHCOMP,
	0,
	(APTR)&it1PStart,
	NULL,
	NULL,
	NULL,
	NULL
};

struct Menu mnuGame = 
{
	&mnuStage,
	2, 0, 66, 12,
	MENUENABLED,
	"GAME",
	&mi1PStart
};

/* The Test Harness ******************************************************/

main()
{
	int menuNum, itemNum;
	struct MenuItem *item;
				
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

	SetMenuStrip(wPacMan, &mnuGame);

	FOREVER
	{
		struct IntuiMessage *msg;

		Wait(1 << wPacMan->UserPort->mp_SigBit);

		/* We only subscribed to MENUPICK, so we don't have */
 		/* to check the message class. */

		while (msg = 
			(struct IntuiMessage *)GetMsg(wPacMan->UserPort))
		{
			SHORT menuNumber = msg->Code;
			int c=0;

			DisplayBeep(NULL);

			while (menuNumber != MENUNULL)
			{
				item = ItemAddress(&mnuGame, menuNumber);
				menuNum = MENUNUM(menuNumber);
				itemNum = ITEMNUM(menuNumber);

				if (menuNum==MENU_GAME && itemNum == ITEM_QUIT)
				{
					ReplyMsg(msg); /* be nice. */
					goto bye;
				}

				menuNumber = item->NextSelect;
			}
		}
	};
	
bye:
	ClearMenuStrip(wPacMan);

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
