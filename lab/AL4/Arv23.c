#include <stdio.h>
#include <stdlib.h>
//Dupla Aleff e Bryan.
struct Arv23{//Definição árvore 2,3.
	int Info1, Info2, NInfos;
	struct Arv23 *esq, *cen,*dir;
};

struct Arv23 *criaNo(int valor, struct Arv23 *FEsq, struct Arv23 *FCen, struct Arv23 *FDir){//Função que cria um novo elemento para a árvore.
	struct Arv23 *No;
	
	No = (struct Arv23 *) malloc(sizeof(struct Arv23));
	
	(*No).Info1 = valor;
	(*No).Info2 = 0;
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

void adiciona(struct Arv23 **Raiz, int Valor, struct Arv23 *MaiorNo)//Função que adiciona um novo valor a um nó, respeitando as condições de inserção da árvore 2,3.
{
	if(Valor > (*Raiz)->Info1){
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

struct Arv23 *quebraNo(struct Arv23 **Raiz,int valor,int *sobe, struct Arv23 *MaiorNo){//Função que quebra um nó, separando o menor valor e deixando-o na raiz, subindo o valor do meio e criando um novo nó com o maior valor.
	struct Arv23 *Novo;
	
	if(valor < (*Raiz)->Info1){
		*sobe = (*Raiz)->Info1;
		Novo = criaNo((*Raiz)->Info2,(*Raiz)->cen,(*Raiz)->dir,NULL);
		(*Raiz)->Info1 = valor;
		(*Raiz)->cen = MaiorNo;
	}
	else if (valor < (*Raiz)->Info2) {
		*sobe = valor;
		Novo = criaNo((*Raiz)->Info2,MaiorNo,(*Raiz)->dir,NULL);
	}
	else{
		*sobe = (*Raiz)->Info2;
		Novo = criaNo(valor,(*Raiz)->dir,MaiorNo,NULL);
	}

	(*Raiz)->Info2 = 0;
	(*Raiz)->NInfos = 1;
	(*Raiz)->dir = NULL;

	return(Novo);	
}


struct Arv23 *insereArv23(struct Arv23 *Pai, struct Arv23 **Raiz, int valor, int *sobe)//Função que insere uma informação, criando um novo nó ou colocando a informação em um nó existente, em uma árvore 2,3.
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
				novo=quebraNo(Raiz,valor,sobe,maiorNo);
					if(Pai == NULL){
						struct Arv23 *no;
						no = criaNo(*sobe,*Raiz,novo,NULL);
						*Raiz = no;
					}else {
						maiorNo = novo;	
					}
				}

		}else{//quando não é folha
			if(valor < (*Raiz)->Info1)
				maiorNo = insereArv23(*Raiz, &((*Raiz)->esq), valor,sobe);
			else if((*Raiz)->NInfos == 1 || (valor < (*Raiz)->Info2)){
					maiorNo = insereArv23(*Raiz, &((*Raiz)->cen), valor,sobe);
			}else {
				maiorNo = insereArv23(*Raiz, &((*Raiz)->dir), valor,sobe);	
			}
				
			if(maiorNo != NULL){
				if((*Raiz)->NInfos == 1){
					adiciona(Raiz,*sobe,maiorNo);
					maiorNo = NULL;
				}else{ // quando não tem espaço
					int sobe1;
					struct Arv23 *novo;	
					novo=quebraNo(Raiz,*sobe,&sobe1,maiorNo);
					if(Pai == NULL){
						struct Arv23 *no;
						no = criaNo(sobe1,*Raiz,novo,NULL);
						*Raiz = no;
						maiorNo = NULL;
					} else {
						maiorNo = novo;
						*sobe = sobe1;
					}
				}
			}  
		}
	}
	
	return maiorNo;	
}

int folhas(struct Arv23 *raiz, int *qtdinf){//Função que retorna o número de nós folha e a quantidade de informações (*qtdinf) contidas nesses nós, em uma árvore 2,3.
	int ret = 0;
	if (raiz != NULL)
	{
		if (ehFolha(raiz))
		{
			ret = 1;
			if (raiz->NInfos == 1)
			{
				*qtdinf += 1; 
			}else{
				*qtdinf += 2; 
			}
			
		}else if (raiz->NInfos == 1){
			ret += folhas(raiz->esq, qtdinf);
			ret += folhas(raiz->cen, qtdinf);
		
		}else{
			ret += folhas(raiz->esq, qtdinf);
			ret += folhas(raiz->cen, qtdinf);
			ret += folhas(raiz->dir, qtdinf);
		}
	}
	return ret;
}

int maiorNivel(struct Arv23 *raiz, int cont){//Função que retorna a maior profundidade ou nivel da árvore.
	int nivel;

	if (raiz != NULL)
	{
		if (ehFolha(raiz))
		{
			nivel = cont;
		}else if (raiz->NInfos == 1){
			nivel = maiorNivel(raiz->esq, cont + 1);	
		}
	}
	return nivel;
}

int busca(struct Arv23 *raiz, int valor){//Função que busca um valor na árvore e retorna 1 caso encontre, e 0 caso não.
	int ret = 0;
	if (raiz != NULL)
	{	
		if (raiz->NInfos == 1)
		{
			if (raiz->Info1 == valor){
				ret = 1;
			}else if (valor < raiz->Info1){
				ret = busca(raiz->esq, valor);

			}else{
				ret = busca(raiz->cen, valor);
			}
		
		}else{
	
			if (raiz->Info1 == valor || raiz->Info2 == valor)
			{
				ret = 1;
			}else if (valor < raiz->Info1)
			{
				ret = busca(raiz->esq, valor);
			}else if (valor > raiz->Info2)
			{
				ret = busca(raiz->dir, valor);
			}else{
				ret = busca(raiz->cen, valor);
			}
		}
	}
	return ret;
}

void mostraOrdem(struct Arv23 *raiz){//Função que mostra os elementos da árvore 2,3 em ordem crescente.
	if (raiz != NULL)
	{
		if (raiz->NInfos == 1)
		{
			printf("%d \n", raiz->Info1);
			mostraOrdem(raiz->esq);
			mostraOrdem(raiz->cen);
		}else{
			printf("%d ", raiz->Info1);
			printf("%d \n", raiz->Info2);
			mostraOrdem(raiz->esq);
			mostraOrdem(raiz->cen);
			mostraOrdem(raiz->dir);	
		}
	}
}

void limpa(struct Arv23 *raiz){//Função que limpa/libera a árvore.
	if (raiz != NULL)
	{
		limpa(raiz->esq);
		limpa(raiz->cen);
		limpa(raiz->dir);
		free(raiz);
		raiz = NULL;
	}
}

int estaContido(struct Arv23 *Raiz, int info){
	int ret = 0;
    if (info == Raiz->Info1)
        ret =  1;
    if (info == Raiz->Info2)
        ret =  2;
    return ret;
}

int main() {
	
	struct Arv23 *Raiz, *Pai;
	int sobe = 0;
	int vet[] = {5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 11, 12};//, 6, 7, 8, 9, 10}; {13, 2, 5, 8, 15, 9, 18, 20, 1, 7};

	Raiz = NULL;
	Pai = NULL;

	for (int i = 0; i < 12; i++)
	{
		insereArv23(Pai, &Raiz, vet[i], &sobe);
	}
	//a
	mostraOrdem(Raiz);
	printf("\n");
	// //b
	// int ret = busca(Raiz, 3);
	// printf("%d\n", ret);
	// //c
	// ret = maiorNivel(Raiz, 0);
	// printf("Maior nivel: %d\n", ret);
	// //d
	// int qtd = 0;
	// ret = folhas(Raiz, &qtd);
	// printf("Qtd de folhas: %d\n", ret);
	// printf("Qtd info nas folhas: %d\n", qtd);

	limpa(Raiz);
	limpa(Pai);
	return 0;
}