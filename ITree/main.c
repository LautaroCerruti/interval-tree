#include "itree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINEA 250

int main() {
    char buffer[MAX_LINEA], operacion;
    double fn, sn;
    buffer[0] = '\0';
    ITree arbol = itree_crear();
    Intervalo intervalo;

    while(strcmp(gets(buffer), "salir\0")){
        if(sscanf(buffer, "%c [%lf,%lf]", &operacion, &fn, &sn) == 3){
            switch (operacion)
            {
            case 'i':
                intervalo.extremoIzq = fn;
                intervalo.extremoDer = sn;
                arbol = itree_insertar(arbol, intervalo);
                break;
            case 'e':
                intervalo.extremoIzq = fn;
                intervalo.extremoDer = sn;
                arbol = itree_eliminar(arbol, intervalo);
                break;
            case '?':
                printf("Not Implemented yet %c, %lf, %lf\n", operacion, fn, sn);
                break;
            default:
                printf("Comando Incorrecto\n");
                break;
            }
        } else if (!strcmp(buffer, "bfs\0")) {
            printf("BFS\n");
        } else if (!strcmp(buffer, "dfs\0")) {
            itree_recorrer_dfs(arbol);
        } else {
            printf("Comando Incorrecto\n");
        }
    }
    return 0;
}
