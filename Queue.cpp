#include "Queue.h"
#include <algorithm>

// --- ROUND ROBIN POLICY ---
RoundRobinPolicy::RoundRobinPolicy(float q) : quantum(q) {}

std::shared_ptr<Process> RoundRobinPolicy::selectNext(std::vector<std::shared_ptr<Process>>& readyPool, 
                                                      std::shared_ptr<Process> currentRunning, 
                                                      float& quantumTracker) {
    if (readyPool.empty()) return nullptr;

    // Si el proceso actual sigue en la cola y no ha superado el quantum asignado, retener CPU
    if (currentRunning && quantumTracker < quantum) {
        for (auto& p : readyPool) {
            if (p == currentRunning) return p;
        }
    }

    // El quantum expiró o el proceso terminó voluntariamente
    quantumTracker = 0.0f;
    if (currentRunning && !readyPool.empty() && readyPool.front() == currentRunning) {
        // Rotación de la cola: envía el elemento al final para cumplir el ciclo de Round Robin
        std::rotate(readyPool.begin(), readyPool.begin() + 1, readyPool.end());
    }

    return readyPool.front();
}

// --- SJF POLICY ---
std::shared_ptr<Process> SJFPolicy::selectNext(std::vector<std::shared_ptr<Process>>& readyPool, 
                                               std::shared_ptr<Process> currentRunning, 
                                               float& quantumTracker) {
    (void)quantumTracker; // Evitar advertencia de variable sin usar
    if (readyPool.empty()) return nullptr;
    
    // Al ser No-Preemptivo, si hay un proceso ejecutándose, se le respeta hasta el final
    if (currentRunning) {
        for (auto& p : readyPool) {
            if (p == currentRunning) return p;
        }
    }
    
    // Si la CPU está libre, busca el proceso con el menor Burst Time total
    auto minIt = readyPool.begin();
    for (auto it = readyPool.begin(); it != readyPool.end(); ++it) {
        if ((*it)->burstTime < (*minIt)->burstTime) {
            minIt = it;
        }
    }
    return *minIt;
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