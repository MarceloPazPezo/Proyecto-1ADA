#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {

    clock_t start, end;
    double tiempo;
    int sizeMatriz = 32, opc1 = 0, opc11 = 0, opc12 = 0, caso2 = 0;

    printf("Bienvenido, este codigo tiene dos modalidades para las cuales se estregara su tiempo de trabajo promedio despues de 10 ejecuciones, \n1.- realizar la multiplicacion de UNA matriz de valores especificos \n2.- multiplicacion sucesiva desde una matriz inicial de 32x32 hasta una de las proporcionadas \n3.-Salir ");
    
    while (opc1 != 1 && opc1 != 2 && opc1 != 3)
    {
        printf("\n(por favor ingrese 1,2 o 3 para seleccionar una opcion)\n");
        scanf("%d", &opc1);
    }
    
    switch (opc1)
    {
    case 1:
        printf("\nde que porte desea que sea la matriz");
        printf("\n1.-[32x32]");
        printf("\n2.-[64x64]");
        printf("\n3.-[128x128]");
        printf("\n4.-[256x256]");
        printf("\n5.-[512x512]");
        printf("\n6.-[1024x1024]");
        printf("\n7.-[2048x2048]");
        printf("\n8.-[4096x4096]");
        printf("\n9.-Salir");

        while (opc11 < 1 || opc11 > 9)
        {
            printf("\n(por favor ingrese una opcion valida)\n");
            scanf("%d", &opc11);
        }
        

        if (opc11 == 9)
        {
            break;
        }

        sizeMatriz = sizeMatriz * pow(2,opc11-1);
        int rep = 10;
        double prom = 0;

        do
        {
            int *Matriz1 = (int *)malloc(sizeMatriz * sizeMatriz * sizeof(int));
            int *Matriz2 = (int *)malloc(sizeMatriz * sizeMatriz * sizeof(int));
            int *Matriz3 = (int *)malloc(sizeMatriz * sizeMatriz * sizeof(int));

            // Inicializar Matriz1 y Matriz2 con valores aleatorios
            for (int i = 0; i < sizeMatriz; i++) {
                for (int j = 0; j < sizeMatriz; j++) {
                    Matriz1[i * sizeMatriz + j] = rand() % 128;
                    Matriz2[i * sizeMatriz + j] = rand() % 128;
                }
            }

            // Inicializar Matriz3 con ceros
            for (int i = 0; i < sizeMatriz; i++) {
                for (int j = 0; j < sizeMatriz; j++) {
                    Matriz3[i * sizeMatriz + j] = 0;
                }
            }

            start = clock();
            // Realizar la multiplicación de matrices con punteros
            for (int i = 0; i < sizeMatriz; i++) {
                for (int j = 0; j < sizeMatriz; j++) {
                    for (int k = 0; k < sizeMatriz; k++) {
                        Matriz3[i * sizeMatriz + j] += Matriz1[i * sizeMatriz + k] * Matriz2[k * sizeMatriz + j];
                    }
                }
            }
            end = clock();

            tiempo = ((double) (end - start)) / CLOCKS_PER_SEC;

            // Liberar la memoria
            free(Matriz1);
            free(Matriz2);
            free(Matriz3);
            prom = prom + tiempo;
            rep = rep - 1;

        } while (rep != 0);
        
        printf("Tiempo promedio multiplicacion matrices [%d x %d] = {%.2f minutos}|{%f segundos}|{%f milisegundos}\n", sizeMatriz,sizeMatriz,(prom/10)/60,prom/10,(prom/10)*1000);

        break;
    
    case 2:

        printf("\nHasta que matriz desea los tiempos?");
        printf("\n1.-[32x32]");
        printf("\n2.-[64x64]");
        printf("\n3.-[128x128]");
        printf("\n4.-[256x256]");
        printf("\n5.-[512x512]");
        printf("\n6.-[1024x1024]");
        printf("\n7.-[2048x2048]");
        printf("\n8.-[4096x4096]");
        printf("\n9.-Salir");
        
        while (opc12 < 1 || opc12 > 9)
        {
            printf("\n(por favor ingrese un valor entre 1 y 9)\n");
            scanf("%d", &opc12);
        }   

        if (opc12 == 9)
        {
            break;
        }
        
        caso2 = sizeMatriz * pow(2,opc12-1);

        do
        {  
            double promedio = 0;
            int rep = 10;

            do
            {
                int *Matriz1 = (int *)malloc(sizeMatriz * sizeMatriz * sizeof(int));
                int *Matriz2 = (int *)malloc(sizeMatriz * sizeMatriz * sizeof(int));
                int *Matriz3 = (int *)malloc(sizeMatriz * sizeMatriz * sizeof(int));

                // Inicializar Matriz1 y Matriz2 con valores aleatorios
                for (int i = 0; i < sizeMatriz; i++) {
                    for (int j = 0; j < sizeMatriz; j++) {
                        Matriz1[i * sizeMatriz + j] = rand() % 128;
                        Matriz2[i * sizeMatriz + j] = rand() % 128;
                    }
                }

                // Inicializar Matriz3 con ceros
                for (int i = 0; i < sizeMatriz; i++) {
                    for (int j = 0; j < sizeMatriz; j++) {
                        Matriz3[i * sizeMatriz + j] = 0;
                    }
                }

                start = clock();
                // Realizar la multiplicación de matrices con punteros
                for (int i = 0; i < sizeMatriz; i++) {
                    for (int j = 0; j < sizeMatriz; j++) {
                        for (int k = 0; k < sizeMatriz; k++) {
                            Matriz3[i * sizeMatriz + j] += Matriz1[i * sizeMatriz + k] * Matriz2[k * sizeMatriz + j];
                        }
                    }
                }
                end = clock();

                tiempo = ((double) (end - start)) / CLOCKS_PER_SEC;

                // Liberar la memoria
                free(Matriz1);
                free(Matriz2);
                free(Matriz3);
                
                rep = rep - 1;
                promedio = promedio + tiempo;

            } while (rep != 0);
            
            printf("Tiempo promedio multiplicacion matrices [%d x %d] = {%.2f minutos}|{%f segundos}|{%f milisegundos}\n", sizeMatriz,sizeMatriz,(promedio/10)/60,promedio/10,(promedio/10)*1000);
            sizeMatriz = sizeMatriz*2;
            
        } while (sizeMatriz <= caso2);
        
        break;
    
    case 3:
        break;
    }
    return 0;
}
