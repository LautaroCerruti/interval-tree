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

/*
    itree_crear: -> ITree
    Retorna un ITree vacio.
*/
ITree itree_crear();

/*
    itree_destruir: ITree FuncionIntervaloVoid
    Dado un arbol y una funcion para destruir intervalos, borra el arbol
    liberando toda la memoria.
*/
void itree_destruir(ITree arbol, FuncionIntervaloVoid funcion);

/*
    itree_altura: ITree -> int
    Dado un arbol, devuelve su altura.
*/
int itree_altura(ITree arbol);

/*
    itree_insertar: ITree Intervalo* -> ITree
    Dado un ITree y un puntero a un intervalo, lo inserta en al arbol, en
    caso que sea valido y que no se encuentre ya en el arbol.
    Retorna la raiz del arbol.
*/
ITree itree_insertar(ITree arbol, Intervalo *intervalo);

/*
    itree_eliminar: ITree Intervalo* -> ITree
    Dado un ITree y un puntero a un intervalo, si el mismo se encuentra en
    el arbol, lo elimina del mismo liberando su memoria.
    Retorna la raiz del arbol.
*/
ITree itree_eliminar(ITree arbol, Intervalo *intervalo);

/*
    itree_intersecar: ITree Intervalo* -> INodo*
    Dado un ITree y un puntero a un intervalo, si el mismo se interseca
    con algun nodo del arbol, devuelve el primer nodo con el que lo hizo,
    en caso contrario NULL.
*/
INodo *itree_intersecar(ITree arbol, Intervalo *intervalo);

/*
    itree_recorrer_dfs: ITree FuncionIntervaloVoid
    Recorre el arbol con un algoritmo DFS de forma inorder, aplicando la 
    funcion dada como parametro a los intervalos almacenados en los nodos.
*/
void itree_recorrer_dfs(ITree arbol, FuncionIntervaloVoid funcion);

/*
    itree_recorrer_bfs: ITree FuncionIntervaloVoid
    Recorre el arbol con un algoritmo BFS, aplicando la funcion dada como
    parametro a los intervalos almacenados en los nodos.
*/
void itree_recorrer_bfs(ITree arbol, FuncionIntervaloVoid funcion);

/*
    itree_aplicar_a_intervalo: INodo* FuncionIntervaloVoid
    Dado un nodo y una funcion, aplica la funcion en el intervalo 
    almacenado en el nodo.
*/
void itree_aplicar_a_intervalo(INodo *arbol, FuncionIntervaloVoid funcion);

#endif /* __ITREE_H__ */