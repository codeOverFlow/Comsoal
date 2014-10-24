#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include "liste.h"

#define MAX_TIME 0                    // Temps maximal de résolution par instance

/*****************************************************************************************************************/
/*                                    Lecture des données et initialisation                                      */
/*****************************************************************************************************************/

/* Structure regroupant les données */
typedef struct data
{
	int        C;			  // Capacité du bin
	int        n;			  // Nombre d'objets
	int*       size;		  // Tableau des tailles des objets
	item_list* pred;		  // Tableau des prédécesseurs immédiats
} data;

/* Ajout d'un prédécesseur */
void add_pred(int x, int y, data* d)
{
	d->pred[y].val++;
	d->pred[y].next = new_item_list(x, d->pred[y].next);
}

/* Lecture du fichier */
void read_data(char* file, data *d)
{
	int i;
	FILE *fin;
	fin = fopen(file, "r");	 			// Ouverture du fichier en lecture
	fscanf(fin, "%d", &d->n);    		// On lit en première ligne le nombre d'objets

	/* Allocation des espaces mémoires */
	d->size     = (int*) calloc((1+d->n), sizeof(int));
	d->pred     = (item_list*) calloc((1+d->n), sizeof(item_list));

	/* Lecture des tailles des objects */
	for (i = 1; i <= d->n; i++)
		fscanf(fin, "%d", &d->size[i]);

	/* Initialisation du tableau des prédécesseurs immédiats */
	for (i = 1; i <= d->n; i++)
	{
		d->pred[i].next = NULL;
		d->pred[i].val  = 0;
	}

	/* Lecture des contraintes */
	int x, y;
	fscanf(fin, "%d,%d", &x, &y);		// On lit la première ligne des contraintes
	while (x != -1)  					// Tant que les contraintes ne sont pas -1
	{
		add_pred(x, y, d);				// On ajoute x comme un predecesseur de y
		fscanf(fin, "%d,%d", &x, &y);	// On lit la ligne suivante
	}
	fclose(fin);						// Fermeture du fichier
}

/* Libération de la mémoire allouée pour "data" */
void FreeData(data* d)
{
	free(d->size);
	free(d->pred);
}

int comsoal(data d)
{
	// capacite des bins
	int capa_bin = d.C;
	// stockage des objets deja affecter
	int affecter[d.n+1];
	for(int i = 1; i <= d.n; i++)
	{
		affecter[i] = 0;
	}
	// nombre de bin utilise
	int nb_bin = 1;
	// taille de la liste CL
	int taille_cl;

	int affectation = 1;
	while (affectation)
	{
		affectation = 0;
		for (int i = 1; i <= d.n; i++)
		{
			// on ajoute le max possible
			if (affecter[i])
				continue;

			// si le bin est plein, on stoppe
			if (!capa_bin)
				break;

			if (!d.pred[i].val)
			{
				if (d.size[i] <= capa_bin)
				{
					capa_bin -= d.size[i];
					affecter[i] = 1;
					affectation = 1;
				}
			}
			else
			{
				if (d.size[i] <= capa_bin)
				{
					int tous_fais = 1;
					for (int j = 1; j <= d.pred[i].val ; j++)
					{
						if (!affecter[d.pred[i].next->val])
						{
							tous_fais = 0;
							break;
						}
					}
					if (tous_fais)
					{

						capa_bin -= d.size[i];
						affecter[i] = 1;
						affectation = 1;
					}
				}
			}
		}
	}

	int tous_affect = 1;
	for (int i = 1; i <= d.n; i++)
	{
		if (!affecter[i])
		{
			tous_affect = 0;
			break;
		}
	}

	if (tous_affect)
		return nb_bin;
	else
		nb_bin++;

	capa_bin = d.C;
	while (!tous_affect) //Tant qu'il reste des objets à affecter
	{
	    // on initialise la taille de la liste CL a 0
		taille_cl = 0;
		
		int* liste_cl = (int*) calloc((d.n+1), sizeof(int)); //Création d'une nouvelle liste de taille n (nombre d'objets)
		// on regarde pour chaque objet s'il peut etre candidat a l'affectation
		for (int i = 1; i <= d.n; i++)
		{
			if (!affecter[i])
			{
				if (!d.pred[i].val)
				{
					if (d.size[i] <= capa_bin)
					{
					    // si l'objet correspond au critère d'affectation on l'ajoute a la liste des candidats
						taille_cl++;
						liste_cl[taille_cl] = i; 
					}
				}
				else
				{
					if (d.size[i] <= capa_bin)
					{
						int tous_fais = 1;
						for (int j = 1; j <= d.pred[i].val ; j++)
						{
							if (!affecter[d.pred[i].next->val])
							{
								tous_fais = 0;
								break;
							}
						}

						if (tous_fais)
						{
                            // si l'objet correspond au critère d'affectation on l'ajoute a la liste des candidats
							taille_cl++;
							liste_cl[taille_cl] = i;
						}
					}
				}
			}
		}
		
		// si la liste CL n'a pas de candidat
		if (!taille_cl)
		{
		    // on regarde si tous les objets ont ete affectés
		    tous_affect = 1;
    		for (int i = 1; i <= d.n; i++)
    		{
    			if (!affecter[i])
    			{
    				tous_affect = 0;
    				break;
    			}
    		}
    		// si oui on libere la memoire de la liste CL
    		if (tous_affect)
    			free(liste_cl);
    		else { // sinon on cree un nouveau bin
			    nb_bin++;
			    capa_bin = d.C;
			}
		}
		else
		{
		    //On prend un objet aléatoire parmi les candidats pour mettre dans le bin en cours
			int alea;
			if (taille_cl == 1)
				alea = 1;
			else
			{
				alea = (rand() % taille_cl)+1;
			}
			affecter[liste_cl[alea]] = 1;
			capa_bin -= d.size[liste_cl[alea]];
		} 
	}

    // une fois que tout est affecté on retourne le nombre de bin utilisés
	return nb_bin;
}

int comsoal2(data d) {
	// capacite des bins
	int capa_bin = d.C;
	// stockage des objets deja affecter
	int affecter[d.n+1];
	for(int i = 1; i <= d.n; i++)
	{
		affecter[i] = 0;
	}
	// nombre de bin utilise
	int nb_bin = 1;
	// taille de la liste CL
	int taille_cl;

	int affectation = 1;
	while (affectation)
	{
		affectation = 0;
		for (int i = 1; i <= d.n; i++)
		{
			// on ajoute le max possible
			if (affecter[i])
				continue;

			// si le bin est plein, on stoppe
			if (!capa_bin)
				break;

			if (!d.pred[i].val)
			{
				if (d.size[i] <= capa_bin)
				{
					capa_bin -= d.size[i];
					affecter[i] = 1;
					affectation = 1;
				}
			}
			else
			{
				if (d.size[i] <= capa_bin)
				{
					int tous_fais = 1;
					for (int j = 1; j <= d.pred[i].val ; j++)
					{
						if (!affecter[d.pred[i].next->val])
						{
							tous_fais = 0;
							break;
						}
					}
					if (tous_fais)
					{

						capa_bin -= d.size[i];
						affecter[i] = 1;
						affectation = 1;
					}
				}
			}
		}
	}

	int tous_affect = 1;
	for (int i = 1; i <= d.n; i++)
	{
		if (!affecter[i])
		{
			tous_affect = 0;
			break;
		}
	}

	if (tous_affect)
		return nb_bin;
	else
		nb_bin++;

	capa_bin = d.C;
	while (!tous_affect)
	{
		taille_cl = 0;
		int* liste_cl = (int*) calloc((d.n+1), sizeof(int));
		for (int i = 1; i <= d.n; i++)
		{
			if (!affecter[i])
			{
				if (!d.pred[i].val)
				{
					if (d.size[i] <= capa_bin)
					{
						taille_cl++;
						liste_cl[taille_cl] = i;
					}
				}
				else
				{
					if (d.size[i] <= capa_bin)
					{
						int tous_fais = 1;
						for (int j = 1; j <= d.pred[i].val ; j++)
						{
							if (!affecter[d.pred[i].next->val])
							{
								tous_fais = 0;
								break;
							}
						}

						if (tous_fais)
						{

							taille_cl++;
							liste_cl[taille_cl] = i;
						}
					}
				}
			}
		}

		if (!taille_cl)
		{
			tous_affect = 1;
			for (int i = 1; i <= d.n; i++)
			{
				if (!affecter[i])
				{
					tous_affect = 0;
					break;
				}
			}
			if (tous_affect)
				free(liste_cl);
			else {
				nb_bin++;
				capa_bin = d.C;
			}
		}
		else
		{
			int min = d.C+1;
			int index = 1;
			for (int i = 1; i < taille_cl; i++) {
				if (min > d.size[liste_cl[i]]) {
					min = d.size[liste_cl[i]];
					index = i;
				}
			}
			affecter[liste_cl[index]] = 1;
			capa_bin -= d.size[liste_cl[index]];
		}
	}
	return nb_bin;
}

int comsoal3(data d) {
	// capacite des bins
	int capa_bin = d.C;
	// stockage des objets deja affecter
	int affecter[d.n+1];
	for(int i = 1; i <= d.n; i++)
	{
		affecter[i] = 0;
	}
	// nombre de bin utilise
	int nb_bin = 1;
	// taille de la liste CL
	int taille_cl;

	int affectation = 1;
	while (affectation)
	{
		affectation = 0;
		for (int i = 1; i <= d.n; i++)
		{
			// on ajoute le max possible
			if (affecter[i])
				continue;

			// si le bin est plein, on stoppe
			if (!capa_bin)
				break;

			if (!d.pred[i].val)
			{
				if (d.size[i] <= capa_bin)
				{
					capa_bin -= d.size[i];
					affecter[i] = 1;
					affectation = 1;
				}
			}
			else
			{
				if (d.size[i] <= capa_bin)
				{
					int tous_fais = 1;
					for (int j = 1; j <= d.pred[i].val ; j++)
					{
						if (!affecter[d.pred[i].next->val])
						{
							tous_fais = 0;
							break;
						}
					}
					if (tous_fais)
					{

						capa_bin -= d.size[i];
						affecter[i] = 1;
						affectation = 1;
					}
				}
			}
		}
	}

	int tous_affect = 1;
	for (int i = 1; i <= d.n; i++)
	{
		if (!affecter[i])
		{
			tous_affect = 0;
			break;
		}
	}

	if (tous_affect)
		return nb_bin;
	else
		nb_bin++;

	capa_bin = d.C;
	while (!tous_affect)
	{
		taille_cl = 0;
		int* liste_cl = (int*) calloc((d.n+1), sizeof(int));
		for (int i = 1; i <= d.n; i++)
		{
			if (!affecter[i])
			{
				if (!d.pred[i].val)
				{
					if (d.size[i] <= capa_bin)
					{
						taille_cl++;
						liste_cl[taille_cl] = i;
					}
				}
				else
				{
					if (d.size[i] <= capa_bin)
					{
						int tous_fais = 1;
						for (int j = 1; j <= d.pred[i].val ; j++)
						{
							if (!affecter[d.pred[i].next->val])
							{
								tous_fais = 0;
								break;
							}
						}

						if (tous_fais)
						{

							taille_cl++;
							liste_cl[taille_cl] = i;
						}
					}
				}
			}
		}

		if (!taille_cl)
		{
			tous_affect = 1;
			for (int i = 1; i <= d.n; i++)
			{
				if (!affecter[i])
				{
					tous_affect = 0;
					break;
				}
			}
			if (tous_affect)
				free(liste_cl);
			else {
				nb_bin++;
				capa_bin = d.C;
			}
		}
		else
		{
			int max = 0;
			int index = 1;
			for (int i = 1; i < taille_cl; i++) {
				if (max < d.size[liste_cl[i]]) {
					max = d.size[liste_cl[i]];
					index = i;
				}
			}
			affecter[liste_cl[index]] = 1;
			capa_bin -= d.size[liste_cl[index]];
		}
	}
	return nb_bin;
}

/// MAIN ///
int main(int argc, char* argv[])
{
	data        d;                   // Données du problème

	clock_t     start, end;          // Variable pour le contrôle du temps

	/* Lecture des données */
	read_data(argv[1], &d);
	d.C = atoi(argv[2]);

	/* Paramètre du hasard */
	srand(time(0));


	start = clock();
	int sol = 0, sol2 = 0, sol3 = 0;
	int min = d.n, min2 = d.n, min3 = d.n;
	do
	{
		/* Votre algorithme */
		if ((sol = comsoal(d)) < min)
		{
			min = sol;
		}
		if ((sol2 = comsoal2(d)) < min2)
		{
			min2 = sol2;
		}
		if ((sol3 = comsoal3(d)) < min3)
		{
			min3 = sol3;
		}
		end = clock();
	}
	while((double)(end-start) / CLOCKS_PER_SEC <= MAX_TIME);
	printf("sol: %d\n", sol);
	printf("sol2: %d\n", sol2);
	printf("sol3: %d\n", sol3);
	/* Libération de la mémoire allouée */
	FreeData(&d);
	return 0;
}
