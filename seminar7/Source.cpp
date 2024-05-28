#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

//generam un cod(cod hash) pt fiecare obiect
//prin functia hash se incearca ca outputul sa fie cam la fel desi inputul e f diferit
//cu cat dispersia e mai mica cu atat sansele de conflict sunt mai mari

typedef struct Galerie Galerie;
struct Galerie {
	int cod;
	char* nume;
	float pretIntrare;
};

typedef struct nod nod;
struct nod {
	Galerie info; //informatie utila
	nod* next;
};

typedef struct hashTable HashTable;
struct hashTable {
	nod** vector;  //avem vector de pointeri
	int dim; 
};

//initializarea tabelei hash
  //trb sa alocam spatiu pt vectorul de pointeri
HashTable initializareHashTable(int dimensiune) {
	HashTable hash;
	hash.dim = dimensiune;
	hash.vector = (nod**)malloc(sizeof(nod*) * dimensiune);
	for (int i = 0; i < dimensiune;i++)
		hash.vector[i] = NULL;

	return hash;
}


Galerie initGalerie(int cod, const char* nume, float pret) {
	Galerie g;
	g.cod = cod;
	g.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(g.nume, nume);
	g.pretIntrare = pret;

	return g;
}


//inserarea in tabela se face pe codul hash
 //=> ne trebuie o functie care calculeaza codul hash
  //functia returneaza pozitia unde o sa inseram(de aceea ii dam dimensiunea casa stie unde se opreste)
int calculHash(int cod, const char* nume, int dimensiune){
	if (dimensiune > 0) {
		int rez = cod * strlen(nume);
		return rez % dimensiune;
	}
	return -1;
}


void inserareLaFinal(nod** cap, Galerie galerie) { //pe nod il trimit pointer pt ca il modific
	nod* temp = (nod*)malloc(sizeof(nod)); 
	temp->info = galerie; //shallow copy dar e ok
	temp->next = NULL;
	if (*cap) { //daca nu am lista nu are sens sa parcurg
		nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = temp;
	}
	else{
		*cap = temp; 
	}
}

//functie de inserare a unei galerii in tabela
void inserareGalerieInTabela(HashTable hash, Galerie galerie) {//nu pointer pt hash pt ca vectorul e deja in heap 
	if (hash.dim > 0){  //ne asiguram ca avem tabela
		int pozitie = calculHash(galerie.cod, galerie.nume, hash.dim);
		if (hash.vector[pozitie] != NULL) //daca e dif de null inaseamna ca deja am ceva acolo si trb sa inserez la finalul listei
			//acest if e aici doar pt a prezenta situatia de conflict
		{
			inserareLaFinal(&(hash.vector[pozitie]), galerie);
		}
		else { //in acest caz nu e conflict => nu am coleziune(adica mai multe obiecte pe aceeasi poz)
			inserareLaFinal(&(hash.vector[pozitie]), galerie);
		}

}
}

void afisareGalerie(Galerie g) {
	printf("%d. Intrarea la galeria %s costa %.2f\n", g.cod, g.nume, g.pretIntrare);
}

void afisareListaGalerii(nod* cap) {
	while (cap) {
		afisareGalerie(cap->info);
		cap = cap->next;
	}
}

void afisareTabela(HashTable tabela) {
	//avem un vector de liste
	for (int i = 0;i < tabela.dim; i++) {
		if (tabela.vector[i] != NULL) {
			printf("\nClusterul: %d\n", (i + 1));
			afisareListaGalerii(tabela.vector[i]);
		}
	}
}

Galerie cautaGalerieDupaCheie(int cod, const char* nume, HashTable tabela) { //la noi cheia e compusa din cod si nume
	int pozitie = calculHash(cod, nume, tabela.dim);
	//pe baza pozitiei cautam in lista
	if (pozitie >= 0 && pozitie < tabela.dim) {
		nod* p = tabela.vector[pozitie];
		while (p && p->info.cod != cod && strcmp(p->info.nume, nume) != 0) {
			p = p->next;
		}
		if (p) {
			return p->info; //shallow copy
		}
		else { //daca p nu exista o sa returnez o galerie care nu exista 
			return initGalerie(-1, "", 0);
		}
	}
	return initGalerie(-1, "", 0);
}


void main() {
	Galerie g1=initGalerie(1,"Orizont",10);
	Galerie g2 = initGalerie(2, "Cercul armatei", 6);
	Galerie g3 = initGalerie(3, "Louvre", 30);
	Galerie g4 = initGalerie(4, "Antipa", 20);
	Galerie g5 = initGalerie(5, "Istorie", 15);
	Galerie g6 = initGalerie(6, "Geologie", 17);

	HashTable tabela = initializareHashTable(5);

	inserareGalerieInTabela(tabela, g1);
	inserareGalerieInTabela(tabela, g2);
	inserareGalerieInTabela(tabela, g3);
	inserareGalerieInTabela(tabela, g4);
	inserareGalerieInTabela(tabela, g5);
	inserareGalerieInTabela(tabela, g6);

	afisareTabela(tabela);

	Galerie g = cautaGalerieDupaCheie(1,"Orizont",tabela);
	printf("\nCautata galerie: ");
	afisareGalerie(g);

}