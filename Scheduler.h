#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <memory>
#include <map>
#include "Process.h"
#include "Queue.h"

class Scheduler {
private:
    std::vector<std::shared_ptr<Process>> allProcesses;
    std::map<int, std::unique_ptr<Queue>> queues;
    float globalTime;

    bool hasUnfinishedProcesses() const;

public:
    Scheduler();
    void addProcess(std::shared_ptr<Process> proc);
    void configureQueue(int queueId, std::unique_ptr<SchedulingPolicy> policy);
    void runSimulation();
    std::vector<std::shared_ptr<Process>> getResults() const;
};

#endif // SCHEDULER_H