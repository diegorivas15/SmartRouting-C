#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>


typedef struct NodoHeap {
    int vertice;        
    int distancia;      
} NodoHeap;


typedef struct MinHeap {
    int tamano;         
    int capacidad;      
    int *posiciones;     
                        
    NodoHeap **arreglo; 
} MinHeap;


MinHeap* crear_min_heap(int capacidad);
void intercambiar_nodos(NodoHeap** a, NodoHeap** b);
void min_heapify(MinHeap* minHeap, int idx);
int esta_vacio(MinHeap* minHeap);
NodoHeap* extraer_minimo(MinHeap* minHeap);
void disminuir_clave(MinHeap* minHeap, int vertice, int distancia);
void liberar_heap(MinHeap* minHeap);

#endif