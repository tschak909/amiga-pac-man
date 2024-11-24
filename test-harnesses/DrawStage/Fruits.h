/**
 * @brief Fruits defined as Intuition Images
 * @verbose The stage fruits
 */

#ifndef FRUITS_H
#define FRUITS_H 1

SHORT bmEmpty[] = 
{
	/* BITPLANE 0 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 1 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 2 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 3 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
};

struct Image iEmpty = 
{
	0, 0,		/* TopEdge, LeftEdge */
	16, 16, 4,	/* Width, Height, Depth (# of bitplanes) */
	bmEmpty,	/* Pointer to bitmap */
	0x0F, 0x00, 	/* PlanePick, PlaneOnOff */
	NULL		/* NextImage */
};

/* PlanePick and PlaneOnOff are explained on page B-7 of the */
/* Amiga Intuition Reference Manual, by Mical and Deyl       */

SHORT bmKey[] = 
{

	/* BITPLANE 0 */
	/* Plane not picked */
	/* BITPLANE 1 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0380, /* 0000001110000000 */
	0x0C60, /* 0000110001100000 */
	0x0FE0, /* 0000111111100000 */
	0x0FE0, /* 0000111111100000 */
	0x0FE0, /* 0000111111100000 */
	0x0280, /* 0000001010000000 */
	0x02C0, /* 0000001011000000 */
	0x0280, /* 0000001010000000 */
	0x0200, /* 0000001000000000 */
	0x0280, /* 0000001010000000 */
	0x02C0, /* 0000001011000000 */
	0x0280, /* 0000001010000000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 2 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0380, /* 0000001110000000 */
	0x0C60, /* 0000110001100000 */
	0x0FE0, /* 0000111111100000 */
	0x0FE0, /* 0000111111100000 */
	0x0FE0, /* 0000111111100000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 3 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0280, /* 0000001010000000 */
	0x02C0, /* 0000001011000000 */
	0x0280, /* 0000001010000000 */
	0x0200, /* 0000001000000000 */
	0x0280, /* 0000001010000000 */
	0x02C0, /* 0000001011000000 */
	0x0280, /* 0000001010000000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */
};

struct Image iKey = 
{
	0, 0,
	16, 16, 4,
	bmKey,
	0x0E, 0x00,
	NULL
};

SHORT bmGalaxian[] = 
{
	/* BITPLANE 0 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x1290, /* 0001001010010000 */
	0x0F78, /* 0001111011110000 */
	0x0FE0, /* 0000111111100000 */
	0x0540, /* 0000010101000000 */
	0x0100, /* 0000000100000000 */
	0x0100, /* 0000000100000000 */
	0x0100, /* 0000000100000000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 1 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0100, /* 0000000100000000 */
	0x0380, /* 0000001110000000 */
	0x07C0, /* 0000011111000000 */
	0x0D60, /* 0000110101100000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 2 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x2008, /* 0010000000001000 */
	0x2008, /* 0010000000001000 */
	0x2008, /* 0010000000001000 */
	0x2008, /* 0010000000001000 */
	0x3018, /* 0011000000011000 */
	0x1830, /* 0001100000110000 */
	0x0C60, /* 0000110001100000 */
	0x0440, /* 0000010001000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 3 */
	/* Plane not picked */
};

struct Image iGalaxian = 
{
	0, 0,
	16, 16, 4,
	bmGalaxian,
	0x07, 0x00,
	NULL
};

SHORT bmBell[] = 
{
	/* BITPLANE 0 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0180, /* 0000000110000000 */
	0x0660, /* 0000011001100000 */
	0x07E0, /* 0000111111110000 */
	0x06E0, /* 0000110111110000 */
	0x0BF0, /* 0000101111110000 */
	0x1BF8, /* 0001101111111000 */
	0x1BF8, /* 0001101111111000 */
	0x1FF8, /* 0001111111111000 */
	0x37FC, /* 0011011111111100 */
	0x37FC, /* 0011011111111100 */
	0x3FFC, /* 0011111111111100 */
	0x20C4, /* 0010000011000100 */
	0x00C0, /* 0000000011000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 1 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x1FF8, /* 0001111111111000 */
	0x1FF8, /* 0001111111111000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 2 */
	/* Plane not picked */

	/* BITPLANE 3 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x1F38, /* 0001111100111000 */
	0x1F38, /* 0001111100111000 */
	0x0000, /* 0000000000000000 */
};

struct Image iBell = 
{
	0, 0,
	16, 16, 4,
	bmBell,
	0x0B, 0x00,
	NULL
};

SHORT bmMelon[] = 
{
	/* BITPLANE 0 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0080, /* 0000000010000000 */
	0x0000, /* 0000000000000000 */
	0x0200, /* 0000001000000000 */
	0x0020, /* 0000000000100000 */
	0x0800, /* 0000100000000000 */
	0x0110, /* 0000000100010000 */
	0x0800, /* 0000100000000000 */
	0x0280, /* 0000001010000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 1 */
	0x0000, /* 0000000000000000 */
	0x0400, /* 0000010000000000 */
	0x03E0, /* 0000001111100000 */
	0x0080, /* 0000000010000000 */
	0x0080, /* 0000000010000000 */
	0x0080, /* 0000000010000000 */
	0x0710, /* 0000011100010000 */
	0x0230, /* 0000001000110000 */
	0x0C10, /* 0000110000010000 */
	0x1A98, /* 0001101010011000 */
	0x0400, /* 0000010000000000 */
	0x02A0, /* 0000001010100000 */
	0x0110, /* 0000000100010000 */
	0x0220, /* 0000001000100000 */
	0x0040, /* 0000000001000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 2 */
	0x0000, /* 0000000000000000 */
	0x0400, /* 0000010000000000 */
	0x03E0, /* 0000001111100000 */
	0x0080, /* 0000000010000000 */
	0x0000, /* 0000000000000000 */
	0x0080, /* 0000000010000000 */
	0x0510, /* 0000010100010000 */
	0x0210, /* 0000001000010000 */
	0x0410, /* 0000010000010000 */
	0x0808, /* 0000100000001000 */
	0x0400, /* 0000010000000000 */
	0x02A0, /* 0000001010100000 */
	0x0110, /* 0000000100010000 */
	0x0220, /* 0000001000100000 */
	0x0040, /* 0000000001000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 3 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0140, /* 0000000101000000 */
	0x0770, /* 0000011101110000 */
	0x08E8, /* 0000100011101000 */
	0x0DCC, /* 0000110111001100 */
	0x13AC, /* 0001001110101100 */
	0x1664, /* 0001011001100100 */
	0x13BC, /* 0001001110111100 */
	0x0C18, /* 0000110000011000 */
	0x0EE8, /* 0000111011101000 */
	0x05D0, /* 0000010111010000 */
	0x0180, /* 0000000110000000 */
	0x0000, /* 0000000000000000 */
};

struct Image iMelon = 
{
	0, 0,
	16, 16, 4,
	bmMelon,
	0x0F, 0x00,
	NULL
};

SHORT bmApple[] = 
{
	/* BITPLANE 0 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0080, /* 0000000010000000 */
	0x0100, /* 0000000100000000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0008, /* 0000000000001000 */
	0x0008, /* 0000000000001000 */
	0x0010, /* 0000000000010000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 1 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0080, /* 0000000010000000 */
	0x1D70, /* 0001110101110000 */
	0x3FF8, /* 0011111111111000 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x1FF8, /* 0001111111111000 */
	0x1FF8, /* 0001111111111000 */
	0x0FF0, /* 0000111111110000 */
	0x06F0, /* 0000011011100000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 2 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0080, /* 0000000010000000 */
	0x0100, /* 0000000100000000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 3 */
	/* Plane not picked */
};

struct Image iApple = 
{
	0, 0,
	16, 16, 3,
	bmApple,
	0x07, 0x00,
	NULL
};

SHORT bmOrange[] = 
{
	/* BITPLANE 0 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0100, /* 0000000100000000 */
	0x0100, /* 0000000100000000 */
	0x0FF0, /* 0000111111110000 */
	0x1FF8, /* 0001111111111000 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x1FF8, /* 0001111111111000 */
	0x1FF8, /* 0001111111111000 */
	0x07E0, /* 0000011111100000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	/* BITPLANE 1 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0C70, /* 0000110001110000 */
	0x1EF8, /* 0001111011111000 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x1FF8, /* 0001111111111000 */
	0x1FF8, /* 0001111111111000 */
	0x07E0, /* 0000011111100000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	/* BITPLANE 2 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0C70, /* 0000110001110000 */
	0x1EF8, /* 0001111011111000 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x3FFC, /* 0011111111111100 */
	0x1FF8, /* 0001111111111000 */
	0x1FF8, /* 0001111111111000 */
	0x07E0, /* 0000011111100000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	/* BITPLANE 3 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0060, /* 0000000001100000 */
	0x01F8, /* 0000000111111000 */
	0x0170, /* 0000000101110000 */
	0x0380, /* 0000001110000000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
};

struct Image iOrange = 
{
	0, 0,
	16, 16, 4,
	bmOrange,
	0x0F, 0x00,
	NULL
};

SHORT bmStrawberry[] = 
{
	/* BITPLANE 0 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0100, /* 0000000100000000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */
	0x0010, /* 0000000000010000 */
	0x1080, /* 0001000001000000 */
	0x0580, /* 0000010100000000 */
	0x0020, /* 0000000000100000 */
	0x1200, /* 0001001000000000 */
	0x0000, /* 0000000000000000 */
	0x0480, /* 0000010010000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 1 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0100, /* 0000000100000000 */
	0x0100, /* 0000000100000000 */
	0x1830, /* 0001100000110000 */
	0x3FF8, /* 0011111111111000 */
	0x3FF8, /* 0011111111111000 */
	0x3FF8, /* 0011111111111000 */
	0x3FF8, /* 0011111111111000 */
	0x1FF0, /* 0001111111110000 */
	0x1FF0, /* 0001111111110000 */
	0x0FC0, /* 0000111111000000 */
	0x07C0, /* 0000011111000000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */

	/* BITPLANE 2 */
	/* Plane not picked. */

	/* BITPLANE 3 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0EE0, /* 0000111011100000 */
	0x07C0, /* 0000011111000000 */
	0x0100, /* 0000000100000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
	0x0000, /* 0000000000000000 */
};

struct Image iStrawberry = 
{
	0, 0,
	16, 16, 4,
	bmStrawberry,
	0x0B, 0x00,
	NULL
};

SHORT bmCherry[] = 
{
	/* BITPLANE 0 */
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x000C,	/* 0b0000000000001100 */	
	0x003C,	/* 0b0000000000111100 */	
	0x00D0,	/* 0b0000000011010000 */	
	0x0110,	/* 0b0000000100010000 */	
	0x0220,	/* 0b0000001000100000 */	
	0x0440,	/* 0b0000010001000000 */	
	0x0040,	/* 0b0000000001000000 */	
	0x1040,	/* 0b0001000001000000 */	
	0x0800,	/* 0b0000100000000000 */	
	0x0080,	/* 0b0000000010000000 */	
	0x0040,	/* 0b0000000001000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */	

	/* BITPLANE 1 */
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x000C,	/* 0b0000000000001100 */	
	0x003C,	/* 0b0000000000111100 */	
	0x00D0,	/* 0b0000000011010000 */	
	0x0110,	/* 0b0000000100010000 */	
	0x1E20,	/* 0b0001111000100000 */	
	0x3F40,	/* 0b0011111101000000 */	
	0x3EF0,	/* 0b0011111011110000 */	
	0x3DF8,	/* 0b0011110111111000 */	
	0x3DF8,	/* 0b0011110111111000 */	
	0x1DF8,	/* 0b0001110111111000 */	
	0x01F8,	/* 0b0000000111111000 */	
	0x00F0,	/* 0b0000000011110000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */

	/* BITPLANE 2 */
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x000C,	/* 0b0000000000001100 */	
	0x003C,	/* 0b0000000000111100 */	
	0x00D0,	/* 0b0000000011010000 */	
	0x0110,	/* 0b0000000100010000 */	
	0x0220,	/* 0b0000001000100000 */	
	0x0440,	/* 0b0000010001000000 */	
	0x0040,	/* 0b0000000001000000 */	
	0x0040,	/* 0b0000000001000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */	
	0x0000,	/* 0b0000000000000000 */
};

struct Image iCherry = 
{
	0, 0,
	16, 16, 3,
	bmCherry,
	0x07, 0x00,
	NULL
};

#endif /* FRUITS_H */