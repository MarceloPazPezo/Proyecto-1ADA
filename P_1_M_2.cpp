#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

// Función para multiplicar dos matrices
std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<short>>& A, const std::vector<std::vector<short>>& B) {
    int n = A.size();
    int m = B.size();
    int p = B[0].size();

    std::vector<std::vector<int>> C(n, std::vector<int>(p, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                C[i][j] += static_cast<int>(A[i][k]) * B[k][j];
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
    file << "Tiempo en segundos para matriz de " << matrixSize << "x" << matrixSize << ": " << time / 10 << std::endl;
    file.close();
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int matrixSize = 32;

    while (matrixSize <= 4096) {
        double averageTime = 0;

        for (int repetition = 0; repetition < 10; ++repetition) {
            std::vector<std::vector<short>> matrix1(matrixSize, std::vector<short>(matrixSize));
            std::vector<std::vector<short>> matrix2(matrixSize, std::vector<short>(matrixSize));
            std::vector<std::vector<int>> resultMatrix(matrixSize, std::vector<int>(matrixSize));

            // Inicializar matrix1 y matrix2 con valores aleatorios
            for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    matrix1[i][j] = rand() % 128;
                    matrix2[i][j] = rand() % 128;
                }
            }

            clock_t start = clock();
            // Multiplicar las matrices
            resultMatrix = multiplyMatrices(matrix1, matrix2);
            clock_t end = clock();

            double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            averageTime += time;

            // Liberar la memoria de las matrices (no es necesario en C++)
        }

        averageTime /= 1;

        std::cout << "Tiempo promedio multiplicacion de matrices [" << matrixSize << "x" << matrixSize << "]: " << averageTime << " segundos." << std::endl;
        saveTimesToFile(averageTime, "tiempos.txt", matrixSize);
        matrixSize *= 2;
    }

    return 0;
}
