#include <stdio.h>
#define LEN 10

typedef struct {
  int values[LEN];
  int qtd;
} List;

int is_full(List *list) { return list->qtd == LEN; }

int is_empty(List *list) { return list->qtd == 0; }

int get_idx(List *list, int value) {
  int idx = 0;
  while (idx < list->qtd && value > list->values[idx])
    idx++;
  return idx;
}

void move_right(List *list, int idx) {
  for (int i = list->qtd; i > idx; i--)
    list->values[i] = list->values[i - 1];
}

void move_left(List *list, int idx) {
  for (int i = idx; i < list->qtd - 1; i++)
    list->values[i] = list->values[i + 1];
}

int _remove(List *list, int value) {
  int idx = get_idx(list, value);
  if (idx == -1)
    return 0; 

  move_left(list, idx);
  list->qtd--;

  return 1;
}

int insert(List *list, int value) {
  if (is_full(list))
    return 0;
  if (is_empty(list)) {
    list->values[0] = value;
    list->qtd++;
  } else {
    int idx = get_idx(list, value);
    move_right(list, idx);
    list->values[idx] = value;
    list->qtd++;
  }
  return 1;
}

void show(List *list) {
  for (int i = 0; i < list->qtd; i++)
    printf("%d ", list->values[i]);
  printf("\n");
}

int main(void) {
  List l;
  l.qtd = 0;
  List *pl = &l;
  int values[] = {21, 14, 13, 10, 87, 35, 27, 56, 85, 29};
  for (int i = 0; i < LEN; i++) {
    insert(pl, values[i]);
    show(pl);
  }
  for (int i = 0; i < LEN; i++) {
    printf("O valor %d está na posição %d\n", values[i],
           get_idx(pl, values[i]));
  }
  for (int i = 0; i < LEN; i++) {
    _remove(pl, values[i]);
    show(pl);
  }

  return 0;
}
