#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//1ª
//	V[]: um vetor vazio de mesmo tanho das do valor que vai ser analisado
//	val: o valor a ser analisado
//	i: 1
//	j: 0
//	o retorno será a quantidade de numeros divisiveis
//	os numeros divisiveis serão retornados por referência
int divi(int V[], int val, int i, int j){

	if(i <= val){
		if (val % i == 0)
		{
			V[j] = i;
			j = divi(V, val, i+1, j+1);
		}else
		{
			j = divi(V, val, i+1, j);
		}
	}
	return j;
}




int main()
{
	int n, m;
	printf("Digite um numero\n");
	scanf("%d", &n);
	int v[n];
	m = divi(v, n, 1, 0);
	printf("Os divisores desse numero eh:\n");
	for (int i = 0; i < m; i++)
	{
		printf("%d \n", v[i]);
	}

	return 0;
}
