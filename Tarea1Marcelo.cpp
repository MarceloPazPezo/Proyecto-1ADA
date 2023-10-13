#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;
// Variables modificables
const int MAXIMO = 128;
int n = 2, muestras = 3;

/**
 * La función "mostrarmatrizint" imprime una matriz byte por consola.
 *
 * @param M El parámetro `M` es un puntero a un puntero a un byte. Representa una matriz 
 * bidimensional de bytes.
 */
void mostrarMatrizByte(byte **M) {
    for (int i = 0; i < n; i++) {
        cout << "[";
        for (int j = 0; j < n; j++) {
            cout << static_cast<int>(M[i][j]) << " ";
        }
        cout << "]" << endl;
    }
}

/**
 * La función "mostrarmatrizint" imprime una matriz entera por consola.
 *
 * @param M El parámetro `M` es un puntero a un puntero a un entero.Representa una matriz 
 * bidimensional de enteros.
 */
void mostrarMatrizInt(int **M) {
    for (int i = 0; i < n; i++) {
        cout << "[";
        for (int j = 0; j < n; j++) {
            cout << M[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

/**
 * La función algoritmotradicional realiza la multiplicación de la matriz utilizando un 3 for anidados.
 *
 * @param A es una matriz de nxn.
 * @param B es la otra matriz de nxn.
 * @param c es la matriz resultante tras multiplicar A x B.
 * @param n El parámetro "n" representa el tamaño de las matrices A, B y C. indica el número
 * de filas y columnas en cada matriz.
 */
void AlgoritmoTradicional(byte **A, byte **B, int **C, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += static_cast<int>(A[i][k]) * static_cast<int>(B[k][j]);
            }
        }
    }
}

int** combinarMatrices(int** C11, int** C12, int** C21, int** C22, int n) {
    int** R = new int*[2*n];
    
    // Combinar las dos mitades superiores de las submatrices
    for (int i = 0; i < n; i++) {
        R[i] = new int[n];
        for (int j = 0; j < n; j++) {
            R[i][j] = *(*(C11 + i) + j);
        }
        for (int j = 0; j < n; j++) {
            R[i][j+n] = *(*(C12 + i) + j);
        }
    }
    
    // Combinar las dos mitades inferiores de las submatrices
    for (int i = 0; i < n; i++) {
        R[i+n] = new int[n];
        for (int j = 0; j < n; j++) {
            R[i+n][j] = *(*(C21 + i) + j);
        }
        for (int j = 0; j < n; j++) {
            R[i+n][j+n] = *(*(C22 + i) + j);
        }
    }
    
    return R;
}

void dividirMatriz(byte** M, int half, byte** R11, byte** R12, byte** R21, byte** R22) {
    R11 = new byte*[half];
    R12 = new byte*[half];
    R21 = new byte*[half];
    R22 = new byte*[half];
    
    for (int i = 0; i < half; i++) {
        (R11)[i] = new byte[half];
        (R12)[i] = new byte[half];
        (R21)[i] = new byte[half];
        (R22)[i] = new byte[half];
        for (int j = 0; j < half; j++) {
            (R11)[i][j] = *(*(M + i) + j);
            (R12)[i][j] = *(*(M + i) + j + half);
            (R21)[i][j] = *(*(M + i + half) + j);
            (R22)[i][j] = *(*(M + i + half) + j + half);
        }
    }
}

int** sumarMatrices(int** M1, int** M2, int n) {
    int** R = new int*[n];
    
    for (int i = 0; i < n; i++) {
        R[i] = new int[n];
        for (int j = 0; j < n; j++) {
            R[i][j] = *(*(M1 + i) + j) + *(*(M2 + i) + j);
        }
    }
    
    return R;
}

/**
 * La función DR1 realiza la multiplicación de la matriz de recursiva utilizando el enfoque Divide and Conquer.
 *
 * @param a a es una matriz 2D de bytes.Representa la primera matriz.
 * @param B El parámetro `B` es un puntero a una matriz 2D de bytes.
 * @param c c es una matriz de enteros 2D que representa la matriz de resultados.
 * @param fila El índice de fila del submatriz actual que se está procesando.
 * @param col El parámetro "col" representa el índice de columna del submatriz actual que se está procesando.
 * @param tamaño El "tamaño" del parámetro representa el tamaño de las matrices.Indica el número de
 * Filas y columnas en las matrices "A", "B" y "C".
 */
// void DR1(byte **A, byte **B, int **C, int row, int col, int size) {
//     if (size == 2) {
//         C[row][col] += static_cast<int>(A[row][col]) * static_cast<int>(B[row][col]);
//         C[row][col+1] += static_cast<int>(A[row][col+1]) * static_cast<int>(B[row+1][col+1]);
//         C[row+1][col] += static_cast<int>(A[row+1][col]) * static_cast<int>(B[row+1][col]);
//         C[row+1][col+1] += static_cast<int>(A[row+1][col]) * static_cast<int>(B[row+1][col+1]);
//     } else {
//         int newSize = size / 2;
//         for (int i = 0; i < newSize; i++) {
//             for (int j = 0; j < newSize; j++) {
//                 DR1(A, B, C, row + i, col + j, newSize);
//                 DR1(A, B, C, row + i, col + newSize + j, newSize);
//                 DR1(A, B, C, row + newSize + i, col + j, newSize);
//                 DR1(A, B, C, row + newSize + i, col + newSize + j, newSize);
//             }
//         }
//     }
// }

// void DR1mod(byte **A, byte **B, int **C, int row, int col, int size) {
    
//     if (size == 2)
//     {
//         C1 = static_cast<int>(A[0][0]) * static_cast<int>(B[0][0]) + static_cast<int>(A[0][1]) * static_cast<int>(B[1][0]);
//         c2 = A[0][0] * B[0][1] + A[0][1] * B[1][1]
//         c3 = A[1][0] * B[0][0] + A[1][1] * B[1][0]
//         c4 = A[1][0] * B[0][1] + A[1][1] * B[1][1]
//         return [[c1, c2], [c3, c4]]
//     }
//     else
//     {
//         int half = size / 2;
//         byte ** A11, A12, A21, A22;
//         dividirMatriz(A, half, A11, A12, A21, A22);
//         B11, B12, B21, B22 = split_matrix(B, half)
        
//         C11 = add_matrices(multiply_matrices(A11, B11), multiply_matrices(A12, B21))
//         C12 = add_matrices(multiply_matrices(A11, B12), multiply_matrices(A12, B22))
//         C21 = add_matrices(multiply_matrices(A21, B11), multiply_matrices(A22, B21))
//         C22 = add_matrices(multiply_matrices(A21, B12), multiply_matrices(A22, B22))
        
//         return combine_matrices(C11, C12, C21, C22)
//     }
//     if (size == 2) {
//         c[row][col] += static_cast<int>(a[row][col]) * static_cast<int>(b[row][col]);
//     } else {
//         int newSize = size / 2;
//         for (int i = 0; i < newSize; i++) {
//             for (int j = 0; j < newSize; j++) {
//                 DR1(a, b, c, row + i, col + j, newSize);
//                 DR1(a, b, c, row + i, col + newSize + j, newSize);
//                 DR1(a, b, c, row + newSize + i, col + j, newSize);
//                 DR1(a, b, c, row + newSize + i, col + newSize + j, newSize);
//             }
//         }
//     }
// }

// void DR2(byte **a, byte **b, int **c, int row, int col, int size) {
//     if (size == 2) {
//         c[row][col] += static_cast<int>(a[row][col]) * static_cast<int>(b[row][col]);
//     } else {
//         int newSize = size / 2;
//         for (int i = 0; i < newSize; i++) {
//             for (int j = 0; j < newSize; j++) {
//                 DR1(a, b, c, row + i, col + j, newSize);
//                 DR1(a, b, c, row + i, col + newSize + j, newSize);
//                 DR1(a, b, c, row + newSize + i, col + j, newSize);
//                 DR1(a, b, c, row + newSize + i, col + newSize + j, newSize);
//             }
//         }
//     }
// }
void llenarMatricesRandom(byte ** A, byte **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = new byte[n];
        B[i] = new byte[n];
        C[i] = new int[n];
        for (int j = 0; j < n; j++) {
            A[i][j] = static_cast<byte>(rand() % 128);
            B[i][j] = static_cast<byte>(rand() % 128);
            C[i][j] = 0;
        }
    }

}
int main() {
    srand(time(NULL));
    // Crear matrices aleatorias
    int menu = 0;
    byte **A = new byte*[n];
    byte **B = new byte*[n];
    int **C = new int*[n];

    cout << "Ingrese el algoritmo que desea ejecutar: " << endl;
    cout << "1. Algoritmo Tradicional" << endl;
    cout << "2. DR1" << endl;
    cout << "3. DR2" << endl;
    cout << ">>> ";
    cin >> menu;
    switch (menu)
    {
        case 1:
            // Cantidad de muestras a tomar
            for (int a = 0; a < muestras; a++) {
                llenarMatricesRandom(A,B,C,n);

                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                AlgoritmoTradicional(A, B, C, n);

                auto fin = high_resolution_clock::now();    // Tiempo final
                mostrarMatrizByte(A);
                cout << "x" << endl;
                mostrarMatrizByte(B);
                cout << "=" << endl;
                mostrarMatrizInt(C);
                cout << endl;
                // Calcular tiempo y transformarlo a minutos, segundos y nanosegundos
                long long nanosegundos = duration_cast<nanoseconds>(fin - inicio).count();

                long long segundos = duration_cast<seconds>(nanoseconds(nanosegundos)).count();
                nanosegundos -= segundos * 1e9;

                // Guardar datos en archivo .txt
                ofstream archivo("t.txt", ios::app);
                if (archivo.is_open()) {
                    archivo << n << "," << segundos << "," << nanosegundos << "," << "AT" << endl;
                    archivo.close();
                } else {
                    cout << "No se pudo abrir el archivo" << endl;
                }
            }
            break;
        case 2:
            // Cantidad de muestras a tomar
            for (int a = 0; a < muestras; a++) {
                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                DR1(A, B, C, 0, 0, n);

                auto fin = high_resolution_clock::now();    // Tiempo final
                mostrarMatrizByte(A);
                cout << "x" << endl;
                mostrarMatrizByte(B);
                cout << "=" << endl;
                mostrarMatrizInt(C);
                // Calcular tiempo y transformarlo a minutos, segundos y nanosegundos
                long long nanosegundos = duration_cast<nanoseconds>(fin - inicio).count();

                long long segundos = duration_cast<seconds>(nanoseconds(nanosegundos)).count();
                nanosegundos -= segundos * 1e9;

                // Guardar datos en archivo .txt
                ofstream archivo("tiempos.txt", ios::app);
                if (archivo.is_open()) {
                    archivo << n << "," << segundos << "," << nanosegundos << "," << "DR1" << endl;
                    archivo.close();
                } else {
                    cout << "No se pudo abrir el archivo" << endl;
                }
            }
            cout << "FIN DE ALGORITMO" << endl;
            break;
        case 3:
            // Cantidad de muestras a tomar
            for (int a = 0; a < muestras; a++) {
                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                // Algoritmo de Strassen
                // DR2(A, B, C, 0, 0, n);

                auto fin = high_resolution_clock::now();    // Tiempo final

                // Calcular tiempo y transformarlo a minutos, segundos y nanosegundos
                long long nanosegundos = duration_cast<nanoseconds>(fin - inicio).count();

                long long segundos = duration_cast<seconds>(nanoseconds(nanosegundos)).count();
                nanosegundos -= segundos * 1e9;

                // Guardar datos en archivo .txt
                ofstream archivo("tiempos.txt", ios::app);
                if (archivo.is_open()) {
                    archivo << n << "," << segundos << "," << nanosegundos << "," << "DR2" << endl;
                    archivo.close();
                } else {
                    cout << "No se pudo abrir el archivo" << endl;
                }
            }
            break;
        
        default:
            break;
    }
    

    return 0;
}