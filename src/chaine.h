#ifndef CHAINE_H_INCLUDED
#define CHAINE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct Element_liste {
    struct Element_liste* pred;
    int obj;
    struct Element_liste* next;
}Element;

typedef struct Chaine {
    Element* first;
    Element* last;
    int list_size;
}Liste;

void init_list(Liste* l);
void add_elem(Liste* l, int o);
void rm_elem(Liste* l, Element* target);
Element* get_elem(Liste* l, int o);

#endif // CHAINE_H_INCLUDED
