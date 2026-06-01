// Código nivel mestre

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho 10

// Variáveis
char pistasColetadas[20][50];
int totalPistas = 0;

// Criação do nó para árvore
struct No{
    char nome[50];
    char pista[20];
    struct No* esquerda;
    struct No* direita;
};

// Criação do nó para pistas (BST)
struct NoPistas{
    char pista[50];
    struct NoPistas* esquerda;
    struct NoPistas* direita;
};

// Criação do nó para suspeitos (hash)
struct NoSuspeito{
    char pista[50];
    char suspeito[50];
    struct NoSuspeito* proximo;
};

struct NoSuspeito* tabelaHash[tamanho];

// Função para criar árvore
struct No* criarSala(char* nome, char* pista){
    struct No* novo = (struct No*) malloc (sizeof(struct No));
    strcpy(novo->nome, nome);
    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Função Hash
int funcaoHash(const char* chave){
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++){
        soma += chave[i];
    }
    return soma % tamanho;
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

// Função para inserir dados na tabela hash
void inserirHash(const char* pista, const char* suspeito){
    int indice = funcaoHash(pista);
    struct NoSuspeito* novo = (struct NoSuspeito*) malloc (sizeof(struct NoSuspeito));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = tabelaHash[indice];
    tabelaHash[indice]= novo;
}

// Função de busca
char* encontrarSuspeito(const char* pista){
    int indice = funcaoHash(pista);
    struct NoSuspeito* atual = tabelaHash[indice];
    while (atual != NULL){
        if (strcmp(atual->pista, pista) == 0) return atual->suspeito;
        atual = atual->proximo;
    }
    return NULL;
}

// Função para verificar se o suspeito acusado possui pelo menos duas pistas associadas
void verificarSuspeitoFinal(char* acusado){
    int contador = 0;
    for(int i = 0; i < totalPistas; i++){
        char* suspeito = encontrarSuspeito(pistasColetadas[i]);
        if(suspeito != NULL && strcmp(suspeito, acusado) == 0){
            contador++;
        }
    }
    if(contador >= 2){
        printf("\nAcusacao confirmada!\n");
        printf("%s é o culpado!\n", acusado);
    }
    else{
        printf("\nNão há pistas suficientes para acusar %s.\n", acusado);
    }
}

// Função para explorar a mansão
void explorarSalas(struct No* atual, struct NoPistas** pistas){
    char opcao;
    while(atual != NULL){
        printf("\nVoce esta em: %s\n", atual->nome);
        if(strlen(atual->pista) > 0){
            printf("Pista encontrada: %s\n", atual->pista);
            *pistas = inserirPista(*pistas, atual->pista);
            strcpy(pistasColetadas[totalPistas], atual->pista);
            totalPistas++;
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

inserirHash("Faca", "Mordomo");
inserirHash("Bilhete", "Mordomo");
inserirHash("Chave", "Governanta");
inserirHash("Livro com marcas", "Governanta");
inserirHash("Pegadas", "Jardineiro");
inserirHash("Toalha", "Jardineiro");

printf("-- Bem vindo ao jogo: Detective Quest! -- \n");
explorarSalas(raiz, &pistas);
printf("\nPistas coletadas em ordem alfabetica:\n");
exibirPistas(pistas);

char acusado[50];
printf("\nQuem é o culpado?\n");
scanf(" %s", acusado);
verificarSuspeitoFinal(acusado);

liberar(raiz);
liberarPistas(pistas);
return 0;
}

