#ifndef __INTERVALO_H__
#define __INTERVALO_H__

#include <stddef.h>
#include <stdio.h>

typedef struct _Intervalo Intervalo;

Intervalo *intervalo_crear(double extremoIzq, double extremoDer);

double intervalo_extremo_izq(Intervalo *intervalo);

double intervalo_extremo_der(Intervalo *intervalo);

int intervalo_valido(Intervalo *intervalo);

int intervalo_interseca(Intervalo *intervalo1, Intervalo *intervalo2);

#endif /* __ITREE_H__ */