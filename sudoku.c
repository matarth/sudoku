/*
 * File:   main.cpp
 * Author: Mata
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <conio.h>

#define DIM 9][9][10
#define POSS '?'
#define IMPO '!'
#define getchar() // getc(stdin)

int su_reset_field(char[DIM] , int, int);
int su_reset_all(char[DIM]);
int su_reset_field(char[DIM], int, int);
int su_reset_poli(char[DIM], int, int);

/*
 *
 */

int pocet_reseni = 0;
char sud_solve[9][9];
int pocitacka = 0;
int pocet_cisel = 0;

//char sud[9][9][10]; // SUDOKU [RADEK] [SLOUPEC] [MOZNOSTI]

int nacteni(char sud[DIM]) { // nacte zacatecni zadani sudoku

    int ii, jj;
    char cc;
    int count = 0;

    for (jj = 0; jj < 9; jj++) {
        for (ii = 0; ii < 10; ii++) {
      //      for (;;) {
 l_nacist_znova:
                scanf("%c",&cc);
        //        printf("%d ",cc);
                if ( (cc >= '1' && cc <='9') || cc == '.' ){
                    if (cc == '.')
                        cc = '0';
                    sud[jj][ii][0] = cc;
                    count++;
                    if (cc >= '1' && cc <='9')
                        pocet_cisel++;
                }
                if (cc == 10 || cc == 13){
                    break;
                }
               if (cc == 32 || cc == 9)
                   goto l_nacist_znova;
        //    }
       //     printf("\n");
        }
    }
   // printf("\nCOUNT - %d\n",count);
    return(count);
}
void nacteni_file(char sud[DIM]){
// nacte zacatecni zadani z filu sudoku.txt
    FILE   *a1;
    int    ii;
    int    jj;
    char   str[13];

    a1 = fopen("d:\\sudoku.txt", "rb");
    for (ii = 0; ii < 9; ii++){
      if (fgets(str, 12, a1) == NULL)
        break;
      for (jj = 0; jj < 9; jj++) {
        if (str[jj] == '.')
          str[jj] = '0';
        sud[ii][jj][0] = str[jj];
      }
    }
    fclose(a1);
    return;
}

int su_found(char sud[DIM], int row, int col,int cislo) {
 // vola se kdyz se doplnuje cislo.. cislo se doplni a resetuje se cela matice

  int         kk;

  //pocitacka++;

  sud[row][col][0] = cislo+'0';
  //su_reset_field(sud,row,col);
  su_reset_poli(sud,row,col);
  return(0);
}

void vypis(char sud[DIM]) {

    int ii;
    int jj;

    for (jj = 0; jj < 9; jj++) {
        for (ii = 0; ii < 9; ii++) {
            if (ii != 8)
              printf("%c ", sud[jj][ii][0]);
            else
              printf("%c", sud[jj][ii][0]);
         }
        printf("\n");
    }

    return;
}

void sud_ini(char sud[DIM]) {
   // inicializace sudoku.. nacteni a reset

  int ii,jj,kk;

// nacteni_file(sud);
  for (ii = 0; ii < 9; ii++){
    for (jj = 0; jj < 9; jj++){
      for (kk = 1; kk < 10; kk++){
        sud[ii][jj][kk] = POSS;
      }
      if (sud[ii][jj][0] != '0')
        su_found(sud, ii, jj, sud[ii][jj][0]-'0');
    }
  }

  return;
}

int checksloupec(char sud[DIM]) {
// kontroluje dualitu cisel ve sloupci 0=OK

    int    ii;
    int    jj;
    int    kk;
    int    cislo;
    int    sloupec[10];


    for (ii = 0;ii < 9;ii++){
        for (kk = 0; kk < 10; kk++)
        sloupec[kk]=0;

        for (jj = 0; jj < 9;jj++){
          cislo = sud[jj][ii][0]-'0';
          if (sud[jj][ii][0] != '0'){
            sloupec[cislo]++;
          }
          if (sloupec[cislo] > 1)
            return(-1);
        }
    }

    return(0);
}

int checkradek(char sud[DIM]){
// kontroluje dualitu cisel v radku 0=OK
    int    ii;
    int    jj;
    int    kk;
    int    cislo;
    int    radek[10];


    for (ii = 0;ii < 9;ii++){
        for (kk = 0; kk < 10; kk++)
        radek[kk]=0;

        for (jj = 0; jj < 9;jj++){
          cislo = sud[ii][jj][0]-'0';
          if (sud[ii][jj][0] != '0'){
            radek[cislo]++;
          }
          if (radek[cislo] > 1)
            return(-1);
        }
    }

    return(0);}

int cisloctverce(int x,int y){
    int cislo;

    cislo = (((y-1)/3)*3)+((x-1)/3)+1;
    return(cislo);
}

void nastavmeze(int sq_num,int* minx,int* maxx,int* miny,int* maxy){

     switch (sq_num){
        case 1 :{
            *minx=0;
            *maxx=2;
            *miny=0;
            *maxy=2;
            break;
        }
        case 2 :{
            *minx=3;
            *maxx=5;
            *miny=0;
            *maxy=2;
            break;
        }
        case 3 :{
            *minx=6;
            *maxx=8;
            *miny=0;
            *maxy=2;
            break;
        }
        case 4 :{
            *minx=0;
            *maxx=2;
            *miny=3;
            *maxy=5;
            break;
        }
        case 5 :{
            *minx=3;
            *maxx=5;
            *miny=3;
            *maxy=5;
            break;
        }
        case 6 :{
            *minx=6;
            *maxx=8;
            *miny=3;
            *maxy=5;
            break;
        }
        case 7 :{
            *minx=0;
            *maxx=2;
            *miny=6;
            *maxy=8;
            break;
        }
        case 8 :{
            *minx=3;
            *maxx=5;
            *miny=6;
            *maxy=8;
            break;
        }
        case 9 :{
            *minx=6;
            *maxx=8;
            *miny=6;
            *maxy=8;
            break;
        }

    }


    return;
}

int checkctverec(char sud[DIM]){
//  kontroluje dualita cisel ve ctverci 0=OK

    int   ii;
    int   jj;
    int   kk;
    int   qq;
    int   cislo;
    int   minx;
    int   maxx;
    int   miny;
    int   maxy;
    int   sq_num;
    int   ctverec[10];

        for (sq_num = 1; sq_num < 10; sq_num++){
            nastavmeze(sq_num,&minx,&maxx,&miny,&maxy);
            for(ii = 0;ii < 10; ii++)
              ctverec[ii] = 0;

            for (ii = minx; ii < maxx+1; ii++){
                for (jj = miny; jj < maxy+1; jj++){
                    cislo = sud[ii][jj][0]-'0';
                    if (sud[ii][jj][0] != '0'){
                      ctverec[cislo]++;
                      if (ctverec[cislo] > 1)
                        return(-1);
                    }
                }
            }
        }


    return(0);
}

int check(char sud[DIM]){
//  check dvou stejnych cislic v radku sloupci ctverci

    if (checksloupec(sud) != 0)
      return(-1);
    if (checkradek(sud) != 0)
      return(-1);
    if (checkctverec(sud) != 0)
      return(-1);
    return(0);
}

int su_reset_all(char sud[DIM]){
    int ii,jj;

    pocitacka++;
    for(ii = 0; ii < 9; ii++)
      for (jj = 0; jj < 9; jj++)
        su_reset_field(sud, ii, jj);

    return(0);
}

int su_reset_poli(char sud[DIM],int row,int col){
// Zresetuje radek,sloupec,ctverec potom co se do sud[row][col][0] prida cislo

    int ii,jj,kk;
    int cislo;
    int sq_num;
    int minx,miny,maxx,maxy;

    // ********* RESET POLE sud[sud][row] **************
    for (kk = 1;kk < 10;kk++){
        if (kk != sud[row][col][0]-'0')
            sud[row][col][kk] = IMPO;
        else{
            sud[row][col][kk] = POSS;
            cislo = kk;
        }
    }

    // ******** RESET RADKU ******************
    for (ii = 0;ii < 9;ii++){
        if (ii != col)
          sud[row][ii][cislo] = IMPO;
    }

    // ******* RESET SLOUPCE ********************
    for (ii = 0;ii < 9;ii++){
        if (ii != row)
          sud[ii][col][cislo] = IMPO;
    }

    // ****** RESET CTVERCE ********************
    sq_num = cisloctverce(col+1,row+1);
    nastavmeze(sq_num, &minx, &maxx, &miny, &maxy);

     for (ii = miny; ii <= maxy; ii++){
      for (jj = minx; jj <= maxx; jj++){
        if (ii != row || jj != col){
            sud[ii][jj][cislo] = IMPO;
          }
        }
      }


    return(0);
}


int su_reset_field(char sud[DIM], int row, int col) {
// zkontroluje radek,ctverec a sloupec a zresetuje POSS a IMPO na sud[row][col]
    int ii,jj,kk;
    int cislo;
    int sq_num;
    int maxx,minx,miny,maxy;


    if (sud[row][col][0] != '0'){
        for (kk = 1;kk < 10;kk++){
            if (kk == (sud[row][col][0] - '0'))
                sud[row][col][kk] = POSS;
            else
                sud[row][col][kk] = IMPO;
        }
    }


 // ************ TESTOVANI RADKU *********
    for (ii = 0; ii < 9; ii++){
      if (ii != col){
        if (sud[row][ii][0] != '0'){
          cislo = sud[row][ii][0] - '0';
          sud[row][col][cislo] = IMPO;
        }
      }
    }

// ************ TESTOVANI SLOUPCE ***********
    for (ii = 0; ii < 9; ii++){
      if (ii != row){
        if (sud[ii][col][0] != '0'){
          cislo = sud[ii][col][0] - '0';
          sud[row][col][cislo] = IMPO;
        }
      }
    }

// ************ TESTOVANI CTVERECE *************
    sq_num = cisloctverce(col+1,row+1);
    nastavmeze(sq_num, &minx, &maxx, &miny, &maxy);

 //   printf("row = %d, col = %d, sq_num = %d, minx = %d, maxx = %d, miny = %d, maxy = %d\n",row,col,sq_num,minx,maxx,miny,maxy);
  //  getc(stdin);

    for (ii = miny; ii <= maxy; ii++){
      for (jj = minx; jj <= maxx; jj++){
        if (ii != row || jj != col){
          if (sud[ii][jj][0] != '0'){
            cislo = sud[ii][jj][0] - '0';
            sud[row][col][cislo] = IMPO;
          }
        }
      }
    }

    return(0);
}

int su_impo_count(char sud[DIM]){

    int ii,jj,kk;
    int count = 0;

    for(ii = 0; ii < 9; ii++)
      for (jj = 0; jj < 9; jj++)
        for (kk = 1; kk < 10; kk++)
          if (sud[ii][jj][kk] == IMPO)
            count++;

    return(count);
}

int su_test_field(char sud[DIM],int row,int col,int num){

    if (sud[row][col][num] == POSS)
        return(0);  // cislo tam muze byt
    else
        return(-1); // cislo tam nemuze byt
}

int su_test_radek(char sud[DIM],int row){
   // zjisti jestli je na radku nejaka moznost jen jednou, kdyztak ji doplni

    int ii,kk;
    int count = 0;
    int x,y;

    for (kk = 1;kk < 10;kk++){
      for(ii = 0;ii < 9;ii++){
        if (sud[row][ii][0] == '0' && su_test_field(sud,row,ii,kk) == 0){
          x = row;
          y = ii;
          count++;
        }
      }
      if (count == 1){
      //    sud[x][y][0]=kk+'0';
          su_found(sud,x,y,kk);
      }
      count = 0;
   //   su_reset_all(sud);
    }
    return(0);
}

int su_test_sloupec(char sud[DIM],int col){
    // zjisti jestli je ve sloupci nejaka moznost jen jednou, kdyztak ji doplni
    int ii,kk;
    int count=0;
    int x,y;

    for(kk = 0;kk < 10;kk++){
      for(ii = 0;ii < 9;ii++){
        if (sud[ii][col][0] == '0' && su_test_field(sud,ii,col,kk) == 0){
            x = ii;
            y = col;
            count++;
        }
      }
      if (count == 1){
 //         sud[x][y][0]=kk+'0';
          su_found(sud,x,y,kk);
      }
      count = 0;
   //   su_reset_all(sud);
    }
    return(0);
}

int su_test_ctverec(char sud[DIM],int sq_num){
    // zjisti jestli je ve ctverci nejaka moznost jen jednou, kdyztak ji doplni

    int minx,maxx,miny,maxy;
    int ii,jj,kk;
    int count = 0;
    int x,y;

    nastavmeze(sq_num,&minx,&maxx,&miny,&maxy);
    for (kk = 1; kk < 10; kk++){
      for (ii = minx;ii <= maxx;ii++){
        for(jj = miny; jj <= maxy; jj++){
          if (sud[ii][jj][0] == '0' && su_test_field(sud,ii,jj,kk) == 0){
            x = ii;
            y = jj;
            count++;
          }
        }
      }
      if (count == 1){
      //    sud[x][y][0] = kk+'0';
          su_found(sud,x,y,kk);
      }
      count = 0;
 //     su_reset_all(sud);
    }

    return(0);
}

int su_vypis_moznosti(char sud[DIM], int row,int col){
// vypise vsechny POSS moznosti na poli sud[row][col]
    int kk;

    for (kk = 1;kk < 10;kk++){
      if (sud[row][col][kk] == POSS)
          printf("%d, ",kk);
    }
    printf("\n");


    return(0);
}

int su_pocet_poss(char sud[DIM],int row, int col){

    int kk,count = 0;

    for (kk = 1;kk < 10;kk++){
        if (sud[row][col][kk] == POSS)
            count++;
    }

    return(count);
}

int su_test_one_op(char sud[DIM]){
// testuje jestli je na nejakem poli jen jedna jedina moznost, a doplni ji
    int ii,jj,kk;

    for (ii = 0;ii < 9;ii++){
      for (jj = 0;jj < 9;jj++){
          if (su_pocet_poss(sud,ii,jj) == 1){
              for (kk = 1;kk < 10;kk++){
                  if (sud[ii][jj][kk] == POSS)
                      su_found(sud,ii,jj,kk);
              }
          }
      }
    }
  //  su_reset_all(sud);

    return(0);
}

int su_test_all(char sud[DIM]){
 // kompletni test cele matice

    int ii,jj,kk;

      for(ii = 0;ii < 9;ii++){
        su_test_radek(sud,ii);
        su_test_sloupec(sud,ii);
        su_test_ctverec(sud,ii+1);
        su_test_one_op(sud);
        //su_reset_all(sud);
      }

    return(0);
}

int su_min_moznosti(char sud[DIM], int* row, int* col){
// vyhleda policko s nejmensim poctem POSS jeho souradnice vrati v argumentu a returnuje pocet
    int ii,jj;
    int minx,miny,hlp,min;

    min = 10;
    for (ii = 0;ii < 9;ii++){
      for (jj = 0;jj < 9;jj++){
        if (sud[ii][jj][0] == '0'){
          hlp = su_pocet_poss(sud,ii,jj);
        if (hlp < min){
            min = hlp;
            miny = ii;
            minx = jj;
        }
      }
    }
    *row = miny;
    *col = minx;
    }
    return(min);
}

int su_copy_cube(char sud[DIM],char sud2[DIM]){
 //  Zkopiruje sud do sud2

    int ii,jj,kk;

    for (ii = 0;ii < 9;ii++){
        for (jj = 0;jj < 9;jj++){
            for (kk = 0;kk < 10;kk++){  // Tady kk od 0 pac kopiruju uplne vsechno
                sud2[ii][jj][kk] = sud[ii][jj][kk];
            }
        }
    }


    return(0);
}

int su_shoot(char sud[DIM]){

    // REKURZE

    int x,y;
    int kk;
    int cislo;

    su_min_moznosti(sud,&x,&y);
    for (kk = 1;kk < 10;kk++){
        if (sud[x][y][kk] == POSS){
            sud[x][y][0] = kk + '0';
        }
    }
}

int su_main(char sud[DIM]){
// hlavni fce programu. testuje dokud nenajde konec a v pripade rekurze vola sama sebe
    int  old_impo,cur_impo;
    int  x,y,p;
    char sud2[DIM];
    int  kk;
    int mm,nn;

    su_reset_all(sud);

    for (;;){
        cur_impo = su_impo_count(sud);
        if (old_impo != cur_impo && cur_impo <= 648){
            old_impo = cur_impo;
            su_test_all(sud);
          //  su_reset_all(sud);
        }
        else{
            if (cur_impo == 648){
                if (pocet_reseni == 0){
                    for (mm = 0;mm < 9;mm++){
                        for (nn = 0;nn < 9;nn++){
                            sud_solve[mm][nn] = sud[mm][nn][0];
                        }
                    }
                }
                pocet_reseni++;
                break;      // NASEL RESENI BEZ REKURZE
            }
            else {
                if (su_min_moznosti(sud,&x,&y) == 0 || cur_impo > 648){   // NEMA RESENI
                    break;
                }
                else {                                       // REKURZE
                    su_min_moznosti(sud,&x,&y);
                    for (kk = 1;kk < 10;kk++){
                        if (sud[x][y][kk] == POSS){
                            su_copy_cube(sud,sud2);
                            su_found(sud2,x,y,kk);
                     /*       printf("REKURZE\n");
                            printf("min moznosti %d, na [%d, %d], strilim tam %d moznosti jsou ",su_min_moznosti(sud,&x,&y),x,y,kk);
                            su_vypis_moznosti(sud,x,y);
                            printf("\n");
                            getchar();
                            printf("Do rekurze posilam:\n");  */
                           // su_reset_all(sud2);
                            su_main(sud2);
                        }
                    }
                break;
                }
            }
        }
    }

    return(0);
}

int main(int argc, char** argv) {

    char sud[DIM];
    int vysledek;
    int load = 0;
    int ii,jj;

    printf("Zadejte sudoku:\n");

    load = nacteni(sud);

   // vypis(sud);
   // printf("\n");

    if (pocet_cisel < 17){
        printf("Nespravny vstup.\n");
        return(0);
    }

    if (load != 81){
        printf("Nespravny vstup.\n");
        return(0);
    }

    sud_ini(sud);
    if (check(sud) != 0){
      printf("Nespravny vstup.\n");
      return(0);
    }

    su_reset_all(sud);

    su_main(sud);

    if (pocet_reseni == 1){
        printf("Reseni:\n");
        for (ii = 0;ii < 9;ii++){
            for (jj = 0;jj < 9;jj++){
                if (jj != 8)
                  printf("%c ",sud_solve[ii][jj]);
                else
                  printf("%c",sud_solve[ii][jj]);

            }
            printf("\n");
        }
    }
    if (pocet_reseni > 1)
        printf("Reseni neni jednoznacne (%d variant).\n",pocet_reseni);
    if (pocet_reseni == 0)
        printf("Sudoku nema zadne reseni.\n");


    return (EXIT_SUCCESS);
}

