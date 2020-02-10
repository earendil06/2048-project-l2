#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk-3.0/gtk/gtk.h>
#include <cairo.h>
#include <gdk/gdkkeysyms.h>

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

enum commandejeu{DROITE, GAUCHE, HAUT, BAS, MENU, QUITTERJEU, NONE2};
typedef enum commandejeu Commandejeu;

/* les prototypes */

long int strlen(const char*);
char* ScoresToString(char*);
int NbEmplacementsSauvegarde(char*);
void AjouterEmplacementSauvegarde(char*);
int draw_callback(GtkWidget*, cairo_t*, GList*);
int on_button_press(GtkWidget*, GdkEventKey*, GList*);
void nouveaujeu(Partie*);
void ecrirescore(char*, int);
void inserer2ou4(Partie*, int);
int estdans(Partie*, int);
void fusionnervecteur(Partie*, int, Commandejeu);
void transformer(Partie*, Commandejeu);
void restaurer(Partie*, Partie*);
int mouvtest(Partie*, Commandejeu);
int estbloque(Partie*);
void OnBack(GtkWidget*, GList*);
void OnDestroy(GtkWidget*, gpointer);
void OnJeu(GtkWidget*, GList*);
void OnNew(GtkWidget*, GList*);
void OnRepr(GtkWidget*, GList*);
void OnSauv(GtkWidget*, GList*);
void OnAjouterSauv(GtkWidget*, GList*);
void OnCharge(GtkWidget*, GList*);
void OnRegles(GtkWidget*, GList*);
void OnHighScores(GtkWidget*, GList*);
void OnSauvAcc(GtkWidget*, GList*);
void OnCharAcc(GtkWidget*, GList*);

