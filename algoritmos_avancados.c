// Código nivel aventureiro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Criação do nó para árvore
struct No{
    char nome[50];
    char pista[20];
    struct No* esquerda;
    struct No* direita;
};

// Criação do nó para pistas
struct NoPistas{
    char pista[50];
    struct NoPistas* esquerda;
    struct NoPistas* direita;
};

// Função para criar árvore
struct No* criarSala(char* nome, char* pista){
    struct No* novo = (struct No*) malloc (sizeof(struct No));
    strcpy(novo->nome, nome);
    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Função para liberar o armazenamento da árvore
void liberar(struct No* raiz){
    if (raiz != NULL){
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

// Função para liberar o armazenamento da árvore BST
void liberarPistas(struct NoPistas* raiz){
    if(raiz != NULL){
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// Função para inserir pistas na árvore de pistas
struct NoPistas* inserirPista(struct NoPistas* raiz, const char* pista){
    if (raiz == NULL){
        struct NoPistas* novo = (struct NoPistas*) malloc (sizeof(struct NoPistas));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
        
    }
    if(strcmp(pista, raiz->pista) < 0){
            raiz->esquerda = inserirPista(raiz->esquerda, pista);
        } else if(strcmp(pista, raiz->pista) > 0){
            raiz->direita = inserirPista(raiz->direita, pista);
        }
    return raiz;
}

// Função para explorar a mansão
void explorarSalas(struct No* atual, struct NoPistas** pistas){
    char opcao;
    while(atual != NULL){
        printf("\nVoce esta em: %s\n", atual->nome);
        if(strlen(atual->pista) > 0){
            printf("Pista encontrada: %s\n", atual->pista);
            *pistas = inserirPista(*pistas, atual->pista);
        }
        // Verifica se chegou a uma folha
        if(atual->esquerda == NULL && atual->direita == NULL){
            printf("Fim do caminho!\n");
            break;
        }
        printf("e - Esquerda\n");
        printf("d - Direita\n");
        printf("s - Sair\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);
        if(opcao == 's'){
            printf("Exploracao encerrada.\n");
            break;
        }
        else if(opcao == 'e'){
            if(atual->esquerda != NULL){
                atual = atual->esquerda;
            }
            else{
                printf("Nao existe caminho para a esquerda!\n");
            }
        }
        else if(opcao == 'd'){
            if(atual->direita != NULL){
                atual = atual->direita;
            }
            else{
                printf("Nao existe caminho para a direita!\n");
            }
        }
        else{
            printf("Opcao invalida!\n");
        }
    }
}

void exibirPistas(struct NoPistas* raiz){
    if (raiz != NULL){
        exibirPistas(raiz->esquerda);
        printf("%s \n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

int main() {
struct No* raiz = criarSala("Hall de entrada", "Pegadas");
raiz->esquerda = criarSala("Cozinha", "Faca");
raiz->direita = criarSala("Sala de estar", "Bilhete");
raiz->direita->direita = criarSala("Banheiro", "Toalha");
raiz->direita->esquerda = criarSala("Quarto de hóspedes", "Chave");
raiz->esquerda->esquerda = criarSala("Biblioteca", "Livro com marcas");
struct NoPistas* pistas = NULL;

printf("-- Bem vindo ao jogo: Detective Quest! -- \n");
explorarSalas(raiz, &pistas);
printf("\nPistas coletadas em ordem alfabetica:\n");
exibirPistas(pistas);
liberar(raiz);
liberarPistas(pistas);
return 0;
}

