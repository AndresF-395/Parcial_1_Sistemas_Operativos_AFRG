#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

std::vector<std::shared_ptr<Process>> FileManager::readInputFile(const std::string& filename) {
    std::vector<std::shared_ptr<Process>> processes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error crítico: Imposible abrir archivo de lectura " << filename << std::endl;
        return processes;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '#') continue; // Omitir comentarios explicativos

        std::stringstream ss(line);
        std::string label, token;
        float burstTime, arrivalTime;
        int queueId, priority;

        if (std::getline(ss, label, ';') && std::getline(ss, token, ';')) {
            burstTime = std::stof(token);
        } else continue;
        
        if (std::getline(ss, token, ';')) { arrivalTime = std::stof(token); } else continue;
        if (std::getline(ss, token, ';')) { queueId = std::stoi(token); } else continue;
        if (std::getline(ss, token, ';')) { priority = std::stoi(token); } else continue;

        processes.push_back(std::make_shared<Process>(label, burstTime, arrivalTime, queueId, priority));
    }

    file.close();
    return processes;
}

void FileManager::writeOutputFile(const std::string& filename, const std::vector<std::shared_ptr<Process>>& processes) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error crítico: Imposible abrir archivo de escritura " << filename << std::endl;
        return;
    }

    // Cabecera requerida por el estándar académico
    file << "Etiqueta;BT;AT;Q;Pr;WT;RT;CT;TAT\n";

    float totalWT = 0.0f, totalRT = 0.0f, totalCT = 0.0f, totalTAT = 0.0f;

    for (const auto& proc : processes) {
        file << proc->label << ";"
             << proc->burstTime << ";"
             << proc->arrivalTime << ";"
             << proc->queueId << ";"
             << proc->priority << ";"
             << proc->waitingTime << ";"
             << proc->responseTime << ";"
             << proc->completionTime << ";"
             << proc->turnaroundTime << "\n";

        totalWT += proc->waitingTime;
        totalRT += proc->responseTime;
        totalCT += proc->completionTime;
        totalTAT += proc->turnaroundTime;
    }

    float count = static_cast<float>(processes.size());
    if (count > 0) {
        file << std::fixed << std::setprecision(1);
        file << "WT=" << (totalWT / count) << "; "
             << "CT=" << (totalCT / count) << "; "
             << "RT=" << (totalRT / count) << "; "
             << "TAT=" << (totalTAT / count) << ";\n";
    }

    file.close();
}