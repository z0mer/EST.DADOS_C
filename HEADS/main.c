#include <stdio.h>
#include <stdlib.h>

#define LEN 10

// Definição da estrutura do heap
typedef struct {
  int valores[LEN]; // Array para armazenar os valores do heap
  int qtde;         // Quantidade de elementos no heap
} heap;

// Função para calcular o índice do filho esquerdo de um nó
int f_e(int pai) { return (2 * pai) + 1; }

// Função para calcular o índice do filho direito de um nó
int f_d(int pai) { return (2 * pai) + 2; }

// Função para calcular o índice do pai de um nó
int pai(int filho) { return (filho - 1) / 2; }

// Função para calcular o índice do último pai no heap
int ultimo_pai(heap *h) { return (h->qtde / 2) - 1; }

// Função para ajustar a estrutura do heap a partir de um nó, garantindo a propriedade do heap
void peneirar(heap *h, int pai) {
  int maior_filho, temp;
  int fe = f_e(pai); // Índice do filho esquerdo
  int fd = f_d(pai); // Índice do filho direito

  // Verifica se o filho esquerdo existe e se é maior que o pai
  if (fe < h->qtde && h->valores[fe] > h->valores[pai])
    maior_filho = fe;
  else
    maior_filho = pai;

  // Verifica se o filho direito existe e se é maior que o maior filho até agora
  if (fd < h->qtde && h->valores[fd] > h->valores[maior_filho])
    maior_filho = fd;

  // Se o maior filho for diferente do pai, troca os valores e continua ajustando
  if (maior_filho != pai) {
    temp = h->valores[pai];
    h->valores[pai] = h->valores[maior_filho];
    h->valores[maior_filho] = temp;
    peneirar(h, maior_filho); // Chama recursivamente peneirar no maior filho
  }
}

// Função para mostrar os elementos do heap
void mostrar(heap *h) {
  for (int i = 0; i < h->qtde; i++) {
    printf("%d ", h->valores[i]);
  }
  printf("\n");
}

// Função para construir o heap a partir de um array de valores
void construir(heap *h) {
  // Começa do último pai e vai até a raiz
  for (int i = ultimo_pai(h); i >= 0; i--) {
    peneirar(h, i); // Chama peneirar para garantir a propriedade do heap
  }
}

// Função para inserir um valor no heap
void inserir(heap *h, int valor) {
  h->valores[h->qtde] = valor; // Insere o valor na última posição disponível
  h-> qtde++;                   // Incrementa a quantidade de elementos no heap
  
  int filho = h->qtde - 1;      // Índice do novo elemento
  int pai_index = pai(filho);    // Índice do pai do novo elemento
  
  // Enquanto o novo valor for maior que seu pai, troca-os e continua subindo na árvore
  while (filho > 0 && h->valores[filho] > h->valores[pai_index]){
    int temp = h->valores[filho];
    h->valores[filho] = h->valores[pai_index];
    h->valores[pai_index] = temp;
    
    filho = pai_index;
    pai_index = pai(filho);
  }
}

// Função para remover o elemento máximo (raiz) do heap
void remover(heap *h) {
  h->valores[0] = h->valores[h->qtde - 1]; // Substitui a raiz pelo último elemento
  h->qtde--;                               // Decrementa a quantidade de elementos
  
  peneirar(h, 0);                          // Chama peneirar para reorganizar o heap
}

// Função principal
int main(void) {
  heap *h = malloc(sizeof(heap)); // Aloca memória para o heap
  int valor;
  h->qtde = 0;                     // Inicializa a quantidade de elementos como zero
  
  // Loop para inserir valores no heap
  for (int i = 0; i < LEN; i++) {
    scanf("%d", &valor);
    inserir(h, valor); // Insere o valor no heap
    mostrar(h);        // Mostra o estado atual do heap
  }
  
  // Loop para remover valores do heap
  for (int i = 0; i < LEN; i++) {
    remover(h); // Remove o elemento máximo do heap
    mostrar(h); // Mostra o estado atual do heap
  }

  return 0; // Retorna 0 para indicar sucesso
}
