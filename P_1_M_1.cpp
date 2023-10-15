#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <fstream>

// Función para multiplicar dos matrices con vectores
std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    int m = B.size();
    int p = B[0].size();

    std::vector<std::vector<int>> C(n, std::vector<int>(p, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Función para guardar tiempos en un archivo
void saveTimesToFile(double time, const std::string& fileName, int matrixSize) {
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }
    if (matrixSize == 32) {
        file << "---------------------------------------\n";
    }
    file << "Tiempo promedio para matriz de " << matrixSize << "x" << matrixSize << ": " << time << " segundos" << std::endl;
    file.close();
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int sizeMatrix = 32, choice1 = 0, choice2 = 0;
    double averageTime, totalTime, totalAverageTime;
    int targetSize;

    std::cout << "Bienvenido, este código tiene dos modalidades para las cuales se entregará el tiempo de trabajo promedio después de 10 ejecuciones:\n";
    std::cout << "1.- Realizar la multiplicación de UNA matriz de valores específicos\n";
    std::cout << "2.- Multiplicación sucesiva desde una matriz inicial de 32x32 hasta una de las proporcionadas\n";
    std::cout << "3.- Salir\n";

    while (choice1 != 1 && choice1 != 2 && choice1 != 3) {
        std::cout << "(Por favor ingrese 1, 2 o 3 para seleccionar una opción): ";
        std::cin >> choice1;
    }

    switch (choice1) {
        case 1:
            std::cout << "¿De qué tamaño desea que sea la matriz?\n";
            std::cout << "1.- [32x32]\n2.- [64x64]\n3.- [128x128]\n4.- [256x256]\n5.- [512x512]\n6.- [1024x1024]\n7.- [2048x2048]\n8.- [4096x4096]\n9.- Salir\n";

            while (choice2 < 1 || choice2 > 9) {
                std::cout << "(Por favor ingrese una opción válida): ";
                std::cin >> choice2;
            }

            if (choice2 == 9) {
                break;
            }

            sizeMatrix = sizeMatrix * std::pow(2, choice2 - 1);
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
                resultMatrix = multiplyMatrices(matrix1, matrix2);
                clock_t end = clock();

                double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
                totalTime += time;

                averageTime = totalTime / 10;
            }

            std::cout << "Tiempo promedio multiplicación de matrices [" << sizeMatrix << "x" << sizeMatrix << "]: " << averageTime << " segundos." << std::endl;
            saveTimesToFile(averageTime, "tiempos.txt", sizeMatrix);

            break;

        case 2:
            std::cout << "¿Hasta qué tamaño de matriz desea calcular los tiempos?\n";
            std::cout << "1.- [32x32]\n2.- [64x64]\n3.- [128x128]\n4.- [256x256]\n5.- [512x512]\n6.- [1024x1024]\n7.- [2048x2048]\n8.- [4096x4096]\n9.- Salir\n";

            while (choice2 < 1 || choice2 > 9) {
                std::cout << "(Por favor ingrese un valor entre 1 y 9): ";
                std::cin >> choice2;
            }

            if (choice2 == 9) {
                break;
            }

            targetSize = sizeMatrix * std::pow(2, choice2 - 1);

            while (sizeMatrix <= targetSize) {
                totalAverageTime = 0;

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
                    resultMatrix = multiplyMatrices(matrix1, matrix2);
                    clock_t end = clock();

                    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
                    totalTime += time;

                    totalAverageTime = totalTime / 10;
                }

                std::cout << "Tiempo promedio multiplicación de matrices [" << sizeMatrix << "x" << sizeMatrix << "]: " << totalAverageTime << " segundos." << std::endl;
                saveTimesToFile(totalAverageTime, "tiempos.txt", sizeMatrix);
                sizeMatrix *= 2;
            }

            break;

        case 3:
            break;
    }

    return 0;
}
