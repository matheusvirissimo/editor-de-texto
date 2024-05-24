#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Lista duplamente encadeada para as strings

typedef struct nostring{
    char c;
    struct nostring *prox;
}NOSTRING;

typedef struct strdin{
    NOSTRING *inicio;
    NOSTRING *fim;
} STRDIN;

void inicializarString(STRDIN *str){
    str->inicio = NULL;
    str->fim = NULL;
}

NOSTRING* criarChar(char c){
    NOSTRING *novoChar = (NOSTRING*) malloc(sizeof(NOSTRING));
    
    novoChar->c = c;
    novoChar->prox = NULL;
    
    return novoChar;
}


void inserirChar(STRDIN *str, char c){
    NOSTRING *auxChar = criarChar(c);

    if(str->inicio = NULL){
        str->inicio = auxChar;
        str->fim = auxChar;
    }else{
        str->fim->prox = auxChar;
        str->fim = auxChar;
    }
}


void escreverArquivo(FILE *file, char palavra[]){
    file = fopen("editorTexto.txt", "a+");
    if(file == NULL){
        printf("O arquivo nao foi aberto\n");
        return;
    }

    int verif = fputs(palavra, file);
    if(verif == EOF){
        printf("Erro na escrita dos dados.\n");
    }else{
        printf("Sucesso na escrita dos dados.\n"); 
    }
    fclose(file);
    return;
}

void lerArquivo(FILE *file){
    char palavra[MAX];
    file = fopen("editorTexto.txt", "r"); 
    if(file == NULL){
        printf("O arquivo nao foi aberto");
        return;
    }

    while(fgets(palavra, MAX, file) != NULL){
        printf("%s", palavra);
    }
    fclose(file);
    return;
}

int main(){
    char frase[MAX];
    FILE *file;

    printf("*** EDITOR DE TEXTO ***\n\n");
    printf("Digite uma palavra: ");
    fgets(frase, 100, stdin);
    int tam = strlen(frase);
    for(int i = 0; i < tam; i++){
        inserirChar
    }

    escreverArquivo(file, frase);
    lerArquivo(file);
    return;
}