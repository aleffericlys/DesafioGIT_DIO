#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.c"
#include "q2.c"
#include <sys/time.h>

int main()
{
	srand(time(NULL));

	double dados[30][2], timeBuscas[5];
	dife *inicio;
	inicio = NULL;
	int maMeProf1[30][2];

	for (int a = 0; a < 30; a++)
	{
		arvNum *raiz, *novo;
		raiz = NULL;
		int x, y, maProf = -1, meProf = -1, buscas[] = {16224, 12659, 12499, 2379, 11706};
		
		struct timeval begin, end;
    	gettimeofday(&begin, 0);

		for (int i = 0; i < 1000; i++)
		{	
			x = rand() % 201;
			y = 1 + rand() % 100;
			novo = novoNo(x*y);
			insereNum(&raiz, novo);
		}

		gettimeofday(&end, 0);
		long seconds = end.tv_sec - begin.tv_sec;
		long microseconds = end.tv_usec - begin.tv_usec;
		dados[a][0] = seconds + microseconds*1e-9;

		// dados[a][0] = fimInsert - iniInsert;

		// for (int b = 0; b < 5; b++)
		// {
		// 	iniBusca = get_nanos();
		// 	busca(raiz, buscas[b]);
		// 	fimBusca = get_nanos();
		// 	timeBuscas[b] = fimBusca - iniBusca;
		// }
		// dados[a][1] = media(timeBuscas);

		profundidade(raiz, 0);
		
		mameProf(raiz, &maProf, &meProf);
		maMeProf1[a][0] = maProf;
		maMeProf1[a][1] = meProf;
		insereOrd(&inicio, (maProf - meProf));
		printf("\nTempo de insercao: %.10f\nMaior profundidade: %d \nMenor profundidade: %d\n", dados[a][0], maProf, meProf);
		limpaArv(raiz);
	}

	// for (int i = 0; i < 30; i++)
	// {
	// 	printf("Tempo de insercao: %10f \tMedia do tempo de 5 buscas: %.10f \tMaior profundidade: %d \t", dados[i][0], dados[i][0], maMeProf[i][0]);
	// 	printf("Menor profundidade: %d \n", maMeProf[i][1]);
	// }
	
	mostraLista(inicio);	

	limpaLista(inicio);

	return 0;
}