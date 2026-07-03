#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "Process.h"

class FileManager {
public:
    static std::vector<std::shared_ptr<Process>> readInputFile(const std::string& filename);
    static void writeOutputFile(const std::string& filename, const std::vector<std::shared_ptr<Process>>& processes);
};

#endif // FILE_MANAGER_H