#define CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

struct Cofetarie {
	char* nume;
	int nrAngajati;
	float* salarii;
};

void afiseazaCofetarie(struct Cofetarie c) {
	if (c.nume != NULL) {
		printf("\nNume: %s", c.nume);

	}
	printf("\nNumar angajati: %d\n", c.nrAngajati);
	if (c.salarii != NULL) {
		printf("Salarii: ");

		for (int i = 0; i < c.nrAngajati; i++) {
			printf("%5.2f", c.salarii[i]);
		}
		printf("\n");
	}
}

struct Cofetarie initializareCofetarie(const char* nume, int nrAngajati, const float* salarii) {
	struct Cofetarie c;
	c.nume = malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrAngajati = nrAngajati;
	c.salarii = malloc(sizeof(float) * nrAngajati);

	for (int i = 0; i < nrAngajati; i++) {
		c.salarii[i] = salarii[i];
	}
	return c;
}

void stergeCofetarie(struct Cofetarie* c) {
	if (c->nume != NULL) {
		free(c->nume);
	}
	free(c->salarii);
	c->nume = NULL;
	c->salarii = NULL;
}

int main() {
	struct Cofetarie cofetarie1;

	//malloc returneaza un pointer!
	cofetarie1.nume = (char*)malloc(strlen("Dulce") + 1); //marimea e exprimata in octeti (bytes)
	strcpy(cofetarie1.nume, "Dulce");
	cofetarie1.nrAngajati = 3;
	cofetarie1.salarii = (float*)malloc(sizeof(float) * cofetarie1.nrAngajati);
	for (int i = 0; i < cofetarie1.nrAngajati; i++) {
		cofetarie1.salarii[i] = (i + 1) * 1000;
	}
	afiseazaCofetarie(cofetarie1);

	float* vector = malloc(sizeof(float) * 2);
	vector[0] = 4567;
	vector[1] = 3456;

	struct Cofetarie cofetarie2 = initializareCofetarie("Mara", 2, vector);

	afiseazaCofetarie(cofetarie2);

	free(cofetarie1.nume);
	free(cofetarie1.salarii);

	free(vector);
	stergeCofetarie(&cofetarie2);
	//afiseazaCofetarie(cofetarie2);

	free(cofetarie2.nume);
	free(cofetarie2.salarii);

	return 0;
}