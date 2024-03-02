#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<ctype.h>

 

void init_table(int table[HEIGHT_MAX][WIDTH_MAX],int a,int b);
 
int init_Firstgamer(int nb_gamers);

void pawn_gravity(int table[HEIGHT_MAX][WIDTH_MAX],int a, int b,int pawn,int num_gamer,gamer tab[3]);

void gravity_table(int table[HEIGHT_MAX][WIDTH_MAX], int a, int b, gamer tab[3],int num_gamer);
     
bool gamer_winner(int table[HEIGHT_MAX][WIDTH_MAX],int a, int b,gamer tab[3], int nb_gamers);

void Nextgamer(int *gamer,int nb_gamers );
    
 
