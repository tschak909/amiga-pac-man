/****************************************************************************
 *                                                                          *
 *                              GELTOOLS                                    *
 *      (c) 1986 Commodore-Amiga, Inc.                                      *
 ****************************************************************************/

#include "vsprite.h"            /* standard includes & definitions */


/* ======================================================================== */
/* ==== PrepGels ========================================================== */
/* ======================================================================== */

MakeGelsInfo(rp, reserve)
struct RastPort *rp;
BYTE reserve;
{
    struct GelsInfo *g;
    struct VSprite *HeadSprite, *TailSprite;

    g = (struct GelsInfo *)AllocMem(sizeof(struct GelsInfo),
        MEMF_PUBLIC | MEMF_CLEAR);
    rp->GelsInfo = g;

    g->sprRsrvd = reserve;
    g->nextLine = (WORD *)AllocMem(8 * sizeof(WORD),
        MEMF_PUBLIC | MEMF_CLEAR);
    g->lastColor = (WORD *)AllocMem(8 * sizeof(LONG),
        MEMF_PUBLIC | MEMF_CLEAR);
    g->collHandler = (struct collTable *)AllocMem(sizeof(struct collTable),
        MEMF_PUBLIC | MEMF_CLEAR);
    g->leftmost = 0;
    g->rightmost = rp->BitMap->BytesPerRow * 8 - 1;
    g->topmost = 0;
    g->bottommost = rp->BitMap->Rows - 1;
 
    HeadSprite = (struct VSprite *)AllocMem(sizeof(struct VSprite),
        MEMF_PUBLIC | MEMF_CLEAR);
    TailSprite = (struct VSprite *)AllocMem(sizeof(struct VSprite),
        MEMF_PUBLIC | MEMF_CLEAR);
    InitGels(HeadSprite, TailSprite, g);
}


/* ======================================================================== */
/* ==== DeleteGelsInfo ==================================================== */
/* ======================================================================== */

DeleteGelsInfo(g)
struct GelsInfo *g;
{
    if(g)
    {
        if(g->nextLine)FreeMem(g->nextLine, 8 * sizeof(WORD));
        if(g->lastColor)FreeMem(g->lastColor, 8 * sizeof(LONG));
        if(g->collHandler)FreeMem(g->collHandler, sizeof(struct collTable));
        if(g->gelHead)FreeMem(g->gelHead, sizeof(struct VSprite));
        if(g->gelTail)FreeMem(g->gelTail, sizeof(struct VSprite));

        FreeMem(g, sizeof(struct GelsInfo));
    }
}


/* ======================================================================== */
/* ==== MakeVSprite ======================================================= */
/* ======================================================================== */

struct VSprite *
MakeVSprite(x, y, vsheight, vswidth, vsdepth, vsimage, vscolors)
WORD x, y;
WORD vsheight, vswidth, vsdepth;
WORD *vsimage;
WORD *vscolors;
{
    WORD i;
    struct VSprite *vs;

    vs = (struct VSprite *)AllocMem(sizeof(struct VSprite),
        MEMF_PUBLIC | MEMF_CLEAR);

    vs->Flags = VSPRITE;
    vs->X = x;
    vs->Y = y;
    vs->Height = vsheight;
    vs->Width = vswidth;
    vs->Depth = vsdepth;
    vs->ImageData = (WORD *)AllocMem(vsheight * vswidth * vsdepth *
        sizeof(WORD), MEMF_CHIP);
    for(i = 0; i < (vsheight * vswidth * vsdepth); i++)
        vs->ImageData[i] = vsimage[i];
 
    vs->SprColors = vscolors;

    return(vs);
}


/* ======================================================================== */
/* ==== DeleteVSprite ===================================================== */
/* ======================================================================== */

DeleteVSprite(vs, pfdepth)
struct VSprite *vs;
WORD pfdepth;
{
    if(vs)
    {
        if(vs->VSBob)
        {
            RemBob(vs->VSBob);
            if(vs->VSBob->SaveBuffer)FreeMem(vs->VSBob->SaveBuffer,
                vs->Height * vs->Width * pfdepth * sizeof(WORD));
            FreeMem(vs->VSBob, sizeof(struct Bob));
        }

        RemVSprite(vs);

        if(vs->ImageData)FreeMem(vs->ImageData,
            vs->Height * vs->Width * vs->Depth * sizeof(WORD));
        if(vs->BorderLine)FreeMem(vs->BorderLine,
            vs->Width * sizeof(WORD));
        if(vs->CollMask) FreeMem(vs->CollMask,
            vs->Height * vs->Width * sizeof(WORD));
 
        FreeMem(vs, sizeof(struct VSprite));
    }
}


/* ======================================================================== */
/* ==== MakeBob =========================================================== */
/* ======================================================================== */

struct VSprite *
MakeBob(x, y, bheight, bwidth, bdepth, bimage, pfdepth, pp, poo)
WORD x, y;
WORD bheight, bwidth, bdepth;
WORD *bimage;
WORD pfdepth;
BYTE pp, poo;
{
    struct Bob *b;
    struct VSprite *v;

    v = MakeVSprite(x, y, bheight, bwidth, bdepth, bimage, NULL);
    b = (struct Bob *)AllocMem(sizeof(struct Bob),
        MEMF_PUBLIC | MEMF_CLEAR);
    v->VSBob = b;
    b->BobVSprite = v;

    v->PlanePick = pp;
    v->PlaneOnOff = poo;
    v->Flags = OVERLAY | SAVEBACK;

    v->BorderLine = (WORD *)AllocMem((bwidth * sizeof(WORD)),
        MEMF_PUBLIC | MEMF_CLEAR);
    v->CollMask = (WORD *)AllocMem((sizeof(WORD) * bheight * bwidth),
        MEMF_CHIP | MEMF_CLEAR);

    b->SaveBuffer = (WORD *)AllocMem(bheight * bwidth * pfdepth *
        sizeof(WORD), MEMF_CHIP | MEMF_CLEAR);
    b->ImageShadow = v->CollMask;

    InitMasks(v);

    return(v);
}


/* =========================== END OF FILE ================================ */


