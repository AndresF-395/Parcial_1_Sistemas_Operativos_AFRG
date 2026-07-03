#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <memory>
#include "Process.h"

// Interfaz del patrón Strategy para Políticas de Planificación
class SchedulingPolicy {
public:
    virtual ~SchedulingPolicy() = default;
    virtual std::shared_ptr<Process> selectNext(std::vector<std::shared_ptr<Process>>& readyPool, 
                                                std::shared_ptr<Process> currentRunning, 
                                                float& quantumTracker) = 0;
};

// Política 1: Round Robin (RR) - Soporta cualquier quantum mediante inicialización
class RoundRobinPolicy : public SchedulingPolicy {
private:
    float quantum;
public:
    explicit RoundRobinPolicy(float q);
    std::shared_ptr<Process> selectNext(std::vector<std::shared_ptr<Process>>& readyPool, 
                                        std::shared_ptr<Process> currentRunning, 
                                        float& quantumTracker) override;
};

// Política 2: Shortest Job First (SJF) No Preemptivo
class SJFPolicy : public SchedulingPolicy {
public:
    std::shared_ptr<Process> selectNext(std::vector<std::shared_ptr<Process>>& readyPool, 
                                        std::shared_ptr<Process> currentRunning, 
                                        float& quantumTracker) override;
};

// Clase Contenedora Queue (Cola de Planificación)
class Queue {
private:
    int id;
    std::unique_ptr<SchedulingPolicy> policy;
    std::vector<std::shared_ptr<Process>> readyPool;
    std::shared_ptr<Process> currentRunningProcess;
    float quantumTracker;

public:
    Queue(int queueId, std::unique_ptr<SchedulingPolicy> p);
    void addProcess(std::shared_ptr<Process> proc);
    std::shared_ptr<Process> selectNextProcess();
    void removeProcess(std::shared_ptr<Process> proc);
    bool isEmpty() const;
    std::vector<std::shared_ptr<Process>>& getProcesses();
    void incrementQuantum();
    void resetQuantum();
};

#endif // QUEUE_H