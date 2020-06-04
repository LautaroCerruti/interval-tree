#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>
#include <time.h>
#include <stdio.h>

typedef struct _QNode QNode;

typedef QNode *Queue;

typedef void (*FuncionDestruir) (void *dato);

/*
    Crea una cola vacia.
*/
Queue queue_create();

/*
    Toma una cola, elimina el primer nodo y devuelve su dato en caso de que la cola no este vacia.
*/
void *queue_pop(Queue *queue);

/*
    Toma una cola y un dato e inserta dicho dato en al cola.
*/
Queue queue_push(Queue queue, void *dato);

/*
    Toma una cola y una funcion, libera la memoria de los nodos, y la de sus datos con la funcion mencionada previamente.
*/
void queue_destruir(Queue queue, FuncionDestruir funcion);

#endif /* __QUEUE_H__ */