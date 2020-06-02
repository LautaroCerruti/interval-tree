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

int intervalo_valido(double extremoIzq, double extremoDer) {
    return extremoIzq <= extremoDer;
}

ITree rotacion_izquierda(ITree arbol) {
    ITree aux = arbol->der;
    arbol->der = arbol->der->izq;
    aux->izq = arbol;
    return aux;
}

ITree rotacion_derecha(ITree arbol) {
    ITree aux = arbol->izq;
    arbol->izq = arbol->izq->der;
    aux->der = arbol;
    return aux;
}

int itree_altura(ITree arbol) {
    if (!arbol)
        return 0;
    return arbol->altura;
}

int itree_balance(ITree arbol) {
    if (!arbol)
        return 0;
    return itree_altura(arbol->izq) - itree_altura(arbol->der);
}

ITree itree_balancear(ITree arbol) {
    int balance = itree_balance(arbol);
    if (balance > 1) {
        if (itree_balance(arbol->izq) < 0)
            arbol->izq = rotacion_izquierda(arbol->izq);
        return rotacion_derecha(arbol);
    }
    if (balance < -1) {
        if (itree_balance(arbol->der) > 0)
            arbol->der = rotacion_derecha(arbol->der);
        return rotacion_izquierda(arbol);
    }
    return arbol;
}

ITree itree_insertar(ITree arbol, double extremoIzq, double extremoDer) {
    if (!intervalo_valido(extremoIzq, extremoDer)) {
        printf("Intervalo invalido");
        return arbol;
    }
    if (arbol) {
        if (extremoIzq > arbol->extremoIzq) {
            arbol->der = itree_insertar(arbol->der, extremoIzq, extremoDer);
            arbol->maxExtremoDer = arbol->der->maxExtremoDer > arbol->maxExtremoDer ? 
                arbol->der->maxExtremoDer : 
                arbol->maxExtremoDer;
        } else if (!(extremoIzq == arbol->extremoIzq && extremoDer == arbol->extremoDer)) {
            arbol->izq = itree_insertar(arbol->izq, extremoIzq, extremoDer);
            arbol->maxExtremoDer = arbol->izq->maxExtremoDer > arbol->maxExtremoDer ? 
                arbol->izq->maxExtremoDer : 
                arbol->maxExtremoDer;
        }
        arbol->altura =  1 + max(itree_altura(arbol->izq), itree_altura(arbol->der));
        return itree_balancear(arbol);
    }
    return itree_nuevo_nodo(extremoIzq, extremoDer);
}

INodo *itree_obtener_menor(ITree arbol) {
    if (!arbol->izq)
        return arbol;
    return itree_obtener_menor(arbol->izq);
}

ITree itree_eliminar(ITree arbol, double extremoIzq, double extremoDer) {
    if (!intervalo_valido(extremoIzq, extremoDer)) {
        printf("Intervalo invalido");
        return arbol;
    }
    if (!arbol)
        return arbol;
    if (extremoIzq == arbol->extremoIzq && extremoDer == arbol->extremoDer) {
        if (!arbol->izq || !arbol->der) {
            ITree aux = arbol->izq ? arbol->izq : arbol->der;
            free(arbol);
            arbol = aux;
        } else {
            INodo *nodo = itree_obtener_menor(arbol->der);
            arbol->extremoIzq = nodo->extremoIzq;
            arbol->extremoDer = nodo->extremoDer;
            arbol->der = itree_eliminar(arbol->der, nodo->extremoIzq, nodo->extremoDer);
        }
    } else if (extremoIzq > arbol->extremoIzq) {
        arbol->der = itree_eliminar(arbol->der, extremoIzq, extremoDer);
    } else {
        arbol->izq = itree_eliminar(arbol->izq, extremoIzq, extremoDer);
    }
    arbol->altura =  1 + max(itree_altura(arbol->izq), itree_altura(arbol->der));
    return itree_balancear(arbol);
}