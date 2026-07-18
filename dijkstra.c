#include "dijkstra.h"

int calcular_ruta_dijkstra(Grafo* grafo, int origen, int destino) {
    int V = grafo->num_nodos;
    

    int* dist = (int*)malloc(V * sizeof(int));      
    int* padre = (int*)malloc(V * sizeof(int));    
    int* en_heap = (int*)malloc(V * sizeof(int));   
    

    MinHeap* minHeap = crear_min_heap(V);
    

    for (int v = 0; v < V; ++v) {
        padre[v] = -1; 
        dist[v] = INT_MAX;
        en_heap[v] = 1;
        

        minHeap->arreglo[v] = (NodoHeap*)malloc(sizeof(NodoHeap));
        minHeap->arreglo[v]->vertice = v;
        minHeap->arreglo[v]->distancia = INT_MAX;
        minHeap->posiciones[v] = v;
    }
    

    minHeap->arreglo[origen]->distancia = 0;
    dist[origen] = 0;
    disminuir_clave(minHeap, origen, dist[origen]);
    minHeap->tamano = V;
    

    while (!esta_vacio(minHeap)) {
    
        NodoHeap* min_nodo = extraer_minimo(minHeap);
        int u = min_nodo->vertice;
        en_heap[u] = 0;
        

        if (u == destino) {
            free(min_nodo);
            break;
        }
        

        Arista* calle = grafo->arreglo[u].cabeza;
        while (calle != NULL) {
            int v = calle->destino;
            

            if (en_heap[v] && dist[u] != INT_MAX && calle->peso + dist[u] < dist[v]) {
                dist[v] = dist[u] + calle->peso;
                padre[v] = u; 
                disminuir_clave(minHeap, v, dist[v]); 
            }
            calle = calle->sig;
        }
        free(min_nodo); 
    }
    

    if (dist[destino] == INT_MAX) {
        printf("\n[Alerta] No existe una ruta posible entre la interseccion %d y la %d.\n", origen, destino);
    } else {
        printf("\n--- RESULTADO DE LA BUSQUEDA ---\n");
        printf("Ruta mas rapida de %d a %d.\n", origen, destino);
        printf("Costo total (Tiempo/Distancia): %d\n", dist[destino]);
        

        printf("Camino a seguir: ");
        int actual = destino;
        int camino[100]; 
        int pasos = 0;
        
        while (actual != -1) {
            camino[pasos++] = actual;
            actual = padre[actual];
        }
        

        for (int i = pasos - 1; i >= 0; i--) {
            printf("%d ", camino[i]);
            if (i > 0) printf("-> ");
        }
        printf("\n--------------------------------\n");
    }
    


    if (dist[destino] == INT_MAX) {
        printf("\n[Alerta] No existe una ruta posible...\n");
    } else {
        
    }
    



    int costo_final = (dist[destino] == INT_MAX) ? -1 : dist[destino];
    

    free(dist);
    free(padre);
    free(en_heap);
    liberar_heap(minHeap);
    

    return costo_final;
}