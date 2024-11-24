/**
 * @brief   PAC-MAN WSG Test 4: Theme
 * @author  Thom Cherryhomes 
 * @email   thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see license.md for details.
 */

#include <exec/types.h>
#include <exec/memory.h>
#include <hardware/custom.h>
#include <hardware/dmabits.h>
#include <libraries/dos.h>
#include <devices/audio.h>
#include <devices/timer.h>

#include "waveforms.h"

#define PRIORITY ADALLOC_MINPREC

#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 4
#define CHANNEL4 8

long unitMap[] = 
{ CHANNEL1, CHANNEL2, CHANNEL3, CHANNEL4 };

struct IOAudio *audio1IOB = 0;
struct MsgPort *audioReplyPort = 0;

extern struct AudChannel aud[];
extern UWORD dmacon;

/* Always allocate a left and right channel, whichever that happens */
/* to be...                                                         */ 
UBYTE allocationMap[] = 
{
        CHANNEL1|CHANNEL2,
	CHANNEL1|CHANNEL3,
	CHANNEL2|CHANNEL4,
	CHANNEL3|CHANNEL4
};

UBYTE deviceOpened = FALSE;
int timerError = 0;

extern struct MsgPort *CreatePort();

/**
 * @brief Initialize sound for playback
 */
init()
{
    deviceOpened = FALSE;

    /* Create our reply audioReplyPorts. */
    audioReplyPort = (struct MsgPort *)CreatePort(NULL,0);
    if (!audioReplyPort)
    {
	return FALSE;
    }

    /* Create our audio I/O block */
    audio1IOB = (struct IOAudio *)
	CreateExtIO(audioReplyPort, sizeof(struct IOAudio));
    if (!audio1IOB)
    {
	return FALSE;
    }

    /* setup audio block with priority and allocation map */
    /* This gets sent as part of OpenDevice.              */
    audio1IOB->ioa_Request.io_Message.mn_Node.ln_Pri = PRIORITY;
    audio1IOB->ioa_Data = allocationMap;
    audio1IOB->ioa_Length = sizeof(allocationMap);
    
    if (OpenDevice(AUDIONAME, 0, audio1IOB, 0)) /* 0 = success */
    {
	return FALSE;
    }
    else
	deviceOpened = TRUE;

    /* Go ahead and start the free running oscillators. */
    audio1IOB->ioa_Request.io_Command = CMD_WRITE;
    audio1IOB->ioa_Request.io_Flags = ADIOF_PERVOL;
    audio1IOB->ioa_Request.io_Unit = (struct Unit *)unitMap[0]; 
    audio1IOB->ioa_Data = waveforms[2];
    audio1IOB->ioa_Length = WAVEFORM_SIZE;
    audio1IOB->ioa_Period = 256;
    audio1IOB->ioa_Volume = 0;
    audio1IOB->ioa_Cycles = 0; /* play waveform continuously */
    BeginIO(audio1IOB);

    audio1IOB->ioa_Request.io_Command = CMD_WRITE;
    audio1IOB->ioa_Request.io_Flags = ADIOF_PERVOL;
    audio1IOB->ioa_Request.io_Unit = (struct Unit *)unitMap[1];
    audio1IOB->ioa_Data = waveform0_16;
    audio1IOB->ioa_Length = 16;
    audio1IOB->ioa_Period = 256;
    audio1IOB->ioa_Volume = 0;
    audio1IOB->ioa_Cycles = 0; /* play waveform continuously */
    BeginIO(audio1IOB);

    return TRUE;
}

/**
 * @brief Put score to given channel
 */
void wsg_play(channel, timerMsg, score)
int channel;
struct timerequest *timerMsg;
struct Score *score;
{
	struct timeval tv;

	while (score->pitch != END)
	{
		ULONG dur = score->dur;
		UWORD vol = 64;

		aud[channel].ac_per = score->pitch;
		aud[channel].ac_vol = vol;

		while(dur)
		{
			tv.tv_secs = 0;
			tv.tv_micro = DUR_SIXTY_FOURTH-channel;
			timerMsg->tr_node.io_Command = TR_ADDREQUEST;
			timerMsg->tr_time = &tv;
			DoIO(timerMsg);

			dur -= DUR_SIXTY_FOURTH;

			if (vol)
			{
				vol -= 4; /* WSG volume is 0-15 */
			}
			else
			{
				vol -= 0; /* don't wrap around. */
			}

			aud[channel].ac_vol = vol;
		}
	
	score++;

	}
}

struct Score theme_ch2[] = 
{
	{C4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{C5,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{G4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{E4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{C5,DUR_SIXTEENTH},
	{G4,DUR_SIXTEENTH},
	{REST,DUR_EIGHTH},
	{E4,DUR_EIGHTH},
	{REST,DUR_EIGHTH},

	{CS4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{CS5,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{GS4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{F4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{CS5,DUR_SIXTEENTH},
	{GS4,DUR_SIXTEENTH},
	{REST,DUR_EIGHTH},
	{F4,DUR_EIGHTH},
	{REST,DUR_EIGHTH},

	{C4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{C5,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{G4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{E4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{C5,DUR_SIXTEENTH},
	{G4,DUR_SIXTEENTH},
	{REST,DUR_EIGHTH},
	{E4,DUR_EIGHTH},
	{REST,DUR_EIGHTH},

	{DS4, DUR_SIXTEENTH},
	{E4, DUR_SIXTEENTH},
	{F4, DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{F4,DUR_SIXTEENTH},
	{FS4,DUR_SIXTEENTH},
	{G4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{G4,DUR_SIXTEENTH},
	{GS4,DUR_SIXTEENTH},
	{A4,DUR_SIXTEENTH},
	{REST,DUR_SIXTEENTH},
	{C5,DUR_EIGHTH},
	{REST,DUR_EIGHTH},

	{END,0}
};

/**
 * @brief play ch2
 */
play_theme_ch2()
{
	struct MsgPort *timerPort = NULL;
	struct timerequest *timerMsg = NULL;

	timerPort = CreatePort(0,0);
	timerMsg  = CreateExtIO(timerPort, sizeof(struct timerequest));
	OpenDevice(TIMERNAME, UNIT_VBLANK, timerMsg, 0);
	wsg_play(1,timerMsg,theme_ch2);
	CloseDevice(timerMsg);
	DeleteExtIO(timerMsg,sizeof(struct timerequest));
	DeletePort(timerPort);

	DeleteTask(0);
}

struct Score theme_ch1[] = 
{
	{C2,DUR_QUARTER},
	{REST,DUR_EIGHTH},
	{G2,DUR_EIGHTH},
	{C2,DUR_QUARTER},
	{REST,DUR_EIGHTH},
	{G2,DUR_EIGHTH},

	{CS2,DUR_QUARTER},
	{REST,DUR_EIGHTH},
	{GS2,DUR_EIGHTH},
	{CS2,DUR_QUARTER},
	{REST,DUR_EIGHTH},
	{GS2,DUR_EIGHTH},

	{C2,DUR_QUARTER},
	{REST,DUR_EIGHTH},
	{G2,DUR_EIGHTH},
	{C2,DUR_QUARTER},
	{REST,DUR_EIGHTH},
	{G2,DUR_EIGHTH},

	{G2,DUR_QUARTER},
	{A2,DUR_QUARTER},
	{B2,DUR_QUARTER},
	{C3,DUR_QUARTER},

	{END,0}
};

/**
 * @brief play ch1
 */
void play_theme_ch1()
{
	struct MsgPort *timerPort = NULL;
	struct timerequest *timerMsg = NULL;

	timerPort = CreatePort(0,0);
	timerMsg  = CreateExtIO(timerPort, sizeof(struct timerequest));
	OpenDevice(TIMERNAME, UNIT_VBLANK, timerMsg, 0);
	wsg_play(0,timerMsg,theme_ch1);
	CloseDevice(timerMsg);
	DeleteExtIO(timerMsg,sizeof(struct timerequest));
	DeletePort(timerPort);

	DeleteTask(0);
}

/**
 * @brief clean up
 */
done()
{
    if (deviceOpened)
	CloseDevice(audio1IOB);

    if (audio1IOB)
    {
	DeleteExtIO(audio1IOB);
    }

    if (audioReplyPort)
	DeletePort(audioReplyPort);

    return TRUE;
}

main()
{
    if (!init())
	done();

    CreateTask("ch1.task",0,&play_theme_ch1,1000);
    CreateTask("ch2.task",0,&play_theme_ch2,1000); 
    
    Delay(300);
  
    done();

    return 0;
}
