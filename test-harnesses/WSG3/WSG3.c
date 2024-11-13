/**
 * @brief   PAC-MAN Game 10,000 points sfx
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

#define MAXVOLUME 64
#define PERIODSIZE 296

#define CHANNEL0 1
#define CHANNEL1 2
#define CHANNEL2 4
#define CHANNEL3 8

struct IOAudio *audio1IOB = 0;
struct MsgPort *port = 0;
struct MsgPort *timerPort = 0;
struct timerequest *timerMsg = 0;

extern struct AudChannel aud[];
extern UWORD dmacon;
 
UBYTE allocationMap[] = 
{
	3,5,10,12
};

UBYTE deviceOpened = FALSE;
int timerError = 0;

extern struct MsgPort *CreatePort();

/**s
 * @brief Initialize sound for playback
 */
init()
{
    deviceOpened = FALSE;

    /* Create our reply ports. */
    port = (struct MsgPort *)CreatePort(NULL,0);
    if (!port)
    {
	return FALSE;
    }

    /* Create our audio I/O block */
    audio1IOB = (struct IOAudio *)
	CreateExtIO(port, sizeof(struct IOAudio));
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

    /* Now create our timer reply port. */
    timerPort = CreatePort(0,0);
    if (!timerPort)
	return FALSE;

    timerMsg = (struct timerequest *)
	CreateExtIO(timerPort, sizeof(struct timerequest));
    
    if (!timerMsg)
    {
	if (timerPort)
		DeletePort(timerPort);

	CloseDevice(timerMsg);
	DeleteExtIO(timerMsg, sizeof(struct timerequest));

	return FALSE;
    }

    timerError = OpenDevice(TIMERNAME, UNIT_VBLANK, timerMsg, 0);

    if (timerError)
    {
	if (timerPort)
		DeletePort(timerPort);

	CloseDevice(timerMsg);
	DeleteExtIO(timerMsg, sizeof(struct timerequest));
	return FALSE;
    }

    return TRUE;
}

/**
 * @brief play.
 */
do_wsg()
{
    int i=0, j=0, volume=64;
    struct timeval tv;

    if (!deviceOpened)
	return FALSE;

	/* Setup I/O block to write to audio device */
    	audio1IOB->ioa_Request.io_Command = CMD_WRITE;
    	audio1IOB->ioa_Request.io_Flags = ADIOF_PERVOL;
    	audio1IOB->ioa_Data = waveforms[3];
    	audio1IOB->ioa_Length = WAVEFORM_SIZE;
    	audio1IOB->ioa_Period = PERIODSIZE;
    	audio1IOB->ioa_Volume = MAXVOLUME;
    	audio1IOB->ioa_Cycles = 0; /* play waveform continuously */
	BeginIO(audio1IOB);

	for (i=0;i<10;i++)
	{
		volume=64;

		for (j=0;j<6;j++)
		{
			volume -= 8;
			aud[0].ac_vol = volume;

			tv.tv_secs = 0;
			tv.tv_micro = 24576;
			timerMsg->tr_node.io_Command = TR_ADDREQUEST;
			timerMsg->tr_time = &tv;
			DoIO(timerMsg);
		}
	}

    return TRUE;
}

/**
 * @brief clean up
 */
done()
{
    if (timerMsg)
	CloseDevice(timerMsg);

    if (timerMsg)
	DeleteExtIO(timerMsg, sizeof(struct timerequest));

    if (timerPort)
	DeletePort(timerPort);

    if (deviceOpened)
	CloseDevice(audio1IOB);

    if (audio1IOB)
    {
	DeleteExtIO(audio1IOB);
    }

    if (port)
	DeletePort(port);

    return TRUE;
}

main()
{
    if (!init())
	done();

    do_wsg();

    done();

    return 0;
}
