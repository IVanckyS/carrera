Carrera de Autos Multithreaded 
Descripcion:
Este proyecto simula una carrera de autos utilizando programacion multihilos en C++. Cada auto corre en un hilo separado y recorre una distancia aleatoria con pausas simulando velocidades variables. La carrera finaliza cuando todos los autos cruzan la meta, y se muestra el orden de llegada.
------------------------------------------------------------------------------------
Requisitos del sistema
Sistema operativo: Linux
Compilador: GNU g++ con soporte para C++11 o superior
Herramienta de construccion: make

------------------------------------------------------------------------------------

Estructura del Proyecto
carrera.cpp: Codigo fuente principal con la implementacio³n de la simulacion.
Makefile: Archivo para compilar el proyecto con make.
README.md: Este archivo con la documentacion del proyecto.

------------------------------------------------------------------------------------
Compilacion y Ejecucion
 Compilacion con Make
Desde el directorio del proyecto, ejecuta el siguiente comando en la terminal:
make

Esto ejecutara el archivo make que tiene como valores predeterminado una distancia de 100 metros con 3 autos

Para limpiar el ejecutable usar: make clean
------------------------------------------------------------------------------------
Para crear un ejecutable y poder usar otros valores usar:
g++ -std=c++11 -pthread carrera.cpp -o carrera

y para ejecutar usar:

./carrera 200 4

o los valores que usted desea.

------------------------------------------------------------------------------------
Detalles Tecnicos
Librerias utilizadas:

<iostream>: Para imprimir en la terminal.
<thread>: Para crear y gestionar hilos.
<mutex>: Para evitar problemas de concurrencia.
<random>: Para generar numeros aleatorios.
<chrono>: Para manejar los intervalos de tiempo.
Caracteristicas:

Cada auto tiene su propio hilo de ejecucion.
El auto avanza distancias aleatorias (maximo 10 metros) y espera pausas aleatorias (100-500 ms).
La carrera termina cuando todos los autos cruzan la meta y se muestra el orden de llegada.
------------------------------------------------------------------------------------


AUTORES: IVAN SALAS MOLINA y MARIA PAZ CONCHA
