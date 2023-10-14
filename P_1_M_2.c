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

void multiplicarMatrices(short **A, short **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = (int)(A[0][0] * B[0][0]);
    } else {
        int m = n / 2;
        short ***submatrices = malloc(6 * sizeof(short **));

        for (int i = 0; i < 6; i++) {
            submatrices[i] = malloc(m * sizeof(short *));
            for (int j = 0; j < m; j++) {
                submatrices[i][j] = malloc(m * sizeof(short));
            }
        }

        // Dividir A y B en submatrices
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                submatrices[0][i][j] = A[i][j];
                submatrices[1][i][j] = A[i][j + m];
                submatrices[2][i][j] = A[i + m][j];
                submatrices[3][i][j] = A[i + m][j + m];

                submatrices[4][i][j] = B[i][j];
                submatrices[5][i][j] = B[i][j + m];
            }
        }

        // Realizar las operaciones de multiplicación de forma recursiva
        int ***Temp = malloc(4 * sizeof(int **));
        for (int i = 0; i < 4; i++) {
            Temp[i] = malloc(m * sizeof(int *));
            for (int j = 0; j < m; j++) {
                Temp[i][j] = malloc(m * sizeof(int));
            }
        }

        multiplicarMatrices(submatrices[0], submatrices[4], Temp[0], m);
        multiplicarMatrices(submatrices[1], submatrices[5], Temp[1], m);
        sumarMatrices(Temp[0], Temp[1], C, m);

        multiplicarMatrices(submatrices[2], submatrices[4], Temp[2], m);
        multiplicarMatrices(submatrices[3], submatrices[5], Temp[3], m);
        sumarMatrices(Temp[2], Temp[3], C + m, m);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < m; j++) {
                free(Temp[i][j]);
            }
            free(Temp[i]);
        }
        free(Temp);

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < m; j++) {
                free(submatrices[i][j]);
            }
            free(submatrices[i]);
        }
        free(submatrices);
    }
}

int main() {
    clock_t start, end;
    double tiempo;

    int sizeMatriz = 2;

    short **Matriz1 = malloc(sizeMatriz * sizeof(short *));
    short **Matriz2 = malloc(sizeMatriz * sizeof(short *));
    int **Matriz3 = malloc(sizeMatriz * sizeof(int *));

    for (int i = 0; i < sizeMatriz; i++) {
        Matriz1[i] = malloc(sizeMatriz * sizeof(short));
        Matriz2[i] = malloc(sizeMatriz * sizeof(short));
        Matriz3[i] = malloc(sizeMatriz * sizeof(int));
    }

    // Inicializar Matriz1 y Matriz2 con valores aleatorios
    srand(time(NULL));
    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            Matriz1[i][j] = rand() % 128 + 0;
            Matriz2[i][j] = rand() % 128 + 0;
        }
    }

    int c = 0;
    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            printf("<%d>",Matriz1[i][j]);
            c++;
            if (c == sizeMatriz)
            {
                printf("\n");
                c = 0;
            }
        }
    }
    c = 0;
    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            printf("{%d}",Matriz2[i][j]);
            c++;
            if (c == sizeMatriz)
            {
                printf("\n");
                c = 0;
            }
        }
    }

    start = clock();
    multiplicarMatrices(Matriz1, Matriz2, Matriz3, sizeMatriz);
    end = clock();
    c = 0;
    for (int i = 0; i < sizeMatriz; i++) {
        for (int j = 0; j < sizeMatriz; j++) {
            printf("{%d}",Matriz3[i][j]);
            c++;
            if (c == sizeMatriz)
            {
                printf("\n");
                c = 0;
            }
        }
    }

    tiempo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo promedio multiplicacion matrices [%d x %d] = {%.2f minutos}|{%f segundos}|{%f milisegundos}\n", sizeMatriz, sizeMatriz, (tiempo / 10) / 60, tiempo / 10, (tiempo / 10) * 1000);

    for (int i = 0; i < sizeMatriz; i++) {
        free(Matriz1[i]);
        free(Matriz2[i]);
        free(Matriz3[i]);
    }
    free(Matriz1);
    free(Matriz2);
    free(Matriz3);

    return 0;
}
