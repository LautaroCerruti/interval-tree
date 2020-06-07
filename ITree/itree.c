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

INodo *itree_nuevo_nodo(Intervalo *intervalo) {
    // Pedimos la memoria para un nodo
    INodo *nodo = (INodo *) malloc(sizeof(INodo));
    nodo->intervalo = intervalo; // Almacenamos el intervalo
    // Al crear un nodo, el maximo extremo derecho es su extremo derecho,
    // su altura es 0 y no tiene hijos
    nodo->maxExtremoDer = intervalo_extremo_der(intervalo); 
    nodo->altura = 0;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

/*
    itree_calcular_max_extremo_der: ITree -> double
    Dado un ITree, calcula el maximo extremo derecho de la raiz, haciendo un
    maximo entre su extremo derecho, y un maximo entre el maximo extremo
    derecho de su hijo izquierdo si existe y el maximo extremo derecho de su
    hijo derecho si existe.
*/
double itree_calcular_max_extremo_der(ITree arbol) {
    return MAX(intervalo_extremo_der(arbol->intervalo), 
        MAX(arbol->izq ? arbol->izq->maxExtremoDer : 
                intervalo_extremo_der(arbol->intervalo), 
            arbol->der ? arbol->der->maxExtremoDer : 
                intervalo_extremo_der(arbol->intervalo)));
}

/*
    itree_calcular_altura: ITree -> int
    Dado un ITree, calcula su altura de la raiz, sumandole 1 a la altura del
    hijo con mayor altura.
*/
int itree_calcular_altura(ITree arbol) {
    return (1 + MAX(itree_altura(arbol->izq), itree_altura(arbol->der)));
}

/*
    itree_actualizar_datos: ITree*
    Dado un puntero a un arbol, actualiza su altura y su maximo extremo derecho
*/
void itree_actualizar_datos(ITree *arbol) {
    if(arbol){ // Si el arbol no es vacio
        (*arbol)->altura = itree_calcular_altura(*arbol); // Actualizmos la altura
        // Actualizmos el maximo extremo derecho
        (*arbol)->maxExtremoDer = itree_calcular_max_extremo_der(*arbol); 
    }
}

/*
    rotacion_izquierda: ITree -> ITree
    Dado un ITree, lo modificamos de manera tal que su hijo derecho sea la 
    raiz, la raiz original sea el hijo izquierdo de la nueva raiz y que el 
    anterior hijo izquierdo de la nueva raiz sea el hijo derecho de la vieja.
    Retornamos la nueva raiz.
*/
ITree rotacion_izquierda(ITree arbol) {
    if (!arbol) // Si el arbol es vacio
        return arbol;
    ITree aux = arbol->der; // Creamos la nueva raiz
    // Cambiamos las referencias del arbol
    arbol->der = arbol->der->izq;
    aux->izq = arbol;
    // Actualizamos los datos
    itree_actualizar_datos(&arbol);
    itree_actualizar_datos(&aux);
    return aux;
}

/*
    rotacion_izquierda: ITree -> ITree
    Dado un ITree, lo modificamos de manera tal que su hijo izquierdo sea la 
    raiz, la raiz original sea el hijo derecho de la nueva raiz y que el 
    anterior hijo derecho de la nueva raiz sea el hijo izquierdo de la vieja.
    Retornamos la nueva raiz.
*/
ITree rotacion_derecha(ITree arbol) {
    if (!arbol) // Si el arbol es vacio
        return arbol;
    ITree aux = arbol->izq; // Creamos la nueva raiz
    // Cambiamos las referencias del arbol
    arbol->izq = arbol->izq->der;
    aux->der = arbol;
    // Actualizamos los datos
    itree_actualizar_datos(&arbol);
    itree_actualizar_datos(&aux);
    return aux;
}

/*
    itree_balance: ITree -> int
    Dado un ITree devuelve su balance
*/
int itree_balance(ITree arbol) {
    if (!arbol) // Si el arbol esta vacio
        return 0; // Su balance es 0
    // Retornamos la altura del subarbol izquierdo menos 
    // la altura del subarbol derecho
    return itree_altura(arbol->izq) - itree_altura(arbol->der);
}

/*
    itree_balancear: ITree -> ITree
    Dado un arbol, en caso de estar desbalanceado, lo balancea realizando las 
    rotaciones necesarias
*/
ITree itree_balancear(ITree arbol) {
    int balance = itree_balance(arbol); // Calcula el balance del arbol
    if (balance > 1) { // Si el balance es mayor a uno
        // Si el balance de su hijo izquierdo es menor a 0
        if (itree_balance(arbol->izq) < 0)
            // Hace una rotacion izquieda en el hijo izquierdo
            arbol->izq = rotacion_izquierda(arbol->izq);
        // Hace una rotacion derecha y retorna la nueva raiz
        return rotacion_derecha(arbol);
    }
    if (balance < -1) { // Si el balance es menor a uno
        // Si el balance de su hijo derecho es mayor a 0
        if (itree_balance(arbol->der) > 0) 
            // Hace una rotacion derecha en su hijo derecho
            arbol->der = rotacion_derecha(arbol->der);
        // Hace una rotacion izquierda y retorna la nueva raiz
        return rotacion_izquierda(arbol);
    }
    return arbol; // En caso de estar balanceado no cambia nada
}

/*
    itree_obtener_menor: ITree -> INodo*
    Dado un aborl, retorna el menor nodo del arbol
*/
INodo *itree_obtener_menor(ITree arbol) {
    if (!arbol || !arbol->izq)
        return arbol;
    return itree_obtener_menor(arbol->izq);
}

void itree_aplicar_a_intervalo(ITree arbol, FuncionIntervaloVoid funcion) {
    if (arbol) // Si el arbol no esta vacio
        // Aplica la funcion en el intervalo de la raiz
        funcion(arbol->intervalo);
}

ITree itree_crear() {
    return NULL; // Retorna un ITree vacio
}

void itree_destruir(ITree arbol, FuncionIntervaloVoid funcion) {
    if (arbol) { // Si existe el arbol
        // Ejecutamos itree_destruir en los 2 hijos del nodo
        itree_destruir(arbol->izq, funcion);
        itree_destruir(arbol->der, funcion);
        // Liberamos la memoria de su intervalo utilizando la funcion "funcion"
        funcion(arbol->intervalo);
        free(arbol); // Liberamos la memoria del nodo
    }
}

int itree_altura(ITree arbol) {
    if (!arbol) // Si el arbol esta vacio
        return -1; // Retornamos -1 para facilitar calculos
    return arbol->altura; // Retornamos su altura
}

ITree itree_insertar(ITree arbol, Intervalo *intervalo) {
    // Si el intervalo es invalido
    if (!intervalo_valido(intervalo))
        return arbol; // Devolvemos el mismo arbol
    if (arbol) { // Si el arbol no esta vacio
        // Si los extremos del intervalo coinciden con los del arbol
        if (intervalo_extremo_izq(intervalo) == intervalo_extremo_izq(arbol->intervalo) 
            && intervalo_extremo_der(intervalo) == intervalo_extremo_der(arbol->intervalo)) {
            printf("  El intervalo ya se encuentra en el arbol\n");
            intervalo_destruir(intervalo);
            return arbol; // Devolvemos el mismo arbol
        // Si el extremo izquierdo del intervalo es menor al extremo izquierdo
        // del intervalo del arbol o el extremo izquierdo del intervalo es 
        // igual al extremo izquiedo del intervalo del arbol y el extremo 
        // derecho del intervalo es menor al extremo derecho del intervalo del arbol
        } else if (intervalo_extremo_izq(intervalo) < intervalo_extremo_izq(arbol->intervalo) || 
            (intervalo_extremo_izq(intervalo) == intervalo_extremo_izq(arbol->intervalo) && 
            intervalo_extremo_der(intervalo) < intervalo_extremo_der(arbol->intervalo)))
            // Insertamos el intervalo en el subarbol izquierdo
            arbol->izq = itree_insertar(arbol->izq, intervalo);
        else
            // Insertamos el intervalo en el subarbol derecho
            arbol->der = itree_insertar(arbol->der, intervalo);
        itree_actualizar_datos(&arbol); // Acutualizamos los datos de la raiz
        return itree_balancear(arbol); // Retornamos el arbol balanceado
    }
    // Retornamos un nuevo nodo con el intervalo
    return itree_nuevo_nodo(intervalo);
}

// [4, 6] [2, 4] [4, 8] [5, 7]   

ITree itree_eliminar(ITree arbol, Intervalo *intervalo) {
    if (!intervalo_valido(intervalo)) // Si el intervalo es invalido
        return arbol;
    // Si el arbol es vacio o el maximo extremo derecho del arbol es menor al
    // extremo izquierdo del intervalo
    if (!arbol || arbol->maxExtremoDer < intervalo_extremo_izq(intervalo)) {
        printf("  Intervalo no encontrado\n");
        return arbol;
    }
    // Si los extremos del intervalo del arbol coinciden con el que queremos
    // eliminar
    if (intervalo_extremo_izq(intervalo) == intervalo_extremo_izq(arbol->intervalo) && 
        intervalo_extremo_der(intervalo) == intervalo_extremo_der(arbol->intervalo)) {
        if (!arbol->izq || !arbol->der) { // Si el arbol tiene a lo sumo un hijo
            // Guardamos el hijo izquierdo en aux en caso de que exista o el 
            // derecho en caso contrario
            ITree aux = arbol->izq ? arbol->izq : arbol->der;
            // Liberamos la memoria del intervalo
            intervalo_destruir(arbol->intervalo);
            // Liberamos la memoria del nodo
            free(arbol);
            // Igualamos el arbol al nuevo nodo
            arbol = aux;
        } else {
            // Obtenemos el menor nodo del subarbol derecho
            INodo *nodo = itree_obtener_menor(arbol->der);
            // Reemplazamos el intervalo del arbol por el del menor nodo 
            // del subarbol derecho
            intervalo_destruir(arbol->intervalo);
            arbol->intervalo = intervalo_crear(intervalo_extremo_izq(nodo->intervalo), intervalo_extremo_der(nodo->intervalo));
            // Eliminamos el menor nodo del subarbol derecho
            arbol->der = itree_eliminar(arbol->der, nodo->intervalo);
        }
    // Si el extremo izquierdo del intervalo es mayor al extremo izquierdo del
    // intervalo de la raiz o los extremos izquierdos son iguales y el  extremo
    // derecho del intervalo es mayor al extremo derecho del intervalo del arbol
    } else if (intervalo_extremo_izq(intervalo) > intervalo_extremo_izq(arbol->intervalo) ||
        (intervalo_extremo_izq(intervalo) == intervalo_extremo_izq(arbol->intervalo) &&
        intervalo_extremo_der(intervalo) > intervalo_extremo_der(arbol->intervalo)))
        // Ejecutamos la funcion eliminar en el subarbol derecho
        arbol->der = itree_eliminar(arbol->der, intervalo);
    else {
        // Ejecutamos la funcion eliminar en el subarbol derecho
        arbol->izq = itree_eliminar(arbol->izq, intervalo);
    }
    if (arbol) // Si el arbol no esta vacio
        itree_actualizar_datos(&arbol); // Actualizamos los datos del arbol
    return itree_balancear(arbol); // Retornamos el arbol balanceado
}

ITree itree_intersecar(ITree arbol, Intervalo *intervalo) {
    // Si el arbol esta vacio o el intervalo es invalido o si maximo extremo
    // derecho de la raiz del arbol es menor al extremo izquierdo del intervalo
    if (!arbol || !intervalo_valido(intervalo) || arbol->maxExtremoDer < intervalo_extremo_izq(intervalo))
        return NULL;
    // Si se intersecan los intervalos
    if (intervalo_interseca(arbol->intervalo, intervalo)) 
        return arbol; // Retornamos la raiz
    // Si el maximo extremo izquierdo del intervalo de la raiz es mayor al 
    // maximo extremo derecho del intervalo a comparar o el maximo extremo 
    // derecho del subarbol izquierdo de la raiz es mayor o igual al extremo 
    // izquiedo del intervalo a comparar
    if (intervalo_extremo_izq(arbol->intervalo) > intervalo_extremo_der(intervalo)
        || arbol->izq->maxExtremoDer >= intervalo_extremo_izq(intervalo))
        // Ejecutamos itree_intersecar en el subarbol izquierdo
        return itree_intersecar(arbol->izq, intervalo);
    // Ejecutamos itree_intersecar en el subarbol derecho
    return itree_intersecar(arbol->der, intervalo);
}

void itree_recorrer_dfs(ITree arbol, FuncionIntervaloVoid funcion) {
    if (arbol) { // Si el arbol no esta vacio
        // Aplica la funcion itree_recorrer_dfs en el hijo izquierdo
        itree_recorrer_dfs(arbol->izq, funcion);
        // Aplica la funcion en el intervalo de la raiz
        funcion(arbol->intervalo);
        // Aplica la funcion itree_recorrer_dfs en el hijo derecho
        itree_recorrer_dfs(arbol->der, funcion);
    }
}

void itree_recorrer_bfs(ITree arbol, FuncionIntervaloVoid funcion) {
    if (arbol) { // Si el arbol no esta vacio
        Queue queue = queue_create(); // Crea una Queue vacia
        ITree aux;
        queue = queue_push(queue, arbol); // Metemos la raiz en la cola
        while (queue) { // Mientras la cola no este vacia
            aux = (ITree) queue_pop(&queue); // Sacamos el primer nodo de la cola
            funcion(aux->intervalo); // Aplica la funcion en el intervalo de aux
            // Si aux tiene hijos, los mete en la cola
            queue = aux->izq ? queue_push(queue, aux->izq) : queue;
            queue = aux->der ? queue_push(queue, aux->der) : queue;
        }
    }
}