#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ano 2022
#define TAM 5

typedef struct Pessoa pessoa;
typedef struct Lista lista; 

struct Pessoa{ 
	int Id; 
	char Nome[30]; 
	int AnoNascimento; 
	float Altura; 
};

struct Lista{ 
	pessoa Info; 
	lista *Prox; 
};

//	cria um novo item na lista 
//	i: id
// 	nome: nome da pessoa
//	anoNas: ano de nascimento
// 	alt: altura
//	retorna o ponteiro para esse nó na lista
lista *novaT(int i, char nome[], int anoNas, float alt){
	lista *nova;
	char lixo;
	nova = (lista*)malloc(sizeof(lista));

	nova->Info.Id = i;
	strcpy(nova->Info.Nome, nome);
	nova->Info.AnoNascimento = anoNas;
	nova->Info.Altura = alt;
	nova->Prox = NULL;
	
	return nova;
}

// 	adiciona o item criado em novaT ao fim da lista
int cadPess(lista **inicio, lista *nova){

	if (*inicio == NULL)
	{
		*inicio = nova;
	}else if((*inicio)->Prox != NULL)
	{
		cadPess(&((*inicio)->Prox), nova);
	}else
	{
		(*inicio)->Prox = nova;
	}
	
return 1;
}

//	como o nome diz ...
void limpaLista(lista *inicio){
	if (inicio != NULL)
	{
		limpaLista(inicio->Prox);
		free(inicio);
		inicio = NULL;
	}
}

// função auxiliar para a letra a
float menor(lista *prim, float meAlt){ //

	if (prim != NULL)
	{
		if (meAlt == 0)
		{
			
			meAlt = menor(prim->Prox, prim->Info.Altura);
		}
		else 
		{
			if (prim->Info.Altura < meAlt)
			{
				meAlt = menor(prim->Prox, prim->Info.Altura);
			}else{
				meAlt = menor(prim->Prox, meAlt);
			}
		}
	}
	return meAlt;
}


//	a
//	prim: ponteiro para o inicio da lista 
//	V: vetor vazio com tamanho igual a quantidade de pessoas na lista
//	alt: altura da menor pessoa conseguida na função "menor"
//	quant: 0
//	a função retorna V por referencia e retorna quant;
int nanicos(lista *prim, char V[TAM][30], float alt, int quant){

	if (prim != NULL)
	{
		if (prim->Info.Altura == alt)
		{
			strcpy(V[quant], prim->Info.Nome);
			quant = nanicos(prim->Prox, V, alt, quant+1);
		}else{
			quant = nanicos(prim->Prox, V, alt, quant);
		}
	}
	
	return quant;
}


//	b
//	prim: ponteiro para o inicio da lista 
//	maAlt: 0.0 passado por referencia em uma variavel float
//	maAlt: 0.0
//	a função retorna maAlt por referencia e meAlt normalmente
float alturas(lista *prim, float *maAlt, float meAlt){ // [1.7, 1.8, 1.7, 1.6, 1.7]

	if (prim != NULL)
	{
		if (*maAlt == 0 && meAlt == 0)
		{
			*maAlt = prim->Info.Altura;
			meAlt = alturas(prim->Prox, maAlt, prim->Info.Altura);
		}
		else 
		{
			if (prim->Info.Altura > *maAlt)
			{
				*maAlt = prim->Info.Altura;
				meAlt = alturas(prim->Prox, maAlt, meAlt);
			}
			else if (prim->Info.Altura < meAlt)
			{
				meAlt = alturas(prim->Prox, maAlt, prim->Info.Altura);
			}else{
				meAlt = alturas(prim->Prox, maAlt, meAlt);
			}
		}
	}
	return meAlt;
}

//	função auxiliar da letra C
float altMed(lista *prim){
	float ma = 0.0;
	float me = alturas(prim, &ma, 0.0);

	return (ma + me) / 2;
}

//c
//	prim: ponteiro para o inicio da lista 
//	altM: altura media conseguina na função altMed
// 	quant: 0
//	retorna quant
int naMedia(lista *prim, float altM, int quant){ 

	if (prim != NULL)
	{
		if(prim->Info.Altura == altM){
			quant = naMedia(prim->Prox, altM, quant) + 1;
		}else{
			quant = naMedia(prim->Prox, altM, quant);
		}
	}
	
	return quant;
}

//	d
//	prim: ponteiro para o inicio da lista 
//	altM: altura media conseguina na função altMed
// 	quant: 0
//	retorna quant
int acimaDaMedia(lista *prim, float altM, int quant){

	if (prim != NULL)
	{
		if(prim->Info.Altura > altM && ((ano - prim->Info.AnoNascimento) > 50)){
			quant = acimaDaMedia(prim->Prox, altM, quant) + 1;
		}else{
			quant = acimaDaMedia(prim->Prox, altM, quant);
		}
	}
	return quant;
}

int main(int argc, char const *argv[])
{
	lista *prim = NULL;

	char nomes[TAM][30] = {"Paulo", "Maria", "Wagnner", "Lucas", "Bianca"};
	int anos[TAM]  = {1940, 1950, 2002, 1955, 1999};
	float alt[TAM]  = {1.7, 1.8, 1.7, 1.6, 1.7};

	for (int i = 0; i < TAM; i++)
	{
		cadPess(&prim, novaT(i, nomes[i], anos[i], alt[i]));
	}

	char nanico[TAM][30];
	int tanto;
	tanto = nanicos(prim, nanico, 1.7, 0);

	for(int i = 0; i < tanto; i++){
		printf("%s\n", nanico[i]);
	}

	float maior = 0.0, menor;

	menor = alturas(prim, &maior, 0.0);

	printf("%.2f, %.2f\n", maior, menor);

	int quant;
	quant = naMedia(prim, altMed(prim), 0);
	printf("%d\n", quant);

	int acima;
	acima = acimaDaMedia(prim, altMed(prim), 0);
	printf("%d\n", acima);
	
	// mostraPessoas(prim);
	limpaLista(prim);
	return 0;
}