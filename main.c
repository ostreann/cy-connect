#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Def.h"

int main() {
  bool winner, tab_box;
  int width, height;
  int table[HEIGHT_MAX][WIDTH_MAX];
  int pawn;
  gamer tab[3];
  int nb_gamers;
  int gamer;
  char a[5];
  int area_rotated;
  int row_pivot;
  int column_pivot;
  int sens;
  int part ;
  printf("Bonjour\n");
  printf("Voulez-vous commencer une nouvelle partie (1) ou reprendre la "
         "dernière partie commencée (2) : ");
  part = Inform_value(1, 2);
  if (part == 1) {
    // initialisation des joueurs
    nb_gamers = init_gamers(tab);
    // determination de la dimension du tableau
    init_Sizetable(&width, &height);
    // initialisation du tableau
    init_table(table, width, height);
    system("clear");

    print_table(table, width, height, tab);
    // detemination du 1er joueur
    gamer = init_Firstgamer(nb_gamers);
  } 
  else {
    printf("restore game\n");
    restore_game(&nb_gamers, tab, &gamer, table, &width, &height);

    // system("clear");
    print_table(table, width, height, tab);
  }

  winner = false;
  tab_box = true;
  pawn = 0;
  printf("Si tu veux sauvegarder la partie une fois celle-ci commencée rentre "
         "0 comme colonne ou tu veux placer ton pion \n");

  while (winner == false && tab_box == true && pawn != -1) {
    // detemination du placement d'un pion par le joueur
    pawn = pawn_placement(width, height, table, gamer, tab);

    if (pawn != -1) {

      // gravité du tableau
      gravity_table(table, width, height, tab, gamer);

      // determination d'un vainqueur
      winner = gamer_winner(table, width, height, tab, nb_gamers);
      tab_box = exist_empty_box(table, width);
      // detemination du joueur suivant
      Nextgamer(&gamer, nb_gamers);
       
    
    } 
    else {
      // Sauvegarde de la partie

      printf("%d\n", nb_gamers);
      save_game(nb_gamers, tab, gamer, table, width, height);
    }
  }
}
