#include <stdio.h>
#include <math.h>

#include "bstr.h"


void BSTR_SetBits(BitString* bstr, char* bits) {
  int i = 0;
	while (bits[i] != '\0') {
		if (bits[i] == '0') {
			bstr->bits[i] = 0;
	    } else {
			bstr->bits[i] = 1;
	    }
        i++;
    }
	bstr->length = i;
}

void BSTR_SetBit(BitString* bstr, int bit, int index) {
    bstr->bits[index] = bit;
}

void BSTR_HemmingWeightGenerator(BitString source, BitString* dest, int wordSise) {
    BitString w_9;
    w_9.length = wordSise;
    
    int i, j, count;
    for(i = 0; i < dest->length; i++) {
		BSTR_SetValue(&w_9, i, wordSise);
		count = 0;
		for(j = wordSise- 1; j >= 0; j--) {
			if(BSTR_GetBitValue(w_9, j))	count ++;
		}
		if (BSTR_GetBitValue(w_9, (wordSise - 1)/2))	count += floor((wordSise - 1));
		BSTR_SetBit(dest, BSTR_GetBitValue(source, count), i);
    }
}

void BSTR_SetValue(BitString* bstr, int n, int size) {
	int i;
	if (size > MAXBITS) {
		return;
    }
	bstr->length = size;

	for (i = bstr->length-1; i >= 0; i--) {
		bstr->bits[i] = n % 2;
		n = n / 2;
    }
}

void BSTR_Invert(BitString* bstr) {
    int i;
	for (i = 0; i < bstr->length; i++) {
		if (bstr->bits[i] == 0) {
			bstr->bits[i] = 1;
	    } else {
			bstr->bits[i] = 0;
	    }
    }
}

void BSTR_AddOne(BitString* bstr) {
    int i;
	for (i = bstr->length-1; i >= 0; i--) {
		if (bstr->bits[i] == 0) {
			bstr->bits[i] = 1;
			break;
	    } else {
			bstr->bits[i] = 0;  /* and add one to next column */
	    }
    }
}

void BSTR_Display(BitString bstr, int fourGrouping) {
	int i;
	for (i = 0; i < bstr.length; i++) {
		if (fourGrouping && (i % 4 == 0) && i != 0)	printf(" ");
		if (bstr.bits[i] == 0)	printf("0");
	  else	printf("1");
	}
	printf("\n");
}

void BSTR_ToFile(BitString bstr, FILE* file) {
	int i;
	for (i = 0; i < bstr.length; i++) {
		if (bstr.bits[i] == 0)	{
			fputs("0", file);
		} else {
			fputs("1", file);
		}
	}
	fputs("\t|", file);
}

int BSTR_GetBitValue(BitString bstr, int index) {
    if (bstr.bits[index] == 1) {
        return 1;
    } else {
        return 0;
    }
}

int BSTR_Length(BitString bstr) {
	return bstr.length;
}

int BSTR_Equal(BitString bstrA, BitString bstrB) {
    int i;
    if (bstrA.length != bstrB.length) return 0;
    for (i = 0; i < bstrA.length; i++) {
        if (bstrA.bits[i] != bstrB.bits[i]) return 0;
    }
    return 1;
}