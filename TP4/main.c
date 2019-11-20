#include <stdio.h> 
#include <stdlib.h>
#include <strings.h> 
#include <string.h> 
#include <unistd.h> 
#include "AlgoGenetique.h" 

//J'ai modifie les tailles de populations

/*int main(){
	srand(time(NULL));
	groupe init;
	groupe parents;
	parents.nombre = 4;
	init.nombre = 10;
	generationAleatoire(&init);
	reproduction(&init, &parents);
	printf("\n\n\n");
	for(int i = 0; i < parents.nombre; i++)
	{
		for(int j = 0; j < NBGENE/2; j++)
		{
			printf("%d , ", parents.membres[i].gene[j]);
		}
		printf("\n");
	 	printf("%d\n", parents.membres[i]);
	}

}*/




int main(int argc, char *argv[]) 
{	
	srand(time(NULL));

	int opt,nbgeneration=0;
 	groupe population,parents; 

	// les valeurs par defaut. 	
	population.nombre=NBPOPULATION; 
	parents.nombre=NBPARENTS; 
	
 	while ((opt = getopt(argc, argv, "p:P:")) != -1) {
               switch (opt) {
               case 'p':
                   population.nombre=atoi(optarg);
                   break;
               case 'P':
                   parents.nombre = atoi(optarg);
                   break;
               default: /* '?' */
                   fprintf(stderr, "Usage: %s [-p nbpopulation] [-P nbparents] \n",argv[0]);
                   exit(EXIT_FAILURE);
               }
        }
	// test et allocation mémoire. 
	if (parents.nombre > population.nombre) exit(EXIT_FAILURE);  

	if ((population.membres=malloc(sizeof(serpent)*population.nombre)) == NULL ) exit(EXIT_FAILURE);
	if ((parents.membres=malloc(sizeof(serpent)*parents.nombre)) == NULL ) exit(EXIT_FAILURE);

	// creation de la premiere génération 
	generationAleatoire(&population);

 
	while (evaluation(&population)) {
		selection(&population,&parents); 
		reproduction(&population,&parents); 
		mutation(&population); 
		nbgeneration++;
	}
	printf("Generation %d\n",nbgeneration);  

	free(population.membres); 
	free(parents.membres); 

}

