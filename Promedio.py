import matplotlib.pyplot as plt
import numpy as np

# Abrir el archivo en modo lectura
archivo = open("TiemposAT.txt", "r")

# Leer todas las líneas del archivo
lineas = archivo.readlines()

# Cerrar el archivo
archivo.close()

# Recorrer todas las líneas y separar los datos
con = 1
cantidadMuestras = 10
tiemposAuxiliar = []
algoritmo = ['Tradicional', 'Strassenb16', 'Strassenb2']
for a in algoritmo:
    for linea in lineas:
        datos = linea.strip().split(",")
        if datos[3] == a:
            n = int(datos[0])
            segundos = int(datos[1])
            nanosegundos = int(datos[2])
            algoritmoa = datos[3]
            tiempoExacto = segundos * 1e9 + (nanosegundos)
            tiempoExacto = tiempoExacto / 1e9
            if con<cantidadMuestras:
                tiemposAuxiliar.append(tiempoExacto)
                con += 1
            else:
                con = 1
                tiempoPromedio = sum(tiemposAuxiliar) / len(tiemposAuxiliar)
                tiemposAuxiliar.clear()
            
                with open("TiempoPromedio.txt", "a") as archivo:
                    archivo.write("{} & {:.5f} & {} \\\\ \n".format(n, tiempoPromedio, algoritmoa))
                    archivo.close()
