#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



#include "bstr.h"
#include "board.h"

void BRD_Init(BitBoard* brd, int dim, int state) {
    BitString b;
    int i, j;
    if (dim <= SIZE_BRD) {
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                brd->bits[i][j] = 0;
            }
        }
    }
    brd->dimention = dim;
    brd->aliveCount = 0;
    if(state == 1) {
        BRD_RandomGenerator(brd, 2);
    } else if (state > 1) {
        BRD_RandomGenerator(brd, 4);
    } else {
        BRD_RandomGenerator(brd, 0.5);
    }
    brd->initCount = brd->aliveCount;
}

void BRD_Rest(BitBoard* brd) {
    BitString b;
    int i, j;
    for (i = 0; i < brd->dimention; i++) {
        for (j = 0; j < brd->dimention; j++) {
            brd->bits[i][j] = brd->initState[i][j];
        }
    }
    brd->aliveCount = 0;
}

void BSTR_InitStateType(BitBoard* brd, int state) {
    int m, d = brd->dimention;
    m = floor(d / 2);   
    switch (state) {
        case 0:
            break;
        case 1:
            /*
                . . .
                . # .
                . . .
            */
            BRD_SetBitOn(brd, m, m);
            brd->initState[m][m] = 1;
            break;
        case 2:
            /*
                 . . .
                 . # #
                 . # #
            */
            BRD_SetBitOn(brd, m, m);
            brd->initState[m][m] = 1;
            BRD_SetBitOn(brd, m, m + 1);
            brd->initState[m][m + 1] = 1;
            BRD_SetBitOn(brd, m + 1, m);
            brd->initState[m + 1][m] = 1;
            BRD_SetBitOn(brd, m + 1, m + 1);
            brd->initState[m + 1][m + 1] = 1;
            break;
        case 3:
            /*
                # # #
                # # #
                # # #
            */
            BRD_SetBitOn(brd, m - 1, m - 1);
            brd->initState[m - 1][m - 1] = 1;
            BRD_SetBitOn(brd, m - 1, m);
            brd->initState[m - 1][m] = 1;
            BRD_SetBitOn(brd, m - 1, m + 1);
            brd->initState[m - 1][m + 1] = 1;
            
            BRD_SetBitOn(brd, m, m - 1);
            brd->initState[m][m - 1] = 1;
            BRD_SetBitOn(brd, m, m);
            brd->initState[m][m] = 1;
            BRD_SetBitOn(brd, m, m + 1);
            brd->initState[m][m + 1] = 1;
            
            BRD_SetBitOn(brd, m + 1, m - 1);
            brd->initState[m + 1][m - 1] = 1;
            BRD_SetBitOn(brd, m + 1, m);
            brd->initState[m + 1][m] = 1;
            BRD_SetBitOn(brd, m + 1, m + 1);
            brd->initState[m + 1][m + 1] = 1;
            break;
        case 4:
            /*
                # # #
                # . #
                # # #
            */
            BRD_SetBitOn(brd, m - 1, m - 1);
            brd->initState[m - 1][m - 1] = 1;
            BRD_SetBitOn(brd, m - 1, m);
            brd->initState[m - 1][m] = 1;
            BRD_SetBitOn(brd, m - 1, m + 1);
            brd->initState[m - 1][m + 1] = 1;
            
            BRD_SetBitOn(brd, m, m - 1);
            brd->initState[m][m - 1] = 1;
            BRD_SetBitOn(brd, m, m + 1);
            brd->initState[m][m + 1] = 1;
            
            BRD_SetBitOn(brd, m + 1, m - 1);
            brd->initState[m + 1][m - 1] = 1;
            BRD_SetBitOn(brd, m + 1, m);
            brd->initState[m + 1][m] = 1;
            BRD_SetBitOn(brd, m + 1, m + 1);
            brd->initState[m + 1][m + 1] = 1;
            break;
        case 5:
            BRD_RandomGenerator(brd, 1);
            break;
        case 6:
            /*
                . # .
                . # .
                . # .
            */
            BRD_SetBitOn(brd, m, m - 1);
            brd->initState[m][m - 1] = 1;
            BRD_SetBitOn(brd, m, m);
            brd->initState[m][m] = 1;
            BRD_SetBitOn(brd, m, m + 1);
            brd->initState[m][m + 1] = 1;
            break;
        case 7:
            /*
                . # .
                . . #
                # # #
            */
            BRD_SetBitOn(brd, m, m - 1);
            brd->initState[m][m - 1] = 1;
            BRD_SetBitOn(brd, m + 1, m);
            brd->initState[m + 1][m] = 1;
            BRD_SetBitOn(brd, m - 1, m + 1);
            brd->initState[m - 1][m + 1] = 1;
            BRD_SetBitOn(brd, m, m + 1);
            brd->initState[m][m + 1] = 1;
            BRD_SetBitOn(brd, m+ 1, m + 1);
            brd->initState[m + 1][m + 1] = 1;
            break;
    }
}

void BRD_SetBitOn(BitBoard* brd, int row, int col) {
    if(row < brd->dimention && col < brd->dimention) {
        brd->bits[row][col] = 1;
        brd->aliveCount ++;
    }
}

void BRD_SetBitOff(BitBoard* brd, int row, int col) {
    if(row < brd->dimention && col < brd->dimention) {
        brd->bits[row][col] =0;
        brd->aliveCount --;
    }
}

int BRD_Equal(BitBoard brdA, BitBoard brdB) {
    int i, j, d = brdA.dimention;
    if (d != brdB.dimention) return 0;
    if (brdA.aliveCount != brdB.aliveCount) return 0;
    for (i = 0; i < d; i++) {
        for (j = 0; j < d; j++) {
            if (brdA.bits[i][j] != brdB.bits[i][j]) return 0;
        }
    }
    return 1;
}

void BRD_Display(BitBoard brd) {
    int i, j, d = brd.dimention;
    for (i = 0; i < d; i++) {
        printf("|");
        for (j = 0; j < d; j++) {
            if (brd.bits[i][j] == 0)    printf(" . ");
	        else	printf(" # ");
	    }
        printf("|\n");
    }
    printf("\nTotal Alive Cells: %d\n", brd.aliveCount);
}

void BRD_ToFile(BitBoard brd, FILE *file) {
    int i, j, l, d = brd.dimention;
    for (i = 0; i < d; i++) {
        fputs("|", file);
        for (j = 0; j < d; j++) {
            if (brd.bits[i][j] == 0)    fputs(" . ", file);
	        else	fputs(" # ", file);
	    }
        fputs("|\n", file);
    }
    char liveCount[] = "\nTotal Alive Cells:       ";
    l=brd.aliveCount;
    char *buf = liveCount + 24;
    for (; l; l /= 10)  *--buf = l % 10 + '0';
    fputs(liveCount,  file);
}

void BRD_UpdatBoard(BitBoard* brd, BitString rule) {
    int d, i, j, neib, aliveCnt;
    d = brd->dimention;
    BitBoard temp;
    temp.dimention = d;
    temp.aliveCount = 0;

    for (i = 0; i < d; i++) {
        for (j = 0; j < d; j++) {
            neib = BRD_NeighboursNum(*brd, i, j);
            if (rule.bits[neib]) {
                temp.bits[i][j] = 1;
                temp.aliveCount ++;
            } else  temp.bits[i][j] = 0; 
        }
    }
    BRD_CopyBoard(temp, brd);
}

int BRD_NeighboursNum(BitBoard brd, int row, int col) {
    int i, j, d, neib = 0, bitInd = 8;
    d = brd.dimention;
    for (i = row + -1; i < row + 2; i++) {
        for (j = col + -1; j < col + 2; j++) {
            if (i < d && j < d && i >= 0 && j >= 0) {
                if(brd.bits[i][j])  neib += pow(2, bitInd);
                bitInd--;
            }
        }
    }
    return neib;
}

void BRD_CopyBoard(BitBoard source, BitBoard* dest) {
    int i, j, d = source.dimention;
    if (d == dest->dimention) {
        for (i = 0; i < d; i++) {
            for (j = 0; j < d; j++) {
                dest->bits[i][j] = source.bits[i][j];
            }
        }
        dest->aliveCount = source.aliveCount;
    }
}

void BRD_RandomGenerator(BitBoard* brd, double chnc) {
    int i, j, r, d = brd->dimention;
    srand((unsigned) time(NULL));
    for (i = 0; i < d; i++) {
        for (j = 0; j < d; j++) {
            r = (rand() % (int)chnc);
            if (r) {
                brd->bits[i][j] = 1;
                brd->initState[i][j] = 1;
                brd->aliveCount ++;
            }
        }
    }
}