#include "chaine.h"

void init_list(Liste* l) {
	l->first = NULL;
	l->last = NULL;
	l->list_size = 0;
}

void add_elem(Liste* l, int o){
	Element* e = (Element*)malloc(sizeof(Element));
	e->pred = NULL;
	e->obj = o;
	e->next = NULL;
	if (l->list_size == 0) {
		l->first = e;
		l->last = e;
		l->list_size++;
	}
	else {
		e->pred = l->last;
		l->last->next = e;
		l->last = e;
		l->list_size++;
	}
}

void rm_elem(Liste* l, Element* target){
	if (target != NULL) {
		l->list_size--;
		if (target->pred != NULL)
			target->pred->next = target->next;
		else
			l->first = target->next;

		if (target->next != NULL)
			target->next->pred = target->pred;
		else
			l->last = target->pred;
	}
}

Element* get_elem(Liste* l, int o){
	Element* target = NULL;
	for (Element* i = l->first; i != NULL; i = i->next) {
		if (i->obj == o) {
			target = i;
			break;
		}
	}

	return target;
}
