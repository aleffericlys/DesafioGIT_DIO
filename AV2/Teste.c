#include <stdio.h>
#include <stdlib.h>
	
// void main()
// {
  // FILE *arq;
  // char Linha[100];
  // char *result;
  // int i;
  // // Abre um arquivo TEXTO para LEITURA
  // arq = fopen("ArqTeste.txt", "rt");
  // if (arq == NULL)  // Se houve erro na abertura
  // {
  //    printf("Problemas na abertura do arquivo\n");
  //    return;
  // }
  // i = 1;
  // while (!feof(arq))
  // {
	// // Lê uma linha (inclusive com o '\n')
  //     result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
  //     if (result)  // Se foi possível ler
	//   printf("Linha %d : %s",i,Linha);
  //     i++;
  // }
  // fclose(arq);

//   FILE *arq;
//   int i;
//   int result;
//   arq = fopen("ArqGrav.txt", "wt");  // Cria um arquivo texto para gravação
//   if (arq == NULL) // Se nào conseguiu criar
//   {
//      printf("Problemas na CRIACAO do arquivo\n");
//      return;
//   }
//   for (i = 0; i < 10;i++)
//   {
// // A funcao 'fprintf' devolve o número de bytes gravados 
// // ou EOF se houve erro na gravação
//       result = fprintf(arq,"Linha %d\n",i);  					  
//       if (result == EOF)		    
// 	      printf("Erro na Gravacao\n");
//   }
//   fclose(arq);
	// char url[]="calcados.txt",
	// ch2[46], ch3[46];
	// int ch1 = 0, ch4 = 0, ch5 = 0;
	// float ch6;
	// FILE *arq;

	// arq = fopen(url, "r");
	// if(arq == NULL)
	// printf("Erro, nao foi possivel abrir o arquivo\n");
	// else
	// while( (fscanf(arq,"%d %s %s %d %d %f\n", &ch1, &ch2, &ch3, &ch4, &ch5, &ch6))!=EOF )
	// 	printf("%d %s %s %d %d %.2f\n", ch1, ch2, ch3, ch4, ch5, ch6);

	// fclose(arq);

// }
int main(int argc, char const *argv[]){
	char url[]="calcados.txt",
	ch2[46], ch3[46];
	int ch1 = 0, ch4 = 0, ch5 = 0;
	float ch6;
	FILE *arq;

	arq = fopen(url, "r");
	if(arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		for (int i = 0;(fscanf(arq,"%d %s %s %d %d %f\n", &ch1, ch2, ch3, &ch4, &ch5, &ch6))!=EOF ;i++)
		{
			printf("%d %s %s %d %d %.2f\n", ch1, ch2, ch3, ch4, ch5, ch6);

		// 	calc = Calc(ch1, ch2, ch3, ch4, ch5, ch6);
		// 	insereArv23(Pai, &Raiz, calc, &sob);
		}
	}
	fclose(arq);
	// limpa(Raiz);
	return 0;
}