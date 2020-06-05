#include "intervalo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Intervalo{
    double extremoIzq;
    double extremoDer;
};

Intervalo *intervalo_crear(double extremoIzq, double extremoDer) {
    Intervalo *intervalo = (Intervalo *) malloc(sizeof(Intervalo));
    intervalo->extremoIzq = extremoIzq;
    intervalo->extremoDer = extremoDer;
    return intervalo;
}

void intervalo_destruir(Intervalo *intervalo) {
    free(intervalo);
}

double intervalo_extremo_izq(Intervalo *intervalo) {
    return intervalo->extremoIzq;
}

double intervalo_extremo_der(Intervalo *intervalo) {
    return intervalo->extremoDer;
}

int intervalo_valido(Intervalo *intervalo) {
    return intervalo->extremoIzq <= intervalo->extremoDer;
}

int intervalo_interseca(Intervalo *intervalo1, Intervalo *intervalo2) {
    return intervalo1->extremoDer >= intervalo2->extremoIzq && intervalo1->extremoIzq <= intervalo2->extremoDer;
}

void intervalo_imprimir(Intervalo *intervalo) {
    if (intervalo)
        printf("  [%g, %g]", intervalo_extremo_izq(intervalo), intervalo_extremo_der(intervalo));
}