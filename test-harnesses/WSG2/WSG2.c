/**
 * @brief   a simple WSG sanity check.
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
#define PERIODSIZE 256

#define CHANNEL0 1
#define CHANNEL1 2
#define CHANNEL2 4
#define CHANNEL3 8

struct IOAudio *audioIOB = 0;
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
    audioIOB = (struct IOAudio *)
	CreateExtIO(port, sizeof(struct IOAudio));
    if (!audioIOB)
    {
	return FALSE;
    }

    /* setup audio block with priority and allocation map */
    /* This gets sent as part of OpenDevice.              */
    audioIOB->ioa_Request.io_Message.mn_Node.ln_Pri = PRIORITY;
    audioIOB->ioa_Data = allocationMap;
    audioIOB->ioa_Length = sizeof(allocationMap);
    
    if (OpenDevice(AUDIONAME, 0, audioIOB, 0)) /* 0 = success */
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
 * @brief Do each wsg
 */
do_wsg()
{
    int i=0, period=272;
    struct timeval tv;

    if (!deviceOpened)
	return FALSE;

	/* Setup I/O block to write to audio device */
    	audioIOB->ioa_Request.io_Command = CMD_WRITE;
    	audioIOB->ioa_Request.io_Flags = ADIOF_PERVOL;
    	audioIOB->ioa_Data = waveforms[2];
    	audioIOB->ioa_Length = WAVEFORM_SIZE;
    	audioIOB->ioa_Period = PERIODSIZE;
    	audioIOB->ioa_Volume = MAXVOLUME;
    	audioIOB->ioa_Cycles = 0; /* play waveform for a bit */
	BeginIO(audioIOB);

        tv.tv_secs = 0;
	tv.tv_micro = 9625;

        for (i=0;i<6;i++)
	{
		period += 64;
		aud[0].ac_per = period;
		tv.tv_secs = 0;
		tv.tv_micro = 9625;

		timerMsg->tr_node.io_Command = TR_ADDREQUEST;
		timerMsg->tr_time = &tv;
	
		DoIO(timerMsg);
	}        

        for (i=0;i<6;i++)
	{
		period -= 64;
		aud[0].ac_per = period;
		tv.tv_secs = 0;
		tv.tv_micro = 9625;

		timerMsg->tr_node.io_Command = TR_ADDREQUEST;
		timerMsg->tr_time = &tv;
	
		DoIO(timerMsg);
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
	CloseDevice(audioIOB);

    if (audioIOB)
    {
	DeleteExtIO(audioIOB);
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
