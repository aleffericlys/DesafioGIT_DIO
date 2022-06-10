#include <stdio.h>
#include <stdlib.h>
#define TAM 5

int inter(int V1[TAM], int V2[TAM], int V3[TAM], int i, int j, int q1, int q2, int q3) 
{ 
	if(i < q1 || j < q2) 
	{ 
		if(V1[i] < V2[j])
		{
	  		q3 = inter(V1,V2,V3,i+1,j,q1,q2,q3); 
		}
		else if(V1[i] > V2[j])
		{
			q3 = inter(V1,V2,V3,i,j+1,q1,q2,q3); 
		}
		else
		{
			V3[q3] = V1[i]; 
			q3 = inter(V1,V2,V3,i+1,j+1,q1,q2,q3+1); 
		}
	}
	return q3;
}

int inter2(int V1[TAM], int V2[TAM], int V3[TAM], int i, int j, int q1, int q2, int q3){

	while(i < q1 || j < q2){
		if (V1[i] < V2[j]){
			i++;
		}
		else if (V1[i] > V2[j]){
			j++;
		}else{
			V3[q3] = V1[i];
			i++;
			j++;
			q3++;
		}	
	} 
	return q3;
}

int main(int argc, char const *argv[])
{
	int vetor[TAM] = {0, 0, 0, 0, 0};
	int V1[TAM] = {1, 2, 3, 4, 5};
	int V2[TAM] = {4, 5, 6, 7, 8};

	int p = inter2(V1, V2, vetor, 0, 0, TAM ,TAM, 0);

	for (int i = 0; i < p; i++)
	{
		printf("%d\n", vetor[i]);
	}
	return 0;
}