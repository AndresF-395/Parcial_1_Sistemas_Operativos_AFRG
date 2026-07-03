# MLQ Scheduler Simulation - C++ (Multilevel Queue Scheduling)

## Description

MLQ Scheduler Simulation is an academic project developed in **C++** using **Object-Oriented Programming (OOP)** principles. The project implements a simulation of the **Multilevel Queue (MLQ) Scheduling algorithm**, commonly used in operating systems for process scheduling and CPU resource management.

The simulator reads process definitions from external text files, distributes processes into multiple scheduling queues, executes them according to their scheduling policy, and calculates important execution metrics.

The implemented MLQ configuration uses:

- Queue 1 → Round Robin (Quantum = 1)
- Queue 2 → Round Robin (Quantum = 3)
- Queue 3 → Shortest Job First (SJF)

The implementation focuses on modularity, maintainability, and scalability using an object-oriented architecture.

---

# Features

- Implementation of the **Multilevel Queue Scheduling (MLQ)** algorithm
- Queue 1 using **Round Robin (Quantum = 1)**
- Queue 2 using **Round Robin (Quantum = 3)**
- Queue 3 using **Shortest Job First (SJF)**
- Dynamic process loading from text files
- Automatic process assignment to corresponding queues
- Waiting Time calculation with cumulative waiting periods
- Response Time calculation
- Completion Time calculation
- Turnaround Time calculation
- Average metric generation
- Automatic output file generation
- Object-oriented modular architecture
- Compatible with **CLion + CMake**
- Ready to execute directly after cloning from GitHub

---

# Technologies Used

- C++
- CMake
- Object-Oriented Programming (OOP)
- Standard Template Library (STL)
- File Handling
- Scheduling Algorithms
- CLion IDE

---

# Project Structure

```text
ProyectoMLQ/
│
├── .vscode/
│
├── cmake-build-debug/
│   ├── input.txt
│   ├── output.txt
│   │
│   ├── CMakeFiles/
│   ├── Testing/
│   │   └── Temporary/
│   │
│   ├── ProyectoMLQ.exe
│   ├── build.ninja
│   ├── cmake_install.cmake
│
├── FileManager.cpp
├── FileManager.h
│
├── Process.cpp
├── Process.h
│
├── Queue.cpp
├── Queue.h
│
├── Scheduler.cpp
├── Scheduler.h
│
├── main.cpp
│
├── CMakeLists.txt
├── CMakeCache.txt
│
└── .gitattributes
```

---

# Main Components

## Process

Represents an individual process inside the scheduling simulation.

Responsibilities:

- Store process information
- Store execution metrics
- Track remaining execution time
- Track execution state

Main attributes:

- Process label
- Burst Time
- Arrival Time
- Queue number
- Priority
- Remaining Time
- Waiting Time
- Completion Time
- Response Time
- Turnaround Time

---

## Queue

Represents an execution queue inside the MLQ scheduler.

Responsibilities:

- Store processes
- Apply scheduling rules
- Manage Round Robin quantum
- Execute scheduling logic

Implemented scheduling policies:

### Queue 1

```text
Round Robin (Quantum = 1)
```

### Queue 2

```text
Round Robin (Quantum = 3)
```

### Queue 3

```text
Shortest Job First (SJF)
```

---

## Scheduler

Acts as the central system controller.

Responsibilities:

- Manage all queues
- Control global simulation time
- Dispatch processes
- Execute scheduling logic
- Compute metrics

MLQ execution priority:

```text
If Queue 1 contains processes:

        Execute Queue 1

Else if Queue 2 contains processes:

        Execute Queue 2

Else:

        Execute Queue 3
```

Priority order:

```text
Queue 1 > Queue 2 > Queue 3
```

---

## FileManager

Handles file operations.

Responsibilities:

- Read input files
- Parse process definitions
- Create Process objects
- Generate output files
- Export execution metrics

---

# Input Format

The simulator receives process definitions from:

```text
cmake-build-debug/input.txt
```

Example:

```txt
# Label;BT;AT;Q;Priority

A;6;0;1;5
B;9;0;1;4
C;10;0;2;3
D;15;0;2;3
E;8;0;3;2
```

Where:

| Field | Description |
|---|---|
| Label | Process identifier |
| BT | Burst Time |
| AT | Arrival Time |
| Q | Queue number |
| Priority | Process priority |

---

# Output Format

The simulator automatically generates:

```text
cmake-build-debug/output.txt
```

Example:

```txt
Label;BT;AT;Q;Pr;WT;RT;CT;TAT

A;6;0;1;5;3;0;9;9
B;9;0;1;4;6;3;15;15
C;10;0;2;3;20;15;30;30

# WT=23.5; CT=35.5; RT=19.5; TAT=35.5;
```

---

# Metrics Definition

## Waiting Time (WT)

Waiting Time represents all the time a process spends outside the processor.

Includes:

- Time before first execution
- Waiting after preemption
- Additional waiting between executions

Formula:

```text
WT = Total time outside CPU - arrival time
```

---

## Completion Time (CT)

Represents the exact moment when the process finishes execution.

Formula:

```text
CT = Final execution instant
```

---

## Turnaround Time (TAT)

Represents total elapsed execution time.

Formula:

```text
TAT = CT − AT
```

---

## Response Time (RT)

Represents the first interaction of the process with the CPU.

Formula:

```text
RT = First execution time 
```

---

# Installation

## Requirements

- C++ compiler with C++17 support
- CMake
- CLion IDE

---

# Clone the repository

```bash
git clone https://github.com/AndresF-395/Parcial_1_Sistemas_Operativos_AFRG.git
```

---

# Open the project

Open the project in **CLion**.

CLion automatically detects:

- CMakeLists.txt
- Source files
- Header files

---

# Build the project

Inside CLion:

```text
Build → Build Project
```

or:

```bash
cmake .
make
```

---

# Run the project

Execute:

```text
main.cpp
```

The program automatically:

1. Reads:

```text
cmake-build-debug/input.txt
```

2. Creates Process objects

3. Assigns processes to queues

4. Executes:

```text
Q1 → RR(1)
Q2 → RR(3)
Q3 → SJF
```

5. Computes:

- Waiting Time
- Response Time
- Completion Time
- Turnaround Time

6. Generates:

```text
cmake-build-debug/output.txt
```

---

# Example Workflow

```text
input.txt
      ↓

Read process data
      ↓

Create Process objects
      ↓

Assign processes to queues
      ↓

Execute MLQ Scheduler

(Q1 → RR(1))
(Q2 → RR(3))
(Q3 → SJF)

      ↓

Calculate metrics
      ↓

Generate output.txt
```

---

# Object-Oriented Architecture

The project follows an Object-Oriented Programming approach:

- **Process**
    - Represents process entities and execution metrics

- **Queue**
    - Manages scheduling behavior and algorithms

- **Scheduler**
    - Controls the global scheduling process

- **FileManager**
    - Handles file reading and writing operations

---

# Repository

GitHub repository:

https://github.com/AndresF-395/Parcial_1_Sistemas_Operativos_AFRG/tree/main

---

# Authors

Developed by:

- Andrés Felipe Rodríguez García

---

# License

This project was developed for academic and educational purposes.
