#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;
using namespace chrono;

// Variables modificables

const int MINIMO = 0; // Valor minimo para los numeros random
const int MAXIMO = 128; // Valor maximo para los numeros random
// int n = 2; // Tamaño de las matrices
int muestras = 1; // Cantidad de muestras a tomar

// Prototipos de funciones que calculan la multiplicacion
void AlgoritmoTradicional(byte **A, byte **B, int **C, int n);
void AlgoritmoTradicionalALE(byte **A, byte **B, int **C, int size);
void DR1(byte **A, byte **B, int **C, int row, int col, int size);
void multiply_matrices(byte **a, byte **b, int **c, int row, int col, int size);
void multiply_matrices1(byte **a, byte **b, int **c, int row, int col, int size);
void strassen(int **matrixA, int **matrixB, int **matrixC, int n);

// Prototipos extras
void sumarMatrices(int **matrixA, int **matrixB, int **matrixC, int n);
void restarMatrices(int **matrixA, int **matrixB, int **matrixC, int n);
void llenarMatricesRandomIdentidad(byte ** A, byte ** B, int ** C, int size);
void llenarMatricesRandomByte(byte ** A, byte **B, int **C, int n);
void llenarMatricesRandomInt(int ** A, int **B, int **C, int n);
void mostrarMatrizByte(byte **M, int size);
void mostrarMatrizInt(int **M, int size);
void calcularTiempoYGuardar(time_point<high_resolution_clock> inicio, time_point<high_resolution_clock> fin, int n, string algoritmo, bool guardar);
bool compararMatrices(int **A, int **B, int n);
bool compararMatricesByte(int **A, byte **B, int n);

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    int menu = 0, n = 0, muestras = 0;
    char guardar = 'N';
    bool guardarBool = false;
    cout << "Ingrese N: " << endl;
    cout << ">>> ";
    cin >> n;
    cout << " " << endl;
    cout << "Ingrese cantidad de muestras: " << endl;
    cout << ">>> ";
    cin >> muestras;
    cout << " " << endl;
    cout << "Deseas guardar los datos en un archivo Tiempos.txt (S, N): " << endl;
    cout << ">>> ";
    cin >> guardar;
    cout << " " << endl;
    if (guardar == 'S' || guardar == 's')
    {
        guardarBool = true;
    }
    else
    {
        guardarBool = false;
    }
    byte **A = new byte*[n];
    byte **B = new byte*[n];
    int **C = new int*[n];
    // int **AUX = new int*[n]; // Matriz para guardar resultados de forma auxiliar y poder comparar el resultado de 2 algoritmos

    cout << "Ingrese el algoritmo que desea ejecutar: " << endl;
    cout << "1. Algoritmo Tradicional" << endl;
    cout << "2. DR1" << endl;
    cout << "3. DR2 (Strassen)" << endl;
    cout << "4. Compara matriz resultante tras multiplicar A x I = A" << endl;
    // cout << "5. Compara matriz resultante tras multiplicar A x I = A" << endl;
    cout << ">>> ";
    cin >> menu;
    cout << " " << endl;
    switch (menu)
    {
        case 1:
            for (int a = 0; a < muestras; a++)
            {
                llenarMatricesRandomByte(A,B,C,n);

                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                AlgoritmoTradicional(A, B, C, n);

                auto fin = high_resolution_clock::now();    // Tiempo final
                calcularTiempoYGuardar(inicio, fin, n, "Tradicional", guardarBool);
            }
            break;

        case 2:
            for (int a = 0; a < muestras; a++)
            {
                llenarMatricesRandomByte(A,B,C,n);

                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                // multiply_matrices(A,B,C,0,0,n);
                
                auto fin = high_resolution_clock::now();    // Tiempo final
                calcularTiempoYGuardar(inicio, fin, n, "DR1", guardarBool);

            }
            break;
        
        case 3:
            for (int a = 0; a < muestras; a++)
            {
                if (a == 0)
                {
                    delete[] A;
                    delete[] B;
                }
                int **Aaux = new int*[n];
                int **Baux = new int*[n];

                llenarMatricesRandomInt(Aaux,Baux,C,n);
                

                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                strassen(Aaux, Baux, C, n);

                auto fin = high_resolution_clock::now();    // Tiempo final
                calcularTiempoYGuardar(inicio, fin, n, "Strassen", guardarBool);

                for (int i = 0; i < n; i ++)
                {
                    delete[] Aaux[i];
                    delete[] Baux[i];
                    delete[] C[i];
                }
                delete [] Aaux;
                delete [] Baux;
            }
            break;

        case 4:
            for (int a = 0; a < 1; a++)
            {
                int opc1 = 0;
                do {
                    cout << "Que algoritmo desea probar: " << endl;
                    cout << "1. Algoritmo Tradicional" << endl;
                    cout << "2. DR1" << endl;
                    cout << "3. DR2" << endl;
                    cout << "4. AT Ale" << endl;
                    cout << "A1>>> ";
                    cin >> opc1;
                    if (opc1 < 1 || opc1 > 4)
                    {
                        cout << "Opcion invalida" << endl;
                    }
                } while (opc1 < 1 || opc1 > 4);
                cout << " " << endl;

                cout << "N: " << n << endl;
                
                llenarMatricesRandomIdentidad(A,B,C,n);
                int **Aaux = new int*[n];
                int **Baux = new int*[n];
                
                if (opc1 == 3)
                {
                    for (int i = 0; i < n; i++)
                    {
                        Aaux[i] = new int[n];
                        Baux[i] = new int[n];
                        for (int j = 0; j < n; j++)
                        {
                            Aaux[i][j] = static_cast<int>(A[i][j]);
                            Baux[i][j] = static_cast<int>(B[i][j]);
                        }
                    }
                    for (int i = 0; i < n; i++)
                    {
                        delete[] A[i];
                        delete[] B[i];
                    }
                    delete[] A;
                    delete[] B;
                }
                else
                {
                    delete[] Aaux;
                    delete[] Baux;
                }           

                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                if (opc1 == 1)
                {
                    AlgoritmoTradicional(A, B, C, n);
                    cout << "Algoritmo Tradicional" << endl;
                }
                else if (opc1 == 2)
                {
                    // multiply_matrices1(A, B, C, 0, 0, n);
                    // DR1(A, B, C, 0, 0, n);
                    cout << "DR1" << endl;
                }
                else if (opc1 == 3)
                {
                    strassen(Aaux,Baux,C,n);
                    cout << "DR2" << endl;
                }
                else if (opc1 == 4)
                {
                    AlgoritmoTradicionalALE(A, B, C, n);
                    cout << "AT Ale" << endl;
                }

                auto fin = high_resolution_clock::now();    // Tiempo final

                // Calcular tiempo y transformarlo a minutos, segundos y nanosegundos
                long long nanosegundos = duration_cast<nanoseconds>(fin - inicio).count();

                long long segundos = duration_cast<seconds>(nanoseconds(nanosegundos)).count();
                nanosegundos -= static_cast<long long>(segundos) * static_cast<long long>(1e9);
                cout << "Tiempo: " << segundos << " segundos y " << nanosegundos << " nanosegundos" << endl;
                
                if (n <= 8) // Mostramos matrices si no son demasiado grandes
                {
                    cout << "Matriz A" << endl;
                    if (opc1 == 3)
                    {
                        mostrarMatrizInt(Aaux, n);
                    }
                    else
                    {
                        mostrarMatrizByte(A, n);
                    }
                    cout << " " << endl;

                    cout << "Matriz B" << endl;
                    if (opc1 == 3)
                    {
                        mostrarMatrizInt(Baux, n);
                    }
                    else
                    {
                        mostrarMatrizByte(B, n);
                    }
                    cout << " " << endl;

                    cout << "Matriz C" << endl;
                    mostrarMatrizInt(C, n);
                    cout << " " << endl;
                }
                if (opc1 == 3)
                {
                     if (compararMatrices(C, Aaux, n)) {
                        cout << "Las matrices A y C son iguales" << endl;
                    } else {
                        cout << "Las matrices A y C son diferentes" << endl;
                    }
                }
                else
                {
                    if (compararMatricesByte(C, A, n)) {
                        cout << "Las matrices A y C son iguales" << endl;
                    } else {
                        cout << "Las matrices A y C son diferentes" << endl;
                    }
                }
            }
            break;

        default:
            break;
    }
    return 0;
}

void calcularTiempoYGuardar(time_point<high_resolution_clock> inicio, time_point<high_resolution_clock> fin, int size, string algoritmo, bool guardar) {
    // Calcular tiempo y transformarlo a minutos, segundos y nanosegundos
    long long nanosegundos = duration_cast<nanoseconds>(fin - inicio).count();

    long long segundos = duration_cast<seconds>(nanoseconds(nanosegundos)).count();
    nanosegundos -= static_cast<long long>(segundos) * static_cast<long long>(1e9);

    // Guardar datos en archivo .txt
    cout << "Una matriz de " << size << "x" << size << " se demora " << segundos << " segundos y " << nanosegundos << " nanosegundos con el Algoritmo " << algoritmo << endl;
    if (guardar == true)
    {
        ofstream archivo("Tiempos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << size << "," << segundos << "," << nanosegundos << "," << algoritmo << endl;
            archivo.close();
        } else {
            cout << "No se pudo abrir el archivo" << endl;
        }
    }
}

void llenarMatricesRandomIdentidad(byte ** A, byte ** B, int ** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
        }
    }
    for (int i = 0; i < size; i++) {
        A[i] = new byte[size];
        B[i] = new byte[size];
        C[i] = new int[size];
        for (int j = 0; j < size; j++) {
            A[i][j] = static_cast<byte>(rand() % (MAXIMO - MINIMO + 1) + MINIMO);
            if (i == j) {
                B[i][j] = static_cast<byte>(1);
            } else {
                B[i][j] = static_cast<byte>(0);
            }
            C[i][j] = 0;
        }
    }

}

/**
 * La función "compararmatrices" compara dos matrices de tamaño n x n y devuelve verdadero si son
 * igual y falso de lo contrario.
 *
 * @param a a es un puntero a una matriz 2D de enteros.Representa la primera matriz.
 * @param B El parámetro "B" es una matriz 2D de enteros.
 * @param n El parámetro `n` representa el tamaño de las matrices cuadradas` a` y `b`.
 *
 * @return La función `compararmatrices` devuelve un valor booleano.Devuelve 'verdadero' si las matrices
 * `A` y` B` son iguales, y `falso` de lo contrario.
 */
bool compararMatrices(int **A, int **B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool compararMatricesByte(int **A, byte **B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != static_cast<int>(B[i][j])) {
                return false;
            }
        }
    }
    return true;
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
void AlgoritmoTradicional(byte **A, byte **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += static_cast<int>(A[i][k]) * static_cast<int>(B[k][j]);
            }
        }
    }
}

void AlgoritmoTradicionalALE(byte **A, byte **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            int r = static_cast<int>(A[i][k]);
            for (int j = 0; j < size; j++) {
                C[i][j] += r * static_cast<int>(B[k][j]);
            }
        }
    }
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
void DR1(byte **A, byte **B, int **C, int row, int col, int size) {
    if (size == 2) {
        C[row][col] += static_cast<int>(A[row][col]) * static_cast<int>(B[row][col]) + static_cast<int>(A[row][col+1]) * static_cast<int>(B[row+1][col]);
        C[row][col+1] += static_cast<int>(A[row][col]) * static_cast<int>(B[row][col+1]) + static_cast<int>(A[row][col+1]) * static_cast<int>(B[row+1][col+1]);
        C[row+1][col] += static_cast<int>(A[row+1][col]) * static_cast<int>(B[row][col]) + static_cast<int>(A[row+1][col+1]) * static_cast<int>(B[row+1][col]);
        C[row+1][col+1] += static_cast<int>(A[row+1][col]) * static_cast<int>(B[row][col+1]) + static_cast<int>(A[row+1][col+1]) * static_cast<int>(B[row+1][col+1]);
    } else {
        int newSize = size / 2;
        DR1(A, B, C, row, col, newSize);
        DR1(A, B, C, row, col + newSize, newSize);
        DR1(A, B, C, row + newSize, col, newSize);
        DR1(A, B, C, row + newSize, col + newSize, newSize);
        
        // for (int i = 0; i < newSize; i++) {
        //     for (int j = 0; j < newSize; j++) {
        //         C[row + i][col + j] += C[row + i][col + j + newSize] + C[row + i + newSize][col + j] + C[row + i + newSize][col + j + newSize];
        //     }
        // }
    }
}

// void multiply_matrices(byte **a, byte **b, int **c, int row, int col, int size) {
//     if (size == 1) {
//         c[row][col] += static_cast<int>(a[row][row]) * static_cast<int>(b[row][col]);
//     } else {
//         int newSize = size / 2;
//         // Multiplicar las submatrices superiores izquierdas
//         multiply_matrices(a, b, c, row, col, newSize);
//         // Multiplicar las submatrices superiores derechas
//         multiply_matrices(a, b, c, row, col + newSize, newSize);
//         // Multiplicar las submatrices inferiores izquierdas
//         multiply_matrices(a, b, c, row + newSize, col, newSize);
//         // Multiplicar las submatrices inferiores derechas
//         multiply_matrices(a, b, c, row + newSize, col + newSize, newSize);
//         // Combinar las submatrices para obtener la matriz resultante
//         for (int i = 0; i < newSize; i++) {
//             for (int j = 0; j < newSize; j++) {
//                 c[row + i][col + j] += c[row + i][col + j + newSize] + c[row + i + newSize][col + j] + c[row + i + newSize][col + j + newSize];
//             }
//         }
//     }
// }

// void multiply_matrices1(byte **a, byte **b, int **c, int row, int col, int size) {
//     if (size == 2) {
//         int a11 = static_cast<int>(a[row][col]);
//         int a12 = static_cast<int>(a[row][col + 1]);
//         int a21 = static_cast<int>(a[row + 1][col]);
//         int a22 = static_cast<int>(a[row + 1][col + 1]);
//         int b11 = static_cast<int>(b[row][col]);
//         int b12 = static_cast<int>(b[row][col + 1]);
//         int b21 = static_cast<int>(b[row + 1][col]);
//         int b22 = static_cast<int>(b[row + 1][col + 1]);
//         c[row][col] += a11 * b11 + a12 * b21;
//         c[row][col + 1] += a11 * b12 + a12 * b22;
//         c[row + 1][col] += a21 * b11 + a22 * b21;
//         c[row + 1][col + 1] += a21 * b12 + a22 * b22;
//     } else {
//         int newSize = size / 2;
//         // Multiplicar las submatrices superiores izquierdas
//         multiply_matrices(a, b, c, row, col, newSize);
//         // Multiplicar las submatrices superiores derechas
//         multiply_matrices(a, b, c, row, col + newSize, newSize);
//         // Multiplicar las submatrices inferiores izquierdas
//         multiply_matrices(a, b, c, row + newSize, col, newSize);
//         // Multiplicar las submatrices inferiores derechas
//         multiply_matrices(a, b, c, row + newSize, col + newSize, newSize);
//         //Combinar las submatrices para obtener la matriz resultante
//         for (int i = 0; i < newSize; i++) {
//             for (int j = 0; j < newSize; j++) {
//                 c[row + i][col + j] += c[row + i][col + j + newSize] + c[row + i + newSize][col + j] + c[row + i + newSize][col + j + newSize];
//             }
//         }
//     }
// }

void mostrarMatrizByte(byte **M, int size) {
    for (int i = 0; i < size; i++) {
        cout << "[";
        for (int j = 0; j < size; j++) {
            cout << static_cast<int>(M[i][j]) << " ";
        }
        cout << "]" << endl;
    }
}

void mostrarMatrizInt(int **M, int size) {
    for (int i = 0; i < size; i++) {
        cout << "[";
        for (int j = 0; j < size; j++) {
            cout << M[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

void llenarMatricesRandomByte(byte ** A, byte **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        A[i] = new byte[size];
        B[i] = new byte[size];
        C[i] = new int[size];
        for (int j = 0; j < size; j++) {
            A[i][j] = static_cast<byte>(rand() % (MAXIMO - MINIMO + 1) + MINIMO);
            B[i][j] = static_cast<byte>(rand() % (MAXIMO - MINIMO +1 ) + MINIMO);
            C[i][j] = 0;
        }
    }
}
void llenarMatricesRandomInt(int ** A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        A[i] = new int[size];
        B[i] = new int[size];
        C[i] = new int[size];
        for (int j = 0; j < size; j++) {
            A[i][j] = rand() % (MAXIMO - MINIMO + 1) + MINIMO;
            B[i][j] = rand() % (MAXIMO - MINIMO +1 ) + MINIMO;
            C[i][j] = 0;
        }
    }
}


void sumarMatrices(int **matrixA, int **matrixB, int **matrixC, int n) {
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

void restarMatrices(int **matrixA, int **matrixB, int **matrixC, int n){
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            matrixC[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
}

void strassen(int **matrixA, int **matrixB, int **matrixC, int n) {
    
    // if(n == 1)
    // {
    //     matrixC[0][0] = matrixA[0][0] * matrixB[0][0];
    
    // } 
    // else if (n == 2)
    // {
    //     int p1 = matrixA[0][0] * (matrixB[0][1] - matrixB[1][1]);
    //     int p2 = (matrixA[0][0] + matrixA[0][1]) * matrixB[1][1];
    //     int p3 = (matrixA[1][0] + matrixA[1][1]) * matrixB[0][0];
    //     int p4 = matrixA[1][1] * (matrixB[1][0] - matrixB[0][0]);
    //     int p5 = (matrixA[0][0] + matrixA[1][1]) * (matrixB[0][0] + matrixB[1][1]);
    //     int p6 = (matrixA[0][1] - matrixA[1][1]) * (matrixB[1][0] + matrixB[1][1]);
    //     int p7 = (matrixA[0][0] - matrixA[1][0]) * (matrixB[0][0] + matrixB[0][1]);
    //     matrixC[0][0] = p5 + p4 - p2 + p6;
    //     matrixC[0][1] = p1 + p2;
    //     matrixC[1][0] = p3 + p4;
    //     matrixC[1][1] = p5 + p1 - p3 - p7;
    // }
    // else if (n == 16)
    // {
    // // Algoritmo de multiplicación de matrices estándar para n == 16
    //     for (int i = 0; i < 16; i++)
    //     {
    //         for (int j = 0; j < 16; j++)
    //         {
    //             matrixC[i][j] = 0;
    //             for (int k = 0; k < 16; k++)
    //             {
    //                 matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
    //             }
    //         }
    //     }
    // }
    if (n == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                matrixC[i][j] = 0;
                for (int k = 0; k < 2; k++)
                {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }   
    }
    else
    {
        int **A11,**A12,**A21,**A22,**B11,**B12,**B21,**B22,**C11,**C12,**C21,**C22,**M1,**M2,**M3,**M4,**M5,**M6,**M7;
        int **matrixTemp1, **matrixTemp2;
        
        A11 = new int*[n/2];
        A12 = new int*[n/2];
        A21 = new int*[n/2];
        A22 = new int*[n/2];
        
        B11 = new int*[n/2];
        B12 = new int*[n/2];
        B21 = new int*[n/2];
        B22 = new int*[n/2];
        
        C11 = new int*[n/2];
        C12 = new int*[n/2];
        C21 = new int*[n/2];
        C22 = new int*[n/2];
        
        M1 = new int*[n/2];
        M2 = new int*[n/2];
        M3 = new int*[n/2];
        M4 = new int*[n/2];
        M5 = new int*[n/2];
        M6 = new int*[n/2];
        M7 = new int*[n/2];
        
        matrixTemp1 = new int*[n/2];
        matrixTemp2 = new int*[n/2];
        
        for(int i=0;i<n/2;i++)
        {
            A11[i] = new int[n/2];
            A12[i] = new int[n/2];
            A21[i] = new int[n/2];
            A22[i] = new int[n/2];
            B11[i] = new int[n/2];
            B12[i] = new int[n/2];
            B21[i] = new int[n/2];
            B22[i] = new int[n/2];
            C11[i] = new int[n/2];
            C12[i] = new int[n/2];
            C21[i] = new int[n/2];
            C22[i] = new int[n/2];
            
            M1[i] = new int[n/2];
            M2[i] = new int[n/2];
            M3[i] = new int[n/2];
            M4[i] = new int[n/2];
            M5[i] = new int[n/2];
            M6[i] = new int[n/2];
            M7[i] = new int[n/2];
            
            matrixTemp1[i] = new int[n/2];
            matrixTemp2[i] = new int[n/2];
            
            memset(A11[i],0,n/2*sizeof(int));
            memset(A12[i],0,n/2*sizeof(int));
            memset(A21[i],0,n/2*sizeof(int));
            memset(A22[i],0,n/2*sizeof(int));
            memset(B11[i],0,n/2*sizeof(int));
            memset(B12[i],0,n/2*sizeof(int));
            memset(B21[i],0,n/2*sizeof(int));
            memset(B22[i],0,n/2*sizeof(int));
            memset(C11[i],0,n/2*sizeof(int));
            memset(C12[i],0,n/2*sizeof(int));
            memset(C22[i],0,n/2*sizeof(int));
            memset(M1[i],0,n/2*sizeof(int));
            memset(M2[i],0,n/2*sizeof(int));
            memset(M3[i],0,n/2*sizeof(int));
            memset(M4[i],0,n/2*sizeof(int));
            memset(M5[i],0,n/2*sizeof(int));
            memset(M6[i],0,n/2*sizeof(int));
            memset(M7[i],0,n/2*sizeof(int));
            memset(matrixTemp1[i],0,n/2*sizeof(int));
            memset(matrixTemp2[i],0,n/2*sizeof(int));
        }
        
        for(int i=0;i<n/2;i++)
        {
            for(int j=0;j<n/2;j++)
            {
                A11[i][j] = matrixA[i][j];
                A12[i][j] = matrixA[i][j+n/2];
                A21[i][j] = matrixA[i+n/2][j];
                A22[i][j] = matrixA[i+n/2][j+n/2];
                
                B11[i][j] = matrixB[i][j];
                B12[i][j] = matrixB[i][j+n/2];
                B21[i][j] = matrixB[i+n/2][j];
                B22[i][j] = matrixB[i+n/2][j+n/2];
            }
        }

        //calculate M1
        sumarMatrices(A11,A22,matrixTemp1,n/2);
        sumarMatrices(B11,B22,matrixTemp2,n/2);
        strassen(matrixTemp1,matrixTemp2,M1,n/2);
        
        //calculate M2
        sumarMatrices(A21,A22,matrixTemp1,n/2);
        strassen(matrixTemp1,B11,M2,n/2);
        
        //calculate M3
        restarMatrices(B12,B22,matrixTemp1,n/2);
        strassen(A11,matrixTemp1,M3,n/2);
        
        //calculate M4
        restarMatrices(B21,B11,matrixTemp1,n/2);
        strassen(A22,matrixTemp1,M4,n/2);
        
        //calculate M5
        sumarMatrices(A11,A12,matrixTemp1,n/2);
        strassen(matrixTemp1,B22,M5,n/2);
        
        //calculate M6
        restarMatrices(A21,A11,matrixTemp1,n/2);
        sumarMatrices(B11,B12,matrixTemp2,n/2);
        strassen(matrixTemp1,matrixTemp2,M6,n/2);
        
        //calculate M7
        restarMatrices(A12,A22,matrixTemp1,n/2);
        sumarMatrices(B21,B22,matrixTemp2,n/2);
        strassen(matrixTemp1,matrixTemp2,M7,n/2);
        
        //C11
        sumarMatrices(M1,M4,C11,n/2);
        restarMatrices(C11,M5,C11,n/2);
        sumarMatrices(C11,M7,C11,n/2);
        
        //C12
        sumarMatrices(M3,M5,C12,n/2);
        
        //C21
        sumarMatrices(M2,M4,C21,n/2);
        
        //C22
        restarMatrices(M1,M2,C22,n/2);
        sumarMatrices(C22,M3,C22,n/2);
        sumarMatrices(C22,M6,C22,n/2);
        
        for(int i=0;i<n/2;i++)
        {
            for(int j=0;j<n/2;j++)
            {
                matrixC[i][j] = C11[i][j];
                matrixC[i][j+n/2] = C12[i][j];
                matrixC[i+n/2][j] = C21[i][j];
                matrixC[i+n/2][j+n/2] = C22[i][j];
            }
        }
        
        for(int i=0;i<n/2;i++)
        {
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
            
            delete[] M1[i];
            delete[] M2[i];
            delete[] M3[i];
            delete[] M4[i];
            delete[] M5[i];
            delete[] M6[i];
            delete[] M7[i];
            delete[] matrixTemp1[i];
            delete[] matrixTemp2[i];
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
        
        delete[] M1;
        delete[] M2;
        delete[] M3;
        delete[] M4;
        delete[] M5;
        delete[] M6;
        delete[] M7;
        delete[] matrixTemp1;
        delete[] matrixTemp2;
    }
}