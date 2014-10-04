#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include "liste.h"
#include "chaine.h"

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
	while (!tous_affect)
	{
		taille_cl = 0;
		int* liste_cl = malloc((d.n+1) * sizeof(int));
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
			nb_bin++;
			capa_bin = d.C;
		}
		else
		{
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
	}

	return nb_bin;
}

int comsoal2(data d) {
	// linked list of objects
	Liste* liste = (Liste*)malloc(sizeof(Liste));
	// init list
	init_list(liste);
	// load list
	//printf("\naoeuaoeu\n");
	for (int i = 1; i <= d.n; i++)
		add_elem(liste, i);

	int nb_bin = 1;
	int capa_bin = d.C;

	// initial packing
	int could = 1;
	while (could) {
		could = 0;
		if (!capa_bin)
			break;

		Element* suppr = NULL;
		for (Element* i = liste->first; i != NULL; i = i->next) {
			if (suppr != NULL)
				free(suppr);
			suppr = NULL;
			//printf("\ni->obj: %d\n", i->obj);
			if (d.size[i->obj] <= capa_bin) {
				if (!d.pred[i->obj].val) {
                    //printf("i->obj: %d\n", i->obj);
					capa_bin -= d.size[i->obj];
					rm_elem(liste, i);
					suppr = i;
					could = 1;
					for (int n = 1; n <= d.n; n++) {
                            //printf("n: %d\n", n);
						if (n != i->obj) {
							if (d.pred[n].val) {
								for (item_list* k = d.pred[n].next; k != NULL; k = k->next) {
								    //printf("k->val: %d\n", k->val);
									if (k->val == i->obj) {
										d.pred[n].val--;
										if (d.pred[n].next == k)
											d.pred[n].next = k->next;
										else {
											item_list* e;
											for (e = d.pred[n].next; e->next != k; e = e->next) {}
											e->next = k->next;
										}
										free(k);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// return if we have finished
	if (!liste->list_size)
		return nb_bin;
	else
		nb_bin++;

	int taille_cl;
	capa_bin = d.C;
	do {
		taille_cl = 0;
		int liste_cl[d.n];
		for (Element* i = liste->first; i != NULL; i = i->next) {
			if (d.size[i->obj] <= capa_bin) {
				if (!d.pred[i->obj].val) {
					liste_cl[taille_cl] = i->obj;
					taille_cl++;
				}
			}
		}

		if (!taille_cl){
			nb_bin++;
			capa_bin = d.C;
		}
		else {
			int alea;
			if (taille_cl == 1)
				alea = 0;
			else
				alea = (rand()%taille_cl);
			Element* tmp = get_elem(liste, liste_cl[alea]);
			rm_elem(liste, tmp);
			free(tmp);
			//printf("alea: %d\n", alea);
            //printf("size: %d\n", d.size[liste_cl[alea]]);
			capa_bin -= d.size[liste_cl[alea]];
			for (int n = 1; n <= d.n; n++) {
				if (n != liste_cl[alea]) {
					if (d.pred[n].val) {
						for (item_list* k = d.pred[n].next; k != NULL; k = k->next) {
							if (k->val == liste_cl[alea]) {
								d.pred[n].val--;
								if (d.pred[n].next == k)
									d.pred[n].next = k->next;
								else {
									item_list* e;
									for (e = d.pred[n].next; e->next != k; e = e->next) {}
									e->next = k->next;
								}
								free(k);
								break;
							}
						}
					}
				}
			}
		}
	//	printf("\n\n");
	//	for (Element* i = liste->first; i != NULL; i = i->next) {
	//		printf("i->obj: %d\n", i->obj);
	//}
	//printf("d.pred[9].val: %d\n", d.pred[9].val);
	} while (liste->list_size);

	free(liste);
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
	int sol = 0, sol2 = 0;
	int min = d.n, min2 = d.n;
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
		end = clock();
	}
	while((double)(end-start) / CLOCKS_PER_SEC <= MAX_TIME);
	printf("sol: %d\n", sol);
	printf("sol2: %d\n", sol2);
	/* Libération de la mémoire allouée */
	FreeData(&d);
	return 0;
}

