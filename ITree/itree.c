#include "itree.h"
#include <stdio.h>
#include <stdlib.h>

struct _INodo {
    Intervalo *intervalo;
    double maxExtremoDer;
    int altura;
    struct _INodo *izq;
    struct _INodo *der;
};

ITree itree_crear() {
    return NULL;
}

INodo *itree_nuevo_nodo(Intervalo *intervalo) {
    INodo *nodo = (INodo *) malloc(sizeof(INodo));
    nodo->intervalo = intervalo;
    nodo->maxExtremoDer = intervalo_extremo_der(intervalo);
    nodo->altura = 0;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void itree_destruir(ITree arbol, FuncionIntervaloVoid funcion) {
    if (arbol) {
        itree_destruir(arbol->izq, funcion);
        itree_destruir(arbol->der, funcion);
        funcion(arbol->intervalo);
        free(arbol);
    }
}

double itree_calcular_max_extremo_der(ITree arbol) {
    return MAX(intervalo_extremo_der(arbol->intervalo), 
        MAX(arbol->izq ? arbol->izq->maxExtremoDer : intervalo_extremo_der(arbol->intervalo), 
            arbol->der ? arbol->der->maxExtremoDer : intervalo_extremo_der(arbol->intervalo)));
}

ITree rotacion_izquierda(ITree arbol) {
    ITree aux = arbol->der;
    arbol->der = arbol->der->izq;
    aux->izq = arbol;
    arbol->altura = 1 + MAX(itree_altura(arbol->izq), itree_altura(arbol->der));
    aux->altura = 1 + MAX(itree_altura(aux->izq), itree_altura(aux->der));
    arbol->maxExtremoDer = itree_calcular_max_extremo_der(arbol);
    aux->maxExtremoDer = itree_calcular_max_extremo_der(aux);
    return aux;
}

ITree rotacion_derecha(ITree arbol) {
    ITree aux = arbol->izq;
    arbol->izq = arbol->izq->der;
    aux->der = arbol;
    arbol->altura = 1 + MAX(itree_altura(arbol->izq), itree_altura(arbol->der));
    aux->altura = 1 + MAX(itree_altura(aux->izq), itree_altura(aux->der));
    arbol->maxExtremoDer = itree_calcular_max_extremo_der(arbol);
    aux->maxExtremoDer = itree_calcular_max_extremo_der(aux);
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

ITree itree_insertar(ITree arbol, Intervalo *intervalo) {
    if (!intervalo_valido(intervalo)) {
        printf("Intervalo invalido\n");
        return arbol;
    }
    if (arbol) {
        if (intervalo_extremo_izq(intervalo) < intervalo_extremo_izq(arbol->intervalo) || 
            (intervalo_extremo_izq(intervalo) == intervalo_extremo_izq(arbol->intervalo) && 
            intervalo_extremo_der(intervalo) < intervalo_extremo_der(arbol->intervalo))) {
            arbol->izq = itree_insertar(arbol->izq, intervalo);
            arbol->maxExtremoDer = arbol->izq->maxExtremoDer > arbol->maxExtremoDer ? 
                arbol->izq->maxExtremoDer : 
                arbol->maxExtremoDer;
        } else if (intervalo_extremo_izq(intervalo) != intervalo_extremo_izq(arbol->intervalo) ||
            intervalo_extremo_der(intervalo) != intervalo_extremo_der(arbol->intervalo)) {
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

ITree itree_eliminar(ITree arbol, Intervalo *intervalo) {
    if (!intervalo_valido(intervalo)) {
        printf("Intervalo invalido\n");
        return arbol;
    }
    if (!arbol){
        printf("Intervalo no encontrado\n");
        return arbol;
    }
    if (intervalo_extremo_izq(intervalo) == intervalo_extremo_izq(arbol->intervalo) && 
        intervalo_extremo_der(intervalo) == intervalo_extremo_der(arbol->intervalo)) {
        if (!arbol->izq || !arbol->der) {
            ITree aux = arbol->izq ? arbol->izq : arbol->der;
            free(arbol->intervalo);
            free(arbol);
            arbol = aux;
        } else {
            INodo *nodo = itree_obtener_menor(arbol->der);
            free(arbol->intervalo);
            arbol->intervalo = intervalo_crear(intervalo_extremo_izq(nodo->intervalo), intervalo_extremo_der(nodo->intervalo));
            arbol->der = itree_eliminar(arbol->der, nodo->intervalo);
        }
    } else if (intervalo_extremo_izq(intervalo) > intervalo_extremo_izq(arbol->intervalo)) {
        arbol->der = itree_eliminar(arbol->der, intervalo);
    } else {
        arbol->izq = itree_eliminar(arbol->izq, intervalo);
    }
    if (arbol) {
        arbol->altura =  1 + MAX(itree_altura(arbol->izq), itree_altura(arbol->der));
        arbol->maxExtremoDer = itree_calcular_max_extremo_der(arbol);
    }
    return itree_balancear(arbol);
}

ITree itree_intersecar(ITree arbol, Intervalo *intervalo) {
    if (!arbol || arbol->maxExtremoDer < intervalo_extremo_izq(intervalo))
        return NULL;
    if (intervalo_interseca(arbol->intervalo, intervalo))
        return arbol;
    if (intervalo_extremo_izq(arbol->intervalo) > intervalo_extremo_der(intervalo)
        || arbol->izq->maxExtremoDer >= intervalo_extremo_izq(intervalo))
        return itree_intersecar(arbol->izq, intervalo);
    return itree_intersecar(arbol->der, intervalo);
}

void itree_recorrer_dfs(ITree arbol, FuncionIntervaloVoid funcion) {
    if (arbol) {
        itree_recorrer_dfs(arbol->izq, funcion);
        funcion(arbol->intervalo);
        itree_recorrer_dfs(arbol->der, funcion);
    }
}

void itree_recorrer_bfs(ITree arbol, FuncionIntervaloVoid funcion) {
    if (arbol) {
        Queue queue = queue_create();
        ITree aux;
        queue = queue_push(queue, arbol);
        while (queue)
        {
            aux = (ITree) queue_pop(&queue);
            funcion(aux->intervalo);
            queue = aux->izq ? queue_push(queue, aux->izq) : queue;
            queue = aux->der ? queue_push(queue, aux->der) : queue;
        }
    }
}
