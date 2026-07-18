#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo.h"
#include "heap.h"
#include <limits.h> 


int calcular_ruta_dijkstra(Grafo* grafo, int origen, int destino);

#endif