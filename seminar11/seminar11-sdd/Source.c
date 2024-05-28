//arbore avl
//diferenta de inaltime intre subarborele stang si cel drept trebuie sa fie de maxim 1 = grad de echilibru
//noi facem stanga - dreapta => daca am 2 - 0 = 2 (pozitiv) => dezechilibru in stanga

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
    fscanf(f, "%d", (&rez->id));

    char aux[30];
    fscanf(f, "%s", &aux);
    rez->numeClient = (char*)malloc(sizeof(char) * strlen(aux) + 1);
    strcpy(rez->numeClient, aux);

    fscanf(f, "%d", (&rez->nrPersoane));
}

//SEMINAR 11 cu arbori avl ------------
Nod* rotireLaDreapta(Nod* rad) {
    Nod* aux = rad->stanga;
    if (rad) {
        rad->stanga = aux->dreapta; //fiul din dreapta al auxului va ajunge sa fie fiul din stanga al radacinii
        aux->dreapta = rad; // iar radacina va deveni fiul dreapta al auxului
    }
    return aux;
}

Nod* rotireLaStanga(Nod* rad) {
    if (rad) {
        Nod* aux = rad->dreapta;
        rad->dreapta = aux->stanga;
        aux->stanga = rad;
        return aux;
    }
    else
        return NULL;
}


//nu mereu se echilibreaza doar printr-o rotire si e nev sa facem dubla rotire
int intaltimeArbore(Nod* rad) {
    if (rad) {
        int inaltimeStanga = intaltimeArbore(rad->stanga);
        int inaltimeDreapta = intaltimeArbore(rad->dreapta);
        /*int maxim;
        if (inaltimeStanga < inaltimeDreapta) {
            maxim = inaltimeDreapta;
        }
        else
        {
            maxim = inaltimeStanga;
        }
        maxim = maxim + 1;
        return maxim;*/
        return 1 + (inaltimeStanga > inaltimeDreapta ? inaltimeStanga : inaltimeDreapta);
    }
    else
        return 0;
}

int calculGradEchilibru(Nod* rad) {
    if (rad) {
        int inaltimeStanga = intaltimeArbore(rad->stanga);
        int inaltimeDreapta = intaltimeArbore(rad->dreapta);
        return inaltimeStanga - inaltimeDreapta;
    }
    else
        return 0;
}

//
Nod* inserareArbore(Nod* arbore, Rezervare rez) {

    if (arbore != NULL) {
        if (arbore->info.id < rez.id) {
            arbore->dreapta = inserareArbore(arbore->dreapta, rez); //aici imi returneaza alta radacina pe care o punem in fiul din dreapta
        }
        else
        {
            arbore->stanga = inserareArbore(arbore->stanga, rez);
        }


        //avl
        int gradEchilibru = calculGradEchilibru(arbore);
        if (gradEchilibru == 2) { //daca = 2 avem dezechil in stanga
            if (calculGradEchilibru(arbore->stanga) == 1) {//facem rotire la dreapta
                arbore = rotireLaDreapta(arbore);
            }
            else {
                //avem situatia complicata care se rezolva cu dubla rotiere, una la stanga si apoi una la dreapta
                arbore->stanga = rotireLaStanga(arbore->stanga);
                arbore = rotireLaDreapta(arbore);
            }
        }
        else
        {
            if (gradEchilibru == -2) {
                if (calculGradEchilibru(arbore->dreapta) == 1) 
                    arbore->dreapta = rotireLaDreapta(arbore->dreapta);
                  
                arbore = rotireLaStanga(arbore);
            }
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



    for (int i = 0; i < nrRezervari; i++) {
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
    if (arbore != NULL) {
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

void stergereArbore(Nod** rad) { //dublu pointer ca sa se schimbe
    if (*rad) //in postordine: S D R 
    {
        stergereArbore(&(*rad)->stanga);
        stergereArbore(&(*rad)->dreapta);
        //pt radacina stergem efectiv informatia de acolo
        free((*rad)->info.numeClient);
        free(*rad);
        (*rad) = NULL; 
    }
}

void main() {
    Nod* radacina = NULL;

    citireFisier("rezervari.txt", &radacina);

    afisareArborePreOrdine(radacina);

    printf("\n---------------------------------\n");
    afisareRezervare(cautareDupaId(radacina, 4));

    printf("\n---------------------------------\nNr total de pers: %d", calculNrTotalPersoane(radacina));

    stergereArbore(&radacina);
    afisareArboreInOrdine(radacina);
}