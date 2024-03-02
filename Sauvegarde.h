#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<ctype.h>


void save_game(int nb_gamers, gamer tab[],int numgamer,int table[HEIGHT_MAX][WIDTH_MAX],int width,int height);
 
void restore_game (int *nb_gamers, gamer tab[],int *num_gamer,int table[HEIGHT_MAX][WIDTH_MAX],int *width,int *height);
