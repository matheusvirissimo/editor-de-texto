#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

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

void salvarMatrizEmArquivo(No* cabeca, char nomeTexto[]) {
    FILE* arquivo = fopen(nomeTexto, "w");
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
    printf("Matriz salva no arquivo %s.\n", nomeTexto);
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

void lerArquivoTexto(No** cabeca, char nomeTexto[]) {
    FILE* arquivo = fopen(nomeTexto, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeTexto);
        return;
    }

    int linha = 0;
    int coluna = 0;
    char ch;
    while ((ch = fgetc(arquivo)) != EOF) {
        if (ch == '\n') {
            linha++;
            coluna = 0;
        } else {
            adicionarElemento(cabeca, linha, coluna, ch);
            coluna++;
        }
    }

    fclose(arquivo);
}

void exibirTexto(No* cabeca) {
    system("cls");
    No* atual = cabeca;
    while (atual != NULL) {
        gotoxy(atual->coluna, atual->linha);
        printf("%c", atual->caracter);
        atual = atual->proximo;
    }
}

void modoEdicao(No** cabeca, char nomeTexto[]) {
    int linhas = 0;
    int colunas = 0;
    int key;

    if (*cabeca != NULL) {
        exibirTexto(*cabeca);
    } else {
        gotoxy(0, 0);
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
                No* atual = *cabeca;
                while (atual != NULL) {
                    if (atual->linha == linhas && atual->coluna == colunas) {
                        No* anterior = atual->anterior;
                        No* proximo = atual->proximo;
                        if (anterior != NULL) {
                            anterior->proximo = proximo;
                        } else {
                            *cabeca = proximo;
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
        } else {  // Caracteres imprimíveis
            printf("%c", key);
            adicionarElemento(cabeca, linhas, colunas, key);
            colunas++;
        }
    }

    printf("\nNumero de linhas: %d\n", linhas);
    printf("Numero de colunas: %d\n", colunas);

    salvarMatrizEmArquivo(*cabeca, nomeTexto);

    liberarLista(cabeca);
}

int main() {
    int menu;
    char nomeTexto[100];
    No* cabeca = NULL;

    while (1) {
        system("cls");
        printf("*** MENU ***\n\n");
        printf("1 - Criar texto\n2 - Ler texto\n3 - Editar texto\n4 - Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &menu);
        fflush(stdin);

        switch (menu) {
        case 1:
            printf("Digite o nome do arquivo para salvar o texto: ");
            scanf("%s", nomeTexto);
            fflush(stdin);
            modoEdicao(&cabeca, nomeTexto);
            break;
        case 2:
            printf("Digite o nome do arquivo para ler o texto: ");
            scanf("%s", nomeTexto);
            fflush(stdin);
            lerArquivoTexto(&cabeca, nomeTexto);
            exibirTexto(cabeca);
            _getch();
            liberarLista(&cabeca);
            break;
        case 3:
            printf("Digite o nome do arquivo para editar o texto: ");
            scanf("%s", nomeTexto);
            fflush(stdin);
            lerArquivoTexto(&cabeca, nomeTexto);
            modoEdicao(&cabeca, nomeTexto);
            break;
        case 4:
            printf("Finalizando o editor.\n");
            liberarLista(&cabeca);
            return 0;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    }

    return 0;
}