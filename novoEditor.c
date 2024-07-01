#include <stdio.h>
#include <conio.h>
#include <windows.h>

typedef struct No {
    int linha;
    int coluna;
    char caracter;
    struct No* anterior;
    struct No* proximo;
} No;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void adicionarElemento(No** cabeca, int linha, int coluna, char caracter) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo != NULL) {
        novoNo->linha = linha;
        novoNo->coluna = coluna;
        novoNo->caracter = caracter;
        novoNo->anterior = NULL;
        novoNo->proximo = NULL;

        if (*cabeca == NULL) {
            *cabeca = novoNo;
        } else {
            No* atual = *cabeca;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novoNo;
            novoNo->anterior = atual;
        }
    }
}

void salvarMatrizEmArquivo(No* cabeca) {
    FILE* arquivo = fopen("matriz.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    No* atual = cabeca;
    int linhaMax = -1;
    int colunaMax = -1;

    while (atual != NULL) {
        if (atual->linha > linhaMax) {
            linhaMax = atual->linha;
        }
        if (atual->coluna > colunaMax) {
            colunaMax = atual->coluna;
        }
        atual = atual->proximo;
    }

    for (int i = 0; i <= linhaMax; i++) {
        for (int j = 0; j <= colunaMax; j++) {
            atual = cabeca;
            while (atual != NULL) {
                if (atual->linha == i && atual->coluna == j) {
                    fprintf(arquivo, "%c", atual->caracter);
                    break;
                }
                atual = atual->proximo;
            }
            if (atual == NULL) {
                fprintf(arquivo, " ");
            }
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Matriz salva no arquivo 'matriz.txt'.\n");
}

void liberarLista(No** cabeca) {
    No* atual = *cabeca;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *cabeca = NULL;
}

int main() {
    int linhas = 0;
    int colunas = 0;
    int menu;
    int key;

    gotoxy(0, 0);

    No* cabeca = NULL;

    printf("*** MENU ***\n\n");
    printf("1 - Criar texto\n2 - Ler texto\n\n");
    printf("Digite sua opcao: ");
    scanf("%d", &menu);

    switch(menu){ 
        case 1:
            break;
        case 2:
            break;
        default:
            printf("Na");
            break;
    }

    while (1) {
        key = _getch();

        if (key == 27) {  // Verifica se a tecla Esc foi pressionada
            break;
        } else if (key == 13) {  // Verifica se a tecla Enter foi pressionada
            linhas++;
            colunas = 0;
            gotoxy(colunas, linhas);
            printf("\n");
        } else if (key == 8) {  // Verifica se a tecla Backspace foi pressionada
            if (colunas > 0) {
                colunas--;
                printf(" ");
                gotoxy(colunas, linhas);
                No* atual = cabeca;
                while (atual != NULL) {
                    if (atual->linha == linhas && atual->coluna == colunas) {
                        No* anterior = atual->anterior;
                        No* proximo = atual->proximo;
                        if (anterior != NULL) {
                            anterior->proximo = proximo;
                        } else {
                            cabeca = proximo;
                        }
                        if (proximo != NULL) {
                            proximo->anterior = anterior;
                        }
                        free(atual);
                        break;
                    }
                    atual = atual->proximo;
                }
            }
        } else if (key == 224 || key == 0) {  // Verifica teclas especiais
            key = _getch();
            switch (key) {
                case 72:  // Tecla de seta para cima
                    linhas--;
                    gotoxy(colunas, linhas);
                    break;
                case 80:  // Tecla de seta para baixo
                    linhas++;
                    gotoxy(colunas, linhas);
                    break;
                case 75:  // Tecla de seta para esquerda
                    colunas--;
                    gotoxy(colunas, linhas);
                    break;
                case 77:  // Tecla de seta para direita
                    colunas++;
                    gotoxy(colunas, linhas);
                    break;
            }
        } else {  // Caracteres imprim�veis
            printf("%c", key);
            adicionarElemento(&cabeca, linhas, colunas, key);
            colunas++;
        }
    }

    printf("\nNumero de linhas: %d\n", linhas);
    printf("Numero de colunas: %d\n", colunas);

    salvarMatrizEmArquivo(cabeca);

    liberarLista(&cabeca);

    return 0;
}