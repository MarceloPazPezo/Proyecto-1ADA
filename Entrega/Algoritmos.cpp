/***
 * Algoritmos.cpp
 * Programa que implementa los algoritmos de multiplicacion de matrices
 * Fecha 16-10-2023
 * Autores:
 * - Bastian Rodriguez
 * - Marcelo Paz
 * - Nicolas Gomez
 * - Juan Henriquez
 * - Victor Lopez
 */

#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace chrono;

const int MINIMO = 0; // Valor minimo para los numeros random
const int MAXIMO = 128; // Valor maximo para los numeros random


void calcularTiempo(time_point<high_resolution_clock> inicio, time_point<high_resolution_clock> fin, int size, string algoritmo) {
    // Calcular tiempo y transformarlo a minutos, segundos y nanosegundos
    long long nanosegundos = duration_cast<nanoseconds>(fin - inicio).count();

    long long segundos = duration_cast<seconds>(nanoseconds(nanosegundos)).count();
    nanosegundos -= static_cast<long long>(segundos) * static_cast<long long>(1e9);

    cout << "Una matriz de " << size << "x" << size << " se demora " << segundos << " segundos y " << nanosegundos << " nanosegundos con el Algoritmo " << algoritmo << endl;
}

void llenarMatricesRandomIdentidad(int ** A, int ** B, int ** C, int size) {
    for (int i = 0; i < size; i++) {
        A[i] = new int[size];
        B[i] = new int[size];
        C[i] = new int[size];
        for (int j = 0; j < size; j++) {
            A[i][j] = rand() % (MAXIMO - MINIMO + 1) + MINIMO;
            if (i == j) {
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
            C[i][j] = 0;
        }
    }

}

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

void AlgoritmoTradicional(byte **A, byte **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += static_cast<int>(A[i][k]) * static_cast<int>(B[k][j]);
            }
        }
    }
}


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
    // // Inicializar la matriz C con ceros
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         C[i][j] = 0;
    //     }
    // }
    // Multiplicar las matrices de manera recursiva
    MultMatricesRecursivo(A, B, C, 0, 0, 0, 0, N);
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

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    int menu = 0, n = 0, muestras = 0;
    cout << "Ingrese N [32 a 4096]: " << endl;
    cout << ">>> ";
    cin >> n;
    cout << " " << endl;
    cout << "Ingrese cantidad de muestras [1 a 10]: " << endl;
    cout << ">>> ";
    cin >> muestras;
    cout << " " << endl;

    int **A = new int*[n];
    int **B = new int*[n];
    int **C = new int*[n];
    // int **AUX = new int*[n]; // Matriz para guardar resultados de forma auxiliar y poder comparar el resultado de 2 algoritmos

    cout << "Ingrese el algoritmo que desea ejecutar: " << endl;
    cout << "1. Algoritmo Tradicional" << endl;
    cout << "2. DR1" << endl;
    cout << "3. DR2 (Strassen)" << endl;
    // cout << "4. Compara matriz resultante tras multiplicar A x I = A" << endl;
    // cout << "5. Compara matriz resultante con otro algoritmo" << endl;
    cout << ">>> ";
    cin >> menu;
    cout << " " << endl;
    switch (menu)
    {
        case 1:
            for (int a = 0; a < muestras; a++)
            {
                if (a == 0)
                {
                    delete[] A;
                    delete[] B;
                }
                byte **Aaux = new byte*[n];
                byte **Baux = new byte*[n];

                llenarMatricesRandomByte(Aaux,Baux,C,n);
                

                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                AlgoritmoTradicional(Aaux, Baux, C, n);

                auto fin = high_resolution_clock::now();    // Tiempo final
                calcularTiempo(inicio, fin, n, "Tradicional");

            }
            break;

        case 2:
            for (int a = 0; a < muestras; a++)
            {
                llenarMatricesRandomInt(A,B,C,n);

                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                MultMatrices_2(A, B, C, n);

                auto fin = high_resolution_clock::now();    // Tiempo final
                calcularTiempo(inicio, fin, n, "DR1");
            }
            break;
        
        case 3:
            for (int a = 0; a < muestras; a++)
            {
                llenarMatricesRandomInt(A,B,C,n);

                auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
                strassen(A, B, C, n);

                auto fin = high_resolution_clock::now();    // Tiempo final
                calcularTiempo(inicio, fin, n, "Strassen");
            }
            break;

        // Funciones que en su momento me sirvieron para probar los algoritmos
        // case 4:
        //     for (int a = 0; a < 1; a++)
        //     {
        //         int opc1 = 0;
        //         do {
        //             cout << "Que algoritmo desea probar: " << endl;
        //             cout << "1. Algoritmo Tradicional" << endl;
        //             cout << "2. DR1" << endl;
        //             cout << "3. DR2" << endl;
        //             cout << "A1>>> ";
        //             cin >> opc1;
        //             if (opc1 < 1 || opc1 > 3)
        //             {
        //                 cout << "Opcion invalida" << endl;
        //             }
        //         } while (opc1 < 1 || opc1 > 3);
        //         cout << " " << endl;

        //         cout << "N: " << n << endl;
                
        //         llenarMatricesRandomIdentidad(A,B,C,n);

        //         auto inicio = high_resolution_clock::now();     // Tiempo inicial
                
        //         if (opc1 == 1)
        //         {
        //             // AlgoritmoTradicional(Aaux, Baux, C, n);
        //             cout << "Algoritmo Tradicional" << endl;
        //         }
        //         else if (opc1 == 2)
        //         {
        //             MultMatrices_2(A, B, C, n);
        //             cout << "DR1" << endl;
        //         }
        //         else if (opc1 == 3)
        //         {
        //             strassen(A,B,C,n);
        //             cout << "DR2" << endl;
        //         }

        //         auto fin = high_resolution_clock::now();    // Tiempo final

        //         // Calcular tiempo y transformarlo a minutos, segundos y nanosegundos
        //         long long nanosegundos = duration_cast<nanoseconds>(fin - inicio).count();

        //         long long segundos = duration_cast<seconds>(nanoseconds(nanosegundos)).count();
        //         nanosegundos -= static_cast<long long>(segundos) * static_cast<long long>(1e9);
        //         cout << "Tiempo: " << segundos << " segundos y " << nanosegundos << " nanosegundos" << endl;
                
        //         if (opc1 == 3 || opc1 == 2)
        //         {
        //              if (compararMatrices(C, A, n)) {
        //                 cout << "Las matrices A y C son iguales" << endl;
        //             } else {
        //                 cout << "Las matrices A y C son diferentes" << endl;
        //             }
        //         }

        //     }
        //     break;

        // case 5:
        //     for (int a = 0; a < 1; a++) {
        //         int opc1 = 0, opc2 = 0;
        //         do {
        //             cout << "Que algoritmo desea comparar: " << endl;
        //             cout << "1. Algoritmo Tradicional" << endl;
        //             cout << "2. DR1" << endl;
        //             cout << "3. DR2" << endl;
        //             cout << "A1>>> ";
        //             cin >> opc1;
        //             cout << "A2>>> ";
        //             cin >> opc2;
        //             if (opc1 == opc2 || opc1 < 1 || opc1 > 3 || opc2 < 1 || opc2 > 3)
        //             {
        //                 cout << "Opcion invalida" << endl;
        //             }
        //         } while (opc1 == opc2 || opc1 < 1 || opc1 > 3 || opc2 < 1 || opc2 > 3);
        //         cout << " " << endl;

        //         cout << "N: " << n << endl;

        //         int **Aaux = new int*[n];
        //         int **Baux = new int*[n];
                
        //         llenarMatricesRandomInt(Aaux,Baux,C,n);
        //         llenarMatricesRandomInt(Aaux,Baux,AUX,n);

        //         auto inicio = high_resolution_clock::now();     // Tiempo inicial

        //         if (opc1 == 1)
        //         {
        //             // AlgoritmoTradicional(A, B, C, n);
        //             cout << "Algoritmo Tradicional" << endl;
        //         }
        //         else if (opc1 == 2)
        //         {
        //             DR1(Aaux, Baux, C, 0, 0, 0, 0, n);
        //             cout << "DR1" << endl;
        //         }
        //         else if (opc1 == 3)
        //         {
        //             strassen(Aaux,Baux,C,n);
        //             cout << "DR2" << endl;
        //         }

        //         auto fin = high_resolution_clock::now();    // Tiempo final

        //         // Calcular tiempo y transformarlo a minutos, segundos y nanosegundos
        //         long long nanosegundos = duration_cast<nanoseconds>(fin - inicio).count();

        //         long long segundos = duration_cast<seconds>(nanoseconds(nanosegundos)).count();
        //         nanosegundos -= static_cast<long long>(segundos) * static_cast<long long>(1e9);
        //         cout << "Tiempo: " << segundos << " segundos y " << nanosegundos << " nanosegundos" << endl;
                
        //         inicio = high_resolution_clock::now();     // Tiempo inicial

        //         if (opc2 == 1)
        //         {
        //             // AlgoritmoTradicional(A, B, AUX, n);
        //             cout << "Algoritmo Tradicional" << endl;
        //         }
        //         else if (opc2 == 2)
        //         {
        //             DR1(Aaux, Baux, AUX, 0, 0, 0, 0, n);
        //             cout << "DR1" << endl;
        //         }
        //         else if (opc2 == 3)
        //         {
        //             strassen(Aaux,Baux,AUX,n);
        //             cout << "DR2" << endl;
        //         }


        //         fin = high_resolution_clock::now();    // Tiempo final

        //         // Calcular tiempo y transformarlo a minutos, segundos y nanosegundos
        //         nanosegundos = duration_cast<nanoseconds>(fin - inicio).count();

        //         segundos = duration_cast<seconds>(nanoseconds(nanosegundos)).count();
        //         nanosegundos -= static_cast<long long>(segundos) * static_cast<long long>(1e9);
        //         cout << "Tiempo: " << segundos << " segundos y " << nanosegundos << " nanosegundos" << endl;

        //         if (compararMatrices(C, AUX, n)) {
        //             cout << "Las matrices son iguales" << endl;
        //         } else {
        //             cout << "Las matrices son diferentes" << endl;
        //         }
        //     }
        //     break;
            
        default:
            break;
    }
    return 0;
}
