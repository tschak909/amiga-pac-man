#ifndef WAVEFORMS_H
#define WAVEFORMS_H 1

#define WAVEFORM_SIZE 32

/* for Waveform0 octaves 5 and 6. */
unsigned char waveform0_16[16] = 
{
   0xF0, 0x20, 0x40, 0x50, 0x60, 0x50, 0x40, 0x20, 0xf0, 0xc0, 0xa0, 0x90,
   0x80, 0x90, 0xa0, 0xc0
};

unsigned char waveforms[8][32] =
    {
        {
            0xf0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x50, 0x60, 0x60, 0x60, 0x50, 0x50,
            0x40, 0x30, 0x20, 0x10, 0xf0, 0xd0, 0xc0, 0xb0, 0xa0, 0x90, 0x90, 0x80,
            0x80, 0x80, 0x90, 0x90, 0xa0, 0xb0, 0xc0, 0xd0
        },
        {
            0xf0, 0x40, 0x60, 0x60, 0x50, 0x30, 0x10, 0x20, 0x30, 0x30, 0x20, 0x10,
            0xe0, 0xc0, 0xb0, 0xd0, 0xf0, 0x10, 0x30, 0x20, 0x00, 0xd0, 0xc0, 0xb0,
            0xb0, 0xc0, 0xd0, 0xb0, 0x90, 0x80, 0x80, 0xa0
        },
        {
            0xf0, 0x20, 0x40, 0x50, 0x60, 0x50, 0x40, 0x20, 0xf0, 0xc0, 0xa0, 0x90,
            0x80, 0x90, 0xa0, 0xc0, 0xf0, 0x30, 0x50, 0x60, 0x50, 0x30, 0xf0, 0xb0,
            0x90, 0x80, 0x90, 0xb0, 0xf0, 0x60, 0xf0, 0x80
        },
        {
            0xf0, 0x50, 0x30, 0x00, 0x30, 0x50, 0x10, 0xe0, 0x30, 0x60, 0x40, 0xf0,
            0x10, 0x20, 0xe0, 0xa0, 0xf0, 0x40, 0x00, 0xc0, 0xd0, 0xf0, 0xa0, 0x80,
            0xb0, 0x00, 0xd0, 0x90, 0xb0, 0xe0, 0xb0, 0x90
        },
        {
            0x80, 0x00, 0x70, 0xf0, 0x90, 0x00, 0x60, 0xf0, 0xa0, 0x00, 0x50, 0xf0,
            0xb0, 0x00, 0x40, 0xf0, 0xc0, 0x00, 0x30, 0xf0, 0xd0, 0x00, 0x20, 0xf0,
            0xe0, 0x00, 0x10, 0xf0, 0xf0, 0x00, 0x00, 0xf0
        },
        {
            0xf0, 0x00, 0xe0, 0x10, 0xd0, 0x20, 0xc0, 0x30, 0xb0, 0x40, 0xa0, 0x50,
            0x90, 0x60, 0x80, 0x70, 0x80, 0x70, 0x90, 0x60, 0xa0, 0x50, 0xb0, 0x40,
            0xc0, 0x30, 0xd0, 0x20, 0xe0, 0x10, 0xf0, 0x00
        },
        {
            0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0, 0x00, 0x10, 0x20, 0x30,
            0x40, 0x50, 0x60, 0x70, 0x70, 0x60, 0x50, 0x40, 0x30, 0x20, 0x10, 0x00,
            0xf0, 0xe0, 0xd0, 0xc0, 0xb0, 0xa0, 0x90, 0x80            
        },
        {
            0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0, 0x00, 0x10, 0x20, 0x30,
            0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0,
            0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70
        }
};

/* Note length in microseconds */
#define DUR_SIXTY_FOURTH  16500
#define DUR_THIRTY_SECOND 33000
#define DUR_SIXTEENTH     66000
#define DUR_EIGHTH        132000
#define DUR_QUARTER       264000
#define DUR_HALF          528000
#define DUR_WHOLE         1056000

#define REST	0
#define END	65535
#define C0	6842
#define CS0	6458
#define DF0	CS0
#define D0	6095
#define DS0	5751
#define EF0	DS0
#define E0	5430
#define F0	5124
#define FS0	4838
#define GF0	FS0
#define G0	4565
#define GS0	4308
#define AF0	GS0
#define	A0	4068
#define AS0	3839
#define BF0	AS0
#define B0	3624
#define C1	3421
#define CS1	3228
#define DF1	CS1
#define D1	3047
#define DS1	2876
#define EF1	DS1
#define E1	2715
#define F1	2562
#define FS1	2419
#define GF1	FS1
#define G1	2283
#define GS1	2155
#define AF1	GS1
#define A1	2033
#define AS1	1920
#define BF1	AS1
#define B1	1812
#define C2	1710
#define CS2	1614
#define DF2	CS2
#define D2	1524
#define DS2	1438
#define EF2	DS2
#define E2	1357
#define F2	1281
#define FS2	1209
#define GF2	FS2
#define G2	1141
#define GS2	1077
#define AF2	GS2
#define A2	1017
#define AS2	960
#define BF2	AS2
#define B2	906
#define C3	855
#define CS3	807
#define DF3	CS3
#define D3	762
#define DS3	719
#define EF3	DS3
#define E3	679
#define F3	641
#define FS3	605
#define GF3	FS3
#define G3	571
#define GS3	539
#define AF3	GS3
#define A3	508
#define AS3	480
#define BF3	AS3
#define B3	453
#define C4	428
#define CS4	404
#define DF4	CS4
#define D4	381
#define DS4	360
#define EF4	DS4
#define E4	339
#define F4	320
#define FS4	302
#define GF4	FS4
#define G4	285
#define GS4	269
#define AF4	GS4
#define A4	254	/* 440Hz */
#define AS4	240
#define BF4	AS4
#define B4	226
#define C5	214
#define CS5	202
#define DF5	CS5
#define D5	190
#define DS5	180
#define EF5	DS5
#define E5	170
#define F5	160
#define FS5	151
#define GF5	FS5
#define G5	143
#define GS5	135
#define AF5	GS5
#define A5	127

/* waveform0_64 tunings for Octaves 5 and 6 */

struct Score
{
	USHORT pitch;
	ULONG dur;	
};

#endif /* WAVEFORMS_H */
