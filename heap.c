#include "heap.h"


MinHeap* crear_min_heap(int capacidad) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) exit(1);
    
    minHeap->posiciones = (int*)malloc(capacidad * sizeof(int));
    minHeap->arreglo = (NodoHeap**)malloc(capacidad * sizeof(NodoHeap*));
    if (!minHeap->posiciones || !minHeap->arreglo) exit(1);
    
    minHeap->tamano = 0;
    minHeap->capacidad = capacidad;
    
    return minHeap;
}


void intercambiar_nodos(NodoHeap** a, NodoHeap** b) {
    NodoHeap* temp = *a;
    *a = *b;
    *b = temp;
}


void min_heapify(MinHeap* minHeap, int idx) {
    int mas_pequeno = idx;
    int izq = 2 * idx + 1;
    int der = 2 * idx + 2;
    
    if (izq < minHeap->tamano && minHeap->arreglo[izq]->distancia < minHeap->arreglo[mas_pequeno]->distancia)
        mas_pequeno = izq;
        
    if (der < minHeap->tamano && minHeap->arreglo[der]->distancia < minHeap->arreglo[mas_pequeno]->distancia)
        mas_pequeno = der;
        
    if (mas_pequeno != idx) {
        
        NodoHeap* nodo_mas_pequeno = minHeap->arreglo[mas_pequeno];
        NodoHeap* nodo_idx = minHeap->arreglo[idx];
        
        
        minHeap->posiciones[nodo_mas_pequeno->vertice] = idx;
        minHeap->posiciones[nodo_idx->vertice] = mas_pequeno;
        
        
        intercambiar_nodos(&minHeap->arreglo[mas_pequeno], &minHeap->arreglo[idx]);
        
        
        min_heapify(minHeap, mas_pequeno);
    }
}


int esta_vacio(MinHeap* minHeap) {
    return minHeap->tamano == 0;
}


NodoHeap* extraer_minimo(MinHeap* minHeap) {
    if (esta_vacio(minHeap)) return NULL;
    
    NodoHeap* raiz = minHeap->arreglo[0];
    NodoHeap* ultimo_nodo = minHeap->arreglo[minHeap->tamano - 1];
    
    minHeap->arreglo[0] = ultimo_nodo;
    
    
    minHeap->posiciones[raiz->vertice] = minHeap->tamano - 1;
    minHeap->posiciones[ultimo_nodo->vertice] = 0;
    
    
    minHeap->arreglo[minHeap->tamano - 1] = NULL; 
    
    
    minHeap->tamano--;
    min_heapify(minHeap, 0);
    
    return raiz;
}


void disminuir_clave(MinHeap* minHeap, int vertice, int distancia) {
    
    int i = minHeap->posiciones[vertice];
    
    minHeap->arreglo[i]->distancia = distancia;
    
    
    while (i && minHeap->arreglo[i]->distancia < minHeap->arreglo[(i - 1) / 2]->distancia) {
        
        NodoHeap* actual = minHeap->arreglo[i];
        NodoHeap* padre = minHeap->arreglo[(i - 1) / 2];
        
        
        minHeap->posiciones[actual->vertice] = (i - 1) / 2;
        minHeap->posiciones[padre->vertice] = i;
        
        intercambiar_nodos(&minHeap->arreglo[i], &minHeap->arreglo[(i - 1) / 2]);
        
        
        i = (i - 1) / 2;
    }
}


void liberar_heap(MinHeap* minHeap) {
    if (minHeap) {
        for (int i = 0; i < minHeap->capacidad; i++) {
            if (minHeap->arreglo[i] != NULL) {
                free(minHeap->arreglo[i]);
            }
        }
        free(minHeap->arreglo);
        free(minHeap->posiciones);
        free(minHeap);
    }
}