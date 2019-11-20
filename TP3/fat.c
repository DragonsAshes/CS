#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fat.h"

void initialise_fat(){

	int i;
	for( i=0; i<BLOCNUM; i++){
		FAT[i] = 0xFFFF;
	}
	freeblocks = BLOCNUM;
	obj = NULL;
}


struct objet *rechercher_objet(char *nom){
	struct objet *tmp = obj;

	while ( tmp != NULL ){
		if(strcmp( nom , tmp->nom ) == 0 ){
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}



struct objet *creer_objet(char *nom, unsigned short auteur,unsigned int taille, char *data){

	if(rechercher_objet(nom) != NULL) //On vérifie que le nom n'est pas encore utilisé
	{
		printf("Erreur, ce nom est deja utilise\n");
		return NULL;
	}

	if(strlen(nom) > NAMELEN) //On vérifie que le nom puisse rentrer dans le champ nom[NAMELEN]
		return NULL;

	struct objet *new = malloc(sizeof(struct objet));

	if(new == NULL)
		return NULL;


	strcpy(new->nom, nom);
	new->auteur = auteur;
	new->taille = taille;
	new->next = obj;
	obj = new;

	unsigned int nbbloc = 0;
	if(taille%BLOCSIZE == 0) 
		nbbloc = taille/BLOCSIZE;
	else 
		nbbloc = taille/BLOCSIZE +1;

	if(nbbloc > freeblocks) //On vérifie qu'il y ait assez d'espace libre
	{
		printf("\nIl n'y a pas assez d'espace libre\n");
		return NULL;
	}

	int i = 0;
	unsigned short index_courant;
	for (i=0; i<BLOCNUM; i++){  //On recherche le premier bloc libre
		if (FAT[i] == 0xFFFF)
		{
			new->index = i;
			FAT[i] = 0xfffe;
			break;
		}
	}
	index_courant = i;
	
	//printf("nbbloc = %d\n", nbbloc);
	//printf("index = %d\n", index_courant);
	
	unsigned short save = 0;
	while(nbbloc != 1){    
		memcpy(volume + 512 * index_courant, data, 512);
		freeblocks--;  //Copie des données et maj des variables
		taille -= 512;
		nbbloc --;
		data = data + 512;
		save = index_courant;
		while(FAT[index_courant] != 0xFFFF){    //On recherche le prochain bloc libre
			index_courant++;
		}
		FAT[index_courant] = 0xfffe;
		FAT[save]=index_courant;
	}
	FAT[index_courant] = 0xfffe;  //On définit le dernier bloc et on y met le reste de données
	memcpy(volume + 512 * index_courant, data, taille);
	freeblocks--;

	return obj;
}

int supprimer_objet(char *nom){
	if(rechercher_objet(nom) == NULL)
	{
		printf("Le fichier que vous voulez supprimer n'existe pas");
		return 0;
	}
	struct objet *tmp = obj;
	struct objet *prev = tmp;
	int first;
	int save = 0;
	

	if(strcmp(tmp->nom, nom) != 0)
	{
		while(strcmp(tmp->nom, nom) != 0 ) //Penser à utiliser strcmp pour comparer des chaines de caractères
		{
			prev = tmp;	//Objet précédent à celui qu'il faut supprimer
			tmp = tmp->next;  //objet à supprimer
		}

		prev->next = tmp->next;
		
		first = tmp->index;
	}
	else
	{
		first = tmp->index;
		obj = tmp->next;
	}
	
	do
	{
		save = first;
		first = FAT[first];
		FAT[save] = 0xffff;
		freeblocks++;
	} while(first != 0xfffe);

	free(tmp);   //Supprimer dans la liste chainée

	return 1;
}

void supprimer_tout(){
	while(obj != NULL){
		supprimer_objet(obj->nom);
	}
}



void listeAffiche(struct objet * ptr){

	if ( ptr == NULL )
		printf("Liste vide!\n") ;
	else 
	{
		printf("\nContenu de la liste : \n") ;
		while ( ptr != NULL ) 	{
			printf("[Objet @%p]\n- name: %s\n- taille: %d\n- auteur: %d\n- index: %d\n", ptr, ptr->nom, ptr->taille, ptr->auteur, ptr->index);
			ptr = ptr->next ;
		}
	}
}

int lire_objet(struct objet *o,char **data)
{
	if(obj == NULL)
		return -1;
	if(o == NULL)
		return -1;

	unsigned int nbbloc = 0;
	if((o->taille)%BLOCSIZE == 0) 
		nbbloc = (o->taille)/BLOCSIZE;
	else 
		nbbloc = (o->taille)/BLOCSIZE +1;

	*data = malloc(o->taille+1);
	int index = o->index;

	int i = 0;

	for(i = 0; i < nbbloc; i++ )
	{
		if (i == nbbloc - 1)
			memcpy(*data + (BLOCSIZE * i), volume + index * i * BLOCSIZE, o->taille - i * BLOCSIZE);
		else
			memcpy(*data + (BLOCSIZE * i), volume + index * i * BLOCSIZE, BLOCSIZE);

		if(index == 0xfffe)
			break;
		index = FAT[index];
	}
	
	return 1;
}

