#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
struct vila {
	char* denumire;
	int nrCamere;
	float* arii;
};

struct vila citire() {
	struct vila v;

	v.denumire = (char*)malloc(sizeof(char)*100);
	printf("\nIntroduceti denumirea vilei: ");
	gets(v.denumire);
	printf("%s",v.denumire);

	printf("\nIntroduceti numarul de camere din vila: ");
	scanf("%d", &v.nrCamere);
	printf("%d",v.nrCamere);

	v.arii = (float*)malloc(v.nrCamere * sizeof(float));
	printf("\nIntroduceti suprafetele camerelor: ");
	for (int i = 0; i < v.nrCamere; i++) {
		printf("\nSuprafata camera %i: ", i+1);
		if (v.arii != NULL) {
			scanf("%f", &v.arii[i]);
		}
	}
	return v;
}


void calculArieMax(struct vila v) {
	float maxim = 0;
	for (int i = 0; i < v.nrCamere; i++) {
		if (v.arii[i] > maxim) {
			maxim = v.arii[i];
		}
	}
	printf("\nSuprafata maxima a unei camere din vila %s este %5.2f", v.denumire, maxim);
}

void modificaDenumire(struct vila* v, char* denumireNoua) {
	v->denumire = denumireNoua;
}

void afisare(struct vila v) {
	if (v.denumire != NULL) {
		printf("\nDenumire: %s", v.denumire);
	}
	printf("\nNumarul de camere: %d", v.nrCamere);
	if (v.arii != NULL) {
		printf("\nSuprafetele camerelor: \n");
		for (int i = 0; i < v.nrCamere; i++) {
			printf("%5.2f", v.arii[i]);
			printf("\n");
		}
	}
	
}

void stergeVila(struct vila* v) {
	if (v->denumire != NULL) {
		free(v->denumire);
	}
	free(v->arii);
	v->denumire = NULL;
	v->arii = NULL;
}

int main() {
	struct vila v = citire(); 
	afisare(v);
	calculArieMax(v);
	//modificare denumire vila
	char* denumireNoua = (char*)malloc(sizeof(char) * 100);
	printf("\nIntroduceti noul nume al vilei: ");
	scanf("%s", denumireNoua);
	modificaDenumire(&v, denumireNoua);
	afisare(v);
	stergeVila(&v);
}