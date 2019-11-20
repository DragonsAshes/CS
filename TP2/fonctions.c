#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "bitmap.h"


void nombres_impairs(){
	int i;
	FILE* fichier = NULL;
	char nombres[1000] = "";
	fichier = fopen("nombres_impairs.txt", "w+");

	if (fichier != NULL)
	{
		for (i=0 ; i < 100 ; i++){
			if 	( i%2 != 0){
			fprintf(fichier, "%d  ",i);
			}
		}
		fgets(nombres , 1000, fichier);
		printf("%s", nombres);

		fclose(fichier);
	}
	else
	{
		printf("L'ouverture du fichier a échouée");
	}
}


void decodage(){
	
	FILE* transporteur = NULL;
	transporteur = fopen("transporteur.txt","rb");
	FILE* source = NULL;
	source = fopen("source.txt", "wb");
	int i;
	char valeur;

	int caractere_courant;

	if (transporteur == NULL) exit(EXIT_FAILURE);

	do
	{
		valeur = 0;

		for ( i = 0 ; i < 8 ; i++)
		{
			caractere_courant = fgetc(transporteur);

			if(caractere_courant == EOF)
				break;
			if(isalpha(caractere_courant))
			{
				
				if(isupper(caractere_courant))
				{

					valeur = valeur << 1;
					valeur += 1;
				}
				else					
					valeur = valeur << 1;

			}
			else{
				i--;
			}

		}

		fputc(valeur , source);

	}while (caractere_courant != EOF);

fclose(transporteur);
fclose(source);

}

void exo2(){

	FILE* transporteur = fopen("transporteur.bmp", "rb");
	if (transporteur == NULL) exit(EXIT_FAILURE);
	
	fichierEntete head;
	
	fread(&head,sizeof(fichierEntete),1,transporteur);
	printf("taille du fichier: %d\n", head.tailleFichier);
	printf("signature : %x\n", head.signature); 
	printf("reserve : %d\n",head.reserve);
	printf("offset : %d\n",head.offset);
	
	imageEntete image;

	fread(&image,sizeof(imageEntete),1,transporteur);

	printf("tailleEntete : %d\n", image.tailleEntete);
	printf("largeur : %d\n", image.largeur);
	printf("hauteur : %d\n", image.hauteur);
	printf("plan : %d\n", image.plan);
	printf("profondeur : %d\n", image.profondeur);
	printf("compression : %d\n", image.compression);
	printf("tailleImage : %d\n", image.tailleImage);
	printf("resolution Horizontale : %d\n", image.resolutionHorizontale);
	printf("resolution Verticale : %d\n", image.resolutionVerticale);
	printf("nombre Couleurs : %d\n", image.nombreCouleurs);
	printf("nombre Couleurs Importantes : %d\n", image.nombreCouleursImportantes);

	fclose(transporteur);

}


void image(char* imagetransporteur, char* nouvelleimage){

	FILE* transporteur = fopen(imagetransporteur, "rb");
	if (transporteur == NULL) exit(EXIT_FAILURE);
	FILE* image = fopen(nouvelleimage, "wb");
	if (image == NULL) exit(EXIT_FAILURE);

	int caractere_courant;
	int i=0;
	int valeur;
	
	do{
		caractere_courant = fgetc(transporteur);
		i++;
	} while(i < 54);


	do{
		valeur = 0;
		for (i=0; i<8; i++){
			caractere_courant = fgetc(transporteur);
			if (caractere_courant == EOF)
				break;
				
			if (caractere_courant & 1){
				valeur = valeur<<1;
				valeur +=1;
			}
			else{
				valeur = valeur<<1;
			}
		}
		fputc(valeur, image);


	}while (caractere_courant != EOF);

	fclose(transporteur);
	fclose(image);

}


/*
	placer le header dans le nouveau fichier
	prendre un octet du fichier originel, prendre le LSB d'un octet de source, corriger la valeur de l"octet le placer dans le nouveau fichier
	shift a gauche recommencer 7 fois
	Prendre un nouvel octet dans le fichier originel
*/



void masquage(){

	FILE* originel = fopen("originel.bmp", "rb");
	if (originel == NULL) exit(EXIT_FAILURE);
	FILE* source = fopen("newimage.bmp", "rb");
	if (source == NULL) exit(EXIT_FAILURE);
	FILE* new = fopen("newtransporteur.bmp", "wb");
	if (new == NULL) exit(EXIT_FAILURE);

	int i=0;
	int caractere_courant;
	int poids_faible;
	int MSB;

	for(i = 0; i < 54; i++){
		caractere_courant = fgetc(originel);
		fputc(caractere_courant,new);
	}

	do{
	
		poids_faible = fgetc(source);
		
		for( i=0; i<8; i++){
			MSB = poids_faible;
			caractere_courant = fgetc(originel);
			if(caractere_courant == EOF)
				break;
			if(poids_faible == EOF){
				caractere_courant &= 0xFE;
				caractere_courant +=1;
				fputc(caractere_courant,new);
			}
			else{
				caractere_courant&=0xFE;
				MSB = MSB & 0x80;
				MSB = MSB >> 7;
				
			
				caractere_courant |= MSB;
				fputc(caractere_courant, new);
			
				poids_faible = poids_faible << 1;
			}

		}

	}while(caractere_courant != EOF);



	fclose(originel);
	fclose(source);
	fclose(new);

}