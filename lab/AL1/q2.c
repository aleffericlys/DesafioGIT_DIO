#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 20

//	2. a)
//	t: vetor de palavras a seres testadas
//	pa: variavel que irá armazenar a menor palavra
//	n: quantidade de palavras em t
//	i, tam: 0
// a função retorna pa por referencia eretorna o tamanho da menor palavra
int mpalavra(char t[3][TAM], char pa[TAM], int i, int n, int tam){
	int l;
	if (i < n)
	{
		tam = mpalavra(t, pa, i+1, n, tam);
		l = strlen(t[i]);
		if (tam == 0 || l < tam) //if (tam == 0 || l <= tam)
		{
			tam = l;
			strcpy(pa, t[i]);
			// printf(" %s ", pa);
		}
	}
	return tam;
}


//2. b)
//	t: vetor de palavras a seres testadas
//	n: quantidade de palavras em t
//	i: 0
//	quant: inteiro passado por referencia inicializado com 0
//	a função retorna quant por referencia
void quantC(char t[TAM][TAM], int i, int n, int *quant){
	if (i < n)
	{
		// printf('%c ', t[i][0]);
		if (t[i][0] == 'a' || t[i][0] == 'A' || t[i][0] == 'e' || t[i][0] == 'E' || t[i][0] == 'i' || t[i][0] == 'I' || t[i][0] == 'o' || t[i][0] == 'O' || t[i][0] == 'u' || t[i][0] == 'U')
		{
			quantC(t, i+1, n, quant);
		}else
		{
			*quant += 1;
			quantC(t, i+1, n, quant);	
		}
	}
}

//2. c)
//	t: vetor de palavras a seres testadas
//	ret: vetor de palavar que irá armazenar as palavras iniciadas com consoante e será retorando por referencia
//	n: quantidade de palavras em t
//	i: 0
//	quant: inteiro passado por referencia inicializado com 0
//	a função retorna quant por referencia
void inMm6(char t[3][TAM], char ret[3][TAM], int i, int n, int *quant){
	if (i < n)
	{
		if ((t[i][0] == 'A'  || t[i][0] == 'E' || t[i][0] == 'I' || t[i][0] == 'O' || t[i][0] == 'U') && (strlen(t[i]) <= 6))
		{
			strcpy(ret[*quant], t[i]);
			*quant += 1;
			inMm6(t, ret, i+1, n, quant);
		}else
		{
			inMm6(t, ret, i+1, n, quant);
		}
	}
}


int main(){
	char t[3][TAM], p[TAM];
	printf("Digite 3 palavras\n");
	for (int i = 0; i < 3; i++)
	{
		scanf("%s", t[i]);
		fflush(stdin);
	}
	//a
	mpalavra(t, p, 0, 3, 0);
	printf("Menor palavra:\n");
	printf("%s\n", p);

	//b
	int quant=0;
	quantC(t, 0, 3, &quant);
	printf("quantidade de strings iniciadas com consoante:\n%d\n", quant);
	
	//c
	int j;
	char ret[3][TAM];
	inMm6(t, ret, 0, 3, &j);
	printf("palavras iniciadas com vogal maiuscolas menores que 6 letras:\n");
	for (int i = 0; i < j; i++)
	{
		printf("%s\n", ret[i]);
	}
	

	return 0;
}