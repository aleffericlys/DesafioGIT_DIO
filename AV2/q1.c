#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arv23 arv23;
typedef struct Calcado calcado;
typedef struct Sobe sobe;

struct Arv23{
	calcado *Info1, *Info2;
	int NInfos;
	arv23 *esq, *cen,*dir;
};

struct Calcado{
	char tipo[46], marca[46];
	int cod, tam, quant, pos;
	float preco;
};

struct Sobe{
	calcado *calcado;
	int P;
};

struct Arv23 *criaNo(calcado *valor, struct Arv23 *FEsq, struct Arv23 *FCen, struct Arv23 *FDir){//Função que cria um novo elemento para a árvore.
	struct Arv23 *No;
	
	No = (struct Arv23 *) malloc(sizeof(struct Arv23));

	(*No).Info1 = valor;
	(*No).Info2 = NULL;
	(*No).NInfos = 1;
	(*No).esq = FEsq;
	(*No).cen = FCen;
	(*No).dir = FDir;
	
	return No;	
}

int ehFolha(struct Arv23 *R){//Função que verifica se um nó é folha. 
	int folha = 0; // não é folha
	if (R->esq == NULL && R->dir == NULL && R->cen == NULL){
		folha = 1;
	}
	return folha;
}

void adiciona(struct Arv23 **Raiz, calcado *Valor, struct Arv23 *MaiorNo)//Função que adiciona um novo valor a um nó, respeitando as condições de inserção da árvore 2,3.
{
	if(Valor->cod > (*Raiz)->Info1->cod){
		(*Raiz)->Info2 = Valor;
		(*Raiz)->dir = MaiorNo;
	}	
	else {
		(*Raiz)->Info2 = (*Raiz)->Info1;
		(*Raiz)->Info1 = Valor;
		(*Raiz)->dir = (*Raiz)->cen;
		(*Raiz)->cen = MaiorNo;
	}
	
	(*Raiz)->NInfos = 2;
}

struct Arv23 *quebraNo(struct Arv23 **Raiz,calcado *valor,calcado **sob, struct Arv23 *MaiorNo){//Função que quebra um nó, separando o menor valor e deixando-o na raiz, subindo o valor do meio e criando um novo nó com o maior valor.
	struct Arv23 *Novo;
	
	if(valor->cod < (*Raiz)->Info1->cod){
		*sob = (*Raiz)->Info1;
		Novo = criaNo((*Raiz)->Info2,(*Raiz)->cen,(*Raiz)->dir,NULL);
		(*Raiz)->Info1 = valor;
		(*Raiz)->cen = MaiorNo;
	}
	else if (valor->cod < (*Raiz)->Info2->cod) {
		*sob = valor;
		Novo = criaNo((*Raiz)->Info2,MaiorNo,(*Raiz)->dir,NULL);
	}
	else{
		*sob = (*Raiz)->Info2;
		Novo = criaNo(valor,(*Raiz)->dir,MaiorNo,NULL);
	}

	(*Raiz)->Info2 = NULL;
	(*Raiz)->NInfos = 1;
	(*Raiz)->dir = NULL;

	return(Novo);	
}


struct Arv23 *insereArv23(struct Arv23 *Pai, struct Arv23 **Raiz, calcado *valor, calcado **sob)//Função que insere uma informação, criando um novo nó ou colocando a informação em um nó existente, em uma árvore 2,3.
{ 
	struct Arv23 *maiorNo;
	maiorNo = NULL;
	if(*Raiz == NULL){
		*Raiz = criaNo(valor,NULL,NULL,NULL);
		
	} else { 
		if(ehFolha(*Raiz)){ 
			if((*Raiz)->NInfos == 1){
				adiciona(Raiz,valor,maiorNo);
			}else {  // quando não tem espaço
				struct Arv23 *novo;	
				novo=quebraNo(Raiz,valor,sob,maiorNo);
					if(Pai == NULL){
						struct Arv23 *no;
						no = criaNo(*sob,*Raiz,novo,NULL);
						*Raiz = no;
					}else {
						maiorNo = novo;	
					}
				}

		}else{//quando não é folha
			if(valor->cod < (*Raiz)->Info1->cod)
				maiorNo = insereArv23(*Raiz, &((*Raiz)->esq), valor,sob);
			else if((*Raiz)->NInfos == 1 || (valor->cod < (*Raiz)->Info2->cod)){
					maiorNo = insereArv23(*Raiz, &((*Raiz)->cen), valor,sob);
			}else {
				maiorNo = insereArv23(*Raiz, &((*Raiz)->dir), valor, sob);	
			}
				
			if(maiorNo != NULL){
				if((*Raiz)->NInfos == 1){
					adiciona(Raiz,*sob,maiorNo);
					maiorNo = NULL;
				}else{ // quando não tem espaço
					calcado *sob1;
					struct Arv23 *novo;	
					novo=quebraNo(Raiz, *sob ,&sob1,maiorNo);
					if(Pai == NULL){
						struct Arv23 *no;
						no = criaNo(sob1,*Raiz,novo,NULL);
						*Raiz = no;
						maiorNo = NULL;
					} else {
						maiorNo = novo;
						*sob = sob1;
					}
				}
			}  
		}
	}
	
	return maiorNo;	
}

void limpa(arv23 *raiz){//Função que limpa/libera a árvore.
	if (raiz != NULL)
	{
		limpa(raiz->esq);
		limpa(raiz->cen);
		limpa(raiz->dir);
		free(raiz);
		raiz = NULL;
	}
}



calcado *busca(arv23 *raiz, int valor){//Função que busca um valor na árvore e retorna 1 caso encontre, e 0 caso não.
	calcado *ret;
	ret = NULL;
	if (raiz != NULL)
	{	
		if (raiz->NInfos == 1)
		{
			if (raiz->Info1->cod == valor){
				ret = raiz->Info1;
			}else if (valor < raiz->Info1->cod){
				ret = busca(raiz->esq, valor);
			}else{
				ret = busca(raiz->cen, valor);
			}
		
		}else{
	
			if (raiz->Info1->cod == valor)
			{
				ret = raiz->Info1;
			}else if(raiz->Info2->cod == valor){
				ret = raiz->Info2;
			}else if (valor < raiz->Info1->cod)
			{
				ret = busca(raiz->esq, valor);
			}else if (valor > raiz->Info2->cod)
			{
				ret = busca(raiz->dir, valor);
			}else{
				ret = busca(raiz->cen, valor);
			}
		}
	}

	return ret;
}


void mostra(calcado *item){
	printf("%d %s %s %d %d %.2f\n", item->cod, item->tipo, item->marca, item->tam, item->quant, item->preco);
}


void mostraOrdem(struct Arv23 *raiz){//Função que mostra os elementos da árvore 2,3 em ordem crescente.
	if (raiz != NULL)
	{
		if (raiz->NInfos == 1)
		{
			mostra(raiz->Info1);
			mostraOrdem(raiz->esq);
			mostraOrdem(raiz->cen);
		}else{
			mostra(raiz->Info1);
			mostra(raiz->Info2);
			printf("\n");
			mostraOrdem(raiz->esq);
			mostraOrdem(raiz->cen);
			mostraOrdem(raiz->dir);	
		}
	}
}


calcado *Calc(int ch1, char ch2[46], char ch3[46], int ch4, int ch5, float ch6 ,int pos){
	calcado *cac = NULL;
	cac = (calcado *) malloc(sizeof(calcado));
	cac->cod = ch1;
	strcpy(cac->tipo, ch2);
	strcpy(cac->marca, ch3);
	cac->tam = ch4;
	cac->quant = ch5;
	cac->preco = ch6;
	cac->pos = pos;
	return cac;
}

void cadastra(arv23 **Raiz, int *pos, FILE *arq){
	char ch2[46], ch3[46];
	int ch1 = 0, ch4 = 0, ch5 = 0;
	float ch6;
	calcado *sob;
	sob = NULL;
	calcado *calc;
	printf("cod: ");
	scanf("%d",&ch1);
	printf("tipo: ");
	scanf("%s", ch2);
	printf("marca: ");
	scanf("%s", ch3);
	printf("tamanho: ");
	scanf("%d", &ch4);
	printf("quantidade: ");
	scanf("%d", &ch5);
	printf("preco: ");
	scanf("%f", &ch6);

	fprintf(arq,"\n%d %s %s %d %d %.2f", ch1, ch2, ch3, ch4, ch5, ch6);
	calc = Calc(ch1, ch2, ch3, ch4, ch5, ch6, *pos);
	*pos += 1;
	insereArv23(NULL, Raiz, calc, &sob);
	mostraOrdem(*Raiz);
}

int main(int argc, char const *argv[])
{
	calcado *sob;
	arv23 *Raiz, *Pai;
	Raiz = NULL;
	sob = NULL;
	Pai = NULL;
	calcado *calc;
	char url[]="calcados.txt",
	ch2[46], ch3[46];
	int ch1 = 0, ch4 = 0, ch5 = 0, i;
	float ch6;
	FILE *arq;

	arq = fopen(url, "a+");
	if(arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		for (i = 1;(fscanf(arq,"%d %s %s %d %d %f\n", &ch1, ch2, ch3, &ch4, &ch5, &ch6))!=EOF ;i++)
		{
			printf("%d %s %s %d %d %.2f\n", ch1, ch2, ch3, ch4, ch5, ch6);
			calc = Calc(ch1, ch2, ch3, ch4, ch5, ch6, i);
			insereArv23(Pai, &Raiz, calc, &sob);
			printf("\n\n");
		}

	}
	mostraOrdem(Raiz);
	printf("\n");

	// cadastra(&Raiz, &i, arq);

	calcado *ret;
	ret = busca(Raiz, 11);
	if (ret != NULL){
		mostra(ret);
		printf("Posicao: linha %d\n", ret->pos);
	}else{
		printf("No tienes\n");
	}
	
	
	limpa(Raiz);
	fclose(arq);
	return 0;
}




// Vizzano;
// Arezzo;
// Via Marte;
// Anacapri;
// Santa Lolla;
// Schutz;
// Luiza Barcelos;
// Bottero;
// Ramarim;
// Moleca;
// Dupe;
// Adidas;
// Nike;
// Caterpillar;
// Scarpin;
// Olinpikos;