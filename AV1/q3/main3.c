#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "q3.c"


static long get_nanos(void) {
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

static long media(long lista[5]){
	return (lista[0]+lista[1]+lista[2]+lista[3]+lista[4]) / 5;
}


int main(int argc, char const *argv[])
{
	srand(time(NULL));

	long iniInsert, fimInsert, timeBuscas[7];

	termos *raiz, *novo;
	raiz = NULL;

	char termos[7][46] = {"Estudar", "Cavar", "Gastar","Alocar", "Blindar", "Forjar", "Desconsiderar"};
	char subt[7][5][46] = {
							//"Alocar", "Blindar", "Cavar", "Desconsiderar", "Estudar", "Forjar", "Gastar"
							"Estudar", "Estudei", "Estudava", "Estudavam", "Estudarei",
							"Cava", "Cavaram", "Cavacao", "Cavo", "Cavei",
							"Gasta", "Gastarei", "Gastava", "Gastaria", "Gastaram",
							"Alocacao", "Aloca", "Aloquei", "Alocam", "Alocando", 
							"Blinda", "Blindagem", "Blindasse", "Blindava", "Blindam", 
							"Forja", "Forjei", "Forjavam", "Forjaria", "Forjava",
							"Desconsiderar", "Desconsideracao", "Desconsiderei", "Desconsiderava", "Desconsideravam"};

	for (int i = 0; i < 7; i++)
	{
		novo = novoTermo(termos[i], subt[i]);

		iniInsert = get_nanos();
		cadTermo(&raiz, novo);
		fimInsert = get_nanos();
		timeBuscas[i] = fimInsert - iniInsert;
	}
	
	mostra(raiz);

	for (int i = 0; i < 7; i++)
	{
		printf("%ld\n", timeBuscas[i]);
	}
	
	printf("\n");
	limpa(raiz);
	return 0;
}