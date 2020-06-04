#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>
#include <time.h>
#include <stdio.h>

typedef struct _QNode QNode;

typedef QNode *Queue;

typedef void (*FuncionDestruir) (void *dato);

/*

*/
Queue queue_create();

/*

*/
void *queue_pop(Queue *queue);

/*

*/
Queue queue_push(Queue queue, void *dato);

/*

*/
void queue_destruir(Queue queue, FuncionDestruir funcion);

#endif /* __QUEUE_H__ */