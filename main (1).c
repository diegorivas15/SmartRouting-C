#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "dijkstra.h"
#include "historial.h"


void imprimir_mapa_caracas(Grafo* grafo, const char* zonas[]) {
    printf("\n=============================================\n");
    printf("   MAPA VIAL DE CARACAS (Estructura Grafo)   \n");
    printf("=============================================\n");
    for (int i = 0; i < grafo->num_nodos; i++) {
        printf("Desde: %s\n", zonas[i]);
        Arista* temp = grafo->arreglo[i].cabeza;
        
        if (temp == NULL) {
            printf("  -> Sin salidas directas.\n");
        }
        
        while (temp != NULL) {
            printf("  --> [Destino: %-18s | Tiempo: %2d min]\n", zonas[temp->destino], temp->peso);
            temp = temp->sig;
        }
        printf("---------------------------------------------\n");
    }
}

int main() {
    printf("==================================================\n");
    printf("   GPS CARACAS METROPOLITANA - SMARTROUTING   \n");
    printf("==================================================\n");

    int num_intersecciones = 15;
    Grafo* mi_mapa = crear_grafo(num_intersecciones);
    Historial* mi_historial = crear_historial(5); 

    
    const char* zonas[] = {
        "Plaza Venezuela",    
        "Chacao",             
        "Altamira",           
        "Las Mercedes",       
        "Bello Monte",        
        "Sabana Grande",      
        "El Rosal",           
        "Los Palos Grandes",  
        "La Castellana",      
        "Chuao",              
        "San Bernardino",     
        "La Candelaria",      
        "El Cafetal",         
        "Macaracuay",         
        "Petare"              
    };

    
    
    
    agregar_arista(mi_mapa, 0, 5, 3);   
    agregar_arista(mi_mapa, 0, 4, 6);   
    agregar_arista(mi_mapa, 0, 10, 8);  

    
    agregar_arista(mi_mapa, 1, 2, 3);   
    agregar_arista(mi_mapa, 1, 6, 2);   
    agregar_arista(mi_mapa, 1, 8, 2);   

    
    agregar_arista(mi_mapa, 2, 7, 2);   
    agregar_arista(mi_mapa, 2, 8, 2);   
    agregar_arista(mi_mapa, 2, 3, 12); 

    
    agregar_arista(mi_mapa, 3, 4, 5);   
    agregar_arista(mi_mapa, 3, 9, 4);   
    agregar_arista(mi_mapa, 3, 0, 10);  

    
    agregar_arista(mi_mapa, 4, 0, 5);   
    agregar_arista(mi_mapa, 4, 6, 4);   

    
    agregar_arista(mi_mapa, 5, 1, 4);   
    agregar_arista(mi_mapa, 5, 0, 3);   

    
    agregar_arista(mi_mapa, 6, 3, 3);   
    agregar_arista(mi_mapa, 6, 1, 2);   

    
    agregar_arista(mi_mapa, 7, 14, 15); 
    agregar_arista(mi_mapa, 7, 13, 10); 

    
    agregar_arista(mi_mapa, 8, 2, 2);   
    agregar_arista(mi_mapa, 8, 1, 2);   

    
    agregar_arista(mi_mapa, 9, 12, 8);  
    agregar_arista(mi_mapa, 9, 3, 4);   

    
    agregar_arista(mi_mapa, 10, 11, 4); 
    agregar_arista(mi_mapa, 10, 0, 8);  

    
    agregar_arista(mi_mapa, 11, 10, 4); 
    agregar_arista(mi_mapa, 11, 0, 10); 

    
    agregar_arista(mi_mapa, 12, 13, 7); 
    agregar_arista(mi_mapa, 12, 9, 8);  

    
    agregar_arista(mi_mapa, 13, 14, 6); 
    agregar_arista(mi_mapa, 13, 12, 7); 

    
    agregar_arista(mi_mapa, 14, 7, 15); 
    agregar_arista(mi_mapa, 14, 13, 6); 

    
    imprimir_mapa_caracas(mi_mapa, zonas);

    int opcion;
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Buscar ruta mas rapida (GPS)\n");
        printf("2. Ver ranking de rutas buscadas (Historial)\n");
        printf("3. Salir del programa\n");
        printf("Selecciona una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Error: Entrada invalida. Saliendo...\n");
            break;
        }

        switch (opcion) {
            case 1: {
                int origen, destino;
                printf("\n--- DIRECTORIO DE ZONAS DE CARACAS ---\n");
                for(int i = 0; i < num_intersecciones; i++) {
                    printf("[%2d] %s\n", i, zonas[i]);
                }
                printf("--------------------------------------\n");
                
                printf("Ingresa el numero de tu ORIGEN: ");
                scanf("%d", &origen);
                printf("Ingresa el numero de tu DESTINO: ");
                scanf("%d", &destino);

                if (origen >= 0 && origen < num_intersecciones && destino >= 0 && destino < num_intersecciones) {
                    printf("\n[GPS] Buscando la mejor ruta desde %s hasta %s...\n", zonas[origen], zonas[destino]);
                    int costo = calcular_ruta_dijkstra(mi_mapa, origen, destino);
                    
                    if(costo != -1) {
                        agregar_registro(mi_historial, origen, destino, costo);
                    }
                } else {
                    printf("\n[Error] Seleccion fuera de rango. Debe ser entre 0 y %d.\n", num_intersecciones - 1);
                }
                break;
            }
            case 2:
                ordenar_historial_heapsort(mi_historial);
                imprimir_historial(mi_historial);
                break;
            
            case 3:
                printf("\nApagando sistema GPS Caracas Metropolitana...\n");
                break;
            
            default:
                printf("\n[Error] Opcion no valida. Intenta de nuevo.\n");
        }
    } while (opcion != 3);

    
    liberar_historial(mi_historial);
    liberar_grafo(mi_mapa);
    printf("Memoria RAM liberada correctamente. ¡Buen viaje!\n");

    return 0;
}
