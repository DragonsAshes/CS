#ifndef NBPOPULATION
#define NBPOPULATION 100
#endif 

#ifndef NBPARENTS
#define NBPARENTS 10
#endif 

#define MAX 2000000
#define SEEK 666

#ifndef NBGENE
#define NBGENE 64
#endif 

typedef struct {
	unsigned char gene[NBGENE/2];  
	int score; 
} serpent; 

typedef struct { 
	serpent *membres; 
	int nombre; 
} groupe; 



void affiche(unsigned char *gene); 
void calcul(serpent *g); 
void selection(groupe *population,groupe *parents); 
int evaluation(groupe *population); 
void generationAleatoire(groupe *population); 
void reproduction(groupe *population,groupe *parents); 
void mutation (groupe *population); 
char convert(char chr);


