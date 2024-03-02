#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<ctype.h>
#include "Def.h"

// fonction qui restaure le jeu qui etait dans le fichier ou nous avons sauvegarder la partie avant 
void restore_game (int *nb_gamers, gamer tab[3],int *num_gamer,int table[HEIGHT_MAX][WIDTH_MAX],int *width,int *height){
  char string[100];
  FILE* file=NULL;
  file= fopen("save.txt", "r");
  fscanf(file,"%d",nb_gamers);
  for (int i = 0; i<*nb_gamers; i++){
    fscanf(file,"%s",string);
    for (int j=0;j<strlen(string)+1;j++){
      tab[i].nom[j]=string[j];
    }
    fscanf(file,"%s",string);
    for (int j=0;j<strlen(string)+1;j++){
      tab[i].color[j]=string[j];
    }
    tab[i].winner = false;
  }
  fscanf(file,"%d",num_gamer);
  fscanf(file,"%d",width);
  fscanf(file,"%d",height);
  for (int i = 0; i<*height; i++){
    for (int j = 0; j<*width; j++){
      fscanf(file,"%d",&table[i][j]);
    }
  }
  fclose(file);
}


// fonction qui permet de sauvegarder la partie en ouvrant un fichier qui va enregistrer la partie commencer 
void save_game (int nb_gamers, gamer tab[],int num_gamer,int table[HEIGHT_MAX][WIDTH_MAX],int width,int height){


  FILE* file=NULL;
  file= fopen("save.txt", "wt+");

  fprintf(file,"%d\n",nb_gamers);
  for (int i = 0; i<nb_gamers; i++)
    {
       fprintf(file,"%s\n",tab[i].nom);  
       fprintf(file,"%s\n",tab[i].color);
    }
    fprintf(file,"%d\n",num_gamer);
  
    fprintf(file,"%d\n%d\n",width, height);
   for (int i = 0; i<height; i++){
      for (int j = 0; j<width; j++){
       fprintf(file,"%d\n",table[i][j]);
       }
    }
    fclose(file);
}
