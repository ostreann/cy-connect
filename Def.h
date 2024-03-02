// Définition des constantes pour la taille de la surface de jeu
#define WIDTH_MIN 8
#define WIDTH_MAX 10
#define HEIGHT_MIN 6
#define HEIGHT_MAX 8



typedef struct {
	char color[100];
	char nom[100];
  bool winner;
} gamer;

int Inform_value(int valmin, int valmax);

int init_gamers(gamer tab[3] );

void  init_Sizetable(int *a, int *b);

void init_table(int table[HEIGHT_MAX][WIDTH_MAX],int a,int b);
 
void print_table(int table[HEIGHT_MAX][WIDTH_MAX],int a,int b, gamer tab[3]);


int init_Firstgamer(int nb_gamers);


void restore_game (int *nb_gamers, gamer tab[],int *num_gamer,int table[HEIGHT_MAX][WIDTH_MAX],int *width,int *height);


int pawn_placement(int a, int b, int table[HEIGHT_MAX][WIDTH_MAX],int num_gamer,gamer tab[3]);

void gravity_table(int table[HEIGHT_MAX][WIDTH_MAX], int a, int b, gamer tab[3],int num_gamer);
     
     
bool gamer_winner(int table[HEIGHT_MAX][WIDTH_MAX],int a, int b,gamer tab[3],int nb_gamers);


bool exist_empty_box(int table[HEIGHT_MAX][WIDTH_MAX],int a);


void Nextgamer(int *gamer,int nb_gamers );
    
    
void save_game(int nb_gamers, gamer tab[],int numgamer,int table[HEIGHT_MAX][WIDTH_MAX],int width,int height);

void print_table(int table[HEIGHT_MAX][WIDTH_MAX],int a,int b, gamer tab[3]);

int print_Size_area_rotaded(gamer tab[3],int num_gamer);

void rotated_Pawn(int area_rotated, int a, int b,int *Ligne_pivot, int *colonne_pivot, int *sens);


void pawn_gravity(int table[HEIGHT_MAX][WIDTH_MAX],int a, int b,int pion,int num_gamer,gamer tab[3]);
