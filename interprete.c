#include "./ITree/itree.h"
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

    while(strcmp(fgets(buffer, sizeof(buffer), stdin), "salir\0")){
        if(sscanf(buffer, "%c [%lf, %lf]", &operacion, &fn, &sn) == 3){
            switch (operacion)
            {
            case 'i':
                intervalo = intervalo_crear(fn, sn);
                arbol = itree_insertar(arbol, intervalo);
                break;
            case 'e':
                intervalo = intervalo_crear(fn, sn);
                arbol = itree_eliminar(arbol, intervalo);
                free(intervalo);
                break;
            case '?':
                intervalo = intervalo_crear(fn, sn);
                nodo = itree_intersecar(arbol, intervalo);
                if (nodo) {
                    printf("Si ");
                    itree_imprimir_intervalo(arbol, intervalo_imprimir);
                } else {
                    printf("No");
                }
                nodo = NULL;
                break;
            default:
                printf("Comando Incorrecto");
                break;
            }
            printf("\n\n");
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
