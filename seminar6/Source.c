//liste dublu inlanuite = o struct de date omogena care cont 3 elem
//ultimul nod are null pt urmatoarea poz
//primul nod are null pt precedentul nod
//la liste dublu inlantuite putem parcurge lista si de la sfarsit la inceput
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Santier Santier; //definim un alias pt struct santier cu santier
struct Santier {
	char* numeProiect;
	int numarMuncitori;
	float suprafata;
};

typedef struct NodLdi NodLdi;
struct NodLdi {
	NodLdi* prev;
	NodLdi* next;
	Santier info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	NodLdi* prim;
	NodLdi* ultim;
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
	Santier santier;
	santier.numeProiect = (char*)malloc(sizeof(char) * strlen(numeProiect) + 1);
	strcpy(santier.numeProiect, numeProiect);
	santier.numarMuncitori = nrMuncitori;
	santier.suprafata = suprafata;

	return santier;

}

void afisareSantier(Santier s) {
	printf("Santierul %s are %d muncitori si %5.2f mp.\n", s.numeProiect, s.numarMuncitori, s.suprafata);
}



float denistateMuncitori(Santier santier)//functie care returneaza santierul cu denistatea cea mai mare pe metru patrat
{
	if (santier.suprafata > 0) {
		return santier.numarMuncitori / santier.suprafata;
	}
}

//fct de inserare la inceput
void inserareInceput(ListaDubla* lista, Santier s) {
	NodLdi* aux = malloc(sizeof(NodLdi));
	aux->info = s;
	aux->next = lista->prim;
	aux->prev = NULL;
	if (lista->prim != NULL) {
		lista->prim->prev = aux;
	}
	else {
		lista->ultim = aux;
	}
	lista->prim = aux;
}

void inserareSfarsit(ListaDubla* lista, Santier s) {
	NodLdi* aux = malloc(sizeof(NodLdi));
	aux->info = s;
	aux->next = NULL;
	aux->prev = lista->ultim;
	if (lista->prim != NULL) {
		lista->ultim->next = aux;
	}
	else {
		lista->prim = aux;
	}
	lista->prim = aux;
}

void afisareLdiDeLaInceput(ListaDubla lista) {
	for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
		afisareSantier(nod->info);
	}
	printf("\n");
}

void afisareLdiDeLaSfarsit(ListaDubla lista) {
	for (NodLdi* nod = lista.ultim; nod != NULL; nod = nod->prev) {
		afisareSantier(nod->info);
	}
	printf("\n");
}

//sa stergem nodul care contine santierul cu numr dat
void stergereSantierDupaNume(ListaDubla* lista, const char* numeSantier) {

	NodLdi* nod = lista->prim;
	while (nod != NULL) {
		if (strcmp(nod->info.numeProiect, numeSantier) == 0) {
			if (nod->prev == NULL) {//inseamna ca ce cautam este primul nod 
				if (nod->next == NULL) {
					lista->prim = NULL;
					lista->ultim = NULL;
				}
				else {
					nod->next->prev = NULL;
					lista->prim = nod->next;
				}
			}
			else {
				if (nod->next == NULL) { //este la final
					nod->prev->next = NULL;
					lista->ultim = nod->prev;
				}
				else { //aici stim sigur ca e la mijloc deci lista dubla nu se modifica
					nod->prev->next = nod->next;
					nod->next->prev = nod->prev;
				}
			}
			free(nod->info.numeProiect);
			free(nod);
			nod = NULL;
		}
		else {
			nod = nod->next;
		}
	}
}

void stergereCompleta(ListaDubla* lista) {
	if (lista != NULL) {
		NodLdi* aux = lista->prim;
		while (aux != NULL) {
			free(aux->info.numeProiect); //am sters inform utila
			NodLdi* temp = aux->next;
			free(aux);
			aux = temp;
		}
		lista->prim = NULL;
		lista->ultim = NULL;
	}
}

int calculNrTotalMuncitori(ListaDubla lista) {
	int suma = 0;
	for (NodLdi* i = lista.prim; i != NULL;i=i->next ) {
		suma += i->info.numarMuncitori;
	}
	return suma;
}

int calculNrMuncitoriSuprafata(ListaDubla lista,float suprafataMaxima) {
	int suma = 0;
	for (NodLdi* i = lista.prim; i != NULL;i = i->next) {
		if(i->info.suprafata < suprafataMaxima)
		suma += i->info.numarMuncitori;
	}
	return suma;
}

int main() {
	
	Santier s1 = initializareSantier("Santier 1", 10, 300);
	Santier s2 = initializareSantier("Santier 2", 27, 2000);
	Santier s3 = initializareSantier("Santier 3", 5, 150);

	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareInceput(&lista, s1);
	inserareInceput(&lista, s2);
	inserareInceput(&lista, s3);

	afisareLdiDeLaInceput(lista);

	//stergereSantierDupaNume(&lista, "Santier 1");
	//afisareLdiDeLaInceput(lista);
	//stergereSantierDupaNume(&lista, "Santier 2");
	//afisareLdiDeLaInceput(lista);
	//stergereSantierDupaNume(&lista, "Santier 3");
	//afisareLdiDeLaInceput(lista);

	//stergereCompleta(&lista);
	//afisareLdiDeLaInceput(lista);

	int nrMuncitori = calculNrTotalMuncitori(lista);
	printf("\nNumar total muncitori: %d", nrMuncitori);

	int nrMuncitoriSuprafata = calculNrMuncitoriSuprafata(lista, 2000);
	printf("\nNumar total muncitori: %d", nrMuncitoriSuprafata);
}