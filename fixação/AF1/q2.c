#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TAM 4


void misterio1(char b[TAM], float *dec, int p, int i) 
{ 
	if(p < strlen(b)) 
	{ 
		if(b[p] == '1')    
			*dec = *dec + pow(2,i); //10
		
		misterio1(b, dec, ++p, --i);  //"1010", 10, 4, -1
	} 
}

float misterio2(char  b[TAM], float dec, int p, int i) 
{
	if(p < strlen(b)) 
	{
		dec = misterio2(b, dec, p+1, i-1);  
		if(b[p] == '1') 
			dec = dec + pow(2,i);
	} 
return(dec); 
}

int main(){
	float dec = misterio2("1010", 0, 0, 3);
	printf("%f", dec);
}