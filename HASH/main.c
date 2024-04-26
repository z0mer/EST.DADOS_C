#include <stdio.h>
#include <stdlib.h>

#define tam_hash 11

typedef struct Celula {
    int valor;
    struct Celula *proximo;
} Celula;

typedef struct Lista {
    int qtde;
    Celula *primeiro;
} Lista;

typedef struct Hash {
    Lista* tabela[tam_hash];
} Hash;

Hash* start_hash() {
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    for(int i = 0; i < tam_hash; i++) {
        hash->tabela[i] = (Lista*)malloc(sizeof(Lista));
        hash->tabela[i]->primeiro = NULL;
        hash->tabela[i]->qtde = 0;
    }
    return hash;
}

int hashing(int valor) {
    return valor % tam_hash;
}

void inserir_lista(Lista *l, int valor) {
    Celula *novo = (Celula*)malloc(sizeof(Celula));
    novo->valor = valor;
    novo->proximo = NULL;

    if(l->primeiro == NULL) {
        l->primeiro = novo;
    } else {
        Celula *atual = l->primeiro;
        Celula *anterior = NULL;
        while(atual != NULL && atual->valor <= valor) {
            anterior = atual;
            atual = atual->proximo;
        }
        if(anterior == NULL) {
            novo->proximo = l->primeiro;
            l->primeiro = novo;
        } else {
            if(atual == NULL) {
                anterior->proximo = novo;
            } else {
                novo->proximo = atual;
                anterior->proximo = novo;
            }
        }
    }
    l->qtde++;
}

void inserir_hash(Hash* hash, int valor) {
    int indice = hashing(valor);
    inserir_lista(hash->tabela[indice], valor);
}

void remover_lista(Lista *l, int valor) {
    Celula *atual = l->primeiro;
    Celula *anterior = NULL;

    while(atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual != NULL) {
        if(anterior == NULL) {
            l->primeiro = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        free(atual);
        l->qtde--;
    }
}

void remover_hash(Hash* hash, int valor) {
    int indice = hashing(valor);
    remover_lista(hash->tabela[indice], valor);
}

void imprimir(Hash* hash) {
    printf("---------------------\n");
    for(int i = 0; i < tam_hash; i++) {
        printf("%d -> ", i);
        Celula* atual = hash->tabela[i]->primeiro;
        while(atual != NULL) {
            printf("%d ", atual->valor);
            atual = atual->proximo;
        }
        printf("\n");
    }
    printf("---------------------\n");
}

void preencher_lista(Lista *lista, int valores[]) {
    for(int i = 0; valores[i] != 0; i++) {
        inserir_lista(lista, valores[i]);
    }
}

int main(void) {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->qtde = 0;

    int valores_primeiro[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0};
    preencher_lista(lista, valores_primeiro);

    Hash* hash = start_hash();
    for(int i = 0; i < tam_hash; i++) {
        hash->tabela[i]->primeiro = NULL;
        hash->tabela[i]->qtde = 0;
    }

    for(int i = 0; valores_primeiro[i] != 0; i++) {
        inserir_hash(hash, valores_primeiro[i]);
    }

    imprimir(hash);

    // Segundo conjunto de entrada
    Lista* nova_lista = (Lista*)malloc(sizeof(Lista));
    nova_lista->primeiro = NULL;
    nova_lista->qtde = 0;

    int valores_segundo[] = {12, 13, 14, 15, 16, 17, 0};
    preencher_lista(nova_lista, valores_segundo);

    Hash* nova_hash = start_hash();
    for(int i = 0; i < tam_hash; i++) {
        nova_hash->tabela[i]->primeiro = NULL;
        nova_hash->tabela[i]->qtde = 0;
    }

    for(int i = 0; valores_segundo[i] != 0; i++) {
        inserir_hash(nova_hash, valores_segundo[i]);
    }

    imprimir(nova_hash);

    return 0;
}
