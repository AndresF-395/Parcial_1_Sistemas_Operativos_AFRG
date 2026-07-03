#include <iostream>
#include "Scheduler.h"
#include "FileManager.h"
#include "Queue.h"
#include <fstream>

int main() {
    std::string inputFile = "input.txt";
    std::string outputFile = "output.txt";

    Scheduler scheduler;

    // Configuración Modular Estratégica de las Colas Multinivel
    // Q1 posee máxima prioridad y corre Round Robin con Quantum de 3
    scheduler.configureQueue(1, std::make_unique<RoundRobinPolicy>(3.0f));

    // Q2 posee prioridad media y corre Round Robin con Quantum de 5
    scheduler.configureQueue(2, std::make_unique<RoundRobinPolicy>(5.0f));

    // Q3 posee prioridad baja y corre Shortest Job First (Fácilmente intercambiable por STCF o Priority)
    scheduler.configureQueue(3, std::make_unique<SJFPolicy>());

    // Carga de Procesos desde el Sistema de Archivos
    // AHORA SOLO LEE EL ARCHIVO, NO LO SOBREESCRIBE
    auto processes = FileManager::readInputFile(inputFile);
    if (processes.empty()) {
        std::cerr << "Abortando: Ningún proceso válido para inicializar el sistema." << std::endl;
        std::cerr << "Por favor, verifica que 'input.txt' exista en el directorio correcto y tenga datos." << std::endl;
        return 1;
    }

    // Ingesta de Procesos al Scheduler
    for (const auto& proc : processes) {
        scheduler.addProcess(proc);
    }

    std::cout << "=========================================" << std::endl;
    std::cout << "Iniciando Simulador de Planificación MLQ" << std::endl;
    std::cout << "=========================================" << std::endl;

    scheduler.runSimulation();

    std::cout << "Simulacion finalizada exitosamente." << std::endl;
    std::cout << "Escribiendo reporte metrico en: " << outputFile << "..." << std::endl;

    // Volcado Final de Reportes
    auto results = scheduler.getResults();
    FileManager::writeOutputFile(outputFile, results);

    std::cout << "Proceso completado. Listo para revision." << std::endl;
    return 0;
}