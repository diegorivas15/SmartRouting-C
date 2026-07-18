#include "historial.h"


Historial* crear_historial(int capacidad_inicial) {
    Historial* hist = (Historial*)malloc(sizeof(Historial));
    hist->registros = (RegistroViaje*)malloc(capacidad_inicial * sizeof(RegistroViaje));
    hist->cantidad = 0;
    hist->capacidad = capacidad_inicial;
    return hist;
}


void agregar_registro(Historial* hist, int origen, int destino, int costo) {
    
    if (hist->cantidad == hist->capacidad) {
        hist->capacidad *= 2;
        hist->registros = (RegistroViaje*)realloc(hist->registros, hist->capacidad * sizeof(RegistroViaje));
    }
    hist->registros[hist->cantidad].origen = origen;
    hist->registros[hist->cantidad].destino = destino;
    hist->registros[hist->cantidad].costo = costo;
    hist->cantidad++;
}


void max_heapify(RegistroViaje* arr, int n, int i) {
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    
    if (izq < n && arr[izq].costo > arr[mayor].costo)
        mayor = izq;

    if (der < n && arr[der].costo > arr[mayor].costo)
        mayor = der;

    
    if (mayor != i) {
        RegistroViaje temp = arr[i];
        arr[i] = arr[mayor];
        arr[mayor] = temp;
        max_heapify(arr, n, mayor);
    }
}


void ordenar_historial_heapsort(Historial* hist) {
    int n = hist->cantidad;
    
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heapify(hist->registros, n, i);
    }
    
    
    for (int i = n - 1; i > 0; i--) {
        RegistroViaje temp = hist->registros[0];
        hist->registros[0] = hist->registros[i];
        hist->registros[i] = temp;
        
        
        max_heapify(hist->registros, i, 0);
    }
}


void imprimir_historial(Historial* hist) {
    printf("\n--- HISTORIAL DE RUTAS (Ordenado por Costo - Heap Sort) ---\n");
    if (hist->cantidad == 0) {
        printf("No hay viajes registrados aun.\n");
    }
    for (int i = 0; i < hist->cantidad; i++) {
        printf("%d. Ruta: %d -> %d | Costo total: %d\n", 
               i + 1, 
               hist->registros[i].origen, 
               hist->registros[i].destino, 
               hist->registros[i].costo);
    }
    printf("-----------------------------------------------------------\n");
}


void liberar_historial(Historial* hist) {
    if (hist) {
        free(hist->registros);
        free(hist);
    }
}