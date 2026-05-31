// Código nivel novato

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Criação do nó para árvore
struct No{
    char nome[50];
    struct No* esquerda;
    struct No* direita;
};


// Função para criar árvore
struct No* criarSala(char* valor){
    struct No* novo = (struct No*) malloc (sizeof(struct No));
    strcpy(novo->nome, valor);
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

// Função para explorar a mansão
void explorarSalas(struct No* atual){
    char opcao;
    while(atual != NULL){
        printf("\nVoce esta em: %s\n", atual->nome);
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


int main() {
struct No* raiz = criarSala("Hall de entrada");
raiz->esquerda = criarSala("Cozinha");
raiz->direita = criarSala("Sala de estar");
raiz->direita->direita = criarSala("Banheiro");
raiz->direita->esquerda = criarSala("Quarto de hóspedes");
raiz->esquerda->esquerda = criarSala("Biblioteca");

printf("-- Bem vindo ao jogo: Detective Quest! -- \n");
explorarSalas(raiz);
liberar(raiz);
return 0;
}

