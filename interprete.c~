#include "./ITree/itree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINEA 660

/*
    leer_cadena: char* -> char*
    Toma lo escrito por el teclado, y lo retorna reemplazando el salto de linea
    por un '\0'.
*/
char *leer_cadena(char *string) {
    char c, *aux = string;
    // Mientras que el caracter leido sea distinto a '\n'
    while ((c = getchar()) != '\n') {
        if (c != '\r') { // Si el caracter leido es distinto a '\r'
            *string = c; // Almacenamos el caracter en string
            ++string; // Movemos la posicion a la que apunta string
        }
    }
    *string = '\0'; // Colocamos un terminador al final
    return aux; // Devolvemos un puntero al comienzo de string
}

/*
    obtener_operacion: char* Intervalo** -> char
    Dado un string y un puntero a un puntero intervalo, si el string cumple el
    formato de una operacion valida devolvemos la operacion a realizar y
    almacenamos el intervalo con los datos tomados.
*/
char obtener_operacion(char *string, Intervalo **intervalo) {
    char operacion = string[0], *resto;
    double numero1, numero2;
    // Si cumple el tamaño minimo de caracteres y los primeros 3 caracteres
    // cumplen un cierto formato
    if (strlen(string) >= 8 && string[1] == ' ' && string[2] == '[') {
        string += 3; // Movemos la posicion a la que apunta string
        // Si el caracter al que apunta string es un numero o un '-'
        if (isdigit(*string) != 0 || *string == '-') {
            // Almacena en numero1 el double que aparece en string y en resto
            // se almacena la direccion de memoria del primer el caracter que no
            // se pudo almacenar en numero1
            numero1 = strtod(string, &resto);
        }
        // Si los primeron 3 caracteres desde donde apunta resto cumple cierto
        // formato
        if (*resto == ',' && *(resto + 1) == ' ' && (isdigit(*(resto + 2)) || *(resto + 2) == '-')) {
            string = resto + 2; // Movemos la posicion a la que apunta string
            // Almacena en numero2 el double que aparece en string y en resto
            // se almacena la direccion de memoria del primer el caracter que no
            // se pudo almacenar en numero2
            numero2 = strtod(string, &resto);
        }
        // Si el penultimo y el ultimo caracter coinciden a '\0' y ']' 
        // respectivamente
        if (*resto == ']' && *(resto + 1) == '\0') {
            // Guarda en intervalo el intervalo creado por numero1 y numero2
            *intervalo = intervalo_crear(numero1, numero2);
            return operacion; // Retorna la operacion
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
                        itree_aplicar_a_intervalo(nodo, intervalo_imprimir);
                    } else
                        printf("  No");
                    printf("\n");
                    intervalo_destruir(intervalo);
                    nodo = NULL;
                    break;
                case '\0':
                    printf("  Comando Incorrecto\n");
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
