#include <iostream>
#include "Scheduler.h"
#include "FileManager.h"
#include "Queue.h"
#include <fstream>

int main() {
    std::string inputFile = "input.txt";
    std::string outputFile = "output.txt";

    Scheduler scheduler;

    // ASIGNACIÓN EXACTA DE COLAS MULTINIVEL SOLICITADAS:
    // Cola 1 (Prioridad Máxima): Round Robin con Quantum = 1
    scheduler.configureQueue(1, std::make_unique<RoundRobinPolicy>(1.0f));

    // Cola 2 (Prioridad Media): Round Robin con Quantum = 3
    scheduler.configureQueue(2, std::make_unique<RoundRobinPolicy>(3.0f));

    // Cola 3 (Prioridad Baja): Shortest Job First No-Preemptivo
    scheduler.configureQueue(3, std::make_unique<SJFPolicy>());

    // Carga dinámica de procesos desde archivo estructurado
    auto processes = FileManager::readInputFile(inputFile);
    if (processes.empty()) {
        std::cerr << "Abortando: Ningun proceso valido para inicializar el sistema." << std::endl;
        std::cerr << "Por favor, verifica que 'input.txt' exista en el directorio y contenga datos." << std::endl;
        return 1;
    }

    // Ingesta de Procesos al Scheduler
    for (const auto& proc : processes) {
        scheduler.addProcess(proc);
    }

    std::cout << "=========================================" << std::endl;
    std::cout << "Iniciando Simulador de Planificacion MLQ" << std::endl;
    std::cout << "Configuracion: Q1=RR(1) -> Q2=RR(3) -> Q3=SJF" << std::endl;
    std::cout << "=========================================" << std::endl;

    scheduler.runSimulation();

    std::cout << "Simulacion finalizada exitosamente." << std::endl;
    std::cout << "Escribiendo reporte metrico en: " << outputFile << "..." << std::endl;

    // Volcado de métricas finales
    auto results = scheduler.getResults();
    FileManager::writeOutputFile(outputFile, results);

    std::cout << "Proceso completado. Listo para revision." << std::endl;
    return 0;
}