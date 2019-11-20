#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "fonctions.h"
#include "bitmap.h"

/*
			Prépa du TP:
	On commence par ouvrir les deux fichiers qui vont nous être utils.
	On initialise une boucle do{}while() qui permettra de réaliser l'algorithme suivant tant qu'il y aura des caractères dans le fichier transporteur.
		On réalise une boucle for jusqu'à 8 afin de regrouper les bits obtenus en octets.
			On récupère un caractère dansle fichier transporteur. On regarde si ce caractère est alphanumérique
			Si il ne l'est pas on décrément juste une variable (ici i) qui nous permet de compenser l'incrémentation de i dans la boucle for. En effet puisque le caractère n'est pas alphanumérique, il ne doit pas intervenir dans la construction de nos octets
			Si il est alphanumérique, on regarde si c'est une majuscule ou un minuscule afin de savoir si l'on place un 1 ou un 0 dans notre variable, puis on shift la variable sur la gauche afin de laisser la place pour le prochain bit à venir.
		Une fois que notre variable contient 8 bits (un octet), notre boucle for s'arrête et on vient placer cette variable dans le fichier source.
*/


int main(){

	// Ecercies préparatoires
	nombres_impairs();

	//Première partie du TP
	decodage();
	
	//Remplissage des champs du fichier bitmap.h
	exo2();

	//Qui se cache derrière la barbe?
	image("transporteur.bmp", "newimage.bmp");
	//La réponse est Richard Stallman

	//Production du fichier transporteur
	masquage();
	//Vérification que notre projet transporteur est bien créé en voulant retrouver l'image de Richard Stallman
	image("newtransporteur.bmp", "imageverification.bmp");

	
	return 1;	
}