#include "itree.h"
#include <stdio.h>
#include <stdlib.h>

struct _INodo {
    Intervalo intervalo;
    double maxExtremoDer;
    int altura;
    struct _INodo *izq;
    struct _INodo *der;
};

ITree itree_crear() {
    return NULL;
}

INodo *itree_nuevo_nodo(Intervalo intervalo) {
    INodo *nodo = malloc(sizeof(INodo));
    nodo->intervalo.extremoIzq = intervalo.extremoIzq;
    nodo->intervalo.extremoDer = intervalo.extremoDer;
    nodo->maxExtremoDer = intervalo.extremoDer;
    nodo->altura = 0;
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

int intervalo_valido(Intervalo intervalo) {
    return intervalo.extremoIzq <= intervalo.extremoDer;
}

ITree rotacion_izquierda(ITree arbol) {
    ITree aux = arbol->der;
    arbol->der = arbol->der->izq;
    aux->izq = arbol;
    arbol->altura = 1 + MAX(itree_altura(arbol->izq), itree_altura(arbol->der));
    aux->altura = 1 + MAX(itree_altura(aux->izq), itree_altura(aux->der));
    return aux;
}

ITree rotacion_derecha(ITree arbol) {
    ITree aux = arbol->izq;
    arbol->izq = arbol->izq->der;
    aux->der = arbol;
    arbol->altura = 1 + MAX(itree_altura(arbol->izq), itree_altura(arbol->der));
    aux->altura = 1 + MAX(itree_altura(aux->izq), itree_altura(aux->der));
    return aux;
}

int itree_altura(ITree arbol) {
    if (!arbol)
        return -1;
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

ITree itree_insertar(ITree arbol, Intervalo intervalo) {
    if (!intervalo_valido(intervalo)) {
        printf("Intervalo invalido\n");
        return arbol;
    }
    if (arbol) {
        if (intervalo.extremoIzq < arbol->intervalo.extremoIzq || 
            (intervalo.extremoIzq == arbol->intervalo.extremoIzq && 
            intervalo.extremoDer < arbol->intervalo.extremoDer)) {
            arbol->izq = itree_insertar(arbol->izq, intervalo);
            arbol->maxExtremoDer = arbol->izq->maxExtremoDer > arbol->maxExtremoDer ? 
                arbol->izq->maxExtremoDer : 
                arbol->maxExtremoDer;
        } else if (intervalo.extremoIzq != arbol->intervalo.extremoIzq ||
            intervalo.extremoDer != arbol->intervalo.extremoDer) {
            arbol->der = itree_insertar(arbol->der, intervalo);
            arbol->maxExtremoDer = arbol->der->maxExtremoDer > arbol->maxExtremoDer ? 
                arbol->der->maxExtremoDer : 
                arbol->maxExtremoDer;
        }
        arbol->altura =  1 + MAX(itree_altura(arbol->izq), itree_altura(arbol->der));
        return itree_balancear(arbol);
    }
    return itree_nuevo_nodo(intervalo);
}

INodo *itree_obtener_menor(ITree arbol) {
    if (!arbol->izq)
        return arbol;
    return itree_obtener_menor(arbol->izq);
}

ITree itree_eliminar(ITree arbol, Intervalo intervalo) {
    if (!intervalo_valido(intervalo)) {
        printf("Intervalo invalido\n");
        return arbol;
    }
    if (!arbol)
        return arbol;
    if (intervalo.extremoIzq == arbol->intervalo.extremoIzq && 
        intervalo.extremoDer == arbol->intervalo.extremoDer) {
        if (!arbol->izq || !arbol->der) {
            ITree aux = arbol->izq ? arbol->izq : arbol->der;
            free(arbol);
            arbol = aux;
        } else {
            INodo *nodo = itree_obtener_menor(arbol->der);
            arbol->intervalo = nodo->intervalo;
            arbol->der = itree_eliminar(arbol->der, nodo->intervalo);
        }
    } else if (intervalo.extremoIzq > arbol->intervalo.extremoIzq) {
        arbol->der = itree_eliminar(arbol->der, intervalo);
    } else {
        arbol->izq = itree_eliminar(arbol->izq, intervalo);
    }
    arbol->altura =  1 + MAX(itree_altura(arbol->izq), itree_altura(arbol->der));
    return itree_balancear(arbol);
}

void itree_recorrer_dfs(ITree arbol) {
    if (arbol) {
        itree_recorrer_dfs(arbol->izq);
        printf("%f, %f, %d, %f\n", arbol->intervalo.extremoIzq, arbol->intervalo.extremoDer, itree_altura(arbol), arbol->maxExtremoDer);
        itree_recorrer_dfs(arbol->der);
    }
}