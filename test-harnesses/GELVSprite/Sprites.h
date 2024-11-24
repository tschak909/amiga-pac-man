/**
 * Blinky/Pinky/Inky SimpleSprite structures.
 */

#ifndef SPRITES_H
#define SPRITES_H 1

WORD paccyColors[3]  = {0xFF0, 0xFF0, 0xFF0};
WORD blinkyColors[3] = {0xF00, 0xFFF, 0x00F};
WORD pinkyColors[3]  = {0xF0F, 0xFFF, 0x00F};
WORD inkyColors[3]   = {0x0FF, 0xFFF, 0x00F};
WORD clydeColors[3]  = {0x770, 0xFFF, 0x00F};

UWORD paccy_right_0[] = 
{
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
	0,0
};

UWORD paccy_right_1[] = 
{
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
	0,0
};

UWORD paccy_right_2[]=
{
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
	0,0
};

UWORD blinky_right_0[] = 
{
			/* BITPLANE 0		BITPLANE 1	 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0x03C0, 0x0000,	/* 0000001111000000	0000000000000000 */
	0x0FF0, 0x0000,	/* 0000111111110000	0000000000000000 */
	0x1FF8, 0x0000,	/* 0001111111111000	0000000000000000 */
	0x39E4, 0x0618,	/* 0011100111100100	0000011000011000 */
	0x30C0, 0x0F3C,	/* 0011000011000000	0000111100111100 */
	0x33CC, 0x0F3C,	/* 0011001111001100	0000111100111100 */
	0x73CE, 0x0F3C,	/* 0111001111001110	0000111100111100 */
	0x79E6, 0x0618,	/* 0111100111100110	0000011000011000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x6E76, 0x0000,	/* 0110111001110110	0000000000000000 */
	0x4662, 0x0000,	/* 0100011001100010	0000000000000000 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0,0
};

UWORD blinky_right_1[] = 
{
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0x03C0, 0x0000,	/* 0000001111000000	0000000000000000 */
	0x0FF0, 0x0000,	/* 0000111111110000	0000000000000000 */
	0x1FF8, 0x0000,	/* 0001111111111000	0000000000000000 */
	0x39E4, 0x0618,	/* 0011100111100100	0000011000011000 */
	0x30C0, 0x0F3C,	/* 0011000011000000	0000111100111100 */
	0x33CC, 0x0F3C,	/* 0011001111001100	0000111100111100 */
	0x73CE, 0x0F3C,	/* 0111001111001110	0000111100111100 */
	0x79E6, 0x0618,	/* 0111100111100110	0000011000011000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7BDE, 0x0000,	/* 0111101111011110	0000000000000000 */
	0x318C, 0x0000,	/* 0011000110001100	0000000000000000 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0,0
};

UWORD pinky_right_0[] = 
{
			/* BITPLANE 0		BITPLANE 1	 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0x03C0, 0x0000,	/* 0000001111000000	0000000000000000 */
	0x0FF0, 0x0000,	/* 0000111111110000	0000000000000000 */
	0x1FF8, 0x0000,	/* 0001111111111000	0000000000000000 */
	0x39E4, 0x0618,	/* 0011100111100100	0000011000011000 */
	0x30C0, 0x0F3C,	/* 0011000011000000	0000111100111100 */
	0x33CC, 0x0F3C,	/* 0011001111001100	0000111100111100 */
	0x73CE, 0x0F3C,	/* 0111001111001110	0000111100111100 */
	0x79E6, 0x0618,	/* 0111100111100110	0000011000011000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x6E76, 0x0000,	/* 0110111001110110	0000000000000000 */
	0x4662, 0x0000,	/* 0100011001100010	0000000000000000 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0,0
};

UWORD pinky_right_1[] = 
{
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0x03C0, 0x0000,	/* 0000001111000000	0000000000000000 */
	0x0FF0, 0x0000,	/* 0000111111110000	0000000000000000 */
	0x1FF8, 0x0000,	/* 0001111111111000	0000000000000000 */
	0x39E4, 0x0618,	/* 0011100111100100	0000011000011000 */
	0x30C0, 0x0F3C,	/* 0011000011000000	0000111100111100 */
	0x33CC, 0x0F3C,	/* 0011001111001100	0000111100111100 */
	0x73CE, 0x0F3C,	/* 0111001111001110	0000111100111100 */
	0x79E6, 0x0618,	/* 0111100111100110	0000011000011000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7BDE, 0x0000,	/* 0111101111011110	0000000000000000 */
	0x318C, 0x0000,	/* 0011000110001100	0000000000000000 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0,0
};

UWORD inky_right_0[] = 
{
			/* BITPLANE 0		BITPLANE 1	 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0x03C0, 0x0000,	/* 0000001111000000	0000000000000000 */
	0x0FF0, 0x0000,	/* 0000111111110000	0000000000000000 */
	0x1FF8, 0x0000,	/* 0001111111111000	0000000000000000 */
	0x39E4, 0x0618,	/* 0011100111100100	0000011000011000 */
	0x30C0, 0x0F3C,	/* 0011000011000000	0000111100111100 */
	0x33CC, 0x0F3C,	/* 0011001111001100	0000111100111100 */
	0x73CE, 0x0F3C,	/* 0111001111001110	0000111100111100 */
	0x79E6, 0x0618,	/* 0111100111100110	0000011000011000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x6E76, 0x0000,	/* 0110111001110110	0000000000000000 */
	0x4662, 0x0000,	/* 0100011001100010	0000000000000000 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0,0
};

UWORD inky_right_1[] = 
{
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0x03C0, 0x0000,	/* 0000001111000000	0000000000000000 */
	0x0FF0, 0x0000,	/* 0000111111110000	0000000000000000 */
	0x1FF8, 0x0000,	/* 0001111111111000	0000000000000000 */
	0x39E4, 0x0618,	/* 0011100111100100	0000011000011000 */
	0x30C0, 0x0F3C,	/* 0011000011000000	0000111100111100 */
	0x33CC, 0x0F3C,	/* 0011001111001100	0000111100111100 */
	0x73CE, 0x0F3C,	/* 0111001111001110	0000111100111100 */
	0x79E6, 0x0618,	/* 0111100111100110	0000011000011000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7BDE, 0x0000,	/* 0111101111011110	0000000000000000 */
	0x318C, 0x0000,	/* 0011000110001100	0000000000000000 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0,0
};

UWORD clyde_right_0[] = 
{
			/* BITPLANE 0		BITPLANE 1	 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0x03C0, 0x0000,	/* 0000001111000000	0000000000000000 */
	0x0FF0, 0x0000,	/* 0000111111110000	0000000000000000 */
	0x1FF8, 0x0000,	/* 0001111111111000	0000000000000000 */
	0x39E4, 0x0618,	/* 0011100111100100	0000011000011000 */
	0x30C0, 0x0F3C,	/* 0011000011000000	0000111100111100 */
	0x33CC, 0x0F3C,	/* 0011001111001100	0000111100111100 */
	0x73CE, 0x0F3C,	/* 0111001111001110	0000111100111100 */
	0x79E6, 0x0618,	/* 0111100111100110	0000011000011000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x6E76, 0x0000,	/* 0110111001110110	0000000000000000 */
	0x4662, 0x0000,	/* 0100011001100010	0000000000000000 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0,0
};

UWORD clyde_right_1[] = 
{
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0x03C0, 0x0000,	/* 0000001111000000	0000000000000000 */
	0x0FF0, 0x0000,	/* 0000111111110000	0000000000000000 */
	0x1FF8, 0x0000,	/* 0001111111111000	0000000000000000 */
	0x39E4, 0x0618,	/* 0011100111100100	0000011000011000 */
	0x30C0, 0x0F3C,	/* 0011000011000000	0000111100111100 */
	0x33CC, 0x0F3C,	/* 0011001111001100	0000111100111100 */
	0x73CE, 0x0F3C,	/* 0111001111001110	0000111100111100 */
	0x79E6, 0x0618,	/* 0111100111100110	0000011000011000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7FFE, 0x0000,	/* 0111111111111110	0000000000000000 */
	0x7BDE, 0x0000,	/* 0111101111011110	0000000000000000 */
	0x318C, 0x0000,	/* 0011000110001100	0000000000000000 */
	0x0000, 0x0000,	/* 0000000000000000	0000000000000000 */
	0,0
};

#endif /* SPRITES_H */