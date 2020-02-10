#include "2048.h"

int main(int argc, char** argv){
  /* initialisation des composants */
  Partie p;
  
  /* Les fenetres et containers */
  GtkWidget* main_fenetre;
  GtkWidget* grid;
  GtkWidget* frame1;
  GtkWidget* gridframe1;
  GtkWidget* frame2;
  GtkWidget* gridframe2;
  GtkWidget* frame3;
  GtkWidget* gridframe3;
  GtkWidget* frame4;
  GtkWidget* gridframe4;
  GtkWidget* frame5;
  GtkWidget* gridframe5;
  GtkWidget* frame6;
  GtkWidget* gridframe6;
  GtkWidget* grillescoresDG;

  /* l'image 2048 (header) de l'application */
  GtkWidget* img2048;

  /* les boutons de l'application (toutes fenetres confondues) */
  GtkWidget* bouton_new;
  GtkWidget* bouton_reprendre;
  GtkWidget* bouton_sauv;
  GtkWidget* bouton_char;
  GtkWidget* bouton_scores;
  GtkWidget* bouton_quit;
  GtkWidget* bouton_regles;
  GtkWidget* bouton_sauvaccepter;
  GtkWidget* bouton_characcepter;
  GtkWidget* bouton_ajoutersauv;
  GtkWidget* bouton_retour1;
  GtkWidget* bouton_retour2;
  GtkWidget* bouton_retour3;
  GtkWidget* bouton_retour4;
  GtkWidget* bouton_retour5;

  /* les labels */
  GtkWidget* labelordrescores;
  GtkWidget* labelbestscores;
  GtkWidget* labelscorepartie;

  /* itembox */
  GtkWidget* listboxsauv;
  GtkWidget* listboxchar;

  /* grille du jeu */
  GtkWidget* canvas;

  /* les boite pour les regles du jeu */
  GtkWidget* textregles;
  GtkTextBuffer* buffer;

  /* la liste des fenetres 
     utilise pour le passage en parametre de chaque fenetre */
  GList* Lst;

  /* les elements css */
  GError *error = NULL;
  GtkCssProvider *cssprovider;
  GFile *file;


  /***********************************************************************/
  /*************************** debut du la GUI ***************************/

  gtk_init(&argc, &argv);
  srand(time(NULL));

  main_fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(main_fenetre), "2048");
  gtk_window_set_position(GTK_WINDOW(main_fenetre), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable(GTK_WINDOW(main_fenetre), FALSE);
  gtk_widget_set_size_request(main_fenetre, 450, 500);


  grid = gtk_table_new(2, 1, FALSE);
  gtk_container_add(GTK_CONTAINER(main_fenetre), GTK_WIDGET(grid));

  img2048 = gtk_image_new_from_file("./2048.png");
  gtk_table_attach(GTK_TABLE(grid), img2048, 0, 1, 0, 1,  GTK_FILL, GTK_FILL, 0, 0);
  

  /* frame du menu principal contenant les boutons de navigation */


  frame1 = gtk_frame_new("Menu Principal");
  gtk_table_attach(GTK_TABLE(grid), frame1, 0, 1, 1, 2, GTK_FILL, GTK_FILL | GTK_EXPAND, 0, 0);
  gridframe1 = gtk_table_new(7, 1, TRUE);
  gtk_container_add(GTK_CONTAINER(frame1), gridframe1);
  bouton_new = gtk_button_new_with_label("Nouvelle partie");
  gtk_table_attach(GTK_TABLE(gridframe1), bouton_new, 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_reprendre = gtk_button_new_with_label("Reprendre la partie");
  gtk_table_attach(GTK_TABLE(gridframe1), bouton_reprendre, 0, 1, 1, 2, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_char = gtk_button_new_with_label("Charger une partie");
  gtk_table_attach(GTK_TABLE(gridframe1), bouton_char, 0, 1, 2, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_sauv = gtk_button_new_with_label("Sauvegarder la partie");
  gtk_table_attach(GTK_TABLE(gridframe1), bouton_sauv, 0, 1, 3, 4, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_scores = gtk_button_new_with_label("Meilleurs scores");
  gtk_table_attach(GTK_TABLE(gridframe1), bouton_scores, 0, 1, 4, 5, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_regles = gtk_button_new_with_label("Règles du jeu");
  gtk_table_attach(GTK_TABLE(gridframe1), bouton_regles, 0, 1, 5, 6, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_quit = gtk_button_new_with_label("Quitter le jeu");
  gtk_table_attach(GTK_TABLE(gridframe1), bouton_quit, 0, 1, 6, 7, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);

  gtk_widget_set_sensitive(bouton_reprendre, FALSE);
  gtk_widget_set_sensitive(bouton_sauv, FALSE);



  /* frame affichant les meilleurs scores */


  frame2 = gtk_frame_new("Meilleurs scores");
  gridframe2 = gtk_table_new(2, 1, TRUE);
  grillescoresDG = gtk_table_new(1, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(frame2), gridframe2);
  labelbestscores = gtk_label_new("");
  labelordrescores = gtk_label_new("1\t------------>\t\t\n"
				   "2\t------------>\t\t\n"
				   "3\t------------>\t\t\n"
				   "4\t------------>\t\t\n"
				   "5\t------------>\t\t\n"
				   "6\t------------>\t\t\n"
				   "7\t------------>\t\t\n"
				   "8\t------------>\t\t\n"
				   "9\t------------>\t\t\n"
				   "10\t------------>\t\t");
  gtk_table_attach(GTK_TABLE(gridframe2), grillescoresDG, 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
  gtk_table_attach(GTK_TABLE(grillescoresDG), labelordrescores, 0, 1, 0, 1, GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
  gtk_table_attach(GTK_TABLE(grillescoresDG), labelbestscores, 1, 2, 0, 1, GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
  bouton_retour1 = gtk_button_new_with_label("Menu Principal");
  gtk_table_attach(GTK_TABLE(gridframe2), bouton_retour1, 0, 1, 1, 2, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);



  /* frame de gestion de sauvegarde */


  frame3 = gtk_frame_new("Sauvegarder la partie");
  gridframe3 = gtk_table_new(4, 1, TRUE);
  gtk_container_add(GTK_CONTAINER(frame3), gridframe3);
  listboxsauv = gtk_combo_box_text_new();
  gtk_table_attach(GTK_TABLE(gridframe3), listboxsauv, 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_ajoutersauv = gtk_button_new_with_label("Ajouter un emplacement");
  gtk_table_attach(GTK_TABLE(gridframe3), bouton_ajoutersauv, 0, 1, 1, 2, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_sauvaccepter = gtk_button_new_with_label("Sauvegarder");
  gtk_table_attach(GTK_TABLE(gridframe3), bouton_sauvaccepter, 0, 1, 2, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_retour2 = gtk_button_new_with_label("Menu Principal");
  gtk_table_attach(GTK_TABLE(gridframe3), bouton_retour2, 0, 1, 3, 4, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);



  /* frame de chargement d'une partie sauvegarde au prealable */


  frame4 = gtk_frame_new("Charger une partie");
  gridframe4 = gtk_table_new(3, 1, TRUE);
  gtk_container_add(GTK_CONTAINER(frame4), gridframe4);
  listboxchar = gtk_combo_box_text_new();
  gtk_table_attach(GTK_TABLE(gridframe4), listboxchar, 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_characcepter = gtk_button_new_with_label("Charger");
  gtk_table_attach(GTK_TABLE(gridframe4), bouton_characcepter, 0, 1, 1, 2, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  bouton_retour3 = gtk_button_new_with_label("Menu Principal");
  gtk_table_attach(GTK_TABLE(gridframe4), bouton_retour3, 0, 1, 2, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);



  /* frame de l'interface de jeu */


  frame5 = gtk_frame_new("Partie - 2048");
  gridframe5 = gtk_table_new(3, 1, FALSE);
  gtk_container_add(GTK_CONTAINER(frame5), gridframe5);
  canvas = gtk_drawing_area_new();
  gtk_widget_set_size_request(canvas, 400, 400);
  gtk_table_attach(GTK_TABLE(gridframe5), canvas, 0, 1, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0);
  labelscorepartie = gtk_label_new("Score : 0");
  gtk_table_attach(GTK_TABLE(gridframe5), labelscorepartie, 0, 1, 1, 2, GTK_EXPAND, GTK_EXPAND, 0, 0);
  bouton_retour4 = gtk_button_new_with_label("Menu Principal");
  gtk_table_attach(GTK_TABLE(gridframe5), bouton_retour4, 0, 1, 2, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);  



  /* frame contenant les regles du jeu */


  frame6 = gtk_frame_new("Règles du jeu");
  gridframe6 = gtk_table_new(2, 1, FALSE);
  gtk_container_add(GTK_CONTAINER(frame6), gridframe6);
  textregles = gtk_text_view_new();
  gtk_table_attach(GTK_TABLE(gridframe6), textregles, 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
  bouton_retour5 = gtk_button_new_with_label("Menu Principal");
  gtk_table_attach(GTK_TABLE(gridframe6), bouton_retour5, 0, 1, 1, 2, GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(textregles), FALSE);
  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textregles), FALSE);
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textregles));
  gtk_text_buffer_insert_at_cursor(buffer, "\n\nBienvenue sur le jeu 2048 !\n\nBut du jeu :\nAssociez les cases de même nombre afin\nd'obtenir une case portant le nombre 2048.\nVous pouvez continuer au-delà !\n\nCommandes :\nUtilisez les flèches directionnelles pour\nles mouvements haut, bas, gauche et droite.", 259); 


  /* Lst est une liste chainee permettant de passer en parametre a une fonction tous les elements necessaires lors du signal pressed d'un bouton */
				   
  Lst = NULL;
  Lst = g_list_append(Lst, main_fenetre);
  Lst = g_list_append(Lst, grid);
  Lst = g_list_append(Lst, frame1);
  Lst = g_list_append(Lst, frame2);
  Lst = g_list_append(Lst, frame3);
  Lst = g_list_append(Lst, frame4);
  Lst = g_list_append(Lst, frame5);
  Lst = g_list_append(Lst, &p);
  Lst = g_list_append(Lst, frame6);



  /* on applique notre theme ici */

  file = g_file_new_for_path ("./gtkstyle.css");
  cssprovider = gtk_css_provider_new ();
  if (!gtk_css_provider_load_from_file (cssprovider, file, &error))
    {
      g_printerr ("%s\n", error->message);
      exit (error->code);
    }
  gtk_style_context_add_provider_for_screen (gdk_display_get_default_screen (gtk_widget_get_display (main_fenetre)), GTK_STYLE_PROVIDER (cssprovider), GTK_STYLE_PROVIDER_PRIORITY_USER);
 


  /* on associe ici tous les evenements de la GUI a une fonction */

  g_signal_connect(G_OBJECT(main_fenetre), "key-press-event", G_CALLBACK(on_button_press), Lst);
  g_signal_connect (G_OBJECT (canvas), "draw", G_CALLBACK (draw_callback), Lst);
  g_signal_connect(G_OBJECT(main_fenetre), "destroy", G_CALLBACK(OnDestroy), NULL);
  g_signal_connect(G_OBJECT(bouton_quit), "clicked", G_CALLBACK(OnDestroy), NULL);
  g_signal_connect(G_OBJECT(bouton_new), "clicked", G_CALLBACK(OnNew), Lst);
  g_signal_connect(G_OBJECT(bouton_reprendre), "clicked", G_CALLBACK(OnRepr), Lst);
  g_signal_connect(G_OBJECT(bouton_scores), "clicked", G_CALLBACK(OnHighScores), Lst);
  g_signal_connect(G_OBJECT(bouton_regles), "clicked", G_CALLBACK(OnRegles), Lst);
  g_signal_connect(G_OBJECT(bouton_sauv), "clicked", G_CALLBACK(OnSauv), Lst);
  g_signal_connect(G_OBJECT(bouton_sauvaccepter), "clicked", G_CALLBACK(OnSauvAcc), Lst);
  g_signal_connect(G_OBJECT(bouton_characcepter), "clicked", G_CALLBACK(OnCharAcc), Lst);
  g_signal_connect(G_OBJECT(bouton_char), "clicked", G_CALLBACK(OnCharge), Lst);
  g_signal_connect(G_OBJECT(bouton_retour1), "clicked", G_CALLBACK(OnBack), Lst);
  g_signal_connect(G_OBJECT(bouton_retour2), "clicked", G_CALLBACK(OnBack), Lst);
  g_signal_connect(G_OBJECT(bouton_retour3), "clicked", G_CALLBACK(OnBack), Lst);
  g_signal_connect(G_OBJECT(bouton_retour4), "clicked", G_CALLBACK(OnBack), Lst);
  g_signal_connect(G_OBJECT(bouton_retour5), "clicked", G_CALLBACK(OnBack), Lst);
  g_signal_connect(G_OBJECT(bouton_ajoutersauv), "clicked", G_CALLBACK(OnAjouterSauv), Lst);

  gtk_widget_show_all(main_fenetre);
  gtk_main();
  g_object_unref (G_OBJECT (cssprovider));
  return EXIT_SUCCESS;
}
/******************************************************************/
/********************* les fonctions utilisees ********************/

/* cette fonction renvoie la longueur d'une chaine de caractere */

long int strlen(const char* str){
  int i = 0;
  while (*str++){
    i++;
  }
  return i;
}

/* cette fonction initialise a des valeurs par defaut une partie */

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

/* cette fonction permet d'inscrire (si possible) un score dans le fichier des scores */

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



/* lors de chaque evenement clavier du jeu, cette fonction genere aleatoirement un 2 ou un 4 dans la grille du jeu */

void inserer2ou4(Partie* p, int type){ /*type = 0: insertion d'un 2 sinon 2 ou 4*/
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



/* cette fonction verifie si un nombre est dans la grille du jeu */

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



/* fonctions de transformation de jeu */

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


/* cette fonction effectue une copie d'une partie p1 dans une partie p2 */

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



/* ces deux fonction permettent de determiner si un mouvement est possible ou si le jeu est bloque */

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



/* cette fonction renvoie le contenu d'un fichier sous forme de string */


char* ScoresToString(char* nom_fichier){
  int length;
  char* str;
  FILE* f;
  f = fopen(nom_fichier, "r");
  if(f == NULL){
    return NULL;
  }
  fseek(f, 0, SEEK_END);
  length = ftell(f);
  fseek(f, 0, SEEK_SET);
  str = malloc(length * sizeof(char));
  if (str){
    fread (str, 1, length, f);
  }
  fclose (f);
  return str;
}


/* renvoie le nombre d'emplacements de sauvegarde */

int NbEmplacementsSauvegarde(char* fichier){
  int nb = 0;
  char c;
  FILE* f;
  f = fopen(fichier, "r");
  while ((c = fgetc(f)) != EOF){
    if (c == '\n'){
      nb++;
    }
  }
  fclose(f);
  return nb;
}



/* ajoute un emplacement de sauvegarde dans le fichier */

void AjouterEmplacementSauvegarde(char* fichier){
  char c;
  FILE* f;
  int nb = NbEmplacementsSauvegarde(fichier);
  f = fopen(fichier, "a");
  while ((c = fgetc(f)) != EOF){
    continue;
  }
  fprintf(f, "%d 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n", nb + 1);
  fclose(f);
}



/***********************************************************************/
/********************** fonctions evenementielles **********************/


void OnBack(GtkWidget* pWidget, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst,0);
  GtkWidget* grid = g_list_nth_data(Lst,1);
  GtkWidget* framemenu = g_list_nth_data(Lst,2);
  GList* L = gtk_container_get_children(GTK_CONTAINER(grid));
  GtkWidget* frameactuelle = g_list_nth_data(L,0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(framemenu));
  GtkWidget* grille = g_list_nth_data(L2, 0);
  GList* L3 = gtk_container_get_children(GTK_CONTAINER(grille));
  GtkWidget* bouton1 = g_list_nth_data(L3, 5);
  GtkWidget* bouton2 = g_list_nth_data(L3, 3);
  Partie* p = g_list_nth_data(Lst,7);
  g_object_ref(G_OBJECT(frameactuelle));
  gtk_container_remove(GTK_CONTAINER(grid), frameactuelle);
  gtk_table_attach(GTK_TABLE(grid), framemenu, 0, 1, 1, 2, GTK_FILL, GTK_FILL | GTK_EXPAND, 0, 0);
  if (estdans(p, 4) || estdans(p, 2)){
    gtk_widget_set_sensitive(bouton1, TRUE);
    gtk_widget_set_sensitive(bouton2, TRUE);
  }
  gtk_widget_show_all(mainfenetre);
}

int draw_callback (GtkWidget *widget, cairo_t *cr, GList* Lst){
  guint width, height;
  GdkRGBA color;
  char str[5];
  int elt;
  int i;
  int j;
  cairo_text_extents_t extents;
  Partie* p = g_list_nth_data(Lst, 7);
  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);
  cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size (cr, 35);
  for (i = 0; i <= 4; i++){
    cairo_rectangle (cr, 99 * i + 1, 0, 2, height);
    cairo_rectangle (cr, 0, 99 * i + 1, width, 2);
  }
  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      sprintf(str, "%d", p->tableau[i][j]);
      cairo_text_extents(cr, str, &extents);
      cairo_move_to(cr, 50 + j * 100 - strlen(str) * 10, 60 + i * 100);
      elt = p->tableau[i][j];
      if (elt != 0){
	cairo_set_source_rgba(cr, 0, 0, 0, 255);
	cairo_show_text(cr, str);
      }
    }
  }     
  gtk_style_context_get_color (gtk_widget_get_style_context (widget), 0, &color);
  gdk_cairo_set_source_rgba (cr, &color);
  cairo_fill (cr);
  return 0;
}

int on_button_press (GtkWidget* widget, GdkEventKey* event, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst,0);
  GtkWidget* framemenu = g_list_nth_data(Lst, 2);
  GtkWidget* grid = g_list_nth_data(Lst,1);
  GList* Lgrid = gtk_container_get_children(GTK_CONTAINER(grid));
  GtkWidget* frameactuelle = g_list_nth_data(Lgrid, 0);
  Partie* p = g_list_nth_data(Lst, 7);
  GtkWidget* framejeu = g_list_nth_data(Lst, 6);
  GList* L = gtk_container_get_children(GTK_CONTAINER(framejeu));
  GtkWidget* grille = g_list_nth_data(L, 0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(grille));
  GtkWidget* label = g_list_nth_data(L2, 1);
  GList* L3 = gtk_container_get_children(GTK_CONTAINER(framemenu));
  GtkWidget* grille2 = g_list_nth_data(L3, 0);
  GList* L4 = gtk_container_get_children(GTK_CONTAINER(grille2));
  GtkWidget* bouton1 = g_list_nth_data(L4, 5);
  GtkWidget* bouton2 = g_list_nth_data(L4, 3);
  GtkWidget* toplevel;
  int key = event->keyval;
  char str[20]; 
  if (framejeu == frameactuelle){
    if (!estbloque(p)){
      if ((!estdans(p, 2048) && !p->continuer) || p->continuer){
	if (key == 65362){
	  if (mouvtest(p, HAUT)){
	    transformer(p, HAUT);
	    inserer2ou4(p, 1);
	  }
	}
	else if (key == 65364){
	  if (mouvtest(p, BAS)){
	    transformer(p, BAS);
	    inserer2ou4(p, 1);
	  }
	}
	else if (key == 65361){
	  if (mouvtest(p, GAUCHE)){
	    transformer(p, GAUCHE);
	    inserer2ou4(p, 1);
	  }
	}
	else if (key == 65363){
	  if (mouvtest(p, DROITE)){
	    transformer(p, DROITE);
	    inserer2ou4(p, 1);
	  }
	}
	sprintf(str, "Score : %d", p->score);
	gtk_label_set_label(GTK_LABEL(label), str);
	g_object_ref(G_OBJECT(framejeu));
	gtk_container_remove(GTK_CONTAINER(grid), framejeu);
	gtk_table_attach(GTK_TABLE(grid), framejeu, 0, 1, 1, 2, GTK_FILL, GTK_FILL | GTK_EXPAND, 0, 0);
	gtk_widget_show_all(mainfenetre);
      }
      if (estdans(p, 2048) && !p->continuer){
	toplevel = gtk_message_dialog_new(GTK_WINDOW(mainfenetre),
					  GTK_DIALOG_MODAL,
					  GTK_MESSAGE_QUESTION,
					  GTK_BUTTONS_YES_NO,
					  "Gagné !\nVoulez-vous continuer ?");
	switch(gtk_dialog_run(GTK_DIALOG(toplevel)))
	  {
	  case GTK_RESPONSE_YES:
	    p->continuer = 1;
	    gtk_widget_destroy(toplevel);
	    break;
	  case GTK_RESPONSE_NONE:
	  case GTK_RESPONSE_NO:
	    gtk_widget_destroy(toplevel);
	    ecrirescore("meilleurs_scores", p->score);
	    nouveaujeu(p);
	    OnBack(widget, Lst);
	    gtk_widget_set_sensitive(bouton1, FALSE);
	    gtk_widget_set_sensitive(bouton2, FALSE);
	    break;
	  }
      }
    }
    else {
      if (p->continuer || estdans(p, 2048)){
	toplevel = gtk_message_dialog_new(GTK_WINDOW(mainfenetre),
					  GTK_DIALOG_MODAL,
					  GTK_MESSAGE_INFO,
					  GTK_BUTTONS_OK,
					  "Dommage...\nBeau jeu tout de même !");
	gtk_dialog_run(GTK_DIALOG(toplevel));
	gtk_widget_destroy(toplevel);
	ecrirescore("meilleurs_scores", p->score);
	nouveaujeu(p);
	OnBack(widget, Lst);
	gtk_widget_set_sensitive(bouton1, FALSE);
	gtk_widget_set_sensitive(bouton2, FALSE);
      }
      else {
	toplevel = gtk_message_dialog_new(GTK_WINDOW(mainfenetre),
					  GTK_DIALOG_MODAL,
					  GTK_MESSAGE_INFO,
					  GTK_BUTTONS_OK,
					  "Perdu !\nVous ferez mieux la prochaine fois...");
	gtk_dialog_run(GTK_DIALOG(toplevel));
	gtk_widget_destroy(toplevel);
	nouveaujeu(p);
	OnBack(widget, Lst);
	gtk_widget_set_sensitive(bouton1, FALSE);
	gtk_widget_set_sensitive(bouton2, FALSE);
      }
    }
  }
  return 0;
}



void OnDestroy(GtkWidget* pWidget, gpointer pData){
  gtk_main_quit();
}

void OnJeu(GtkWidget* pWidget, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst,0);
  GtkWidget* grid = g_list_nth_data(Lst,1);
  GtkWidget* framemenu = g_list_nth_data(Lst,2);
  GtkWidget* framejeu = g_list_nth_data(Lst,6);
  Partie* p = g_list_nth_data(Lst, 7);
  GList* L = gtk_container_get_children(GTK_CONTAINER(framejeu));
  GtkWidget* grille = g_list_nth_data(L, 0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(grille));
  GtkWidget* label = g_list_nth_data(L2, 1);
  char str[20];
  g_object_ref(G_OBJECT(framemenu));
  gtk_container_remove(GTK_CONTAINER(grid), framemenu);
  gtk_table_attach(GTK_TABLE(grid), framejeu, 0, 1, 1, 2, GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
  sprintf(str, "Score : %d", p->score);
  gtk_label_set_label(GTK_LABEL(label), str);
  gtk_widget_show_all(mainfenetre);
}

void OnNew(GtkWidget* pWidget, GList* Lst){
  Partie* p = g_list_nth_data(Lst,7);
  GtkWidget* framejeu = g_list_nth_data(Lst, 6);
  GList* L = gtk_container_get_children(GTK_CONTAINER(framejeu));
  GtkWidget* grille = g_list_nth_data(L, 0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(grille));
  GtkWidget* label = g_list_nth_data(L2, 1);
  nouveaujeu(p);
  gtk_label_set_label(GTK_LABEL(label), "Score : 0");
  OnJeu(pWidget, Lst);
}

void OnRepr(GtkWidget* pWidget, GList* Lst){
  OnJeu(pWidget, Lst);
}

void OnSauv(GtkWidget* pWidget, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst,0);
  GtkWidget* grid = g_list_nth_data(Lst,1);
  GtkWidget* framemenu = g_list_nth_data(Lst,2);
  GtkWidget* framesauv = g_list_nth_data(Lst,4);
  GList* L = gtk_container_get_children(GTK_CONTAINER(framesauv));
  GtkWidget* grille = g_list_nth_data(L, 0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(grille));
  GtkWidget* itembox = g_list_nth_data(L2, 3);
  int nb = NbEmplacementsSauvegarde("sauv");
  int i;
  char nom[14] = {'E', 'm', 'p', 'l', 'a', 'c', 'e', 'm', 'e', 'n', 't', ' ', 'i', '\0'};
  gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(itembox));
  for (i = 1; i <= nb; i++){
    sprintf(nom + 12, "%d", i);
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(itembox), nom, nom);
  }
  gtk_combo_box_set_active_id(GTK_COMBO_BOX(itembox), "Emplacement 1");
  g_object_ref(G_OBJECT(framemenu));
  gtk_container_remove(GTK_CONTAINER(grid), framemenu);
  gtk_table_attach(GTK_TABLE(grid), framesauv, 0, 1, 1, 2, GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
  gtk_widget_show_all(mainfenetre);
}

void OnAjouterSauv(GtkWidget* pWidget, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst, 0);
  GtkWidget* framesauv = g_list_nth_data(Lst,4);
  GList* L = gtk_container_get_children(GTK_CONTAINER(framesauv));
  GtkWidget* grille = g_list_nth_data(L, 0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(grille));
  GtkWidget* itembox = g_list_nth_data(L2, 3);
  GtkWidget* toplevel;
  int nb = NbEmplacementsSauvegarde("sauv");
  char nom[14] = {'E', 'm', 'p', 'l', 'a', 'c', 'e', 'm', 'e', 'n', 't', ' ', 'i', '\0'};
  sprintf(nom + 12, "%d", nb + 1);
  if (nb < 9){
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(itembox), nom, nom);
    AjouterEmplacementSauvegarde("sauv");
  }
  else {
    toplevel = gtk_message_dialog_new(GTK_WINDOW(mainfenetre),
				      GTK_DIALOG_MODAL,
				      GTK_MESSAGE_ERROR,
				      GTK_BUTTONS_CLOSE,
				      "Vous avez atteint le nombre maximal\nd'emplacements !");
    gtk_dialog_run(GTK_DIALOG(toplevel));
    gtk_widget_destroy(toplevel);
  }
}

void OnCharge(GtkWidget* pWidget, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst,0);
  GtkWidget* grid = g_list_nth_data(Lst,1);
  GtkWidget* framemenu = g_list_nth_data(Lst,2);
  GtkWidget* framecharge = g_list_nth_data(Lst,5);
  GList* L = gtk_container_get_children(GTK_CONTAINER(framecharge));
  GtkWidget* grille = g_list_nth_data(L, 0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(grille));
  GtkWidget* itembox = g_list_nth_data(L2, 2);
  int nb = NbEmplacementsSauvegarde("sauv");
  int i;
  char nom[14] = {'E', 'm', 'p', 'l', 'a', 'c', 'e', 'm', 'e', 'n', 't', ' ', 'i', '\0'};
  gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(itembox));
  for (i = 1; i <= nb; i++){
    sprintf(nom + 12, "%d", i);
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(itembox), nom, nom);
  }
  gtk_combo_box_set_active_id(GTK_COMBO_BOX(itembox), "Emplacement 1");
  g_object_ref(G_OBJECT(framemenu));
  gtk_container_remove(GTK_CONTAINER(grid), framemenu);
  gtk_table_attach(GTK_TABLE(grid), framecharge, 0, 1, 1, 2, GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
  gtk_widget_show_all(mainfenetre);
}

void OnRegles(GtkWidget* pWidget, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst,0);
  GtkWidget* grid = g_list_nth_data(Lst,1);
  GtkWidget* framemenu = g_list_nth_data(Lst,2);
  GtkWidget* frameregles = g_list_nth_data(Lst,8);
  g_object_ref(G_OBJECT(framemenu));
  gtk_container_remove(GTK_CONTAINER(grid), framemenu);
  gtk_table_attach(GTK_TABLE(grid), frameregles, 0, 1, 1, 2, GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
  gtk_widget_show_all(mainfenetre);
}

void OnHighScores(GtkWidget* pWidget, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst,0);
  GtkWidget* grid = g_list_nth_data(Lst,1);
  GtkWidget* framemenu = g_list_nth_data(Lst,2);
  GtkWidget* framescore = g_list_nth_data(Lst,3);
  GList* L = gtk_container_get_children(GTK_CONTAINER(framescore));
  GtkWidget* grille = g_list_nth_data(L, 0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(grille));
  char* str = ScoresToString("meilleurs_scores");
  GtkWidget* grillescores = g_list_nth_data(L2, 1);
  GList* L3 = gtk_container_get_children(GTK_CONTAINER(grillescores));
  GtkWidget* label = g_list_nth_data(L3, 0);
  gtk_label_set_text(GTK_LABEL(label), str);
  g_object_ref(G_OBJECT(framemenu));
  gtk_container_remove(GTK_CONTAINER(grid), framemenu);
  gtk_table_attach(GTK_TABLE(grid), framescore, 0, 1, 1, 2, GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
  gtk_widget_show_all(mainfenetre);
}



void OnSauvAcc(GtkWidget* pWidget, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst,0);
  Partie* p = g_list_nth_data(Lst, 7);
  GtkWidget* framesauv = g_list_nth_data(Lst,4);
  GList* L = gtk_container_get_children(GTK_CONTAINER(framesauv));
  GtkWidget* grille = g_list_nth_data(L, 0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(grille));
  GtkWidget* itembox = g_list_nth_data(L2, 3);
  GtkWidget* toplevelconfirmation;
  char* nom = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(itembox));
  char numero = nom[12];
  int emplacement;
  FILE* f = fopen("sauv", "r");
  int nbemp = 20 * NbEmplacementsSauvegarde("sauv");
  int* tab = malloc(nbemp * sizeof(int));
  int i;
  int j;
  int k;
  sscanf(&numero, "%d", &emplacement);
  for (i = 0; i < nbemp; i++){
    fscanf(f, "%d", tab + i);
  }
  fclose(f);
  k = 20 * (emplacement - 1) + 1; /* 20 * emplacement - 19*/
  if (tab[k] == 1){
    toplevelconfirmation = gtk_message_dialog_new(GTK_WINDOW(mainfenetre),
						  GTK_DIALOG_MODAL,
						  GTK_MESSAGE_QUESTION,
						  GTK_BUTTONS_YES_NO,
						  "Sauvegarde existante...\nVoulez-vous la remplacer ?");
    switch(gtk_dialog_run(GTK_DIALOG(toplevelconfirmation)))
      {
      case GTK_RESPONSE_YES:
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
	f = fopen("sauv", "w");
	for (i = 0; i < nbemp; i++){
	  fprintf(f, "%d ", tab[i]);
	  if ((i+1)%20 == 0){
	    fprintf(f, "\n");
	  } 
	}
	fclose(f);
	gtk_widget_show_all(mainfenetre);
	gtk_widget_destroy(toplevelconfirmation);
	break;
      case GTK_RESPONSE_NONE:
      case GTK_RESPONSE_NO:
	gtk_widget_destroy(toplevelconfirmation);
	break;
      }
  }
  else {
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
    f = fopen("sauv", "w");
    for (i = 0; i < nbemp; i++){
      fprintf(f, "%d ", tab[i]);
      if ((i+1)%20 == 0){
	fprintf(f, "\n");
      } 
    }
    fclose(f);
    gtk_widget_show_all(mainfenetre);
    toplevelconfirmation = gtk_message_dialog_new(GTK_WINDOW(mainfenetre),
						  GTK_DIALOG_MODAL,
						  GTK_MESSAGE_INFO,
						  GTK_BUTTONS_OK,
						  "Sauvegarde réussie !");
    gtk_dialog_run(GTK_DIALOG(toplevelconfirmation));
    gtk_widget_destroy(toplevelconfirmation);
  }
}


void OnCharAcc(GtkWidget* pWidget, GList* Lst){
  GtkWidget* mainfenetre = g_list_nth_data(Lst,0);
  GtkWidget* framecharge = g_list_nth_data(Lst,5);
  GtkWidget* toplevelconfirmation;
  GList* L = gtk_container_get_children(GTK_CONTAINER(framecharge));
  GtkWidget* grille = g_list_nth_data(L, 0);
  GList* L2 = gtk_container_get_children(GTK_CONTAINER(grille));
  GtkWidget* itembox = g_list_nth_data(L2, 2);
  Partie* p = g_list_nth_data(Lst, 7);
  char* nom = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(itembox));
  char numero = nom[12];
  int emplacement;
  FILE* f = fopen("sauv", "r");
  int nbemp = 20 * NbEmplacementsSauvegarde("sauv");
  int* tab = malloc(nbemp * sizeof(int));
  int i;
  int j;
  int k;      
  sscanf(&numero, "%d", &emplacement);
  for (i = 0; i < nbemp; i++){
    fscanf(f, "%d", tab + i);
  }
  k = 20 * (emplacement - 1) + 2; /* 20 * emplacement -18 */
  fclose(f);
  if (tab[k - 1] == 1){
    toplevelconfirmation = gtk_message_dialog_new(GTK_WINDOW(mainfenetre),
						  GTK_DIALOG_MODAL,
						  GTK_MESSAGE_QUESTION,
						  GTK_BUTTONS_YES_NO,
						  "Voulez-vous vraiment\ncharger cette partie ?");
    switch(gtk_dialog_run(GTK_DIALOG(toplevelconfirmation)))
      {
      case GTK_RESPONSE_YES:
	for (i = 0 ; i < 4; i++){
	  for (j = 0; j < 4; j++){
	    p->tableau[i][j] = tab[k];
	    k++;
	  }
	}
	p->score = tab[emplacement * 20 -2];
	p->continuer = tab[emplacement * 20 -1];
	gtk_widget_show_all(mainfenetre);
	OnBack(pWidget, Lst);
	OnJeu(pWidget, Lst);
	gtk_widget_destroy(toplevelconfirmation);
	break;
      case GTK_RESPONSE_NONE:
      case GTK_RESPONSE_NO:
	gtk_widget_destroy(toplevelconfirmation);
	break;
      }
  }
  else {
    toplevelconfirmation = gtk_message_dialog_new(GTK_WINDOW(mainfenetre),
						  GTK_DIALOG_MODAL,
						  GTK_MESSAGE_ERROR,
						  GTK_BUTTONS_CLOSE,
						  "Cet emplacement est vide !");
    gtk_dialog_run(GTK_DIALOG(toplevelconfirmation));
    gtk_widget_destroy(toplevelconfirmation);
  }
}
