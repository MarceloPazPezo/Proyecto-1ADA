# Proyecto-1ADA

Objetivos:

- [X] [Algoritmo Tradicional](#algoritmo-tradicional)
- [ ] [Dr1](#dr1) (Algoritmo recursivo semejante al tradicional en tiempos)
- [ ] [Dr2](#dr2) (Algoritmo de Strassen n^2.81)

## Algoritmo Tradicional

El algoritmo tradicional se basa en la multiplicación de matrices de la siguiente forma:

```cpp
void AlgoritmoTradicional(byte **A, byte **B, int **C, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += static_cast<int>(A[i][k]) * static_cast<int>(B[k][j]);
            }
        }
    }
}
```

El cual tiene 8 multiplicaciones y 4 sumas por cada iteración del ciclo más 2 operaciones de asignación *(esto segun pepito)*, al realizar el analisis se obtiene que:
T(n) = 8T(n/2) + O(n^2) = O(n^3)

## DR1

El algoritmo DR1 se basa en la multiplicación de matrices de la siguiente forma:

```cpp

```

El cual tiene 8 multiplicaciones y 4 sumas por cada iteración del ciclo más 2 operaciones de asignación *(esto segun pepito)*, al realizar el analisis se obtiene que:
T(n) = 8T(n/2) + O(n^2) = O(n^log_2(8)) = O(n^3)

## DR2

El algoritmo DR2 se basa en la multiplicación de matrices de la siguiente forma:

```cpp

```

El cual tiene 7 multiplicaciones y varias sumas, al realizar el analisis se obtiene que:
T(n) = 7T(n/2) + O(n^2) = O(n^log_2(7)) = O(n^2.81)
