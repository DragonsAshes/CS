#include <stdio.h> 
#include <stdlib.h>
#include <strings.h> 
#include <string.h> 
#include <unistd.h> 
#include "AlgoGenetique.h" 



#define lire(gene,i)    (i%2)?(gene[i/2]&0xF):(gene[i/2]>>4); 

char convert(char chr)
{
	if(chr >= '0' && chr <= '9')
		return (chr - '0');
	else if(chr >= 'A' && chr <= 'F')
		return (10 + chr - 'A');
	return 0;
}

void affiche(unsigned char *gene)
{
	char code[]="+-*/"; 
	int i=0,res;  
	// the last gene is useless 
	while (i<(NBGENE-1)) {
		res=lire(gene,i); 
		if (i%2)
			printf("%c ",code[res%4]); 
		else 
			printf("0x%x ",res);	
		i=i+1; 
	}
	printf("\n"); 
}

void calcul(serpent *g) 
{
	
	char code[]="+-*/";
	char valeurs[]= "0123456789ABCDEF";
	int i;
	char expression [NBGENE + 2];
	char operande;
	char operateur;
	int j = 0;

	for(i = 0; i < (NBGENE/2); i++ )
	{

		operande = (g->gene[i] >> 4);
		operateur = (g->gene[i] & 0x03);

		operateur = code[operateur];
		operande = valeurs[operande];
		//strcpy(operande, code[operateur]);
		//strcpy(operande, valeurs[operande]);


		expression[j++] = operande;
		expression[j++] = operateur;
	}

	expression[j-1] = 0;

	unsigned int calcul[NBGENE];
	int resultat = 0;
	j = 0;

	for(i = 0; i < strlen(expression); i++)
	{
		if( expression[i] == '*')
		{
			
			calcul[j-1] = calcul[j-1]*convert(expression[i+1]);			
			i++;
		}
		else if(expression[i] == '/')
		{
			if (expression[i+1] == '0')
			{
				g->score = MAX;
				return;
			}
			calcul[j-1] = calcul[j-1]/convert(expression[i + 1]);
			i++;
		}
		else if (expression[i] == '+' || expression[i] == '-')
		{
			calcul[j] = expression[i];
			j++;
		}
		
		else
		{
			calcul[j] = convert(expression[i]);
			j++;
			
		}
	}
	calcul[j] = 0x00;

	for( i = 0; i < j; i+=2)
	{
		if (i == 0)
		{
			resultat += convert(calcul[i]);
			continue;
		}
		if (calcul[i-1] == '+')
			resultat += calcul[i];
		else if(calcul[i-1] == '-')
			resultat -=  calcul[i];
	}
	g->score = abs(resultat - 666);
}


void testCalcul() 
{
int i,expect; 
serpent test[]={
	{"\x67\xc6\x69\x73\x51\xff\x4a\xec\x29\xcd\xba\xab\xf2\xfb\xe3\x46\x7c\xc2\x54\xf8\x1b\xe8\xe7\x8d\x76\x5a\x2e\x63\x33\x9f\xc9\x9a",660},
	{"\x66\x32\x0d\xb7\x31\x58\xa3\x5a\x25\x5d\x05\x17\x58\xe9\x5e\xd4\xab\xb2\xcd\xc6\x9b\xb4\x54\x11\x0e\x82\x74\x41\x21\x3d\xdc\x87",735},
	{"\x70\xe9\x3e\xa1\x41\xe1\xfc\x67\x3e\x01\x7e\x97\xea\xdc\x6b\x96\x8f\x38\x5c\x2a\xec\xb0\x3b\xfb\x32\xaf\x3c\x54\xec\x18\xdb\x5c",694},
	{"\x02\x1a\xfe\x43\xfb\xfa\xaa\x3a\xfb\x29\xd1\xe6\x05\x3c\x7c\x94\x75\xd8\xbe\x61\x89\xf9\x5c\xbb\xa8\x99\x0f\x95\xb1\xeb\xf1\xb3",646},
	{"\x05\xef\xf7\x00\xe9\xa1\x3a\xe5\xca\x0b\xcb\xd0\x48\x47\x64\xbd\x1f\x23\x1e\xa8\x1c\x7b\x64\xc5\x14\x73\x5a\xc5\x5e\x4b\x79\x63",MAX},
	{"\x3b\x70\x64\x24\x11\x9e\x09\xdc\xaa\xd4\xac\x0f2\x1b\x10\xaf\x3b\x33\xcd\xe3\x50\x48\x47\x15\x5c\xbb\x6f\x22\x19\xba\x9b\x7d\xf5",543},
	{"\x0b\xe1\x1a\x1c\x7f\x23\xf8\x29\xf8\xa4\x1b\x13\xb5\xca\x4e\xe8\x98\x32\x38\xe0\x79\x4d\x3d\x34\xbc\x5f\x4e\x77\xfa\xcb\x6c\x05",1302},
	{"\xac\x86\x21\x2b\xaa\x1a\x55\xa2\xbe\x70\xb5\x73\x3b\x04\x5c\xd3\x36\x94\xb3\xaf\xe2\xf0\xe4\x9e\x4f\x32\x15\x49\xfd\x82\x4e\xa9",MAX},
	{"\x08\x70\xd4\xb2\x8a\x29\x54\x48\x9a\x0a\xbc\xd5\x0e\x18\xa8\x44\xac\x5b\xf3\x8e\x4c\xd7\x2d\x9b\x09\x42\xe5\x06\xc4\x33\xaf\xcd",MAX},
	{"\xa3\x84\x7f\x2d\xad\xd4\x76\x47\xde\x32\x1c\xec\x4a\xc4\x30\xf6\x20\x23\x85\x6c\xfb\xb2\x07\x04\xf4\xec\x0b\xb9\x20\xba\x86\xc3",MAX},
	{"\x3e\x05\xf1\xec\xd9\x67\x33\xb7\x99\x50\xa3\xe3\x14\xd3\xd9\x34\xf7\x5e\xa0\xf2\x10\xa8\xf6\x05\x94\x01\xbe\xb4\xbc\x44\x78\xfa",727}
	};

	for(i=0;i<sizeof(test)/sizeof(serpent);i++) {
		expect=test[i].score; 
		calcul(&test[i]);
		if (expect != test[i].score) printf("error\n");  
	}
}


void selection(groupe *population,groupe *parents)
{
	int i = 0;
	int j;
	int k = 0;

	while( i <= MAX && k <= parents->nombre)
	{
		//printf("selection %d\n", i);
		for(j = 0; j < population->nombre; j++)
		{
				//printf("selection %d\n", i);
				if(population->membres[j].score == i)
				{
					parents->membres[k] = population->membres[j];
					k++;
				}
		}
		i++;
	}
}


int evaluation(groupe *population) 
{
	int i;
	for(i = 0; i < population->nombre; i++)
	{
		calcul(&population->membres[i]);
	}

	for(i = 0; i < population->nombre; i++)
	{
		if(population->membres[i].score == 0)
		{
			printf("Le membre %d est maléfique\n", i);
			return 0;
		}

	}
	return 1;

}




void generationAleatoire(groupe *population) 
{
	int i;
	int j;
	for(i = 0; i < population->nombre; i++)
	{
		for (j = 0; j < NBGENE/2; j++)
			population->membres[i].gene[j] = rand() % 0xff;
	}
}

void reproduction(groupe *population,groupe *parents)
{	
	for(int i = 0; i < population->nombre; i++)
	{
		int p1 = rand() % parents->nombre;
		
		int p2 = 0;
		do { p2 = rand() % parents->nombre; } while(p1 == p2);

		int dist = rand() % NBGENE / 2 ;
		memcpy(population->membres[i].gene, parents->membres[p1].gene, dist);
		memcpy(population->membres[i].gene + dist, parents->membres[p2].gene + dist, NBGENE / 2 - dist);
	}
}


void mutation (groupe *population)  //Choix de la mutation par subsitution
{
	int gene_selectionne;
	int new_valeur;
	int membre_selectionne;
	int pourcentage_mutation = rand() % 6;     //pourcentage de mutation
	int i;
	for(i = 0; i < pourcentage_mutation; i++)
	{
		new_valeur = rand() % 0xff;
		gene_selectionne =rand() % NBGENE/2;
		membre_selectionne = rand() % population->nombre;
		population->membres[membre_selectionne].gene[gene_selectionne] = new_valeur; 
	}

}



