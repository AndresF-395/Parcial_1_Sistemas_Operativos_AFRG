#include "Scheduler.h"

Scheduler::Scheduler() : globalTime(0.0f) {}

void Scheduler::addProcess(std::shared_ptr<Process> proc) {
    allProcesses.push_back(proc);
}

void Scheduler::configureQueue(int queueId, std::unique_ptr<SchedulingPolicy> policy) {
    queues[queueId] = std::make_unique<Queue>(queueId, std::move(policy));
}

bool Scheduler::hasUnfinishedProcesses() const {
    for (const auto& proc : allProcesses) {
        if (!proc->isFinished) return true;
    }
    return false;
}

void Scheduler::runSimulation() {
    globalTime = 0.0f;

    while (hasUnfinishedProcesses()) {
        // 1. Despachar procesos recién llegados a sus respectivas colas
        for (auto& proc : allProcesses) {
            if (proc->arrivalTime <= globalTime && !proc->isQueued && !proc->isFinished) {
                if (queues.find(proc->queueId) != queues.end()) {
                    queues[proc->queueId]->addProcess(proc);
                    proc->isQueued = true;
                }
            }
        }

        // 2. Selección estricta de colas MLQ por prioridad (Q1 > Q2 > Q3)
        Queue* activeQueue = nullptr;
        for (int i = 1; i <= 3; ++i) {
            if (queues.find(i) != queues.end() && !queues[i]->isEmpty()) {
                activeQueue = queues[i].get();
                break; // Romper en el momento que se localiza la cola prioritaria con procesos listos
            }
        }

        if (activeQueue) {
            std::shared_ptr<Process> runningProc = activeQueue->selectNextProcess();

            if (runningProc) {
                // Cálculo de Response Time (RT) en la primera interacción de CPU
                if (!runningProc->started) {
                    runningProc->started = true;
                    runningProc->responseTime = globalTime - runningProc->arrivalTime;
                }

                // Ejecución atómica por un ciclo de reloj (1 unidad de tiempo)
                runningProc->remainingTime -= 1.0f;
                activeQueue->incrementQuantum();

                // Incremento exacto del Waiting Time (WT) para todo proceso relegado fuera del CPU
                for (auto& proc : allProcesses) {
                    if (proc->arrivalTime <= globalTime && !proc->isFinished && proc != runningProc) {
                        proc->waitingTime += 1.0f;
                    }
                }

                // Manejo de culminación del Proceso
                if (runningProc->remainingTime <= 0.0f) {
                    runningProc->isFinished = true;
                    runningProc->completionTime = globalTime + 1.0f;
                    // TAT = CompletionTime - ArrivalTime
                    runningProc->turnaroundTime = runningProc->completionTime - runningProc->arrivalTime;
                    activeQueue->removeProcess(runningProc);
                }
            }
        } else {
            // El procesador se encuentra en estado OCIOSO (Idle) esperando arribos subsecuentes.
        }

        globalTime += 1.0f;
    }
}

std::vector<std::shared_ptr<Process>> Scheduler::getResults() const {
    return allProcesses;
}