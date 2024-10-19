/**
 * @brief   Slice WSG Prom into seperate files
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com 
 * @license gpl v. 3, see LICENSE for details.
 *
 * Compile with:
 * cc -owsg-slice wsg-slice.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WAVEFORM_SIZE 32

void split(FILE *fp, const char *dfn)
{
    FILE *dfp = fopen(dfn,"wb");

    if (!dfp)
    {
        perror("wsg-slice split");
        fclose(fp);
        exit(3);
    }

    for (int i=0;i<WAVEFORM_SIZE;i++)
        fputc((fgetc(fp) << 4)-128,dfp);

    fclose(dfp);
}

int main(int argc, char *argv[])
{
    if (argc<2)
    {
        printf("%s <pm1-3.1m>\n",argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1],"rb");

    if (!fp)
    {
        perror("wsg-slice");
        return 2;
    }
    
    split(fp,"pm1-3.1m.0");
    split(fp,"pm1-3.1m.1");
    split(fp,"pm1-3.1m.2");
    split(fp,"pm1-3.1m.3");
    split(fp,"pm1-3.1m.4");
    split(fp,"pm1-3.1m.5");
    split(fp,"pm1-3.1m.6");
    split(fp,"pm1-3.1m.7");

    fclose(fp);
}
