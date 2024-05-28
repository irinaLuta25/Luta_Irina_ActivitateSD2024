#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Masina {
	int id; 
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));

	for (int i = 0; i < (*nrMasini);i++) {
		aux[i] = masini[i]; 
	}
	aux[(*nrMasini)] = m;
	(*nrMasini)++; //am adaugat o masina deci creste numarul 

	if(masini != NULL) free(masini);
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
	FILE* f = fopen(numeFisier, "r"); //fopen returneaza un FILE*
	//fscanf citeste pana la spatiu => citesc intreaga linie si dupa o sparg la fiecare linie
	char buffer[100];
	const char delimitare[] = ",\n";
	struct Masina* masini = NULL;
	(*nrMasini) = 0;

	while (fgets(buffer, 100, f) != NULL) //fgets citeste o linie intreaga
	{
		char* element = strtok(buffer, delimitare);
		
		struct Masina m;
		
		m.id = atoi(element); //atoi=ascii to int (un fel de cast la int); strtoi=string to int
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator,element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);

		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(f);
	return masini;
}


int main() {
	int nrMasini = 0;
	struct Masina* masini = citireFisier("masini.txt.txt", &nrMasini);
	

	for (int i = 0; i < nrMasini; i++) {
		printf("Masina nr %d \n", i+1);
		printf("id: %d \n", masini[i].id);
		printf("Producator: %s \n", masini[i].producator);
		printf("Nr usi: %d \n", masini[i].nrUsi);
		printf("Pret: %5.2f \n", masini[i].pret);
		printf("\n");
	}
}