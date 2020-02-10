/* on definit ci dessous la structure d'une partie
   - un tableau d'entiers = la grille du jeu
   - un entier score
   - un booleen : 1 si la personne veut aller au dela de 2048, 0 sinon
*/

struct partie{
  int tableau[4][4];
  int score;
  int continuer;
};
typedef struct partie Partie;


/* on definit ci dessous les choix possibles pour le menu */

enum choixmenu{NOUVEAU, CHARGER, SAUVEGARDER, BEST, QUITTERMENU, NONE1};
typedef enum choixmenu Choixmenu;

/* ainsi que les choix possibles durant une partie en cours */

enum commandejeu{DROITE, GAUCHE, HAUT, BAS, MENU, QUITTERJEU, NONE2};
typedef enum commandejeu Commandejeu;

/* les prototypes */

void nouveaujeu(Partie*);
void chargerpartie(char*, Partie*);
void printscores(char*);
void printsauvegardes(char*);
void ecrirescore(char*, int);
void sauvegarderpartie(char*, Partie*);
void inserer2ou4(Partie*, int);
int estdans(Partie*, int);
void fusionnervecteur(Partie*, int, Commandejeu);
void transformer(Partie*, Commandejeu);
void restaurer(Partie*, Partie*);
int mouvtest(Partie*, Commandejeu);
int estbloque(Partie*);
Choixmenu entreetochoix(char);
Commandejeu entreetocommande(char);
void gestionnairechoix(Choixmenu, Partie*);
void gestionnairecommande(Commandejeu, Partie*);
void purger(void);
void menu(Partie*);
void jeu(Partie*);
