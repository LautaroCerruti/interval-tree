#include "itree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    ITree arbol = itree_crear();
    Intervalo intervalo1 = {10, 100};
    Intervalo intervalo2 = {5, 100};
    Intervalo intervalo3 = {15, 100};
    Intervalo intervalo4 = {3, 100};
    Intervalo intervalo5 = {6, 100};
    Intervalo intervalo6 = {14, 100};
    Intervalo intervalo7 = {16, 100};
    Intervalo intervalo8 = {2, 100};
    Intervalo intervalo9 = {4, 100};
    Intervalo intervalo10 = {1, 100};
    Intervalo intervalo11 = {0.5, 100};
    Intervalo intervalo12 = {7, 100};
    arbol = itree_insertar(arbol, intervalo1);
    arbol = itree_insertar(arbol, intervalo2);
    arbol = itree_insertar(arbol, intervalo3);
    arbol = itree_insertar(arbol, intervalo4);
    arbol = itree_insertar(arbol, intervalo5);
    arbol = itree_insertar(arbol, intervalo6);
    arbol = itree_insertar(arbol, intervalo7);
    arbol = itree_insertar(arbol, intervalo8);
    arbol = itree_insertar(arbol, intervalo9);
    arbol = itree_insertar(arbol, intervalo10);
    arbol = itree_insertar(arbol, intervalo11);
    arbol = itree_insertar(arbol, intervalo12);
    itree_recorrer_dfs(arbol);
    return 0;
}
//        [5-7]

//               [5-7]
// [2-4]
//        [3-5]

//               [5-7]
//        [3-5]
// [2-4]

//        [3-5]
// [2-4]         [5-7]

//               [3-5]
// [2-4]                         [5-7]
//                          [4-8]

//               [3-5]
// [2-4]                         [5-7]
//                       [4-8]
//                   [4-6]

//               [3-5]
// [2-4]                         [4-8]
//                           [4-6]   [5-7]

//               [3-5]
//                               [4-8]
//                           [4-6]   [5-7]

//               [4-8]
// [3-5]                         [5-7]
//     [4-6]








