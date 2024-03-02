#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<ctype.h>
#include"Def.h"




//fonction pour le renseignement d'une valeur entière par l'opérateur comprise entre valmin et valmax pour empecher qu'il y a des bugs si on met une lettre dans alors qu'on demande un chiffre 
int Inform_value(int valmin, int valmax){
  char str_nbre[50];
  int nbre;
  scanf("%s",str_nbre);
  nbre = atoi(str_nbre);
  while(nbre< valmin || nbre> valmax){
  printf("Erreur,la valeur doit être comprise entre %d et %d : ",valmin,valmax);
    scanf("%s",str_nbre);
    nbre = atoi(str_nbre);
  }
  return nbre;
} 
    

//fonction pour initialiser les joueurs ou on lui associe un nom et une couleur, on utilise la structure gamer dans cette fonction 
int init_gamers(gamer tab[3] ){
  char a[50];
  char surname[100];
  char color[100];
  int nb_gamers;
  printf("combien il y a t'il de joueurs (entre 2 et 3 joueurs) : ");
  nb_gamers = Inform_value(2, 3);
  for(int i=0;i<nb_gamers;i++){
    printf("joueur %d donnez votre prénom : ", i+1);
    scanf("%s", surname);
    if (i == 1) {
    // On verifie que le nom choisi n'est pas celui du premier joueur
      while (strcmp(surname,tab[0].nom)==0){
        printf("joueur %d donnez un prénom différent du premier joueur 1: ", i+1);
        scanf("%s", surname);
      }
    }
    if (i == 2) {
    // On verifie que le nom choisi n'est pas celui des deux premiers joueurs
      while (strcmp(surname,tab[0].nom)==0 || strcmp(surname,tab[1].nom)==0){
        printf ("joueur %d donnez un prénom différent des deux premiers joueurs : ", i+1);
        scanf("%s", surname);
      }
    }
    for(int j=0;j<strlen(surname)+1;j++){
      tab[i].nom[j]=surname[j];
    }
    color[0] = 0;
    while(strcmp(color,"JAUNE")!=0 && strcmp(color,"BLEU")!=0 && strcmp(color,"ROUGE")!=0 ){
      printf("%s choisissez votre couleur entre rouge jaune et bleu différente de celle des autres joueurs : ",surname);
      scanf("%s",color);
      for(int j=0;j<strlen(color);j++){
        color[j]=toupper(color[j]);
      }
      if (i == 1) {
      // On verifie que la couleur choisie n'est pas celle du premier joueur
        if (strcmp(color,tab[0].color)==0){
          color[0] = 0;
        }
      }
      if (i == 2) {
      // On verifie que la couleur choisie n'est pas celle des deux premiers joueurs
        if (strcmp(color,tab[0].color)==0 || strcmp(color,tab[1].color)==0){
          color[0] = 0;
        }
      }
    }
    for(int j=0;j<strlen(color)+1;j++){
      tab[i].color[j]=color[j];
    }
    tab[i].winner = false;
  }
  return nb_gamers ;
}

//procédure pour initialiser le tableau pour choisir la largeur et la hauteur de la surface du jeu
void  init_Sizetable(int *width, int *height){
    printf("Entrez la largeur de la surface de jeu (entre %d et %d): ", WIDTH_MIN, WIDTH_MAX);
    *width = Inform_value(WIDTH_MIN, WIDTH_MAX);
    printf("Entrez la hauteur de la surface de jeu (entre %d et %d): ", HEIGHT_MIN, HEIGHT_MAX);
    *height= Inform_value(HEIGHT_MIN, HEIGHT_MAX);
}



//fonction qui permet d'avoir les couleur jaune rouge bleu pour les joueurs
int ColorOfGamer(int num_gamer,gamer tab[3]){
  int color;
  if (strcmp(tab[num_gamer].color,"JAUNE")==0){
    color = 33;
  }
  else if (strcmp(tab[num_gamer].color,"BLEU")==0){
    color = 34;
  }
  else if (strcmp(tab[num_gamer].color,"ROUGE")==0){
    color = 31;
  }
  return color;
}



  
 
//fonction pour afficher le tableau et mettre le jeu sur un fond noir avec les murs infranchissable en blanc
void print_table(int table[HEIGHT_MAX][WIDTH_MAX],int width,int height, gamer tab[3]){
   int couleur;
   system("clear");
   for(int i=0; i<height;i++){ 
    for(int j=0;j<width;j++){
      printf("\033[40;37m+----");
    }
    printf("\033[40;37m+\n");
    for (int j = 0; j < width; j++) {
      printf("\033[40;37m|  ");
      switch (table[i][j]) {
        case 0 :
         printf("\033[40;37m");
         printf("  ");
         break;
        case 1 :
         printf("\033[40;37m");
         printf("X ");
         break;
        default :
         couleur = ColorOfGamer(table[i][j]-2,tab);
         printf("\033[40;%dm",couleur);
         printf("X ");
         break;
      }
    }
    printf("\033[40;37m| %d\n",i+1);
   }
   for (int j = 0; j < width; j++) {
      printf("\033[40;37m+----");
   }
   printf("\033[40;37m+\n");
   for (int j = 0; j < width; j++) {
      printf("\033[40;37m  %d  ", j+1);
   }
   printf("\n");
   printf("\n");
}
   

 //fonction pour la determination du placement d'un pion par le joueur qui ensuite appele la fonction pawn_gravity pour appliquer la graviter 
int pawn_placement(int width, int height, int table[HEIGHT_MAX][WIDTH_MAX],int num_gamer,gamer tab[3]){
  int pawn;
  char str_pawn[50];
  printf("%s choisis la colonne ou tu veux mettre ton pion : ",tab[num_gamer].nom);
  pawn = Inform_value(0, width);
  if (pawn > 0){
  //gravité d'un pion
    pawn_gravity(table, width, height,pawn-1,num_gamer,tab );
  }
  return pawn-1;
} 



//foction qui permet la determination de la zone et l'affichage de la largeur a pivoter que l'ordinateur chois aleatoirement entre 3 cases ou 5 cases
int print_Size_area_rotaded(gamer tab[3],int num_gamer){
  int width_swing;
  printf("l'ordinateur va choisir la largeur de la zone a pivoter\n");
  srand(time(NULL));
  width_swing=rand()%(5-3+1)+3;
  while (width_swing==4){
    width_swing=rand()%(5-3+1)+3;
  }
  printf("l'ordinateur a choisis. %s votre largeur de zone a pivoter est de %d cases\n", tab[num_gamer].nom,width_swing);
  return width_swing;
}

//determination de la case pivot et sens de rotation 
void rotated_Pawn(int area_rotated, int width, int height,int *row_pivot, int *column_pivot, int *sens){
  //ce sont les valeurs minimum ou maximale que l'on peut choisir pour la case pivot 
  int xmin= area_rotated/2+1;//exemple si l'ordinateur dit que la zone a pivoter est de 3 cases ici cela fait qu'on obtient xmin=2 puisque c'est un int donc la ligne minimum ou on pourra placer sera 2, on ne pourrait donc pas choisir la ligne 1
  int xmax=height-(area_rotated/2);//pour la colonne mac c'est la meme sauf que cela depend aussi de la hauteur
  int ymax=width-(area_rotated/2);
  int ymin=area_rotated/2+1;
  printf("choisis la ligne de la case pivot, comprise entre %d et %d ",xmin,xmax);
  *row_pivot=Inform_value(xmin,xmax);
  printf("choisis la colonne de la case pivot, comprise entre %d et %d ",ymin,ymax);
  *column_pivot=Inform_value(ymin,ymax);
  printf("dans quel sens veux tu pivoter le tableau,tape 1 pour droite et 2 pour gauche ");
  *sens=Inform_value(1,2);
}


//fonction avec un boléen qui indique la fin de la partie sans vainqueur si tout le tableau est remplie ou qu'il est impossble de jouer. Return false si le jeu est remplie 
bool exist_empty_box(int table[HEIGHT_MAX][WIDTH_MAX],int width){
  int nombre=0;
  for(int i=0;i<width;i++){
    if(table[0][i]!=0 ){
       nombre++;
    }
  }
  if(nombre==width){
    printf("le jeu est remplie. Fin de la partie");
    return false;
  }
  else{
    return true;
  }
}

