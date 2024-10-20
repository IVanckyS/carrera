#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <mutex>
#include <atomic>
#include <algorithm>

// Variables globales
std::mutex cout_mutex; // Para proteger el acceso a std::cout
std::atomic<int> lugar{1}; // Para controlar el orden de llegada

// Función para generar un número aleatorio en un rango dado
int generar_aleatorio(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// Función que representa la carrera de cada auto en una hebra
void carrera(int id, int M, std::vector<int>& posiciones, std::vector<int>& resultados) {
    int recorrido = 0;

    while (recorrido < M) {
        int avance = generar_aleatorio(1, 10);  // Avance entre 1 y 10 metros
        int tiempo = generar_aleatorio(100, 500); // Pausa entre 100 y 500 ms

        recorrido += avance;
        recorrido = std::min(recorrido, M); // Asegura que no supere la meta

        // Actualiza la posición del auto y muestra el avance en la terminal
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Auto" << id << " avanza " << avance 
                      << " metros (total: " << recorrido << " metros)\n";
        }

        // Actualiza la posición actual del auto
        posiciones[id] = recorrido;

        // Espera antes del siguiente avance
        std::this_thread::sleep_for(std::chrono::milliseconds(tiempo));
    }

    // Marca el lugar de llegada de este auto
    int lugar_actual = lugar.fetch_add(1);

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Auto" << id << " termina la carrera en el lugar " 
                  << lugar_actual << "!\n";
    }

    // Guarda el resultado final para este auto
    resultados[lugar_actual - 1] = id;
}

int main(int argc, char* argv[]) {
    // Verifica que se pasen los argumentos correctos
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <distancia_total> <num_autos>\n";
        return 1;
    }

    int M = std::stoi(argv[1]); // Distancia total
    int N = std::stoi(argv[2]); // Número de autos

    std::vector<int> posiciones(N, 0);      // Posición actual de cada auto
    std::vector<int> resultados(N, -1);     // Orden de llegada de los autos

    // Crea y lanza las hebras para cada auto
    std::vector<std::thread> hilos;
    for (int i = 0; i < N; ++i) {
        hilos.emplace_back(carrera, i, M, std::ref(posiciones), std::ref(resultados));
    }

    // Espera a que todas las hebras terminen
    for (auto& hilo : hilos) {
        hilo.join();
    }

    // Muestra los resultados finales
    std::cout << "\nLugar  Auto\n";
    std::cout << "--------------\n";
    for (int i = 0; i < N; ++i) {
        std::cout << (i + 1) << "      Auto" << resultados[i] << '\n';
    }

    return 0;
}
