#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<ctype.h>
#include"Def.h" 


//fonction ou on intialise le tableau avec les case vide et aussi placer les murs infranchissables
void init_table(int table[HEIGHT_MAX][WIDTH_MAX],int width,int height){
  for(int i=0; i<height;i++){
    for(int j=0;j<width;j++){
      table[i][j]=0;
    }
  }
  table[0][0]=1;
  table[0][width-1]=1;
  table[height-1][0]=1;
  table[height-1][width-1]=1;
}

// fonction qui detemine le 1er joueur qui va jouer. On a décider que c'etait l'ordinateur qui allait choisir au hasard le premier joueur qui joue 
int init_Firstgamer(int nb_gamers){
  int first_gamer;
  printf("l'ordinateur va choisir au hasard le premier joueur qui joue\n");
  srand(time(NULL));
  if (nb_gamers==2){
     first_gamer=rand()%(1)+1;
  }
  if (nb_gamers==3){
      first_gamer=rand()%(2)+1;
  }
  return first_gamer;
}



 
//fonction pour appliquer la graviter quand on place un pion et ou utilise la foction print_table pour avoir une impression d'avoir un vrai pion qui tombe avec la gravité
void  pawn_gravity(int table[HEIGHT_MAX][WIDTH_MAX],int width, int height,int pawn,int num_gamer,gamer tab[3]){
  int p=-1;
  if(table[p+1][pawn]==1){
    printf("erreur il y a un mur infranchissable, choisissez une autre colonne\n \n");
    pawn_placement(width, height, table, num_gamer,  tab);
  }
  if(table[p+1][pawn]==2 ||table[p+1][pawn]==3 || table[p+1][pawn]==4){
    printf("toute la colonne est deja remplie, choisissez une autre colonne\n \n");
    pawn_placement(width, height, table, num_gamer,  tab);
  }
  while(p<height-1 && table[p+1][pawn]==0){
    p++; 
    if (p!=-1){
        table[p][pawn]=num_gamer+2;
    }
    print_table(table, width,height,tab);
    usleep(100000);
    if (p!=-1){
      table[p][pawn]=0;
    }
  }
  if (p!=-1){
    table[p][pawn]=num_gamer+2;
  }
  print_table(table, width,height,tab);
  usleep(100000);
}

 






//fonction ou on regarde si la case pivot du joueur choisis est possible. Ensuite cette fonction va executer la rotation des pions ou des lurs infranchissable, enfin cette fonction applique la gravité apres la rotation des pions gravité.
void gravity_table(int table[HEIGHT_MAX][WIDTH_MAX], int width, int height, gamer tab[3],int num_gamer){
  int area_rotated, row_pivot,  column_pivot, sens;
  int num_col,num_row;
  int num_col_rotated,num_row_rotated;
  int imaginary_table[HEIGHT_MAX][WIDTH_MAX];
  int delta;
    // determination  et affichage de la taille a pivoter par l'orinateur
  area_rotated=print_Size_area_rotaded(tab,num_gamer);
  delta = area_rotated/2;
  bool empty_cell = true;
  while(empty_cell==true){
  // determination de la case pivot et sens de rotation par le joueur
    rotated_Pawn(area_rotated,width,height,&row_pivot,&column_pivot,&sens);
    for(num_row=row_pivot-delta;num_row<row_pivot+delta+1;num_row++){
      for(num_col=column_pivot-delta;num_col<column_pivot+delta+1;num_col++){ 
        if (table[num_row-1][num_col-1]!=0){
          empty_cell = false;
        }
      }
    }
    if (empty_cell == true){
      printf("Erreur tu dois choisir une zone de rotation contenat un pion ou un mur infranchissable\n");
    }
  }
  if (sens==1){
    num_row_rotated = 1;
    for(num_col=column_pivot-delta;num_col<column_pivot+delta+1;num_col++){ 
      num_col_rotated = area_rotated;
      for(num_row=row_pivot-delta;num_row<row_pivot+delta+1;num_row++){
        imaginary_table[num_row_rotated-1][num_col_rotated-1]=table[num_row-1][num_col-1];
        num_col_rotated--;
      }
      num_row_rotated++;
    }
  }
  else if (sens == 2){
    num_row_rotated = area_rotated;
    for(num_col=column_pivot-delta;num_col<column_pivot+delta+1;num_col++){ 
      num_col_rotated = 1;
      for(num_row=row_pivot-delta;num_row<row_pivot+delta+1;num_row++){
        imaginary_table[num_row_rotated-1][num_col_rotated-1]=table[num_row-1][num_col-1];
        num_col_rotated++;
      }
      num_row_rotated--;
    }
        
  }
  // Réécriture de la zone tournée dans la table
  num_col_rotated = 1;
    for(num_col=column_pivot-delta;num_col<column_pivot+delta+1;num_col++){ 
      num_row_rotated = 1;
      for(num_row=row_pivot-delta;num_row<row_pivot+delta+1;num_row++){
        table[num_row-1][num_col-1]=imaginary_table[num_row_rotated-1][num_col_rotated-1];
        num_row_rotated++;
      }
      num_col_rotated++;
    }
    print_table(table,width,height,tab);
    usleep(100000);
    // ensuite application de la gravité
    int nb_modification=1;
    while(nb_modification>0){
      nb_modification = 0;
      for(int ligne=height-2;ligne>0;ligne-- ){
        for(int colonne=0;colonne<=width-1;colonne++){
          if(table[ligne+1][colonne]==0 && table[ligne][colonne] > 1){
            table[ligne+1][colonne]=table[ligne][colonne];
            table[ligne][colonne]=0;
            nb_modification++;
          }
        }
      }
      print_table(table, width,height,tab);
      usleep(100000);
    }
}



//fonction pour savoir si il y a un gagnant donc qu'il y a 5 piece aligné soit verticalement soit horizontalement ou bien en diagonales
bool gamer_winner(int table[HEIGHT_MAX][WIDTH_MAX],int width, int height,gamer tab[3], int nb_gamers){
int nb_winner;
int winner;
int imaginary_table[5][5];

	

  //ici on crée un table_imaginaire qui va parcourir tout le tableau pour determiner si il y a un gagnant
  for(int i=0;i<height-4;i++){
   for(int j=0;j<width-4;j++){
     for(int k=0;k<5;k++){
       for(int l=0;l<5;l++){
         imaginary_table[k][l]=table[k+i][l+j];
        }
      }
      for(int k=0;k<5;k++){
        //avec la table imaginaire ici on determine tout les possibilité qu'il y a un gagnant avec les pieces alignée horizontalement
       if(imaginary_table[k][0]==imaginary_table[k][1] &&
              imaginary_table[k][0]==imaginary_table[k][2] &&
              imaginary_table[k][0]==imaginary_table[k][3] &&
              imaginary_table[k][0]==imaginary_table[k][4] && 
              imaginary_table[k][0] < 5 && imaginary_table[k][0]>1){
                winner= imaginary_table[k][0] - 2;
                tab[winner].winner = true;
                
        }
      }
      for(int l=0;l<5;l++){
         //avec la table imaginaire ici on determine tout les possibilité qu'il y a un gagnant avec les pieces alignée verticalement
       if(imaginary_table[0][l]==imaginary_table[1][l] &&
              imaginary_table[0][l]==imaginary_table[2][l] &&
              imaginary_table[0][l]==imaginary_table[3][l] &&
              imaginary_table[0][l]==imaginary_table[4][l]&& 
              imaginary_table[0][l] < 5 && imaginary_table[0][l]>1){
                winner= imaginary_table[0][l] - 2;
                tab[winner].winner = true;
              
        }
      }
       //avec la table imaginaire ici on determine tout les possibilité qu'il y a un gagnant avec les pieces alignée à la diagonales
      if(imaginary_table[0][0]==imaginary_table[1][1] &&
              imaginary_table[0][0]==imaginary_table[2][2] &&
              imaginary_table[0][0]==imaginary_table[3][3] &&
              imaginary_table[0][0]==imaginary_table[4][4]&& 
              imaginary_table[0][0] < 5 && imaginary_table[0][0]>1){
                winner= imaginary_table[0][0] - 2;
                tab[winner].winner = true;
                  
      }
      //avec la table imaginaire ici on determine tout les possibilité qu'il y a un gagnant avec les pieces alignée à la diagonales
      if(imaginary_table[0][4]==imaginary_table[1][3] &&
              imaginary_table[0][4]==imaginary_table[2][2] &&
              imaginary_table[0][4]==imaginary_table[3][1] &&
              imaginary_table[0][4]==imaginary_table[4][0]&& 
              imaginary_table[0][4] < 5 && imaginary_table[0][4]>1){
                winner= imaginary_table[0][4] - 2;
                tab[winner].winner = true;
                
      }
          
    }
  }
 
  nb_winner = 0;
  for(int t=0;t<nb_gamers;t++){
    if (tab[t].winner == true) {
     nb_winner++;
    }
  }
  if (nb_winner == 1){
    for(int t=0;t<nb_gamers;t++){
      if (tab[t].winner == true) {
        printf("le gagnant est : %s\n", tab[t].nom);
      }
    }
  }
  else if(nb_winner > 1){
    printf("les gagnants sont : " );
    for(int t=0;t<nb_gamers;t++){
      if (tab[t].winner == true) {
        printf("%s", tab[t].nom);
      }
      printf("\n" );
    }  
  }
 
  if (nb_winner >0)
    return true;
    else return false;
    
  }
// procedure pour determiner le joueur suivant avec des pointeurs car on ne peut pas retourner tout sinon
void Nextgamer(int *gamer,int nb_gamers ){
  if (nb_gamers==2){
     if(*gamer==0){
        *gamer=1;
      }
      else{
        *gamer=0;
      }
  }
  if (nb_gamers==3){
    if(*gamer==0){
       *gamer=1;
    }
    else if(*gamer==1){
       *gamer=2;
    }
    else{
      *gamer=0;
    }
  }
  
}
  
  
