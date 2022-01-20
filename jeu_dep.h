#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>



#define taille_max 30





void lecture_fichier(char tab[][taille_max]);
void affichage_tableau(char tab[][taille_max], int indice);
void lancement_jeu();
void jeu(int i_deb, int i_fin);
bool present(int X, int tab[], int l);
void minuscules(char mot[]);
void clear();
void ecriture_fichier_dep();
