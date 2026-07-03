#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
public:
    // Atributos de Entrada
    std::string label;
    float burstTime;
    float arrivalTime;
    int queueId;
    int priority;

    // Métricas de Rendimiento del Sistema Operativo
    float waitingTime;
    float completionTime;
    float responseTime;
    float turnaroundTime;
    float remainingTime;

    // Variables de Control Auxiliares del Planificador
    bool started;
    bool isQueued;
    bool isFinished;

    // Constructor estructurado
    Process(std::string lbl, float bt, float at, int q, int pr);
};

#endif // PROCESS_H