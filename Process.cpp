#include "Process.h"

Process::Process(std::string lbl, float bt, float at, int q, int pr)
    : label(lbl), burstTime(bt), arrivalTime(at), queueId(q), priority(pr),
      waitingTime(0.0f), completionTime(0.0f), responseTime(-1.0f),
      turnaroundTime(0.0f), remainingTime(bt), started(false),
      isQueued(false), isFinished(false) {}