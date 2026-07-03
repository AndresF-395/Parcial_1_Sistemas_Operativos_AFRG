#include "Queue.h"
#include <algorithm>

// --- ROUND ROBIN POLICY ---
RoundRobinPolicy::RoundRobinPolicy(float q) : quantum(q) {}

std::shared_ptr<Process> RoundRobinPolicy::selectNext(std::vector<std::shared_ptr<Process>>& readyPool, 
                                                      std::shared_ptr<Process> currentRunning, 
                                                      float& quantumTracker) {
    if (readyPool.empty()) return nullptr;

    // Si hay un proceso en ejecución y aún no se vence su quantum, retenerlo
    if (currentRunning && quantumTracker < quantum) {
        for (auto& p : readyPool) {
            if (p == currentRunning) return p;
        }
    }

    // El quantum ha vencido o el proceso actual terminó
    quantumTracker = 0.0f;
    if (currentRunning && !readyPool.empty() && readyPool.front() == currentRunning) {
        // Enviar al final de la cola circular
        std::rotate(readyPool.begin(), readyPool.begin() + 1, readyPool.end());
    }

    return readyPool.front();
}

// --- SJF POLICY ---
std::shared_ptr<Process> SJFPolicy::selectNext(std::vector<std::shared_ptr<Process>>& readyPool, 
                                               std::shared_ptr<Process> currentRunning, 
                                               float& quantumTracker) {
    if (readyPool.empty()) return nullptr;
    // No-preemptivo: si ya hay uno ejecutándose, continuar hasta que termine
    if (currentRunning) {
        for (auto& p : readyPool) {
            if (p == currentRunning) return p;
        }
    }
    // Seleccionar el de menor Burst Time inicial
    auto minIt = readyPool.begin();
    for (auto it = readyPool.begin(); it != readyPool.end(); ++it) {
        if ((*it)->burstTime < (*minIt)->burstTime) {
            minIt = it;
        }
    }
    return *minIt;
}

// --- STCF POLICY ---
std::shared_ptr<Process> STCFPolicy::selectNext(std::vector<std::shared_ptr<Process>>& readyPool, 
                                                std::shared_ptr<Process> currentRunning, 
                                                float& quantumTracker) {
    (void)currentRunning; // Suprimir warnings de desuso
    (void)quantumTracker;
    if (readyPool.empty()) return nullptr;
    
    // Preemptivo: Buscar siempre el de menor tiempo restante a cada tick
    auto minIt = readyPool.begin();
    for (auto it = readyPool.begin(); it != readyPool.end(); ++it) {
        if ((*it)->remainingTime < (*minIt)->remainingTime) {
            minIt = it;
        }
    }
    return *minIt;
}

// --- PRIORITY POLICY ---
std::shared_ptr<Process> PriorityPolicy::selectNext(std::vector<std::shared_ptr<Process>>& readyPool, 
                                                    std::shared_ptr<Process> currentRunning, 
                                                    float& quantumTracker) {
    (void)currentRunning;
    (void)quantumTracker;
    if (readyPool.empty()) return nullptr;

    // Mayor valor numérico indica mayor prioridad externa
    auto maxIt = readyPool.begin();
    for (auto it = readyPool.begin(); it != readyPool.end(); ++it) {
        if ((*it)->priority > (*maxIt)->priority) {
            maxIt = it;
        }
    }
    return *maxIt;
}

// --- QUEUE IMPLEMENTATION ---
Queue::Queue(int queueId, std::unique_ptr<SchedulingPolicy> p)
    : id(queueId), policy(std::move(p)), currentRunningProcess(nullptr), quantumTracker(0.0f) {}

void Queue::addProcess(std::shared_ptr<Process> proc) {
    readyPool.push_back(proc);
}

std::shared_ptr<Process> Queue::selectNextProcess() {
    currentRunningProcess = policy->selectNext(readyPool, currentRunningProcess, quantumTracker);
    return currentRunningProcess;
}

void Queue::removeProcess(std::shared_ptr<Process> proc) {
    readyPool.erase(std::remove(readyPool.begin(), readyPool.end(), proc), readyPool.end());
    if (currentRunningProcess == proc) {
        currentRunningProcess = nullptr;
        quantumTracker = 0.0f;
    }
}

bool Queue::isEmpty() const {
    return readyPool.empty();
}

std::vector<std::shared_ptr<Process>>& Queue::getProcesses() {
    return readyPool;
}

void Queue::incrementQuantum() {
    quantumTracker += 1.0f;
}

void Queue::resetQuantum() {
    quantumTracker = 0.0f;
}