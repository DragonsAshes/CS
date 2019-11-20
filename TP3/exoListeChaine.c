#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Ici, on est obligé d'utiliser la notation struct xxx,
car la structure s'auto-référence!*/
typedef struct node {
		char data ;
		struct node *link ;
		} Lnode ;

/* Insertion en "tête de liste" */
void insertionTete(Lnode **ph,char item){

	Lnode *tmp=malloc(sizeof(Lnode));

	tmp->link = *ph;
	tmp->data = item;
	*ph = tmp;
	
}

/* Insertion en "queue de liste" */
void insertionQueue(Lnode **ph,char item)	{

	Lnode* tmp = *ph;
	Lnode* new=malloc(sizeof(Lnode));

	while (tmp->link != NULL){
		tmp = tmp->link;
	}
	new->data = item;
	new->link = NULL;
	tmp->link = new;
}

/* Suppression en "tête de liste" */
void suppressionTete(Lnode **ph){

	Lnode* tmp = *ph;

	*ph = tmp->link;
	free(tmp);

}

/* Suppression en "Queue" de liste" */
void suppressionQueue(Lnode **ph){
	
	Lnode* tmp = *ph;


	while (tmp->link->link != NULL) {
		tmp = tmp->link;
	}
	Lnode* suppr = tmp->link;
	tmp->link = NULL;

	free(suppr);
}

/* Procédure d'affichage de la liste. Ne doit pas être modifiée!!! */
void listeAffiche(Lnode * ptr){
	if ( NULL == ptr )
		printf("Liste vide!") ;
	else 
		printf("Contenu de la liste : ") ;
	while ( NULL != ptr ) 	{
		printf("%c ",ptr->data);
		ptr = ptr->link ;
		}
	printf("\n") ;
	}

/* Programme principal. Ne doit pas être modifié!!! */
int main(void) {
	Lnode *tete = NULL ;

	listeAffiche(tete) ;
	insertionTete(&tete,'a') ;
	listeAffiche(tete) ;
	insertionTete(&tete,'c') ;
	listeAffiche(tete) ;
	insertionQueue(&tete,'t') ;
	listeAffiche(tete) ;
	insertionQueue(&tete,'s') ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;
	suppressionQueue(&tete) ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;

   return EXIT_SUCCESS;
   }	
