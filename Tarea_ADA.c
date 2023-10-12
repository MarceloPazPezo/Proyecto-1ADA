#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para multiplicar de manera tradicional
void multiplicarMatricesTradicional(int **matriz_A, int **matriz_B, int **matriz_resultado, int n)
{
    // Supongamos que tenemos matrices A, B y C de tamaño n x n
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz_resultado[i][j] = 0; // Inicializa el elemento Cij en cero
            for (int k = 0; k < n; k++)
            {
                matriz_resultado[i][j] += matriz_A[i][k] * matriz_B[k][j]; // Calcula el elemento Cij
            }
        }
    }
}

// Función para multiplicar dos matrices usando la Propiedad 1 Dr1
void multiplicarMatricesDR1(int **matriz_A, int **matriz_B, int **matriz_resultado, int n)
{

}

// Función para multiplicar dos matrices usando la Propiedad 2 con tamaño genérico (nxn)
void multiplicarMatricesDR2(int **matriz_A, int **matriz_B, int **matriz_resultado, int n)
{

}

int main()
{
    struct timespec inicio, fin;
    long long unsigned int diff;
    int n;
    printf("Ingrese el tamaño de la matriz:");
    scanf("%d", &n);

    // Declaración de matrices con asignación dinámica de memoria
    int **matriz_A = (int **)malloc(n * sizeof(int *));
    int **matriz_B = (int **)malloc(n * sizeof(int *));
    int **matriz_resultado = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        matriz_A[i] = (int *)malloc(n * sizeof(int));
        matriz_B[i] = (int *)malloc(n * sizeof(int));
        matriz_resultado[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Generando numeros aleatorios...\n");
    // Inicializa la semilla para generar números aleatorios
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz_A[i][j] = rand() % 128; // Asigna un valor aleatorio entre 0 y 127
            matriz_B[i][j] = rand() % 128; // Asigna un valor aleatorio entre 0 y 127
        }
    }
    printf("Comenzando multiplicacion \n");
    printf("Tomando el tiempo \n");
    //clock_t inicio = clock(); // Inicia el cronómetro

    clock_gettime(CLOCK_MONOTONIC, &inicio); // Inicia el cronómetro
    // Llamamos a la función para realizar la multiplicación
    // Metodo 1
    multiplicarMatricesTradicional(matriz_A, matriz_B, matriz_resultado, n);

    // Metodo 2
    // multiplicarMatricesDR1(matriz_A, matriz_B, matriz_resultado, n);

    // Metodo 3
    //multiplicarMatricesDR2(matriz_A, matriz_B, matriz_resultado, n);

    //clock_t fin = clock(); // Detiene el cronómetro
    //double tiempo = (double)(fin - inicio) /  CLOCKS_PER_SEC;
    //printf("Tiempo transcurrido: %.f", tiempo);

    clock_gettime(CLOCK_MONOTONIC, &fin); // Detiene el cronómetro
    diff = 1000000000L * (fin.tv_sec - inicio.tv_sec) + fin.tv_nsec - inicio.tv_nsec;
    double tiempo = (double)diff / 1000000000.0;
    printf("Tiempo transcurrido: %.9f segundos\n", tiempo);
    //printf("Tiempo transcurrido: %llu nanosegundos\n", (long long unsigned int)diff);

    // Liberar la memoria asignada dinámicamente
    for (int i = 0; i < n; i++)
    {
        free(matriz_A[i]);
        free(matriz_B[i]);
        free(matriz_resultado[i]);
    }
    free(matriz_A);
    free(matriz_B);
    free(matriz_resultado);

    return 0;
}
