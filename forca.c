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

// 🚩️ Variáveis globais:

char palavra_secreta[TAMANHO_PALAVRA];
char chutes[26];
int chutes_dados = 0;


// 🚩️ Funções de controle:

int letra_existe(char letra) {
    for(int j = 0; j < strlen(palavra_secreta); j++) {
        if(letra == palavra_secreta[j]) {
            return 1;
        }
    }
    return 0;
}

// Definindo o desfecho do jogo: venceu ou perdeu?

int chutes_errados() {
	int erros = 0;
	for(int i = 0; i < chutes_dados; i++) {
		if(!letra_existe(chutes[i])) {
			erros++;
		}
	}
	return erros;
}

// 😭️
int enforcou() {
	return chutes_errados() >= 5;
}

// 😄️
int acertou(){
	for(int i = 0; i < strlen(palavra_secreta); i++) {
		if(!ja_chutou(palavra_secreta[i])){
			return 0;
		}
	}
	return 1;
}

// Cabeçalho do jogo:

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
	if(letra_existe(chute)) {
        	printf("Você acertou: a palavra tem a letra %c\n\n", chute);
    	} else {
        	printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
    	}
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

	int erros = chutes_errados(); // desenhando a forca com 'if ternário'.

	printf(" _______	   \n");
	printf(" |/	 |	   \n");
	printf(" |      %c%c%c     \n", (erros>=1?'(':' '),(erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c     \n", (erros>=3?'\\':' '),(erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |	 %c        \n", (erros>=2?'|':' '));
	printf(" |	%c %c      \n", (erros>=4?'/':' '),(erros>=4?'\\':' '));
	printf(" |	           \n");
	printf("_|___		   \n");
	printf("\n\n");

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
		fscanf(f, "%s", palavra_secreta);
	}
	fclose(f);
}

void adiciona_palavra(){
	char quer;
	printf("Quer adicionar uma nova palavra ao jogo?\n");
	scanf(" %c", &quer);
	if(quer == 'S'){
		char nova_palavra[TAMANHO_PALAVRA];
		printf("Digite a nova palavra: \n");
		scanf("%s", nova_palavra);

		FILE* f;
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
		fprintf(f, "\n%s", nova_palavra);
		fclose(f);
	}
}

// 🚩️ Executando o jogo:

int main() {

	abertura();
	escolhe_palavra ();

    do {

		chuta();
		desenha_forca();

	} while (!acertou() && !enforcou());

	if(acertou()){
		printf("Parabéns! Escapaste da forca!\n\n");
		printf("	d–(^ ‿ ^ )z  \n\n");
		adiciona_palavra();
	} else {
		printf("Perdeste e foste para a forca. Mas tente de novo!\n\n");
		printf("	ヽ〳 ՞ ᗜ ՞ 〵ง  \n\n");
	}
}
