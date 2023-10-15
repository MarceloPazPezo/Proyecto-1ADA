#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cmath>

// Función para multiplicar dos matrices con vectores
void multiplyMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
    int n = A.size();
    int m = B.size();
    int p = B[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            int sum = 0;
            for (int k = 0; k < m; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

// Función para guardar tiempos en un archivo
void saveTimesToFile(double time, const std::string& fileName, int matrixSize) {
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }
    file << "Tiempo promedio para matriz de " << matrixSize << "x" << matrixSize << ": " << time << " segundos" << std::endl;
    file.close();
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int sizeMatrix = 32, choice1 = 0, choice2 = 0;
    double averageTime, totalTime;

    std::cout << "Bienvenido, este código tiene dos modalidades para las cuales se entregará el tiempo de trabajo promedio después de 10 ejecuciones:\n";
    std::cout << "1.- Realizar la multiplicación de UNA matriz de valores específicos\n";
    std::cout << "2.- Multiplicación sucesiva desde una matriz inicial de 32x32 hasta una de las proporcionadas\n";
    std::cout << "3.- Salir\n";

    while (choice1 != 1 && choice1 != 2 && choice1 != 3) {
        std::cout << "(Por favor ingrese 1, 2 o 3 para seleccionar una opción): ";
        std::cin >> choice1;
    }

    if (choice1 == 1) {
        std::cout << "¿De qué tamaño desea que sea la matriz?\n";
        std::cout << "1.- [32x32]\n2.- [64x64]\n3.- [128x128]\n4.- [256x256]\n5.- [512x512]\n6.- [1024x1024]\n7.- [2048x2048]\n8.- [4096x4096]\n9.- Salir\n";

        while (choice2 < 1 || choice2 > 9) {
            std::cout << "(Por favor ingrese una opción válida): ";
            std::cin >> choice2;
        }

        if (choice2 != 9) {
            int sizeMatrix = 32 * static_cast<int>(std::pow(2, choice2 - 1));
            averageTime = 0;

            for (int repetition = 0; repetition < 10; ++repetition) {
                std::vector<std::vector<int>> matrix1(sizeMatrix, std::vector<int>(sizeMatrix));
                std::vector<std::vector<int>> matrix2(sizeMatrix, std::vector<int>(sizeMatrix));
                std::vector<std::vector<int>> resultMatrix(sizeMatrix, std::vector<int>(sizeMatrix, 0));

                // Inicializar matrix1 y matrix2 con valores aleatorios
                for (int i = 0; i < sizeMatrix; i++) {
                    for (int j = 0; j < sizeMatrix; j++) {
                        matrix1[i][j] = rand() % 128;
                        matrix2[i][j] = rand() % 128;
                    }
                }

                totalTime = 0;

                clock_t start = clock();
                // Multiplicar las matrices con la función
                multiplyMatrices(matrix1, matrix2, resultMatrix);
                clock_t end = clock();

                double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
                totalTime += time;

                averageTime += totalTime;
            }

            averageTime /= 10;

            std::cout << "Tiempo promedio multiplicación de matrices [" << sizeMatrix << "x" << sizeMatrix << "]: " << averageTime << " segundos." << std::endl;
            saveTimesToFile(averageTime, "tiempos.txt", sizeMatrix);
        }
    } else if (choice1 == 2) {
        int choice2 = 0;

        std::cout << "¿Hasta qué tamaño de matriz desea calcular los tiempos?\n";
        std::cout << "1.- [32x32]\n2.- [64x64]\n3.- [128x128]\n4.- [256x256]\n5.- [512x512]\n6.- [1024x1024]\n7.- [2048x2048]\n8.- [4096x4096]\n9.- Salir\n";

        while (choice2 < 1 || choice2 > 9) {
            std::cout << "(Por favor ingrese un valor entre 1 y 9): ";
            std::cin >> choice2;
        }

        if (choice2 != 9) {
            int targetSize = 32 * static_cast<int>(std::pow(2, choice2 - 1));

            while (sizeMatrix <= targetSize) {
                averageTime = 0;

                for (int repetition = 0; repetition < 10; ++repetition) {
                    std::vector<std::vector<int>> matrix1(sizeMatrix, std::vector<int>(sizeMatrix));
                    std::vector<std::vector<int>> matrix2(sizeMatrix, std::vector<int>(sizeMatrix));
                    std::vector<std::vector<int>> resultMatrix(sizeMatrix, std::vector<int>(sizeMatrix, 0));

                    // Inicializar matrix1 y matrix2 con valores aleatorios
                    for (int i = 0; i < sizeMatrix; i++) {
                        for (int j = 0; j < sizeMatrix; j++) {
                            matrix1[i][j] = rand() % 128;
                            matrix2[i][j] = rand() % 128;
                        }
                    }

                    totalTime = 0;

                    clock_t start = clock();
                    // Multiplicar las matrices con la función
                    multiplyMatrices(matrix1, matrix2, resultMatrix);
                    clock_t end = clock();

                    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
                    totalTime += time;

                    averageTime += totalTime;
                }

                averageTime /= 10;

                std::cout << "Tiempo promedio multiplicación de matrices [" << sizeMatrix << "x" << sizeMatrix << "]: " << averageTime << " segundos." << std::endl;
                saveTimesToFile(averageTime, "tiempos.txt", sizeMatrix);
                sizeMatrix *= 2;
            }
        }
    }

    return 0;
}
