#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiplicarMatrices(int **A, int **B, int **C, int n) {
    if (n == 1) {
        // Caso base: matrices de 1x1
        C[0][0] = A[0][0] * B[0][0];
    } else {
        // Dividir las matrices en submatrices
        int m = n / 2;

        // Crear submatrices de A, B y C
        int **A11, **A12, **A21, **A22;
        int **B11, **B12, **B21, **B22;
        int **C11, **C12, **C21, **C22;
        int **Temp1, **Temp2;

        A11 = (int **)malloc(m * sizeof(int *));
        A12 = (int **)malloc(m * sizeof(int *));
        A21 = (int **)malloc(m * sizeof(int *));
        A22 = (int **)malloc(m * sizeof(int *));
        B11 = (int **)malloc(m * sizeof(int *));
        B12 = (int **)malloc(m * sizeof(int *));
        B21 = (int **)malloc(m * sizeof(int *));
        B22 = (int **)malloc(m * sizeof(int *));
        C11 = (int **)malloc(m * sizeof(int *));
        C12 = (int **)malloc(m * sizeof(int *));
        C21 = (int **)malloc(m * sizeof(int *));
        C22 = (int **)malloc(m * sizeof(int *));
        Temp1 = (int **)malloc(m * sizeof(int *));
        Temp2 = (int **)malloc(m * sizeof(int *));

        for (int i = 0; i < m; i++) {
            A11[i] = (int *)malloc(m * sizeof(int));
            A12[i] = (int *)malloc(m * sizeof(int));
            A21[i] = (int *)malloc(m * sizeof(int));
            A22[i] = (int *)malloc(m * sizeof(int));
            B11[i] = (int *)malloc(m * sizeof(int));
            B12[i] = (int *)malloc(m * sizeof(int));
            B21[i] = (int *)malloc(m * sizeof(int));
            B22[i] = (int *)malloc(m * sizeof(int));
            C11[i] = (int *)malloc(m * sizeof(int));
            C12[i] = (int *)malloc(m * sizeof(int));
            C21[i] = (int *)malloc(m * sizeof(int));
            C22[i] = (int *)malloc(m * sizeof(int));
            Temp1[i] = (int *)malloc(m * sizeof(int));
            Temp2[i] = (int *)malloc(m * sizeof(int));
        }

        // Dividir A en submatrices
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + m];
                A21[i][j] = A[i + m][j];
                A22[i][j] = A[i + m][j + m];
            }
        }

        // Dividir B en submatrices
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + m];
                B21[i][j] = B[i + m][j];
                B22[i][j] = B[i + m][j + m];
            }
        }

        // Realizar las operaciones de multiplicación de forma recursiva
        int M = (Matriz1 + Matriz1[sizeMatriz*sizeMatriz - 1]) * (Matriz2[0] + Matriz2[sizeMatriz*sizeMatriz - 1]);
        int N = (Matriz1[sizeMatriz - 1] + Matriz1[sizeMatriz*sizeMatriz - 1]) * Matriz2[0];
        int O = Matriz1[0] * (Matriz2[sizeMatriz - 1] - Matriz2[sizeMatriz*sizeMatriz - 1]);
        int P = Matriz1[sizeMatriz*sizeMatriz - 1] * (Matriz2[sizeMatriz*sizeMatriz - 1 - sizeMatriz] - Matriz2[0]);
        int Q = (Matriz1[0] + Matriz1[sizeMatriz]) * Matriz2[sizeMatriz*sizeMatriz - 1];
        int R = (Matriz1[sizeMatriz - 1] - Matriz1[0]) * (Matriz2[0] + Matriz2[sizeMatriz]);
        int S = (Matriz1[sizeMatriz] - Matriz1[sizeMatriz*sizeMatriz - 1]) * (Matriz2[sizeMatriz*sizeMatriz - 1] + Matriz2[sizeMatriz*sizeMatriz - 2]);

        multiplicarMatrices(A11, B11, Temp1, m);
        multiplicarMatrices(A12, B21, Temp2, m);
        sumarMatrices(Temp1, Temp2, C11, m);

        multiplicarMatrices(A11, B12, Temp1, m);
        multiplicarMatrices(A12, B22, Temp2, m);
        sumarMatrices(Temp1, Temp2, C12, m);

        multiplicarMatrices(A21, B11, Temp1, m);
        multiplicarMatrices(A22, B21, Temp2, m);
        sumarMatrices(Temp1, Temp2, C21, m);

        multiplicarMatrices(A21, B12, Temp1, m);
        multiplicarMatrices(A22, B22, Temp2, m);
        sumarMatrices(Temp1, Temp2, C22, m);

        // Combinar las submatrices para obtener C
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                C[i][j] = C11[i][j];
                C[i][j + m] = C12[i][j];
                C[i + m][j] = C21[i][j];
                C[i + m][j + m] = C22[i][j];
            }
        }

        // Liberar la memoria de las submatrices 
        free(A11);
        free(A12);
        free(A21);
        free(A22);
        free(B11);
        free(B12);
        free(B21);
        free(B22);
        free(C11);
        free(C12);
        free(C21);
        free(C22);
        free(Temp1);
        free(Temp2);
    }
}

int main() {
    int sizeMatriz = 4;
    int *Matriz1 = (int *)malloc(sizeMatriz * sizeMatriz * sizeof(int));
    int *Matriz2 = (int *)malloc(sizeMatriz * sizeMatriz * sizeof(int));
    int *Matriz3 = (int *)malloc(sizeMatriz * sizeMatriz * sizeof(int));

    srand(time(NULL));

    // Inicializar Matriz1 y Matriz2 con valores aleatorios
    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            Matriz1[i * sizeMatriz + j] = rand() % 128;
            Matriz2[i * sizeMatriz + j] = rand() % 128;
        }
    }

    int contador = 0;

    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            printf("{%d}", Matriz1[i * sizeMatriz + j]);
            contador++;
            if (contador == sizeMatriz)
            {
                printf("\n");
                contador = 0;
            }
                    
        }
    }
    contador = 0;

    printf("\n");
    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            printf("<%d>", Matriz2[i * sizeMatriz + j]);
            contador++;
            if (contador == sizeMatriz)
            {
                printf("\n");
                contador = 0;
            }
                    
        }
    }
    contador = 0;
    printf("\n");

    int selector = rand() % sizeMatriz;
    int inicial = Matriz3[selector * sizeMatriz + selector];

    // Inicializar Matriz3 con ceros
    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            Matriz3[i * sizeMatriz + j] = 0;
        }
    }

    // Realizar la multiplicación de matrices con punteros
    // Realizar los cálculos para las propiedades adicionales
    int M = (Matriz1[0] + Matriz1[sizeMatriz*sizeMatriz - 1]) * (Matriz2[0] + Matriz2[sizeMatriz*sizeMatriz - 1]);
    int N = (Matriz1[sizeMatriz - 1] + Matriz1[sizeMatriz*sizeMatriz - 1]) * Matriz2[0];
    int O = Matriz1[0] * (Matriz2[sizeMatriz - 1] - Matriz2[sizeMatriz*sizeMatriz - 1]);
    int P = Matriz1[sizeMatriz*sizeMatriz - 1] * (Matriz2[sizeMatriz*sizeMatriz - 1 - sizeMatriz] - Matriz2[0]);
    int Q = (Matriz1[0] + Matriz1[sizeMatriz]) * Matriz2[sizeMatriz*sizeMatriz - 1];
    int R = (Matriz1[sizeMatriz - 1] - Matriz1[0]) * (Matriz2[0] + Matriz2[sizeMatriz]);
    int S = (Matriz1[sizeMatriz] - Matriz1[sizeMatriz*sizeMatriz - 1]) * (Matriz2[sizeMatriz*sizeMatriz - 1] + Matriz2[sizeMatriz*sizeMatriz - 2]);

    // Calcular las submatrices Cij según las propiedades
    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            if (i < sizeMatriz / 2 && j < sizeMatriz / 2) {
                // C11
                Matriz3[i * sizeMatriz + j] = M + P - Q + S;
            } else if (i < sizeMatriz / 2 && j >= sizeMatriz / 2) {
                // C12
                Matriz3[i * sizeMatriz + j] = O + Q;
            } else if (i >= sizeMatriz / 2 && j < sizeMatriz / 2) {
                // C21
                Matriz3[i * sizeMatriz + j] = N + P;
            } else {
                // C22
                Matriz3[i * sizeMatriz + j] = M + O - N + R;
            }
        }
    }

    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            printf("[%d]", Matriz3[i * sizeMatriz + j]);
            contador++;
            if (contador == sizeMatriz)
            {
                printf("\n");
                contador = 0;
            }
                    
        }
    }

    int final = Matriz3[selector * sizeMatriz + selector];

    if (inicial != final) {
        printf("EXITO\n");
    } else {
        printf("FRACASO\n");
    }

    // Liberar la memoria
    free(Matriz1);
    free(Matriz2);
    free(Matriz3);

    return 0;
}
