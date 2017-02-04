//  interfaz.c
//  Planificador de procesos
//
//  Created by Juan Ortiz & Andres Buelvas on 29/1/17.
//  Copyright © 2017 Juan Ortiz & Andres Buelvas. All rights reserved.
//

#include "interfaz.h"
#include "colasPrioridades.h"

// Metodo que imprime opciones en la terminal
void menu(EstrucSched* s, char* salida){
    
    int opcion=-1;
    long pid;
    Estado e;
    short prio;
    float time;
    char cmd [20];

    while (opcion!=0) {
        
        printf("\n----------------------------------\nPlanificador de Procesos A&J\n----------------------------------");
        
        printf("\nMenu:");
        printf("\n1.- Insertar proceso.");
        printf("\n2.- Eliminar proceso.");
        printf("\n3.- Iniciar proximo proceso.");
        printf("\n4.- Detener proceso en ejecucion.");
        printf("\n5.- Imprimir el contenido del planificador de Procesos.");
        printf("\n0.- Salir del programa.");
        printf("\n\nIntroduzca una opcion.\n>>> ");
        
        fflush(stdin);
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 0:
                printf("\n---> Gracias por usar el planificador de Procesos A&J <---\n");
                Salir(s, salida);
                LiberarMemoria (s);
                exit(0);
                
            case 1:
                printf("Introduzca el PID del proceso a insertar:\n>>> ");
                fflush(stdin);
                scanf("%ld", &pid);
                
                printf("\nIntroduzca el estado del proceso a insertar:\n>>> ");
                fflush(stdin);
                scanf(" %c", &e);
                
                printf("\nIntroduzca la prioridad del proceso a insertar:\n>>> ");
                fflush(stdin);
                scanf(" %hd", &prio);
                
                printf("\nIntroduzca el tiempo del proceso a insertar:\n>>> ");
                fflush(stdin);
                scanf(" %f", &time);
                
                printf("\nIntroduzca el comando del proceso a insertar:\n>>> ");
                fflush(stdin);
                scanf(" %s", cmd);
                
                Proceso* p = CrearProceso(pid, e, prio, time, cmd);
                InsertarProceso(s, p, p->prioridad);

                break;
                
            case 2:
                menuInterno(s, salida);
                break;
                
            case 3:
                if (ProxProceso(s))
                    printf("\n-----> Proximo proceso a ejecutar asignado.");
                else
                    printf("\nOperacion cancelada: no quedan procesos por ejecutar.");
                break;
                
            case 4:
                if (s->enEjecucion) {
                    DetenerEjecucion(s);
                    printf("\n-----> Proceso dentenido.");
                } else
                    printf ("\nOperacion cancelada: no hay procesos en ejecucion.");
                
                break;
                
            case 5:
                printf("\n----------------------------------");
                printf("\nProcesos del planificador actual: \n");
                Imprime(s);
                break;
                
            default:
                printf("\nNo ha marcado una opcion valida. Intente nuevamente.");
                break;
        }
    }
}

void menuInterno(EstrucSched* s, char* salida){
    
    int opcion;
    long pid;
    short prio;
    
    printf("\n1.- Eliminar proceso");
    printf("\n2.- Elminar ultimo proceso ejecutado");
    printf("\n0.- Regresar al menu principal");
    printf("\n\nIntroduzca una opcion\n>>> ");

    scanf("%d", &opcion);
    fflush(stdin);
    
    switch (opcion) {
            
        case 1:
            printf("Introduzca el PID del proceso a eliminar: \n>>> ");
            fflush(stdin);
            scanf("%ld", &pid);
            
            printf("Marque el numero correspondiente a la cola de prioridad del proceso a eliminar:\n\n0.- Cola 0. \n1.- Cola 1. \n2.- Cola 2. \n3.- Cola 3. \n4.- Cola 4. \n5.- Cola 5.\n>>> ");
            fflush(stdin);
            scanf("%hd", &prio);
            
            ElimProceso (s, pid, prio);
            s->enEjecucion = NULL;
            
            printf("\n-----> Eliminacion completada.\n");
            
            menu(s, salida);
            break;
            
        case 2:
            if (s->enEjecucion) {
                ElimProcesoE(s);
                printf("\n-----> Eliminación completada.");
            }
            else
                printf("\nOperacion cancelada: no hay procesos en ejecucion.");
            
            menu(s, salida);
            break;
            
        case 0:
            printf("\nDevuelta al menu principal.");
            menu(s, salida);
            break;
            
        default:
            printf("\nNo ha introducido una opcion valida. Vuelva a intentarlo.");
            menuInterno(s, salida);
            break;
    }
}

void Imprime(EstrucSched *s){
    Proceso* p;
    s->q0->cabeza = s->q0->primero;
    s->q1->cabeza = s->q1->primero;
    s->q2->cabeza = s->q2->primero;
    s->q3->cabeza = s->q3->primero;
    s->q4->cabeza = s->q4->primero;
    s->q5->cabeza = s->q5->primero;
    
    while (s->q0->cabeza) {
        p = s->q0->cabeza->proceso;
        ImprimeProceso(p);
        s->q0->cabeza = s->q0->cabeza->siguiente;
    }
    
    while (s->q1->cabeza) {
        p = s->q1->cabeza->proceso;
        ImprimeProceso(p);
        s->q1->cabeza = s->q1->cabeza->siguiente;
    }
    
    while (s->q2->cabeza) {
        p = s->q2->cabeza->proceso;
        ImprimeProceso(p);
        s->q2->cabeza = s->q2->cabeza->siguiente;
    }
    
    while (s->q3->cabeza) {
        p = s->q3->cabeza->proceso;
        ImprimeProceso(p);
        s->q3->cabeza = s->q3->cabeza->siguiente;
    }
    
    while (s->q4->cabeza) {
        p = s->q4->cabeza->proceso;
        ImprimeProceso(p);
        s->q4->cabeza = s->q4->cabeza->siguiente;
    }
    
    while (s->q5->cabeza) {
        p = s->q5->cabeza->proceso;
        ImprimeProceso(p);
        s->q5->cabeza = s->q5->cabeza->siguiente;
    }
}

void ImprimeProceso (Proceso* p) {
    printf("\n%ld %c %hd %.2f %s", p->PID, p->estado, p->prioridad, p->time, p->comando);
}

void Salir (EstrucSched *s, char* salida){
    Proceso* p;
    s->q0->cabeza = s->q0->primero;
    s->q1->cabeza = s->q1->primero;
    s->q2->cabeza = s->q2->primero;
    s->q3->cabeza = s->q3->primero;
    s->q4->cabeza = s->q4->primero;
    s->q5->cabeza = s->q5->primero;
    
    FILE* fp = fopen (salida, "w");
    
    while (s->q0->cabeza) {
        p = s->q0->cabeza->proceso;
        escribeSalida(p, fp);
        s->q0->cabeza = s->q0->cabeza->siguiente;
    }
    
    while (s->q1->cabeza) {
        p = s->q1->cabeza->proceso;
        escribeSalida(p, fp);
        s->q1->cabeza = s->q1->cabeza->siguiente;
    }
    
    while (s->q2->cabeza) {
        p = s->q2->cabeza->proceso;
        escribeSalida(p, fp);
        s->q2->cabeza = s->q2->cabeza->siguiente;
    }
    
    while (s->q3->cabeza) {
        p = s->q3->cabeza->proceso;
        escribeSalida(p, fp);
        s->q3->cabeza = s->q3->cabeza->siguiente;
    }
    
    while (s->q4->cabeza) {
        p = s->q4->cabeza->proceso;
        escribeSalida(p, fp);
        s->q4->cabeza = s->q4->cabeza->siguiente;
    }
    
    while (s->q5->cabeza) {
        p = s->q5->cabeza->proceso;
        escribeSalida(p, fp);
        s->q5->cabeza = s->q5->cabeza->siguiente;
    }
    fclose(fp);
}

void escribeSalida (Proceso *p, FILE* fp){
    fprintf(fp, "%ld %c %hd %.2f %s\n", p->PID, p->estado, p->prioridad, p->time, p->comando);
}

void LiberarMemoria (EstrucSched* s) {
    s->enEjecucion = NULL;
    DestruirCola(s->q0);
    DestruirCola(s->q1);
    DestruirCola(s->q2);
    DestruirCola(s->q3);
    DestruirCola(s->q4);
    DestruirCola(s->q5);
    free(s);
}

void msg_Insercion () {
    printf("\n-----> Insercion completada\n");
}

void msg_ErrorInsertar (Proceso* p) {
    ImprimeProceso(p);
    printf ("\nOperacion fallida: el proceso no cumple con el formato admitido: ");
    printf ("\nPID - estado - prioridad - time - comando");
    printf ("\nPID: es un entero.");
    printf ("\nestado: es un caracter, inicialmente es 'L'.");
    printf ("\nprioridad: es un entero del 0 al 5.");
    printf ("\ntime: es un numero real.");
    printf ("\ncomando: es una cadena de caracteres.");
}

void msg_errorInsertPID (Proceso* p) {
    printf ("\nOperacion cancelada: el siguiente proceso tiene el mismo PID.");
    ImprimeProceso(p);
    printf ("\nUtilice un PID diferente.");
}

void msg_ErrorElim () {
    printf ("\nOperacion fallida: el proceso ha eliminar no existe.");
}

void msg_Busy () {
    printf("\nOperacion cancelada: hay un proceso en ejecucion. Detenga el proceso y vuelva a intentarlo.");
}

void msg_ErrorOpenFile () {
    printf("\nHa ocurrido un error al cargar el archivo.\n");
    exit (0);
}