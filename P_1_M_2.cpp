#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

void sumarMatrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiplicarMatrices(short **A, short **B, int **C, int n) {
    if (n == 1) {
        // Caso base: matrices de 1x1
        C[0][0] = static_cast<int>(A[0][0]) * B[0][0];
    } else {
        int m = n / 2;

        short **A11 = new short *[m];
        short **A12 = new short *[m];
        short **A21 = new short *[m];
        short **A22 = new short *[m];
        short **B11 = new short *[m];
        short **B12 = new short *[m];
        short **B21 = new short *[m];
        short **B22 = new short *[m];
        int **C11 = new int *[m];
        int **C12 = new int *[m];
        int **C21 = new int *[m];
        int **C22 = new int *[m];

        for (int i = 0; i < m; i++) {
            A11[i] = new short[m];
            A12[i] = new short[m];
            A21[i] = new short[m];
            A22[i] = new short[m];
            B11[i] = new short[m];
            B12[i] = new short[m];
            B21[i] = new short[m];
            B22[i] = new short[m];
            C11[i] = new int[m];
            C12[i] = new int[m];
            C21[i] = new int[m];
            C22[i] = new int[m];
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + m];
                A21[i][j] = A[i + m][j];
                A22[i][j] = A[i + m][j + m];
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + m];
                B21[i][j] = B[i + m][j];
                B22[i][j] = B[i + m][j + m];
            }
        }

        int **Temp1 = new int *[m];
        int **Temp2 = new int *[m];

        for (int i = 0; i < m; i++) {
            Temp1[i] = new int[m];
            Temp2[i] = new int[m];
        }

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

        for (int i = 0; i < m; i++) {
            delete[] A11[i];
            delete[] A12[i];
            delete[] A21[i];
            delete[] A22[i];
            delete[] B11[i];
            delete[] B12[i];
            delete[] B21[i];
            delete[] B22[i];
            delete[] C11[i];
            delete[] C12[i];
            delete[] C21[i];
            delete[] C22[i];
            delete[] Temp1[i];
            delete[] Temp2[i];
        }

        delete[] A11;
        delete[] A12;
        delete[] A21;
        delete[] A22;
        delete[] B11;
        delete[] B12;
        delete[] B21;
        delete[] B22;
        delete[] C11;
        delete[] C12;
        delete[] C21;
        delete[] C22;
        delete[] Temp1;
        delete[] Temp2;
    }
}

void guardarTiemposEnArchivo(double tiempo, const char *nombreArchivo, int sizeMatriz) {
    std::ofstream archivo(nombreArchivo, std::ios::app);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return;
    }
    if (sizeMatriz == 32) {
        archivo << "------------------------------------------\n";
    }

    archivo << "Tiempo en segundos para matriz de " << sizeMatriz << "x" << sizeMatriz << " = " << (tiempo / 10) << std::endl;
    archivo.close();
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int sizeMatriz = 32;

    do {
        double promedio = 0;

        for (int rep = 0; rep < 10; rep++) {
            short **Matriz1 = new short *[sizeMatriz];
            short **Matriz2 = new short *[sizeMatriz];
            int **Matriz3 = new int *[sizeMatriz];

            for (int i = 0; i < sizeMatriz; i++) {
                Matriz1[i] = new short[sizeMatriz];
                Matriz2[i] = new short[sizeMatriz];
                Matriz3[i] = new int[sizeMatriz];
            }

            for (int i = 0; i < sizeMatriz; i++) {
                for (int j = 0; j < sizeMatriz; j++) {
                    Matriz1[i][j] = static_cast<short>(std::rand() % 128 + 0);
                    Matriz2[i][j] = static_cast<short>(std::rand() % 128 + 0);
                }
            }

            std::clock_t start = std::clock();
            multiplicarMatrices(Matriz1, Matriz2, Matriz3, sizeMatriz);
            std::clock_t end = std::clock();

            double tiempo = static_cast<double>(end - start) / CLOCKS_PER_SEC;

            for (int i = 0; i < sizeMatriz; i++) {
                delete[] Matriz1[i];
                delete[] Matriz2[i];
                delete[] Matriz3[i];
            }
            delete[] Matriz1;
            delete[] Matriz2;
            delete[] Matriz3;

            promedio += tiempo;
        }

        std::cout << "Tiempo promedio multiplicación matrices [" << sizeMatriz << "x" << sizeMatriz << "] = " << (promedio / 10) << " segundos" << std::endl;
        guardarTiemposEnArchivo(promedio, "tiemposDR1C++.txt", sizeMatriz);
        sizeMatriz *= 2;

    } while (sizeMatriz <= 1024);

    return 0;
}
