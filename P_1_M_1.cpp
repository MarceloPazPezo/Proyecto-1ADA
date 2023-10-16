#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

void multiplyMatrices(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& result) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int sizeMatriz = 32;
    int opc1 = 0, opc11 = 0, opc12 = 0, caso2 = 0;
    int rep = 0;
    double prom = 0;
    double promedioTiempo = 0;

    std::ofstream outputFile("tiemposATC++.txt", std::ios::app); // Abre el archivo fuera del switch

    std::cout << "Bienvenido, este código tiene dos modalidades para las cuales se entregará su tiempo de trabajo promedio después de 10 ejecuciones, \n1.- realizar la multiplicación de UNA matriz de valores específicos \n2.- multiplicación sucesiva desde una matriz inicial de 32x32 hasta una de las proporcionadas \n3.- Salir\n";

    while (opc1 != 1 && opc1 != 2 && opc1 != 3) {
        std::cout << "(por favor ingrese 1, 2 o 3 para seleccionar una opción)\n";
        std::cin >> opc1;
    }

    switch (opc1) {
        case 1:
            std::cout << "¿De qué tamaño desea que sea la matriz?\n";
            std::cout << "1.- [32x32]\n2.- [64x64]\n3.- [128x128]\n4.- [256x256]\n5.- [512x512]\n6.- [1024x1024]\n7.- [2048x2048]\n8.- [4096x4096]\n9.- Salir\n";
            
            while (opc11 < 1 || opc11 > 9) {
                std::cout << "(por favor ingrese una opción válida)\n";
                std::cin >> opc11;
            }

            if (opc11 == 9) {
                break;
            }

            sizeMatriz = sizeMatriz * std::pow(2, opc11 - 1);
            rep = 10;
            prom = 0;

            do {
                std::vector<std::vector<int>> Matriz1(sizeMatriz, std::vector<int>(sizeMatriz));
                std::vector<std::vector<int>> Matriz2(sizeMatriz, std::vector<int>(sizeMatriz));
                std::vector<std::vector<int>> Matriz3(sizeMatriz, std::vector<int>(sizeMatriz));

                // Inicializar Matriz1 y Matriz2 con valores aleatorios
                for (int i = 0; i < sizeMatriz; i++) {
                    for (int j = 0; j < sizeMatriz; j++) {
                        Matriz1[i][j] = std::rand() % 128;
                        Matriz2[i][j] = std::rand() % 128;
                    }
                }

                // Inicializar Matriz3 con ceros
                for (int i = 0; i < sizeMatriz; i++) {
                    for (int j = 0; j < sizeMatriz; j++) {
                        Matriz3[i][j] = 0;
                    }
                }

                clock_t start = std::clock();
                multiplyMatrices(Matriz1, Matriz2, Matriz3);
                clock_t end = std::clock();

                double tiempo = static_cast<double>(end - start) / CLOCKS_PER_SEC;

                prom += tiempo;
                rep--;

            } while (rep != 0);

            promedioTiempo = prom / 10;
            std::cout << "Tiempo promedio multiplicación matrices [" << sizeMatriz << " x " << sizeMatriz << "] = " << (promedioTiempo / 60) << " minutos | " << promedioTiempo << " segundos | " << (promedioTiempo * 1000) << " milisegundos\n";

            // Almacenar los resultados en el archivo de texto externo
            if (outputFile.is_open()) {
                outputFile << "------------------------------------------\n";
                outputFile << "Tiempo promedio multiplicación matrices [" << sizeMatriz << " x " << sizeMatriz << "] = " << (promedioTiempo / 60) << " minutos | " << promedioTiempo << " segundos | " << (promedioTiempo * 1000) << " milisegundos\n";
            }

            break;

        case 2:
            std::cout << "Hasta qué matriz desea calcular los tiempos?\n";
            std::cout << "1.- [32x32]\n2.- [64x64]\n3.- [128x128]\n4.- [256x256]\n5.- [512x512]\n6.- [1024x1024]\n7.- [2048x2048]\n8.- [4096x4096]\n9.- Salir\n";

            while (opc12 < 1 || opc12 > 9) {
                std::cout << "(por favor ingrese un valor entre 1 y 9)\n";
                std::cin >> opc12;
            }

            if (opc12 == 9) {
                break;
            }

            caso2 = sizeMatriz * std::pow(2, opc12 - 1);

            do {
                double promedio = 0;
                rep = 10;

                do {
                    std::vector<std::vector<int>> Matriz1(sizeMatriz, std::vector<int>(sizeMatriz));
                    std::vector<std::vector<int>> Matriz2(sizeMatriz, std::vector<int>(sizeMatriz));
                    std::vector<std::vector<int>> Matriz3(sizeMatriz, std::vector<int>(sizeMatriz));

                    // Inicializar Matriz1 y Matriz2 con valores aleatorios
                    for (int i = 0; i < sizeMatriz; i++) {
                        for (int j = 0; j < sizeMatriz; j++) {
                            Matriz1[i][j] = std::rand() % 128;
                            Matriz2[i][j] = std::rand() % 128;
                        }
                    }

                    // Inicializar Matriz3 con ceros
                    for (int i = 0; i < sizeMatriz; i++) {
                        for (int j = 0; j < sizeMatriz; j++) {
                            Matriz3[i][j] = 0;
                        }
                    }

                    clock_t start = std::clock();
                    multiplyMatrices(Matriz1, Matriz2, Matriz3);
                    clock_t end = std::clock();

                    double tiempo = static_cast<double>(end - start) / CLOCKS_PER_SEC;

                    promedio += tiempo;
                    rep--;

                } while (rep != 0);

                promedioTiempo = promedio / 10;
                std::cout << "Tiempo promedio multiplicación matrices [" << sizeMatriz << " x " << sizeMatriz << "] = " << (promedioTiempo / 60) << " minutos | " << promedioTiempo << " segundos | " << (promedioTiempo * 1000) << " milisegundos\n";
                // Almacenar los resultados en el archivo de texto externo
                if (outputFile.is_open()) {
                    if (sizeMatriz == 32)
                    {
                        outputFile << "------------------------------------------\n";
                    }
                    outputFile << "Tiempo promedio multiplicación matrices [" << sizeMatriz << " x " << sizeMatriz << "] = " << (promedioTiempo / 60) << " minutos | " << promedioTiempo << " segundos | " << (promedioTiempo * 1000) << " milisegundos\n";
                }
                sizeMatriz *= 2;

            } while (sizeMatriz <= caso2);

            break;

        case 3:
            break;
    }

    outputFile.close(); // Cerrar el archivo después del switch

    return 0;
}
