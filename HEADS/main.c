#include <stdio.h>
#include <stdlib.h>

#define LEN 10

typedef struct {
  int valores[LEN];
  int qtde;
} heap;

int f_e(int pai) { return (2 * pai) + 1; }

int f_d(int pai) { return (2 * pai) + 2; }

int pai(int filho) { return (filho - 1) / 2; }

int ultimo_pai(heap *h) { return (h->qtde / 2) - 1; }

void peneirar(heap *h, int pai) {
  int maior_filho, temp;
  int fe = f_e(pai);
  int fd = f_d(pai);

  if (fe < h->qtde && h->valores[fe] > h->valores[pai])
    maior_filho = fe;
  else
    maior_filho = pai;

  if (fd < h->qtde && h->valores[fd] > h->valores[maior_filho])
    maior_filho = fd;

  if (maior_filho != pai) {
    temp = h->valores[pai];
    h->valores[pai] = h->valores[maior_filho];
    h->valores[maior_filho] = temp;
    peneirar(h, maior_filho);
  }
}

void mostrar(heap *h) {
  for (int i = 0; i < h->qtde; i++) {
    printf("%d ", h->valores[i]);
  }
  printf("\n");
}

void construir(heap *h) {
  for (int i = ultimo_pai(h); i >= 0; i--) {
    peneirar(h, i);
  }
}

void inserir(heap *h, int valor) {
  h->valores[h->qtde] = valor;
  h->qtde++;

  int filho = h->qtde - 1;
  int pai_index = pai(filho);

  while (filho > 0 && h->valores[filho] > h->valores[pai_index]) {
    int temp = h->valores[filho];
    h->valores[filho] = h->valores[pai_index];
    h->valores[pai_index] = temp;

    filho = pai_index;
    pai_index = pai(filho);
  }
}

void remover(heap *h) {
  h->valores[0] = h->valores[h->qtde - 1];
  h->qtde--;

  peneirar(h, 0);
}

int main(void) {
  heap *h = malloc(sizeof(heap));
  int valor;
  h->qtde = 0;
  for (int i = 0; i < LEN; i++) {
    scanf("%d", &valor);
    inserir(h, valor);
    mostrar(h);
  }
  for (int i = 0; i < LEN; i++) {
    remover(h);
    mostrar(h);
  }

  return 0;
}
