#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Arista {
    int destino;           
    int peso;              
    struct Arista* sig;    
} Arista;


typedef struct Vertice {
    Arista* cabeza;        
} Vertice;


typedef struct Grafo {
    int num_nodos;         
    Vertice* arreglo;      
} Grafo;

Grafo* crear_grafo(int num_nodos);
void agregar_arista(Grafo* grafo, int origen, int destino, int peso);
void liberar_grafo(Grafo* grafo);
void imprimir_grafo(Grafo* grafo);

#endif