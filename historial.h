#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <stdio.h>
#include <stdlib.h>


typedef struct RegistroViaje {
    int origen;
    int destino;
    int costo;
} RegistroViaje;


typedef struct Historial {
    RegistroViaje* registros; 
    int cantidad;             
    int capacidad;            
} Historial;

Historial* crear_historial(int capacidad_inicial);
void agregar_registro(Historial* hist, int origen, int destino, int costo);
void max_heapify(RegistroViaje* arr, int n, int i);
void ordenar_historial_heapsort(Historial* hist);
void imprimir_historial(Historial* hist);
void liberar_historial(Historial* hist);

#endif