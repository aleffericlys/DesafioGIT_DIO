#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.c"
#include "q2.c"


static long get_nanos(void) {
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

static long media(long lista[5]){
	return (lista[0]+lista[1]+lista[2]+lista[3]+lista[4]) / 5;
}


int main()
{
	srand(time(NULL));

	long iniInsert, fimInsert, iniBusca, fimBusca,  dados[30][2], timeBuscas[5];
	dife *inicio;
	inicio = NULL;
	int maMeProf[30][2];

	for (int a = 0; a < 30; a++)
	{
		arvNum *raiz, *novo;
		raiz = NULL;
		int x, y, maProf = -1, meProf = -1, buscas[] = {16224, 12659, 12499, 2379, 11706};
		
		iniInsert = get_nanos();
		for (int i = 0; i < 1000; i++)
		{	
			x = rand() % 201;
			y = 1 + rand() % 100;
			novo = novoNo(x*y);
			insereNum(&raiz, novo);
		}
		fimInsert = get_nanos();

		dados[a][0] = fimInsert - iniInsert;

		for (int b = 0; b < 5; b++)
		{
			iniBusca = get_nanos();
			busca(raiz, buscas[b]);
			fimBusca = get_nanos();
			timeBuscas[b] = fimBusca - iniBusca;
		}
		dados[a][1] = media(timeBuscas);

		profundidade(raiz, 0);
		
		mame(raiz, &maProf, &meProf);
		maMeProf[a][0] = maProf;
		maMeProf[a][1] = meProf;
		insereOrd(&inicio, (maProf - meProf));
		printf("\ntempo de insersao: %ld\nmaior profundidade: %d \nmenor profundidade: %d\n", dados[a][0], maProf, meProf);
		limpaArv(raiz);
	}


	for (int i = 0; i < 30; i++)
	{
		printf("tempos de insersão: %ld\n", dados[i][0]);
	}
	
	for (int i = 0; i < 30; i++)
	{
		printf("media do tempo de 5 buscas: %ld\n", dados[i][1]);
	}

	for (int i = 0; i < 30; i++)
	{
		printf("diferenca de profundiade: %d \n",maMeProf[i][0] - maMeProf[i][1]);
	}
	
	
	mostraLista(inicio);	

	limpaLista(inicio);

	return 0;
}