#ifndef __ITREE_H__
#define __ITREE_H__

#include "../Intervalo/intervalo.h"
#include "../Queue/queue.h"
#include <stddef.h>
#include <stdio.h>
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

typedef struct _INodo INodo;

typedef INodo *ITree;

typedef void (*FuncionIntervaloVoid) (Intervalo *intervalo);

ITree itree_crear();

void itree_destruir(ITree arbol, FuncionIntervaloVoid funcion);

int itree_altura(ITree arbol);

ITree itree_insertar(ITree arbol, Intervalo *intervalo);

ITree itree_eliminar(ITree arbol, Intervalo *intervalo);

INodo *itree_intersecar(ITree arbol, Intervalo *intervalo);

void itree_recorrer_dfs(ITree arbol, FuncionIntervaloVoid funcion);

void itree_recorrer_bfs(ITree arbol, FuncionIntervaloVoid funcion);

void itree_imprimir_intervalo(ITree arbol, FuncionIntervaloVoid funcion);

#endif /* __ITREE_H__ */