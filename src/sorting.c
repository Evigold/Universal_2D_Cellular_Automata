#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "bstr.h"

#include "board.h"

#define SIZE_InitRUle 18
#define SIZE_FinalRule 512
#define SIZE_BOARD 50
#define CELL_NUM 2500

void sim();

void test();

void sortAll();

void main(void) {
    // printf("here");
    
//    test();
//    sim();
sortAll();
}

void sim() {
    // FILE *file;
    // file = fopen("./file.txt", "a");
    BitString r_18;
    r_18.length = SIZE_InitRUle;
    BitString r_512;
    r_512.length = SIZE_FinalRule;
    BSTR_SetBits(&r_18, "000100000001100000");
    BSTR_HemmingWeightGenerator(r_18, &r_512, (int) log2(SIZE_FinalRule));

    BitString fixed;
    fixed.length = SIZE_FinalRule;
    BSTR_SetBits(&fixed, "00000001000101100001011101111110000101100110100001111110111010000001011001101000011111101110100001101000100000001110100010000000000101100110100001111110111010000110100010000000111010001000000001101000100000001110100010000000100000000000000010000000000000000001011001101000011111101110100001101000100000001110100010000000011010001000000011101000100000001000000000000000100000000000000001101000100000001110100010000000100000000000000010000000000000001000000000000000100000000000000000000000000000000000000000000000");
  
    BitBoard brd;
    BRD_Init(&brd, SIZE_BOARD, 7);
   
    FILE *a;
    a = fopen("a.txt", "a");
    BRD_ToFile(brd, a);
    fclose(a);
    int i = 0,loop = 0;
    BRD_Display(brd);
    while (loop < 1) {
        BRD_UpdatBoard(&brd, r_512);
        BRD_Display(brd);
        i++;
        printf("cycle: %d\n", i);
    }
}

void test() {

    int cycle = 0;
    double c, l;
    c= 0;
    l = pow(2, 18);
    BitString r_18;
    r_18.length = SIZE_InitRUle;
    BitString r_512;
    r_512.length = SIZE_FinalRule;
    BSTR_SetBits(&r_18, "000000000000000000");
    BSTR_HemmingWeightGenerator(r_18, &r_512, (int) log2(SIZE_FinalRule));

    BitBoard brd;

    BRD_Init(&brd, SIZE_BOARD, 2);
    printf("board initiated");

    // FILE *ca, *cd, *cl, *cr;
    // ca = fopen("./../results/glider_b/Group_A.txt", "a");
    // cd = fopen("./../results/glider_b/AllDie.txt", "a");
    // cl = fopen("./../results/glider_b/AllLive.txt", "a");
    // cr = fopen("./../results/glider_b/InitialState.txt", "a");



    BitString comp;
    comp.length = SIZE_InitRUle;
    BSTR_SetBits(&comp, "111111111111111111");
    
    // BRD_ToFile(brd, cr);
    printf("before start sim");
    do {
        while(cycle <= 50) {
            if (cycle == 50) {
                // BSTR_ToFile(r_18, ca);
                cycle = 0;
                break;
            }
            BRD_UpdatBoard(&brd, r_512);
            if (brd.aliveCount == 0) {
                // BSTR_ToFile(r_18, cd);
                cycle = 0;
                break;
            } else if (brd.aliveCount == CELL_NUM) {
                // BSTR_ToFile(r_18, cl);
                cycle = 0;
                break;
            
            }
            cycle ++;
        }
        c++;
        printf("percent :%% %lf\n", (double)(c/l*100));
        BSTR_AddOne(&r_18);
        BSTR_HemmingWeightGenerator(r_18, &r_512, (int) log2(SIZE_FinalRule));
        BRD_Init(&brd, SIZE_BOARD, 7);
    } while (!BSTR_Equal(r_18, comp));
    // fclose(ca);
    // fclose(cd);
    // fclose(cl);
    // fclose(cr);
}

void sortAll() {
    printf("here");
    
    int i, c = 0, cycle = 0;
    double l;
    l = pow(2, 18);
    BitString r_18;
    r_18.length = SIZE_InitRUle;
    BitString r_512;
    r_512.length = SIZE_FinalRule;
    BSTR_SetBits(&r_18, "000000000000000000");
    BSTR_HemmingWeightGenerator(r_18, &r_512, (int) log2(SIZE_FinalRule));

    BitString comp;
    comp.length = SIZE_InitRUle;
    BSTR_SetBits(&comp, "111111111111111111");
    
    BitBoard brd[9];
    BRD_Init(&brd[0], SIZE_BOARD, 1);
    BRD_Init(&brd[1], SIZE_BOARD, 1);
    BRD_Init(&brd[2], SIZE_BOARD, 2);
    BRD_Init(&brd[3], SIZE_BOARD, 2);
    BRD_Init(&brd[4], SIZE_BOARD, 2);
    BRD_Init(&brd[5], SIZE_BOARD, 2);
    BRD_Init(&brd[6], SIZE_BOARD, 4);
    BRD_Init(&brd[7], SIZE_BOARD, 4);
    
    char line[] = {"     |     |     |     |     |     |     |    |\n"};
    char *rule, **state = (char**)malloc(sizeof(char*) * 8);;
    rule = line;
    FILE *file, *boards_init;
    file = fopen("./../result/sorted.txt", "a");
    fputs("       Rule          | 75% | 75% | 50% | 50% | 50% | 50% | 25% | 25%|\n\n", file);
//"       Rule          |
    // boards_init = fopen("./../results/boards_init.txt", "a");
    // for(i = 0; i < 8; i++) {
    //     fputs("\tBoard Number  " , boards_init);
    //     char l = i%10 + '0';
    //     fputs(&l, boards_init);
    //     fputs(":\t\n",boards_init);
    //     BRD_ToFile(brd[i], boards_init);
    //     fputs("\n\n",boards_init);
    // }
    do {
        BSTR_ToFile(r_18, file);
        for(i = 0; i < 8; i++) {
            while(cycle <= 20) {
                if (cycle == 20) {
                    line[2 + 6 * i] = '2';
                    cycle = 0;
                    BRD_Rest(&brd[i]);
                    break;
                }
                BRD_UpdatBoard(&brd[i], r_512);
                if (brd[i].aliveCount == 0) {
                    line[2 + 6 * i] = '0';
                    cycle = 0;
                    break;
                } else if (brd[i].aliveCount == brd[i].dimention*brd[i].dimention) {
                    line[2 + 6 * i] =  '1';
                    cycle = 0;
                    break;
                
                }
                cycle ++;
            }
        }
        fputs(line, file);
        c++;
        if(c % 100 == 1) {
            printf("percent :%% %lf\n", (double)(c/l*100));
        }
        BSTR_AddOne(&r_18);
        BSTR_HemmingWeightGenerator(r_18, &r_512, (int) log2(SIZE_FinalRule));
    } while (!BSTR_Equal(r_18, comp));
    fclose(file);
    // fclose(boards_init);
}
