//--------------------------------//
         /*** LISTE ***/
//--------------------------------//
        
/* Un élément de la liste chaînée */
typedef struct item_list{
	int               val;    // Valeur
	struct item_list* next;   // Pointeur vers l'élément suivant dans la liste
} item_list;

/* Créer un nouveau élément de la liste */
item_list* new_item_list(int val, item_list* next) {
    item_list* temp = (item_list*) calloc(1, sizeof(item_list));
    temp->val       = val;
    temp->next      = next;
    return temp;
}



 