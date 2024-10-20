# Variables
CXX = g++                      # Compilador
CXXFLAGS = -std=c++11 -Wall -Wextra -O2  # Flags del compilador
TARGET = carrera               # Nombre del ejecutable
DISTANCIA = 100                # Parámetro: distancia
AUTOS = 3                      # Parámetro: número de autos

# Regla principal
all: $(TARGET) run

# Regla para crear el ejecutable
$(TARGET): carrera.o
	$(CXX) $(CXXFLAGS) carrera.o -o $(TARGET)

# Regla para compilar el archivo objeto
carrera.o: carrera.cpp
	$(CXX) $(CXXFLAGS) -c carrera.cpp

# Regla para ejecutar el programa con parámetros
run:
	./$(TARGET) $(DISTANCIA) $(AUTOS)

# Regla para limpiar archivos generados
clean:
	rm -f *.o $(TARGET)

# Indica que estas reglas no corresponden a archivos
.PHONY: all clean run

