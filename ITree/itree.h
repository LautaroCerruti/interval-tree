#ifndef __ITREE_H__
#define __ITREE_H__

#include <stddef.h>
#include <stdio.h>

typedef struct _INodo INodo;

typedef INodo *ITree;

ITree itree_crear();

INodo *itree_nuevo_nodo(double extremoIzq, double extremoDer);

void itree_destruir(ITree arbol);

int intervalo_valido(double extremoIzq, double extremoDer);

int itree_balance(ITree arbol);

ITree rotacion_izquierda(ITree arbol);

ITree rotacion_derecha(ITree arbol);

int itree_altura(ITree arbol);

ITree itree_balancear(ITree arbol);

ITree itree_insertar(ITree arbol, double extremoIzq, double extremoDer);

INodo *itree_obtener_menor(ITree arbol);

ITree itree_eliminar(ITree arbol, double extremoIzq, double extremoDer);

INodo *itree_intersecar(ITree arbol, double extremoIzq, double extremoDer);

void itree_recorrer_dfs(ITree arbol);

void itree_recorrer_bfs(ITree arbol);

#endif /* __GLIST_H__ */