#include <stdio.h>
#include <stdlib.h>

#define tam_hash 11 // Tamanho da tabela de espalhamento

typedef struct Celula {
    int valor;
    struct Celula *proximo;
} Celula;

typedef struct Lista {
    int qtde; // Quantidade de elementos na lista
    Celula *primeiro; // Ponteiro para o primeiro elemento da lista
} Lista;

typedef struct Hash {
    Lista *tabela[tam_hash]; // Array de listas para a tabela de espalhamento
} Hash;

// Função para inicializar a tabela de espalhamento
Hash *start_hash() {
    Hash *hash = (Hash *) malloc(sizeof(Hash)); // Aloca memória para a estrutura Hash
    for (int i = 0; i < tam_hash; i++) {
        hash->tabela[i] = (Lista *) malloc(sizeof(Lista)); // Aloca memória para cada lista na tabela
        hash->tabela[i]->primeiro = NULL; // Inicializa o ponteiro para o primeiro elemento como NULL
        hash->tabela[i]->qtde = 0; // Inicializa a quantidade de elementos como 0
    }
    return hash; // Retorna a tabela de espalhamento inicializada
}

// Função de espalhamento usando o método da divisão
int hashing(int valor) {
    return valor % tam_hash; // Retorna o valor módulo o tamanho da tabela
}

// Função para inserir um valor na lista encadeada
void inserir_lista(Lista *l, int valor) {
    Celula *novo = (Celula *) malloc(sizeof(Celula)); // Aloca memória para o novo elemento
    novo->valor = valor; // Define o valor do novo elemento
    novo->proximo = l->primeiro; // O próximo do novo elemento aponta para o antigo primeiro elemento
    l->primeiro = novo; // Atualiza o primeiro elemento da lista para ser o novo elemento
    l->qtde++; // Incrementa a quantidade de elementos na lista
}

// Função para inserir um valor na tabela de espalhamento
void inserir_hash(Hash *hash, int valor) {
    int indice = hashing(valor); // Calcula o índice usando a função de espalhamento
    inserir_lista(hash->tabela[indice], valor); // Insere o valor na lista correspondente ao índice
}

// Função para remover um valor da tabela de espalhamento
void remover_hash(Hash *hash, int valor) {
    int indice = hashing(valor); // Calcula o índice usando a função de espalhamento
    Celula *atual = hash->tabela[indice]->primeiro; // Ponteiro para o primeiro elemento da lista correspondente
    Celula *anterior = NULL; // Ponteiro para o elemento anterior ao elemento atual

    // Percorre a lista até encontrar o elemento a ser removido ou o final da lista
    while (atual != NULL && atual->valor != valor) {
        anterior = atual; // Atualiza o ponteiro para o elemento anterior
        atual = atual->proximo; // Move para o próximo elemento
    }

    // Se o elemento não foi encontrado, retorna
    if (atual == NULL)
        return;

    // Se o elemento é o primeiro da lista
    if (anterior == NULL)
        hash->tabela[indice]->primeiro = atual->proximo;
    else
        anterior->proximo = atual->proximo; // Atualiza o próximo do elemento anterior para pular o elemento atual

    free(atual); // Libera a memória do elemento removido
    hash->tabela[indice]->qtde--; // Decrementa a quantidade de elementos na lista
}

// Função para imprimir a tabela de espalhamento
void imprimir(Hash *hash) {
    printf("---------------------\n");
    for (int i = 0; i < tam_hash; i++) {
        printf("%d -> ", i); // Imprime o índice atual
        Celula *atual = hash->tabela[i]->primeiro; // Ponteiro para o primeiro elemento da lista atual
        while (atual != NULL) {
            printf("%d ", atual->valor); // Imprime o valor do elemento atual
            atual = atual->proximo; // Move para o próximo elemento
        }
        printf("\n"); // Imprime uma nova linha ao final de cada lista
    }
    printf("---------------------\n");
}

// Função principal
int main(void) {
    Hash *hash = start_hash(); // Inicializa a tabela de espalhamento
    int valor;
    while (1) {
        scanf("%d", &valor); // Lê um valor do usuário
        if (valor == 0)
            break; // Se o valor for 0, encerra o loop
        inserir_hash(hash, valor); // Insere o valor na tabela de espalhamento
    }
    imprimir(hash); // Imprime a tabela de espalhamento após a inserção dos valores
    while (1) {
        scanf("%d", &valor); // Lê um valor do usuário
        if (valor == 0)
            break; // Se o valor for 0, encerra o loop
        remover_hash(hash, valor); // Remove o valor da tabela de espalhamento
    }
    imprimir(hash); // Imprime a tabela de espalhamento após a remoção dos valores
    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}
