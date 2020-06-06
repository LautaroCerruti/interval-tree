#include "./ITree/itree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINEA 660

char *leer_cadena(char *string) {
    char c, *aux = string;
    while ((c = getchar()) != '\n') {
        if (c != '\r') {
            *string = c;
            ++string;
        }
    }
    *string = '\0';
    return aux;
}

char obtener_operacion(char *string, Intervalo **intervalo) {
    char operacion = string[0], *resto;
    double numero1, numero2;
    if (strlen(string) >= 8 && string[1] == ' ' && string[2] == '[') {
        string += 3;
        if (isdigit(*string) != 0 || *string == '-') {
            numero1 = strtod(string, &resto);
        }
        if (*resto == ',' && *(resto + 1) == ' ' && (isdigit(*(resto + 2)) || *(resto + 2) == '-')) {
            string = resto + 2;
            numero2 = strtod(string, &resto);
        }
        if (*resto == ']' && *(resto + 1) == '\0') {
            *intervalo = intervalo_crear(numero1, numero2);
            return operacion;
        }
    }
    return '\0';
}

int main() {
    char buffer[MAX_LINEA];
    buffer[0] = '\0';
    ITree arbol = itree_crear(), nodo;
    Intervalo *intervalo;

    printf("i: insertar\ne: eliminar\n?: intersecar\ndfs, bfs: mostrar arbol\nsalir: finalizar programa\n\n");

    while(strcmp(leer_cadena(buffer), "salir\0")) {
        if (!strcmp(buffer, "dfs\0")) {
            itree_recorrer_dfs(arbol, intervalo_imprimir);
            printf("\n");
        } else if (!strcmp(buffer, "bfs\0")) {
            itree_recorrer_bfs(arbol, intervalo_imprimir);
            printf("\n");
        } else {
            switch (obtener_operacion(buffer, &intervalo)) {
                case 'i':
                    arbol = itree_insertar(arbol, intervalo);
                    break;
                case 'e':
                    arbol = itree_eliminar(arbol, intervalo);
                    intervalo_destruir(intervalo);
                    break;
                case '?':
                    nodo = itree_intersecar(arbol, intervalo);
                    if (nodo) {
                        printf("  Si,");
                        itree_imprimir_intervalo(nodo, intervalo_imprimir);
                    } else
                        printf("  No");
                    printf("\n");
                    intervalo_destruir(intervalo);
                    nodo = NULL;
                    break;
                default:
                    intervalo_destruir(intervalo);
                    printf("  Comando Incorrecto\n");
                    break;
            }
        }
    }
    itree_destruir(arbol, intervalo_destruir);
    return 0;
}
