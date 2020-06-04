#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>
#include <time.h>
#include <stdio.h>

typedef struct _QNode QNode;

typedef QNode *Queue;

/*

*/
Queue queue_create();

/*

*/
void *queue_pop(Queue *list);

/*

*/
Queue queue_push(Queue list, void *data);

#endif /* __QUEUE_H__ */
