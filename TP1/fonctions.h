#ifndef FONCTIONS_H
#define FONCTIONS_H

void affiche(int* a, int n);

int compare(int* a, int *b, int n);

void swap(int* a, int* b);

int BubbleSort(int* a, int n);

int insertionSort (int *tab, int taille);

void merge(int* tab, int* tmp, int left, int mid, int right, int* cnt);

int mergeSort(int* tab, int taille);

int min (int a, int b);

#endif