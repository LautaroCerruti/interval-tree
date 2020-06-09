#include "intervalo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Intervalo {
  double extremoIzq;
  double extremoDer;
};

Intervalo *intervalo_crear(double extremoIzq, double extremoDer) {
  // Pedimos memoria
  Intervalo *intervalo = (Intervalo *) malloc(sizeof(Intervalo));
  intervalo->extremoIzq = extremoIzq;   // Asignamos los valores
  intervalo->extremoDer = extremoDer;
  return intervalo;             // Retornamos el puntero al intervalo
}

void intervalo_destruir(Intervalo * intervalo) {
  free(intervalo);
}

double intervalo_extremo_izq(Intervalo * intervalo) {
  return intervalo->extremoIzq;
}

double intervalo_extremo_der(Intervalo * intervalo) {
  return intervalo->extremoDer;
}

int intervalo_valido(Intervalo * intervalo) {
  // Si el extremo izquierdo del intervalo es mayor al extremo derecho
  if (intervalo->extremoIzq > intervalo->extremoDer) {
    printf("  Intervalo invalido\n");
    intervalo_destruir(intervalo); // Eliminamos el intervalo ya que es invalido
    return 0;
  }
  return 1;
}

int intervalo_interseca(Intervalo * intervalo1, Intervalo * intervalo2) {
  // Un intervalo interseca con otro si el extremo derecho del primer
  // intervalo es mayor o igual al extremo izquierdo del segundo y el extremo
  // izquierdo del primero es menor o igual que el del segundo
  return intervalo1->extremoDer >= intervalo2->extremoIzq &&
      intervalo1->extremoIzq <= intervalo2->extremoDer;
}

void intervalo_imprimir(Intervalo * intervalo) {
  if (intervalo)
    printf("  [%g, %g]", intervalo_extremo_izq(intervalo),
           intervalo_extremo_der(intervalo));
}
