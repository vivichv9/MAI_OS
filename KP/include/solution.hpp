#ifndef KP_SOLUTION_HPP
#define KP_SOLUTION_HPP

#include <iostream>
#include <fstream>
#include <set>
#include <functional>
#include <vector>
#include <string>
#include <sys/wait.h>
#include <thread>
#include <queue>
#include <unordered_set>
#include "unistd.h"
#include <cstdlib>
#include "inipp.h"

namespace kp {

std::vector<std::string> split(const std::string& str);

void executeJob(const std::string& job);

void processJob(const std::string& job, const std::map<std::string, std::vector<std::string>>& dependencies,
           std::unordered_set<std::string>& visitedJobs);

bool hasCycle(const std::map<std::string, std::vector<std::string>>& jobs, const std::string& currentJob,
              std::set<std::string>& visited, std::set<std::string>& recursionStack);

bool isValidDAG(const std::map<std::string, std::vector<std::string>>& jobs);

bool hasOnlyOneComponent(const std::map<std::string, std::vector<std::string>>& jobs);

bool hasStartAndEndJobs(const std::map<std::string, std::vector<std::string>>& jobs);

}

#endif //KP_SOLUTION_HPP
