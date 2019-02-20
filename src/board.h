#ifndef BRD
#define BRD

#include "bstr.h"

#define SIZE_BRD 50

typedef struct bitBoardType {
    char bits[SIZE_BRD][SIZE_BRD];
    char initState[SIZE_BRD][SIZE_BRD];
    int dimention;
    int aliveCount;
    int initCount;
}BitBoard;

void BRD_Init(BitBoard* brd, int dim, int state);

void BRD_Rest(BitBoard* brd);

void BSTR_InitStateType(BitBoard* brd, int state);

void BRD_SetBitOn(BitBoard* brd, int row, int col);

void BRD_SetBitOff(BitBoard* brd, int row, int col);

void BRD_CopyBoard(BitBoard source, BitBoard* dest);

int BRD_Equal(BitBoard brdA, BitBoard brdB);

void BRD_Display(BitBoard brd);

void BRD_ToFile(BitBoard brd, FILE *file);

void BRD_UpdatBoard(BitBoard* brd, BitString rule);

int BRD_NeighboursNum(BitBoard brd, int row, int col);

void BRD_CopyBoard(BitBoard source, BitBoard* dest);

void BRD_RandomGenerator(BitBoard* brd);

#endif 