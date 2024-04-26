#include <stdio.h>
#include <stdlib.h>


typedef struct Celula{
	int valor;
	struct Celula *proximo;
}Celula;

typedef struct Lista{
	int qtde;
	Celula *primeiro;
}Lista;

void inserir(Lista *l, int valor){
	Celula *novo = malloc(sizeof(Celula));
	novo->valor = valor;
	novo->proximo = NULL;

	if(l->primeiro == NULL){
		l->primeiro = novo;
	}else{
		Celula *atual = l->primeiro;
		Celula *anterior = NULL;
		while(atual != NULL && atual->valor <= valor){
			anterior = atual;
			atual = atual->proximo;
		}
		if(anterior == NULL){
			novo->proximo = l->primeiro;
			l->primeiro = novo;
		}else{
			if(atual == NULL){
				anterior->proximo = novo;
			}else{
				novo->proximo = atual;
				anterior->proximo = novo;
			}
		}
	}
	l->qtde++;
}

void remover(Lista *l, int valor) {
	Celula *atual = l->primeiro;
	Celula *anterior = NULL;

	while (atual != NULL && atual->valor != valor) {
		anterior = atual;
		atual = atual->proximo;
	}
	if (anterior == NULL) {
		l->primeiro = atual->proximo;
	} else {
		anterior->proximo = atual->proximo;
	}
	l->qtde--;
	free(atual);
}

Lista *inicializa_lista(){
	Lista *l = malloc(sizeof(Lista));
	l->primeiro = NULL;
	l->qtde = 0;
	return l;
}

void imprimir(Lista *l){
	Celula *atual = l->primeiro;
	while(atual != NULL){
		printf("%d ", atual->valor);
		atual = atual->proximo;
	}
	printf("\n");
}

int main(void) {
	Lista *l = inicializa_lista();
	int valores[] = {2, 1, 0, 9, 3, 8, 5, 7, 6, 4};
	for(int i = 0; i < 10; i++){
		inserir(l, valores[i]);
		imprimir(l);
	}
	for(int i = 0; i < 10; i++){
		remover(l, valores[i]);
		imprimir(l);
	}
	
	return 0;
}
