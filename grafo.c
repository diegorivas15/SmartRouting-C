#include "grafo.h"


Grafo* crear_grafo(int num_nodos) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        printf("Error: No se pudo asignar memoria para el grafo.\n");
        exit(1);
    }
    
    grafo->num_nodos = num_nodos;
    
    
    grafo->arreglo = (Vertice*)malloc(num_nodos * sizeof(Vertice));
    if (grafo->arreglo == NULL) {
        printf("Error: No se pudo asignar memoria para los vértices.\n");
        free(grafo);
        exit(1);
    }
    
    
    for (int i = 0; i < num_nodos; i++) {
        grafo->arreglo[i].cabeza = NULL;
    }
    
    return grafo;
}


void agregar_arista(Grafo* grafo, int origen, int destino, int peso) {
    
    if (origen < 0 || origen >= grafo->num_nodos || destino < 0 || destino >= grafo->num_nodos) {
        printf("Error: Nodos fuera de rango.\n");
        return;
    }

    Arista* nueva_arista = (Arista*)malloc(sizeof(Arista));
    if (nueva_arista == NULL) {
        printf("Error: No se pudo asignar memoria para la arista.\n");
        exit(1);
    }
    
    nueva_arista->destino = destino;
    nueva_arista->peso = peso;
    

    nueva_arista->sig = grafo->arreglo[origen].cabeza;
    grafo->arreglo[origen].cabeza = nueva_arista;
}


void imprimir_grafo(Grafo* grafo) {
    printf("\n--- Mapa de Rutas (Grafo) ---\n");
    for (int i = 0; i < grafo->num_nodos; i++) {
        printf("Interseccion %d: ", i);
        Arista* temp = grafo->arreglo[i].cabeza;
        
        if (temp == NULL) {
            printf("Sin salidas.");
        }
        
        while (temp != NULL) {
            printf("-> [Destino: %d, Costo: %d] ", temp->destino, temp->peso);
            temp = temp->sig;
        }
        printf("\n");
    }
    printf("-----------------------------\n");
}


void liberar_grafo(Grafo* grafo) {
    if (grafo != NULL) {
        for (int i = 0; i < grafo->num_nodos; i++) {
            Arista* temp = grafo->arreglo[i].cabeza;
            while (temp != NULL) {
                Arista* a_liberar = temp;
                temp = temp->sig;
                free(a_liberar); 
            }
        }
        free(grafo->arreglo); 
        free(grafo);          
    }
}

