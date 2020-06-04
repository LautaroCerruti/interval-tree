#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct _QNode {
  void *data;
  struct _QNode *prev;
  struct _QNode *next;
};

Queue queue_create() {
  return NULL;
}

void *queue_pop(Queue *list) {
  void *data = NULL;
  if (*list && list) {
    data = (*list)->data;
    if ((*list)->next == *list){
      free(*list);
      *list = NULL;
    } else {
      Queue aux = *list;
      aux->prev->next = aux->next;
      aux->next->prev = aux->prev;
      *list = aux->next;
      free(aux);
    }
  }
  return data;
}

Queue queue_push(Queue list, void *data) {
  QNode *node = malloc(sizeof(QNode));
  node->data = data;
  if (!list) {
    node->prev = node;
    node->next = node;
    return node;
  }
  list->prev->next = node;
  node->prev = list->prev;
  list->prev = node;
  node->next = list; 
  return list;
}
