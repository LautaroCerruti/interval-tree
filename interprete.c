#include ".\ITree\itree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINEA 250

int main() {
    char buffer[MAX_LINEA], operacion;
    double fn, sn;
    buffer[0] = '\0';
    ITree arbol = itree_crear(), nodo;
    Intervalo *intervalo;

    while(strcmp(gets(buffer), "salir\0")){
        if(sscanf(buffer, "%c [%lf, %lf]", &operacion, &fn, &sn) == 3){
            switch (operacion)
            {
            case 'i':
                intervalo = intervalo_crear(fn, sn);
                arbol = itree_insertar(arbol, intervalo);
                printf("\n\n");
                break;
            case 'e':
                intervalo = intervalo_crear(fn, sn);
                arbol = itree_eliminar(arbol, intervalo);
                free(intervalo);
                printf("\n\n");
                break;
            case '?':
                intervalo = intervalo_crear(fn, sn);
                nodo = itree_intersecar(arbol, intervalo);
                printf(nodo ? "Si\n\n" : "No\n\n");
                nodo = NULL;
                break;
            default:
                printf("Comando Incorrecto\n\n");
                break;
            }
        } else if (!strcmp(buffer, "bfs\0")) {
            itree_recorrer_bfs(arbol, intervalo_imprimir);
            printf("\n\n");
        } else if (!strcmp(buffer, "dfs\0")) {
            itree_recorrer_dfs(arbol, intervalo_imprimir);
            printf("\n\n");
        } else {
            printf("Comando Incorrecto\n\n");
        }
    }
    itree_destruir(arbol, intervalo_destruir);
    return 0;
}
