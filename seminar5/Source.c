#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
//la vect avem acces direct pt ca ocupa o zona de memorie contigua ,
//lista se parcurge secvential
//lista nu stocheaza elementele unul dupa altul, deci la fiecare nod trb sa salvam adresa urmatorului nod (practic ca sa ajung la 3 trebuie as trec prin 1 -> apoi prin 2 -> 3)
//putem sa inseram in lista la inceput, la final sau la mijloc (3 moduri de inserare)
//primul nod mai poarta denumirea de cap 

typedef struct Santier Santier; //definim un alias pt struct santier cu santier
typedef struct Nod Nod;
struct Santier {
	char* numeProiect;
	int numarMuncitori;
	float suprafata;
};

struct Nod {
	Santier santier;
	Nod* next; //adresa urmatorului nod 
};

Nod* inserareInceput(Santier santier, Nod* lista) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->santier = santier; //putem sa facem shallow copy si nu mai folosim acel santier dupa
	nod->next = lista;
	return nod;

}

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
	Santier santier;
	santier.numeProiect = (char*)malloc(sizeof(char) * strlen(numeProiect) + 1 );
	strcpy(santier.numeProiect, numeProiect);
	santier.numarMuncitori = nrMuncitori;
	santier.suprafata = suprafata;

	return santier;

}

void afisareSantier(Santier s) {
	printf("Santierul %s are %d muncitori si %5.2f mp.\n", s.numeProiect, s.numarMuncitori, s.suprafata);
}

void afisareLista(Nod* lista) {
	while (lista != NULL) {

		afisareSantier(lista->santier); //procesare
		lista = lista->next; //parcurgerea clasica pt o lista simpla inlantuita
		
	}
}

int sumaMuncitori(Nod* lista) {
	int suma = 0;
	while (lista != NULL) {
		suma = suma + lista->santier.numarMuncitori;
		lista = lista->next;
	}

	return suma;
}

void stergereLista(Nod** lista) { // (Nod* &lista)
	while ((*lista) != NULL) {
		free((*lista)->santier.numeProiect);
		Nod* aux = (*lista);
		(*lista) = (*lista)->next;
		free(aux);
	}
	(*lista) = NULL;
}

float denistateMuncitori(Santier santier)//functie care returneaza santierul cu denistatea cea mai mare pe metru patrat
{
	if (santier.suprafata > 0) {
		return santier.numarMuncitori / santier.suprafata;
	}
}

char* numeSantierDensitateMaxima(Nod* lista) {
	float max = 0;
	char* aux = NULL;
	while (lista != NULL) {
		if (denistateMuncitori(lista->santier) > max) {
			max = denistateMuncitori(lista->santier);
			aux = lista->santier.numeProiect;
		}
		lista = lista->next;
	}
	char* numeProiectDensitate = (char*)malloc(strlen(aux) + 1);
	strcpy(numeProiectDensitate, aux);

	return numeProiectDensitate;
	
}

int main() {
	Nod* lista = NULL; 
	Santier s1 = initializareSantier("Santier 1", 10, 300);
	Santier s2 = initializareSantier("Santier 2", 27, 2000);
	Santier s3 = initializareSantier("Santier 3", 5, 150);

	lista = inserareInceput(s1, lista);
	lista = inserareInceput(s2, lista);
	lista = inserareInceput(s3, lista);
	lista = inserareInceput(initializareSantier("Santier 4", 14, 730), lista);

	afisareLista(lista);

	int suma = sumaMuncitori(lista);
	printf("\nNumar muncitori: %d\n", suma);

	char* aux = numeSantierDensitateMaxima(lista);
	printf("\nDensitate maxima: %s\n", aux);

	
	stergereLista(&lista);
	afisareLista(lista);
}