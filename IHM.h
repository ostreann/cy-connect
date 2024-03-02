#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<ctype.h>
 
 
int Inform_value(int valmin, int valmax);

int init_gamers(gamer tab[3] );

void  init_Sizetable(int *a, int *b);

int ColorOfGamer(int num_gamer,gamer tab[3]);

void print_table(int table[HEIGHT_MAX][WIDTH_MAX],int a,int b, gamer tab[3]);

int pawn_placement(int a, int b, int table[HEIGHT_MAX][WIDTH_MAX],int num_gamer,gamer tab[3]);

  
int print_Size_area_rotaded(gamer tab[3],int num_gamer);

void rotated_Pawn(int area_rotated, int a, int b,int *row_pivot, int *column_pivot, int *sens);


bool exist_empty_box(table[HEIGHT_MAX][WIDTH_MAX],int a);
     





