#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

struct Farmacie {
	int id;
	char* nume;
	float suprafata;
};

struct Farmacie initializareFarmacie(int id, const char* nume, float suprafata)
{
	struct Farmacie f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;

	return f;
}

void afisareFarmacie(struct Farmacie farmacie) {
	printf("%d. %s are o suprafata de %5.2f mp\n", farmacie.id, farmacie.nume, farmacie.suprafata);
}

void afisareVector(struct Farmacie* farmacii, int nrFarmacii) {
	//printf("%5.2f", (float)sizeof(farmacii) / (float)sizeof(struct Farmacie)); //nu merge sa sccriem asa la dinamic
	for (int i = 0;i < nrFarmacii;i++) { 
		afisareFarmacie(farmacii[i]);
	}
}

struct Farmacie* copieazaNElemente(struct Farmacie* vector, int nrFarmacii, int n) { //n = nr elemente copiate
	if (n <= nrFarmacii && n > 0) {
		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * n);
		for (int i = 0;i < n;i++)
		{
			copiat[i] = initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
		return copiat;
	}
	else
		return NULL;

}

struct Farmacie* copiazaFarmaciiMici(struct Farmacie* farmacii, int nrFarmacii, float pragSuprafata, int* nrFarmaciiMici) {
	*nrFarmaciiMici = 0;
	for (int i = 0;i < nrFarmacii;i++)
		if (farmacii[i].suprafata < pragSuprafata) (*nrFarmaciiMici)++;

	struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*nrFarmaciiMici)); //derefe nrfarmmici pt ca e pointer
	int k = 0;
	for (int i = 0;i < nrFarmacii;i++)
	{
		if (farmacii[i].suprafata < pragSuprafata)
			vector[k++] = initializareFarmacie(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata);
	}
	//ca sa dezaloc pozitiile in care nu am pus trec din nou prin for si dezaloc negatia conditiei cu &
	return vector;
}

void dezalocareVectorFarmacii(struct Farmacie** vector, int* nrFarmacii) //cu 2 ** pentru ca nu vrem sa avem dangling pointers
{
	for (int i = 0; i < *nrFarmacii;i++) {
		free((*vector)[i].nume);
	}
	free(*vector);
	*nrFarmacii = 0;
	*vector = NULL;
}

struct Farmacie getFarmacieByID(struct Farmacie* vector, int nrFarmacii, int idCautat) {//cautam dupa id si returnam
	for (int i = 0;i < nrFarmacii;i++) {
		if (vector[i].id == idCautat)
			return initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
	}
	return initializareFarmacie(0, "N\A", 0);
}

int main() {
	//un vector este o struct de date omogena, liniara, ocupa o zona de memorie contigua (ceea ce ne permite accesul)
	//daca un vector e alocat static se afla in stiva
	
	int nrFarmacii = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);

	for (int i = 0;i < nrFarmacii;i++) {
		farmacii[i] = initializareFarmacie(i + 1, "Farmacie", 30 * i + 10);

	}

	afisareVector(farmacii, nrFarmacii);

	int nrObiecteCopiate = 2;

	struct Farmacie* farmaciiCopiate = copieazaNElemente(farmacii, nrFarmacii, nrObiecteCopiate);

	printf("\n\n");
	afisareVector(farmaciiCopiate, nrObiecteCopiate);

	farmacii[3].suprafata = 20;

	int nrFarmaciiMici = 0;
	struct Farmacie* farmaciiMici = copiazaFarmaciiMici(farmacii, nrFarmacii, 50, &nrFarmaciiMici);
	printf("\n\n");
	afisareVector(farmaciiMici, nrFarmaciiMici);

	struct Farmacie farmacieCautata = getFarmacieByID(farmacii, nrFarmacii, 9);
	printf("\nFarmacie cautata: ");
	afisareFarmacie(farmacieCautata);
	free(farmacieCautata.nume);

	dezalocareVectorFarmacii(&farmacii, &nrFarmacii);
	dezalocareVectorFarmacii(&farmaciiCopiate, &nrObiecteCopiate);
	dezalocareVectorFarmacii(&farmaciiMici, &nrFarmaciiMici);

}
