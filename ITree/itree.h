#ifndef __ITREE_H__
#define __ITREE_H__

#include <stddef.h>
#include <stdio.h>
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

struct _Intervalo{
    double extremoIzq;
    double extremoDer;
};

typedef struct _Intervalo Intervalo;

typedef struct _INodo INodo;

typedef INodo *ITree;

ITree itree_crear();

INodo *itree_nuevo_nodo(Intervalo intervalo);

void itree_destruir(ITree arbol);

int intervalo_valido(Intervalo intervalo);

int itree_balance(ITree arbol);

ITree rotacion_izquierda(ITree arbol);

ITree rotacion_derecha(ITree arbol);

int itree_altura(ITree arbol);

ITree itree_balancear(ITree arbol);

ITree itree_insertar(ITree arbol, Intervalo intervalo);

INodo *itree_obtener_menor(ITree arbol);

ITree itree_eliminar(ITree arbol, Intervalo intervalo);

INodo *itree_intersecar(ITree arbol, Intervalo intervalo);

void itree_recorrer_dfs(ITree arbol);

void itree_recorrer_bfs(ITree arbol);

#endif /* __ITREE_H__ */