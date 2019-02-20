#ifndef BSTR
#define BSTR

#define MAXBITS  512


typedef struct bitStringType {
    char bits[MAXBITS];
	int length;
}BitString;  

/* bits is a c-string (array of ascii codes ending with 0). */
/* It should be made of 0's and 1's - "0110" for example. */
/* Those characters are converted to a similar set of 0's and 1's */
/* in the bitstring.  "0" is replace by 0, "1" is replaced by 1. */
void BSTR_SetBits(BitString* bstr, char* bits);

void BSTR_SetBit(BitString* bstr, int bit, int index);

void BSTR_HemmingWeightGenerator(BitString source, BitString* dest, int wordSise);

void BSTR_SetValue(BitString* bstr, int n, int size);

/* flips all bits */
void BSTR_Invert(BitString *bstr);

/* adds one to the binary number treating it as unsigned */
void BSTR_AddOne(BitString *bstr);

//* Returns the value of the bit at the index.
int BSTR_GetBitValue(BitString bstr, int index);

/* prints out the bit string.  If the second parameter is true (1), */
/* then there is a blank after every 4 bits for easy reading. */
void BSTR_Display(BitString bstr, int fourGrouping);

void BSTR_ToFile(BitString bstr, FILE* file);

/* returns the length of the bistring (i.e. the number of bits) */
int BSTR_Length(BitString bstr);

int BSTR_Equal(BitString a, BitString b);

#endif