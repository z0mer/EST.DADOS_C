#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice {
  int valor;
  struct Vertice *esq;
  struct Vertice *dir;
  struct Vertice *pai;
} Vertice;

typedef struct Arvore {
  Vertice *raiz;
  int qtde;
} Arvore;

void in_ordem(Vertice *raiz) {
  if (raiz != NULL) {
    in_ordem(raiz->esq);
    printf("%d ", raiz->valor);
    in_ordem(raiz->dir);
  }
}

void pre_ordem(Vertice *raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->valor);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);
  }
}

void pos_ordem(Vertice *raiz) {
  if (raiz != NULL) {
    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("%d ", raiz->valor);
  }
}

Vertice *cria_vertice(Arvore *arvore, int valor) {
  Vertice *novo = malloc(sizeof(Vertice));
  novo->dir = NULL;
  novo->esq = NULL;
  novo->pai = NULL;
  novo->valor = valor;

  return novo;
}

Arvore *cria_arvore() {
  Arvore *arvore = malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  arvore->qtde = 0;

  return arvore;
}

void inserir(Arvore *arvore, int valor) {
  Vertice *novo = cria_vertice(arvore, valor);
  if (arvore->raiz == NULL) {
    arvore->raiz = novo;
  } else {
    Vertice *pai = NULL;
    Vertice *atual = arvore->raiz;

    while (atual != NULL) {
      pai = atual;
      if (novo->valor > atual->valor) {
        atual = atual->dir;
      } else {
        atual = atual->esq;
      }
    }
    if (novo->valor > pai->valor) {
      pai->dir = novo;
    } else {
      pai->esq = novo;
    }
    novo->pai = pai;
  }
  arvore->qtde++;
}

int remover_vertice(Arvore *arvore, Vertice *vertice) {
  if (vertice != NULL) {
    int filhos = 0;
    if (vertice->esq != NULL) {
      filhos++;
    }
    if (vertice->dir != NULL) {
      filhos++;
    }

    if (filhos == 0) {
      if (arvore->raiz == vertice) {
        arvore->raiz = NULL;
      } else if (vertice->pai->esq == vertice) {
        vertice->pai->esq = NULL;
      } else {
        vertice->pai->dir = NULL;
      }
      free(vertice);
      arvore->qtde--;
      return 1;
    } else if (filhos == 1) {
      Vertice *filho = NULL;
      if (vertice->esq != NULL) {
        filho = vertice->esq;
      } else {
        filho = vertice->dir;
      }
      if (vertice->pai != NULL) {
        if (vertice->pai->esq == vertice) {
          vertice->pai->esq = filho;
        } else {
          vertice->pai->dir = filho;
        }
        filho->pai = vertice->pai;
      } else {
        arvore->raiz = filho;
        filho->pai = NULL;
      }
      free(vertice);
      arvore->qtde--;
      return 1;
    } else {
      Vertice *pai = NULL;
      Vertice *atual = vertice->esq;
      int aux;
      while (atual != NULL) {
        pai = atual;
        atual = atual->dir;
      }
      aux = pai->valor;
      pai->valor = vertice->valor;
      vertice->valor = aux;
      remover_vertice(arvore, pai);
    }
  }
  return 0;
}

Vertice *buscar_valor(Arvore *arvore, int valor) {
  Vertice *atual = arvore->raiz;
  while (atual != NULL) {
    if (valor < atual->valor) {
      atual = atual->esq;
    } else {
      if (valor > atual->valor) {
        atual = atual->dir;
      } else {
        return atual;
      }
    }
  }
  return NULL;
}

int main(void) {
  int dados[] = {5, 3, 8, 2, 4, 7, 9, 1, 6, 10};
  Arvore *arvore = cria_arvore();

  for (int i = 0; i < 8; i++) {
    inserir(arvore, dados[i]);
    printf("Inseriu %d mostra em ordem -> ", dados[i]);
    in_ordem(arvore->raiz);
    printf("\n");
    printf("Inseriu %d mostra em pré-ordem -> ", dados[i]);
    pre_ordem(arvore->raiz);
    printf("\n");
    printf("Inseriu %d mostra em pós-ordem -> ", dados[i]);
    pos_ordem(arvore->raiz);
    printf("\n");
  }

  for (int i = 0; i < 10; i++) {
    Vertice *vertice = buscar_valor(arvore, dados[i]);
    if (vertice != NULL) {
      remover_vertice(arvore, vertice);
    }
    printf("Removeu %d mostra em ordem -> ", dados[i]);
    in_ordem(arvore->raiz);
    printf("\n");
    printf("Removeu %d mostra em pré-ordem -> ", dados[i]);
    pre_ordem(arvore->raiz);
    printf("\n");
    printf("Removeu %d mostra em pós-ordem -> ", dados[i]);
    pos_ordem(arvore->raiz);
    printf("\n");
  }

  return 0;
}
