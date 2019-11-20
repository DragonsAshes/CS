
#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include <math.h>


void affiche(int* a, int n){
	int i;
	for (i = 0 ; i < n ; i++){
		printf("%d ", a[i]);
	}
	printf("\n\n");
}

int compare(int* a, int *b, int n){
	int i;
	for(i=0; i < n ; i++){
		if (a[i] != b[i]){
			printf("Comparison FAILED at index %d\n\n", i);
			return i;
		}
	}
	printf("Comparison OK\n\n");
	return -1;	
}


void swap(int* a, int* b){
	int c;
	c = *a;
	*a = *b;
	*b =c;	
}

int BubbleSort(int* tab, int taille){  
	affiche(tab, taille);
	int nbcomp=0;
	int i;
	int j;

	for(j=0; j<taille-1; j++){
		for (i=0; i<taille-j-1; i++){
			nbcomp++;
			if (tab[i] > tab[i+1]){
				swap (&tab[i], &tab[i+1]);
			}
		}
	}
	affiche(tab , taille);
	printf("%d\n", nbcomp);
	
	return nbcomp;
}


int insertionSort(int* tab, int taille){
	affiche(tab, taille);
	int nboperations = 0;
	int i;
	int compteur = 1;
	while(compteur == 1){
		compteur = 0;
		for(i = 1; i < taille ; i++){
			if ( tab[i] < tab[i-1] ){
				while(tab[i] < tab[i-1] && (i)!=0){
					swap( tab+i , tab+(i-1) );
					i--;
					compteur++;
					nboperations++;
					
				}
			}
		}

	}
	affiche(tab, taille);
	printf("%d\n", nboperations);
	
	return nboperations;
} 


void merge(int* tab, int* tmp, int left, int mid, int right, int* cnt){
	
	int compteur = left;
	int save = left;
	int save2 = right;
	int save3 = mid;

	while( left < save3 && mid <= save2 ){
		if(tab[left] <= tab[mid]){
			tmp[compteur] = tab[left];
			left++;
			compteur++;
			(*cnt)++;
			
		}
		else if(tab[left] > tab[mid]){
			tmp[compteur] = tab[mid];
			mid++;
			compteur++;
			(*cnt)++;
			
		}
		
	}
	
	if ( left == save3 ){
		while (mid <= right){
			tmp[compteur] = tab[mid];
			mid++;
			compteur++;
			(*cnt)++;
			
			
		}
	}
	if (mid == right+1){
		while (left < save3){
			tmp[compteur] = tab[left];
			left++;
			compteur++;
			(*cnt)++;
			
			
		}
	}

	

	int i;
	for ( i = save ; i <= save2 ; i++){
		tab[i]=tmp[i];
		
	
	}
	

}

int min(int a, int b){
	int valeur;
	if (a<b){
		valeur = a;
	}
	else{
		valeur = b;
	}
	return valeur;
}

int mergeSort(int* tab, int taille){
	affiche(tab, taille);
	int* tmp = NULL;
	tmp = malloc(taille*sizeof(int)); 
	int i,j;
	int cnt = 0;
	int compteur=0;
	int left;
	int mid;
	int right;
	int k = 1;

	for (i=1; i<(taille); i*=2){
		int l = pow(2,k);
		for(j=0; j<taille; j+=l){
			left = j;
			mid = min(j + i, taille-1);
			right = min(j+2*i-1, taille-1);

			merge(tab, tmp, left, mid, right, &cnt);
			compteur++;



			
		}
		k++;
		

	}
	affiche(tab, taille);
	printf("%d\n", cnt);
	free(tmp);

	return(compteur);
}