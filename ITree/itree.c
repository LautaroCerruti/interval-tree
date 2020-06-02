#include "itree.h"
#include <stdio.h>
#include <stdlib.h>

struct _INodo {
  double extremoIzq;
  double extremoDer;
  double maxExtremoDer;
  int altura;
  struct _INodo *izq;
  struct _INodo *der;
};

ITree itree_crear() {
    return NULL;
}

INodo *itree_nuevo_nodo(double extremoIzq, double extremoDer) {
    INodo *nodo = malloc(sizeof(INodo*));
    nodo->extremoIzq = extremoIzq;
    nodo->extremoDer = extremoDer;
    nodo->maxExtremoDer = extremoDer;
    nodo->altura = 1;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void itree_destruir(ITree arbol) {
    if (arbol) {
        itree_destruir(arbol->izq);
        itree_destruir(arbol->der);
        free(arbol);
    }
}

ITree itree_insertar(ITree arbol, double extremoIzq, double extremoDer) {
    if (arbol) {
        if (extremoIzq > arbol->extremoIzq) {
            arbol->der = itree_insertar(arbol->der, extremoIzq, extremoDer);
            arbol->maxExtremoDer = arbol->der->maxExtremoDer > arbol->maxExtremoDer ? 
                arbol->der->maxExtremoDer : 
                arbol->maxExtremoDer;
        } else if (extremoIzq < arbol->extremoIzq) {
            arbol->izq = itree_insertar(arbol->izq, extremoIzq, extremoDer);
            arbol->maxExtremoDer = arbol->izq->maxExtremoDer > arbol->maxExtremoDer ? 
                arbol->izq->maxExtremoDer : 
                arbol->maxExtremoDer;
        }
        //arbol->altura = arbol->izq->altura > arbol->der->altura ? arbol->izq->altura++ : arbol->der->altura++;
    }
    return itree_nuevo_nodo(extremoIzq, extremoDer);
}