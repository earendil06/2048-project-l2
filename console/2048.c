#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "2048.h"

/* les fonctions ci dessous permettent d'initialiser une partie */

void nouveaujeu(Partie* p){
  int i;
  int j;
  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      p->tableau[i][j] = 0;
    }
  }
  p->score = 0;
  p->continuer = 0;
  inserer2ou4(p, 0);
}

void chargerpartie(char* nom_fichier, Partie* p){
  int emplacement;
  FILE* f = fopen(nom_fichier, "r");
  int tab[100]; /* total de 100 int dans le fichier de sauvegarde */
  int i;
  int j;
  int k;
  printsauvegardes("sauv");
  if (f == NULL){
    printf("Le fichier %s est absent...\n", nom_fichier);
    printf("Ouverture impossible !\n");
  }
  else {
    for (i = 0; i < 100; i++){
      fscanf(f, "%d", tab + i);
    }
    do {
      printf("Choisissez un emplacement : ");
      scanf("%d", &emplacement);
      purger();
      if(!tab[20 * (emplacement - 1) + 1]){ /* 20*emplacement -19 */
	printf("Cet emplacement est vide...\n");
	emplacement = -1;
      }
    }while (emplacement < 0 || emplacement > 5);
    k = 20 * (emplacement - 1) + 2; /* 20 * emplacement -18 */
    for (i = 0 ; i < 4; i++){
      for (j = 0; j < 4; j++){
	p->tableau[i][j] = tab[k];
	k++;
      }
    }
    p->score = tab[emplacement * 20 -2];
    p->continuer = tab[emplacement * 20 -1];
    fclose(f);
  }
}

/* les fonctions printeurs */

void printjeu(Partie* p){
  int i;
  int j;
  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      if (p->tableau[i][j] != 0){
	printf("%d\t", p->tableau[i][j]);
      }
      else{
	printf("-\t");
      }
    }
    if (!i){
      printf("\tScore : %d", p->score);
    }
    printf("\n\n");
  }
}


void printscores(char* nom_fichier){
  FILE* f = fopen(nom_fichier, "r");
  int s;
  int i;
  if (f == NULL){
    printf("Le fichier %s est absent...\n", nom_fichier);
    printf("Ouverture impossible !\n");
  }
  else{
    for (i = 0; i < 10; i++){
      fscanf(f, "%d", &s);
      printf("%d\t-\t%d\n", i + 1, s);
    }
    printf("\n");
    fclose(f);
  }
}

void printsauvegardes(char* nom_fichier){
  FILE* f = fopen(nom_fichier, "r");
  int i;
  int k = 1;
  int tab[100];
  if (f == NULL){
    printf("Le fichier %s est absent...\n", nom_fichier);
    printf("Ouverture impossible !\n");
  }
  else {
    for (i = 0; i < 100; i++){
      fscanf(f, "%d", tab + i);
      if (i % 20 == 1){
	if (tab[i]){
	  printf("%d\t-\tPartie n*%d\n", k, k);
	}
	else{
	  printf("%d\t-\t--- Vide ---\n", k);
	}
	k++;
      }
    }
    printf("\n");
    fclose(f);
  }
}

/* les ecritures fichiers : inserer un score et ecrire une sauvegarde*/

void ecrirescore(char* nom_fichier, int score){
  FILE* f = fopen(nom_fichier, "r");
  int tab_scores[10] = {0};
  int i;
  int insertion = 0;
  if (f == NULL){
    printf("Le fichier %s est absent...\n", nom_fichier);
    printf("Ecriture du score impossible !");
  }
  else{
    for (i = 0; i < 10; i++){
      fscanf(f, "%d", tab_scores + i);
    }
    fclose(f);
    f = fopen(nom_fichier, "w");
    for (i = 0; i < 10; i++){
      if (i){
	fprintf(f, "\n");
      }
      if (tab_scores[i] < score && !insertion){
	fprintf(f, "%d", score);
	insertion = 1;
      }
      else {
	fprintf(f, "%d", tab_scores[i - insertion]);
      }
    }
    fclose(f);
  }
}

void sauvegarderpartie(char* nom_fichier, Partie* p){
  int emplacement = -1;
  FILE* f = fopen(nom_fichier, "r");
  int tab[100];
  int i;
  char c;
  int j;
  int k;
  for (i = 0; i < 100; i++){
    fscanf(f, "%d", tab + i);
  }
  printsauvegardes("sauv");
  while (emplacement < 0 || emplacement > 5){
    printf("Choisissez un emplacement : ");
    scanf("%d", &emplacement);
    purger();
    if(tab[20 * (emplacement - 1) + 1]){
      printf("Cet emplacement est utilise...\n");
      printf("Voulez-vous ecraser la sauvegarde existante ? (1=oui) ");
      if ((c = getchar()) != '1'){
	emplacement = -1;
      }
    }
  }
  k = 20 * (emplacement - 1) + 1; /* 20 * emplacement - 19*/
  tab[k] = 1;
  k++;
  for (i = 0 ; i < 4; i++){
    for (j = 0; j < 4; j++){
      tab[k] = p->tableau[i][j];
      k++;
    }
  }
  tab[emplacement * 20 - 2] = p->score;
  tab[emplacement * 20 - 1] = p->continuer;
  fclose(f);
  f = fopen(nom_fichier, "w");
  for (i = 0; i < 100; i++){
    fprintf(f, "%d ", tab[i]);
    if ((i+1)%20 == 0){
      fprintf(f, "\n");
    } 
  }
  fclose(f);
  printf("Partie sauvegardee !\n");
}

/* les transformations de la grille */

void inserer2ou4(Partie* p, int type){ /* type = 0 : insertion d'un 2 sinon 2 ou 4*/
  int i;
  int j;
  int r;
  do{
    i = rand()%4;
    j = rand()%4;
  }while (p->tableau[i][j]);
  if (!type){
    p->tableau[i][j] = 2;
  }
  else{
    r = rand()%10; /* sortie du 4 avec proba 1/10 */
    if (r){
      p->tableau[i][j] = 2;
    }
    else{
      p->tableau[i][j] = 4;
    }
  }
}

int estdans(Partie* p, int elt){
  int i;
  int j;
  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      if (p->tableau[i][j] == elt){
	return 1;
      }
    }
  }
  return 0;
}

void fusionnervecteur(Partie* p, int numero, Commandejeu commande){
  int tab[4] = {0,0,0,0};
  int index = 0;
  int i;
  if (commande == GAUCHE){
    for (i = 0; i < 4; i++){
      if (p->tableau[numero][i] != 0){
	tab[index] = p->tableau[numero][i];
	p->tableau[numero][i] = 0;
	index++;
      }
    }
  }
  else if (commande == DROITE){
    for (i = 0; i < 4; i++){
      if (p->tableau[numero][3 - i] != 0){
	tab[index] = p->tableau[numero][3 - i];
	p->tableau[numero][3 - i] = 0;
	index++;
      }
    }
  }
  else if (commande == HAUT){
    for (i = 0; i < 4; i++){
      if (p->tableau[i][numero] != 0){
	tab[index] = p->tableau[i][numero];
	p->tableau[i][numero] = 0;
	index++;
      }
    }
  }
  else if (commande == BAS){
    for (i = 0; i < 4; i++){
      if (p->tableau[3 - i][numero] != 0){
	tab[index] = p->tableau[3 - i][numero];
	p->tableau[3 - i][numero] = 0;
	index++;
      }
    }
  }
  for (i = 0; i < 3; i++){
    if (tab[i] == tab[i + 1] && tab[i] != 0){
      tab[i] *= 2;
      p->score += tab[i];
      tab[i + 1] = 0;
    }
  }
  index = 0;
  if (commande == GAUCHE){
    for (i = 0; i < 4; i++){
      if (tab[i] != 0){
	p->tableau[numero][index] = tab[i];
	index++;
      }
    }
  }
  else if (commande == DROITE){
    for (i = 0; i < 4; i++){
      if (tab[i] != 0){
	p->tableau[numero][3 - index] = tab[i];
	index++;
      }
    }
  }
  else if (commande == HAUT){
    for (i = 0; i < 4; i++){
      if (tab[i] != 0){
	p->tableau[index][numero] = tab[i];
	index++;
      }
    }
  }
  else if (commande == BAS){
    for (i = 0; i < 4; i++){
      if (tab[i] != 0){
	p->tableau[3 - index][numero] = tab[i];
	index++;
      }
    }
  }
}

void transformer(Partie* p, Commandejeu commande){
  int i;
  for (i = 0; i < 4; i++){
    fusionnervecteur(p, i, commande);
  }
}

void restaurer(Partie* p, Partie* rest){
  int i;
  int j;
  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      p->tableau[i][j] = rest->tableau[i][j];
    }
  }
  p->score = rest->score;
  p->continuer = rest->continuer;
}

int mouvtest(Partie* p, Commandejeu commande){
  int i;
  int j;
  Partie sauvegarde;
  Partie nouveau;
  restaurer(&sauvegarde, p);
  transformer(p, commande);
  restaurer(&nouveau, p);
  restaurer(p, &sauvegarde);
  for(i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      if (nouveau.tableau[i][j] != sauvegarde.tableau[i][j]){
	return 1;
      }
    }
  }
  return 0;
}

int estbloque(Partie* p){
  return  
    !mouvtest(p, DROITE) && 
    !mouvtest(p, GAUCHE) && 
    !mouvtest(p, HAUT) && 
    !mouvtest(p, BAS);
}

/* les convertisseurs de commande */

Choixmenu entreetochoix(char entree){
  Choixmenu c;
  c = 
    (entree == '1') ? NOUVEAU : 
    (entree == '2') ? CHARGER : 
    (entree == '3') ? SAUVEGARDER : 
    (entree == '4') ? BEST :
    (entree == '5') ? QUITTERMENU :
    NONE1;
  return c;
}

Commandejeu entreetocommande(char entree){
  Commandejeu c;
  c = 
    (entree == 'd') ? DROITE : 
    (entree == 'g') ? GAUCHE : 
    (entree == 'h') ? HAUT : 
    (entree == 'b') ? BAS : 
    (entree == 'q') ? QUITTERJEU : 
    (entree == 'm') ? MENU : 
    NONE2;
  return c;
}

/* les gestionnaires de commande */

void gestionnairechoix(Choixmenu choix, Partie* p){
  if (choix == NOUVEAU){
    nouveaujeu(p);
    printjeu(p);
    jeu(p);
  }
  else if (choix == CHARGER){
    chargerpartie("sauv", p);
    printjeu(p);
    jeu(p);
  }
  else if (choix == SAUVEGARDER){
    sauvegarderpartie("sauv", p);
    menu(p);
  }
  else if (choix == BEST){
    printscores("meilleurs_scores");
    menu(p);
  }
  else if (choix == QUITTERMENU){
    exit(0);
  }
}

void gestionnairecommande(Commandejeu commande, Partie* p){
  if (commande == HAUT || commande == BAS || commande == GAUCHE || commande == DROITE){
    if (mouvtest(p, commande)){
	transformer(p, commande);
	inserer2ou4(p, 1);
	printjeu(p);
	jeu(p);
      }
    else{
      jeu(p);
    }
  }
  else if (commande == QUITTERJEU){
    exit(0);
  }
  else if (commande == MENU){
    menu(p);
  }
  else if (commande == NONE2){
    jeu(p);
  }
}

void purger(){
   int c = 0;
   while ((c = getchar()) != '\n' && c != EOF);
}

void menu(Partie* p){
  char entree;
  Choixmenu c;
  printf("******* MENU 2048 *******\n");
  printf("*************************\n");
  printf("1 - Nouvelle partie\n");
  printf("2 - Charger une partie\n");
  printf("3 - Sauvegarder la partie\n");
  printf("4 - Meilleurs scores\n");
  printf("5 - Quitter\n\n");
  do{
    printf("Choisissez une option : ");
    scanf("%c", &entree);
    purger();
    c = entreetochoix(entree);
  }while (c == NONE1);
  printf("\n");
  gestionnairechoix(c, p);
}

void jeu(Partie* p){
  char entree;
  Commandejeu commande_entree;
  while (!estbloque(p)){
    if ((!estdans(p, 2048) && !p->continuer) || p->continuer){
      printf("Entrez une commande : ");
      scanf("%c", &entree);
      purger();
      commande_entree = entreetocommande(entree);
      gestionnairecommande(commande_entree, p);
    }
    else if (estdans(p, 2048) && !p->continuer){
      printf("Gagne ! Continuer (Oui = 1/ Non = 0) ? ");
      scanf("%d", &p->continuer);
      purger();
    }
    if (!p->continuer){
      break;
    }
  }
  printf("\n");
  if (estbloque(p)){
    if (!estdans(p, 2048) && !p->continuer){
      printf("Perdu !\n");
    }
    else if (estdans(p, 2048)){
      printf("Gagne !\n");
    }
    else if (p->continuer){
      printf("Partie terminee\n");
    }
  }
  ecrirescore("meilleurs_scores", p->score);
  menu(p);
}
  
/* --------------------------------------------------------------------
-----------------------------------------------------------------------
********************    LE JEU ***************************
-----------------------------------------------------------------*/

int main(void){
  Partie p;
  nouveaujeu(&p);
  srand(time(NULL));
  menu(&p);
  return 0;
}
