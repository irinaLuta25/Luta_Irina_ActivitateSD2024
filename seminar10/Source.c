//arbore = graf conex cu n-1 muchii
//arbore binar = fiecare nod are cel mult 2 fii


//arbore binar de cautare = inf din radacina trb sa fie mai mare decat fiu stanga si mai mica decat fiu dreapta
//          5

//       3     8
       
//       1   6  10


//fiecare nod trebuie sa contina informatia utila si fii

//putem citi un arbore in 3 moduri 
//radacina stanga dreapta = preordine (radacina e in fata)
//stanga dreapta radacina = postordine (radacina e la final)
//stanga radacina dreapta = inordine (radacina e la mijloc)

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Rezervare Rezervare;
struct Rezervare {
    int id;
    char* numeClient;
    int nrPersoane;
};

typedef struct Nod Nod;
struct Nod {
    Nod* stanga;
    Nod* dreapta;
    Rezervare info;
};


void citireRezervare(FILE* f, Rezervare* rez) {
    fscanf(f, "%d",(&rez->id));
    
    char aux[30];
    fscanf(f, "%s", &aux);
    rez->numeClient = (char*)malloc(sizeof(char) * strlen(aux)+1);
    strcpy(rez->numeClient, aux);

    fscanf(f, "%d", (& rez->nrPersoane));
}

Nod* inserareArbore(Nod* arbore, Rezervare rez) {

    if (arbore != NULL) {
        if (arbore->info.id < rez.id) {
            arbore->dreapta = inserareArbore(arbore->dreapta, rez); //aici imi returneaza alta radacina pe care o punem in fiul din dreapta
        }
        else
        {
            arbore->stanga = inserareArbore(arbore->stanga, rez);
        }
    }
    else
    {
        Nod* temp = (Nod*)malloc(sizeof(Nod));
        temp->info = rez; //shallow copy
        temp->dreapta = NULL;
        temp->stanga = NULL;

        arbore = temp;
    }

    return arbore;
}

void citireFisier(const char* numeFisier, Nod** nodRadacina) {
    FILE* f = fopen(numeFisier, "r");

    int nrRezervari = 0;
    fscanf(f, "%d", &nrRezervari);



    for (int i = 0; i < nrRezervari;i++) {
        Rezervare rez;
        citireRezervare(f, &rez);

        *nodRadacina = inserareArbore(*nodRadacina, rez);
    }

}

void afisareRezervare(Rezervare r) {
    printf("Rezervarea %d facuta de %s are %d persoane.\n", r.id, r.numeClient, r.nrPersoane);
}

//putem citi un arbore in 3 moduri 
//radacina stanga dreapta = preordine (radacina e in fata)
//stanga dreapta radacina = postordine (radacina e la final)
//stanga radacina dreapta = inordine (radacina e la mijloc)
void afisareArborePreOrdine(Nod* arbore) {
    if (arbore != NULL) //mereu verficam daca avem arbore
    {
        afisareRezervare(arbore->info);
        afisareArborePreOrdine(arbore->stanga);
        afisareArborePreOrdine(arbore->dreapta);
    }
}


void afisareArboreInOrdine(Nod* arbore) { //sorteaza elementele in ordine crescatare = sortarea binara
    if (arbore != NULL ) {
        afisareArboreInOrdine(arbore->stanga);
        afisareRezervare(arbore->info);
        afisareArboreInOrdine(arbore->dreapta);
    }
}

void afisareArboreInPostOrdine(Nod* arbore) {
    if (arbore != NULL) {
        afisareArboreInOrdine(arbore->stanga);
        afisareArboreInOrdine(arbore->dreapta);
        afisareRezervare(arbore->info);
    }
}


//functie care cauta un nod(adica o rez) dupa id
Rezervare cautareDupaId(Nod* radacina, int id)
{
    if (radacina != NULL) {
        if (radacina->info.id < id)
            return cautareDupaId(radacina->dreapta, id);
        else
            if (radacina->info.id > id)
                return cautareDupaId(radacina->stanga, id);
            else
                return radacina->info; //in acest caz sunt egale
    }
    else
    {
        Rezervare r;
        r.id = -1;
        r.numeClient = NULL;
        r.nrPersoane = -1;

        return r;
    }
}

//suma tuturor pers -> facem suma stanga + suma dreapta + nr de pers din radacina
int calculNrTotalPersoane(Nod* rad) {
    if (rad) {
        int rPersoane = rad->info.nrPersoane; //nr de pers din radacina
        int sPersonae = calculNrTotalPersoane(rad->stanga); //nr de pers stanga
        int dPersonae = calculNrTotalPersoane(rad->dreapta);

        return rPersoane + sPersonae + dPersonae;
    }
    else {
        return 0;
    }
}

void main() {
    Nod* radacina = NULL;

    citireFisier("rezervari.txt", &radacina);

    afisareArborePreOrdine(radacina);

    printf("\n---------------------------------\n");
    afisareRezervare(cautareDupaId(radacina, 4));

    printf("\n---------------------------------\nNr total de pers: %d", calculNrTotalPersoane(radacina));
    
}