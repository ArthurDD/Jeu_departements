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





int main()
{

	lancement_jeu();

	return(0);
}













void lecture_fichier(char tab[][taille_max])
{
	FILE *fichier = fopen("Liste_dep.txt","r");

	char p1[30], p2[30];
	fgets(p1,100,fichier);		//On élimine le titre (cad la première ligne) du fichier		
	fscanf(fichier,"%s%s",p1,p2);	//On élimine la deuxième

	//printf("p1 = %s, p2 = %s\n",p1,p2);
	
	int num;
	char nom[30];
	int i =1;
	
	while(fscanf(fichier,"%d%s",&num,nom) == 2)
	{
	
		
		strcpy(tab[i], nom);
		i+= 1;
	}
	
	fclose(fichier);
}





void affichage_tableau(char tab[][taille_max],int indice)
{
	int i = 1;
	
	printf("Affichage du tableau des départements :\n");
	printf("[ ");
	for (i=1 ; i<=indice ; i++)
	{
		printf("%s ; ", tab[i]);
	}

	printf("]\n");
}


void lancement_jeu()
{
	char tab[120][taille_max];
	lecture_fichier(tab);
	int i_deb, i_fin;
	
	printf("À partir de quel numéro de département souhaitez vous jouer ?\t");
	scanf("%d",&i_deb);
	printf("\n");
	
	printf("Jusqu'à quel numéro de département souhaitez vous jouer ?\t");
	scanf("%d",&i_fin);
	printf("\n");

	jeu(i_deb,i_fin);
}




void jeu(int i_deb, int i_fin)
{
	int compteur = 0;
	int tab[i_fin+10];
	int nb_dep = i_fin - i_deb + 1 ;
	int c_bonnes_rep = 0;
	bool bonne_rep = false;
	bool prem_passage = true;

	char tab_dep[110][taille_max];
	lecture_fichier(tab_dep);	

	clear();
	
	while(compteur != nb_dep)
	{
		
		//Mécanisme du choix du département
		
		int X = i_deb + floorf((float)rand()/(float)RAND_MAX *nb_dep); 	//U e [i_deb;i_fin]
		
		while(present(X,tab, compteur) == true)
		{
			X = i_deb + floorf((float)rand()/(float)RAND_MAX *nb_dep);
		}
		
		tab[compteur] = X;
		compteur += 1;
		

		//Mécanisme du jeu
		
		if (prem_passage)
		{
			prem_passage = false;
		}
		else
		{
			if (bonne_rep)
			{
				printf("Bonne réponse ! \n");
	
			}
			else
			{
				printf("Mauvaise réponse. \n");
	
			}
		}
	
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

		printf("\t\t\t\t\tPoints : %d / %d.\n\n\n\n\n",c_bonnes_rep, compteur-1);
		
		printf("\n\n\n\n\n");

		char rep[taille_max];
		printf("Quel est le département associé au numéro %d ?\nRéponse : ",X);
		scanf("%s",rep);
		clear();

		char sol[taille_max];
		strcpy(sol, tab_dep[X]);
		
		minuscules(rep);
		minuscules(sol);

		if (strcmp(rep,sol) == 0)	//Si bonne réponse
		{
			c_bonnes_rep += 1;
			//printf("Bonne réponse !\n");
			bonne_rep = true;
		}
		else	//Si mauvaise réponse
		{
			//printf("Mauvaise réponse.\n");
			bonne_rep = false;
		}
	}


	//Traitement du résultat
	clear();
	printf("Jeu terminé. Votre score est de %d / %d.\n",c_bonnes_rep, compteur);
	printf("\n\n\nSouhaitez vous enregistrer votre score ? (Oui/Non)\n");
	printf("Réponse :\t");

	char reponse[10];
	scanf("%s", reponse);
	minuscules(reponse);
	
	if (strcmp("oui", reponse) == 0)
	{
		clear();
		char nom[taille_max];
		printf("Sous quel nom souhaitez vous ce score enregistré ?\n");
		printf("Réponse :\t");


		scanf("%s", nom);
		printf("\n");

		FILE *fichier = fopen("Historique_des_parties.txt","r");
		if (fichier == NULL)	//Si le fichier n'existe pas
		{
			fichier = fopen("Historique_des_parties.txt","w");
			fprintf(fichier,"Pseudo\t\tScore\t\tDépartement traités\n\n");
		}
		else
		{
			fclose(fichier);
			fichier = fopen("Historique_des_parties.txt","a");
		}
		
		fprintf(fichier,"%s\t\t%d / %d\t\t %d-%d\n",nom, c_bonnes_rep, compteur, i_deb, i_fin);
		fclose(fichier);

		printf("Enregistré !\n");
	}
}




bool present(int X, int tab[], int l)
{
	int i;
	for (i=0 ; i<l ; i++)
	{
		if (tab[i] == X)
		{
			return(true);
		}
	}
	return(false);
}



void minuscules(char mot[])
{
	int i;
	for (i = 0 ; mot[i] != '\0' ; i++)
		{
			mot[i] = tolower(mot[i]);
		}
}




void clear()
{			
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); 	//Commande pour nettoyer la console
}




void ecriture_fichier_dep()
{
	FILE *fichier = fopen("Liste_dep.txt","w+");
	fprintf(fichier,"\t\t\tLISTE DES DÉPARTEMENTS\n\n");
	fprintf(fichier,"Numéro\tNom\n");

	int i;
	for (i=1 ; i<96 ; i++)
	{
		char nom[taille_max];
		printf("Nom du département n°%d :\t",i);
		scanf("%s",nom);
		fprintf(fichier,"%d\t%s",i, nom);
	}
	fclose(fichier);
}

	
