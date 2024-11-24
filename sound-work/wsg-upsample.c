#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "waveforms.h"

void main(void)
{

	for (int i=0;i<32;i+=2)
	{
		printf("0x%02x,",waveforms[0][i]);
	}

	printf("\n");
}
