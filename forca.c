#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h" // definindo novo header file com nossas funções principais.

/*
Introdução à linguagem 'C': O Jogo da Forca. 👻️
Conhecendo um pouco mais sobre funções e parâmetros e ponteiros.
Ponteiros e operações com arrays.
*/

// Variáveis globais:

char palavra_secreta[20];
char chutes[26];
int chutes_dados = 0;


// Funções de controle:

void abertura(){
	printf(" ************************************************************************   \n");
	printf(" -+                         Bem vindo ao                               +- \n\n");
	printf("      | |                       | |       |_____|                           \n");
	printf("      | | ___   __ _  ___     __| | __ _  | |__ ___  _ __ ___ __ _          \n");
	printf("  _   | |/ _ \\ / _` |/ _ \\   / _` |/ _` | |  __/ _ \\| '__/ __/ _` |      \n");
	printf(" | |__| | (_) | (_| | (_) | | (_| | (_| | | | | (_) | | | (_| (_| |         \n");
	printf("  \\____/ \\___/ \\__, |\\___/   \\__,_|\\__,_| |_|  \\___/|_|  \\___\\__,_|\n");
	printf("                __/ |                                                       \n");
	printf("               |___/      											      \n\n");
	printf(" -+                Descobre qual a palavra secreta!                    +-   \n");
	printf(" ************************************************************************   \n");
}

void chuta(){ 
	char chute;
	printf("Chuta uma letra!\n");
	scanf(" %c", &chute);
	chutes[chutes_dados] = chute;
	chutes_dados++;
}

int ja_chutou (char letra){ 
	int achou = 0;
	for(int j = 0; j < chutes_dados; j++) {
		if(chutes[j] == letra) {
			achou = 1;
		    	break;
		}
	}
	return achou;
}

void desenha_forca(){ 
	printf("Você já deu %d chutes\n", chutes_dados);
	for(int i = 0; i < strlen(palavra_secreta); i++) {
		if(ja_chutou(palavra_secreta[i])) {
		        printf("%c ", palavra_secreta[i]);
	    	} else {
			printf("_ ");
	    	}
    	}
   	 printf("\n\n");
}

// Trabalhando com arquivo .txt com a lista de palavras.

void escolhe_palavra (){
	FILE* f;
	f = fopen("palavras.txt", "r");
	if(f == 0) {
        	printf("Banco de dados de palavras não disponível\n\n");
        	exit(1);
	}
	
	int qtd_palavras;
	fscanf(f, "%d", &qtd_palavras);
	
	srand(time(0));
	int randomico = rand() % qtd_palavras;
	
	for(int i = 0; i <= randomico; i++){
		fscanf(f, "%s", &palavra_secreta);
	}
	fclose(f);
}

void adiciona_palavra(){
	char quer;
	printf("Quer adicionar uma nova palavra ao jogo?\n");
	scanf(" %c", &quer);
	if(quer == 'S'){
		char nova_palavra[20];
		printf("Digite a nova palavra: \n");
		scanf("%s", &nova_palavra);
		
		FILE* f
		f = fopen("palavras.txt", "r+");
		if(f == 0) {
        		printf("Banco de dados de palavras não disponível\n\n");
       			exit(1);
       		}
		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;
		
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);
		
		fseek(f, 0, SEEK_END);
		printf(f, "\n%s", nova_palavra);
		fclose(f);		
	}
}

// Definindo o desfecho do jogo: venceu ou perdeu?

// 😄️
int acertou(){ 
	for(int i = 0; i < strlen(palavra_secreta); i++) {
		if(!ja_chutou(palavra_secreta[i])){
			return 0;
		} 
	}
	return 1;
}
	
// 😭️
int enforcou(){ 
	int erros = 0; 
	for(int i = 0; i < chutes_dados; i++){
		int existe = 0;
		for(int j = 0; j < strlen(palavra_secreta); j++) {
			if(chutes[i] == palavra_secreta[j]){
				existe = 1;
				break;
			}
		}
		if(!existe){
			erros++;
		}
	}
	return erros >= 5;
}

// Executando o jogo:

int main() {
			
	abertura();
	escolhe_palavra ();
	
	do {
		
		chuta();
		desenha_forca();
				
	} while (!acertou() && !enforcou());
	
	if(enforcou()){
		printf("Perdeste e foste para a forca. Mas tente de novo!\n");
		printf("	ヽ〳 ՞ ᗜ ՞ 〵ง  \n");
	}
	if(acertou()){
		printf("Parabéns! Escapaste da forca!\n");
		printf("	d–(^ ‿ ^ )z  \n");
		adiciona_palavra();
	}
