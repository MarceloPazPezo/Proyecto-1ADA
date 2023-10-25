/***
 * DR1.c
 * Programa que implementa los algoritmos de multiplicacion de matrices usando DR1
 * Fecha 16-10-2023
 * Autores:
 * - Bastian Rodriguez
 * - Marcelo Paz
 * - Nicolas Gomez
 * - Juan Henriquez
 * - Victor Lopez
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaración de funciones
void MultMatricesRecursivo(int** A, int** B, int** C, int rowA, int colA, int rowB, int colB, int N);
void MultMatrices_2(int** A, int** B, int** C, int N);
void LiberarMemoria(int*** matriz, int N);


void MultMatricesRecursivo(int** A, int** B, int** C, int rowA, int colA, int rowB, int colB, int N) {
    if (N == 1) {
        C[rowA][colB] += A[rowA][colA] * B[rowB][colB];
    } else {
        int nuevaDimension = N / 2;

        MultMatricesRecursivo(A, B, C, rowA, colA, rowB, colB, nuevaDimension);
        MultMatricesRecursivo(A, B, C, rowA, colA + nuevaDimension, rowB + nuevaDimension, colB, nuevaDimension);
        MultMatricesRecursivo(A, B, C, rowA, colA, rowB, colB + nuevaDimension, nuevaDimension);
        MultMatricesRecursivo(A, B, C, rowA, colA + nuevaDimension, rowB, colB + nuevaDimension, nuevaDimension);

        MultMatricesRecursivo(A, B, C, rowA + nuevaDimension, colA, rowB, colB, nuevaDimension);
        MultMatricesRecursivo(A, B, C, rowA + nuevaDimension, colA + nuevaDimension, rowB + nuevaDimension, colB, nuevaDimension);
        MultMatricesRecursivo(A, B, C, rowA + nuevaDimension, colA, rowB, colB + nuevaDimension, nuevaDimension);
        MultMatricesRecursivo(A, B, C, rowA + nuevaDimension, colA + nuevaDimension, rowB + nuevaDimension, colB + nuevaDimension, nuevaDimension);
    }
}

void MultMatrices_2(int** A, int** B, int** C, int N) {
    // Inicializar la matriz C con ceros
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }
    // Multiplicar las matrices de manera recursiva
    MultMatricesRecursivo(A, B, C, 0, 0, 0, 0, N);
}

// Función para liberar la memoria de una matriz cuadrada de tamaño N
void LiberarMemoria(int*** matriz, int N) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < N / 2; j++) {
            free(matriz[i][j]);
        }
        free(matriz[i]);
    }
    free(matriz);
}

int main() {
    
    int N;
    printf("N: ");
    scanf("%d",&N);
    
    // Asignar memoria dinámica para las matrices A, B y C
    int** A = (int**)malloc(N * sizeof(int*));
    int** B = (int**)malloc(N * sizeof(int*));
    int** C = (int**)malloc(N * sizeof(int*));
        
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
    }

    // Inicializar la semilla para números aleatorios
    srand(time(NULL));

    // Llenar las matrices A y B con números aleatorios en un rango de 0 a 256
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *(*(A + i) + j) = rand() % 257;
            *(*(B + i) + j) = rand() % 257;
        }
    }

    // Medir el tiempo de ejecución
    clock_t tiempo_inicial = clock();
        
    MultMatrices_2(A, B, C, N);
        
    clock_t tiempo_final = clock();

    // Calcular el tiempo de ejecución en milisegundos
    double tiempo_ejecucion = ((double)(tiempo_final - tiempo_inicial) / CLOCKS_PER_SEC) * 1000;
        
    // Mostrar el tiempo de ejecución en milisegundos, segundos y minutos
    printf("Tiempo de ejecución de %d: %.10f milisegundos (%.6f segundos, %.6f minutos)\n",
            N, tiempo_ejecucion, tiempo_ejecucion / 1000, tiempo_ejecucion / (1000 * 60));

    // Liberar memoria
    LiberarMemoria(A, N);
    LiberarMemoria(B, N);
    LiberarMemoria(C, N);

    return 0;
}

/*
    printf("Matriz resultante C:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Imprimir cada elemento de la matriz separado por espacio
                printf("%d ", C[i][j]);
            }
            // Imprimir una nueva línea después de cada fila
            printf("\n");
        }
*/


