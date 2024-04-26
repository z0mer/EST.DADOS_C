#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
  struct celula *anterior;
  int valor;
  struct celula *proximo;
} celula;

typedef struct {
  int qtde;
  celula *primeiro;
} lista;

lista *criar_lista() {
  lista *l = malloc(sizeof(lista));
  l->primeiro = NULL;
  l->qtde = 0;
  return l;
}

celula *criar_celula(int valor) {
  celula *c = malloc(sizeof(celula));
  c->anterior = NULL;
  c->valor = valor;
  c->proximo = NULL;
  return c;
}

void inserir(lista *l, int valor) {
  celula *nova = criar_celula(valor);
  celula *atual = l->primeiro;
  celula *anterior = NULL;
  while (atual != NULL && atual->valor < valor) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (anterior == NULL) { // inserção no início
    l->primeiro = nova;
  } else {
    nova->anterior = anterior;
    anterior->proximo = nova;
  }
  if (atual != NULL) { // inserção no meio
    atual->anterior = nova;
    nova->proximo = atual;
  }
  l->qtde++;
}

void mostrar(lista *l) {
  printf("início -> ");
  celula *atual = l->primeiro;
  while (atual != NULL) {
    printf("%d ", atual->valor);
    atual = atual->proximo;
  }
  printf("<- final\n");
}

void mostrar_invertido(lista *l) {
  printf("final -> ");
  celula *atual = l->primeiro;
  celula *ultimo = NULL;
  while (atual != NULL){
    ultimo = atual;
    atual = atual->proximo;
  }
  while (ultimo != NULL){
    printf("%d ", ultimo->valor);
    ultimo = ultimo->anterior;
  }
  printf("<- início\n");
}

void remover(lista *l, int valor) {
  celula *atual = l->primeiro;
  celula *anterior = NULL;
  while (atual != NULL && atual->valor != valor){
    anterior = atual;
    atual = atual->proximo;
  }
  if(atual != NULL){
    if(anterior == NULL){
      l->primeiro = atual->proximo;
    } else {
      anterior->proximo = atual->proximo;
    }
    if (atual->proximo != NULL){
      atual->proximo->anterior = anterior;
    }
    free(atual);
    l->qtde--;
  }
}

int main(void) {
  // não alterar essa função
  lista *l = criar_lista();
  inserir(l, 10);
  inserir(l, 20);
  inserir(l, 15);
  mostrar(l);
  mostrar_invertido(l);
  for (int i = 0; i < 10; i++) {
    inserir(l, i + 1);
  }
  mostrar(l);
  mostrar_invertido(l);
  remover(l, 20);
  remover(l, 15);
  remover(l, 10);
  mostrar(l);
  mostrar_invertido(l);
  remover(l, 20);
  remover(l, 15);
  remover(l, 10);
  for (int i = 0; i < 10; i++) {
    remover(l, i + 1);
  }
  mostrar(l);
  mostrar_invertido(l);
  return 0;
}
