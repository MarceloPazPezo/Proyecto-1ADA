#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sumarMatrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void restarMatrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

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

        for (int i = 0; i < m; i++) {
            free(A11[i]);
            free(A12[i]);
            free(A21[i]);
            free(A22[i]);
            free(B11[i]);
            free(B12[i]);
            free(B21[i]);
            free(B22[i]);
            free(C11[i]);
            free(C12[i]);
            free(C21[i]);
            free(C22[i]);
            free(Temp1[i]);
            free(Temp2[i]);
        }
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
    
    clock_t start, end;
    double tiempo;
    int sizeMatriz = 32;

    do
    {  
        double promedio = 0;
        int rep = 5;

        // do
        // {
            
            int **Matriz1 = (int **)malloc(sizeMatriz * sizeof(int *));
            int **Matriz2 = (int **)malloc(sizeMatriz * sizeof(int *));
            int **Matriz3 = (int **)malloc(sizeMatriz * sizeof(int *));

            for (int i = 0; i < sizeMatriz; i++) {
                Matriz1[i] = (int *)malloc(sizeMatriz * sizeof(int));
                Matriz2[i] = (int *)malloc(sizeMatriz * sizeof(int));
                Matriz3[i] = (int *)malloc(sizeMatriz * sizeof(int));
            }

            // Inicializar Matriz1 y Matriz2 con valores aleatorios
            for (int i = 0; i < sizeMatriz; i++) {
                for (int j = 0; j < sizeMatriz; j++) {
                    Matriz1[i][j] = rand() % 128 + 0;
                    Matriz2[i][j] = rand() % 128 + 0;
                }
            }

            start = clock();
            // Multiplicar las matrices
            multiplicarMatrices(Matriz1, Matriz2, Matriz3, sizeMatriz);
            end = clock();

            tiempo = ((double) (end - start)) / CLOCKS_PER_SEC;
            

            // Liberar la memoria de las matrices
            for (int i = 0; i < sizeMatriz; i++) {
                free(Matriz1[i]);
                free(Matriz2[i]);
                free(Matriz3[i]);
            }
            free(Matriz1);
            free(Matriz2);
            free(Matriz3);

            rep = rep - 1;
            promedio = promedio + tiempo;

        //}while(rep != 0);

        printf("Tiempo promedio multiplicacion matrices [%d x %d] = {%.2f minutos}|{%f segundos}|{%f milisegundos}\n", sizeMatriz,sizeMatriz,(promedio/10)/60,promedio/10,(promedio/10)*1000);
        sizeMatriz = sizeMatriz*2;

    }while(sizeMatriz <= 1024);

    return 0;
}
