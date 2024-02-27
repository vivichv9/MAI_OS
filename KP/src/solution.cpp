#include "solution.hpp"

std::vector<std::string> kp::split(const std::string& str) {
  std::istringstream iss(str);
  std::vector<std::string> strings;
  std::string s;

  while (getline(iss, s, ',')) {
    strings.push_back(s);
  }

  return strings;
}

void kp::executeJob(const std::string& job) {
  pid_t pid = fork();

  if (pid == -1) {
    throw std::runtime_error("Create process error!");
  }

  if (pid == 0) {
    sleep(1);
    exit(0);
  } else {
    std::cout << "Executing: " << job << std::endl;
    sleep(1);
    std::cout << "Exec completed: " << job << std::endl;
    wait(NULL);
  }
}

void kp::processJob(const std::string& job, const std::map<std::string, std::vector<std::string>>& dependencies,
                std::unordered_set<std::string>& visitedJobs) {

  if (visitedJobs.size() == dependencies.size()) {
    return;
  }

  if (visitedJobs.count(job) == 0) {
    visitedJobs.insert(job);
  }

  if (dependencies.count(job) > 0) {
    const std::vector<std::string>& currentDependencies = dependencies.at(job);

    if (currentDependencies.size() > 1) {
      std::vector<std::thread> threads;

      for (const auto& dependency : currentDependencies) {
        if (visitedJobs.count(dependency) == 0) {
          visitedJobs.insert(dependency);

          if (visitedJobs.size() == dependencies.size()) {
            threads.emplace_back(executeJob, dependency);

          } else {
            threads.emplace_back(processJob, job, std::ref(dependencies), std::ref(visitedJobs));
          }
        }
      }

      for (auto& thread : threads) {
        thread.join();
      }

    } else {
      for (const auto& dependency : currentDependencies) {
        if (visitedJobs.count(dependency) == 0) {
          visitedJobs.insert(dependency);

          if (visitedJobs.size() == dependencies.size()) {
            executeJob(dependency);

          } else {
            processJob(dependency, dependencies, visitedJobs);
          }
        }
      }
    }
  }

  executeJob(job);
}

bool kp::hasCycle(const std::map<std::string, std::vector<std::string>>& jobs, const std::string& currentJob, std::set<std::string>& visited, std::set<std::string>& recursionStack) {
  visited.insert(currentJob);
  recursionStack.insert(currentJob);
  auto dependencies = jobs.at(currentJob);
  for (const auto& dependency : dependencies) {
    const std::string& dependencyJob = dependency;

    if (recursionStack.count(dependencyJob)) {
      return true;
    }

    if (!visited.count(dependencyJob) && hasCycle(jobs, dependencyJob, visited, recursionStack)) {
      return true;
    }
  }

  recursionStack.erase(currentJob);
  return false;
}

bool kp::isValidDAG(const std::map<std::string, std::vector<std::string>>& jobs) {
  std::set<std::string> visited;
  std::set<std::string> recursionStack;

  for (const auto& job : jobs) {
    if (!visited.count(job.first) && hasCycle(jobs, job.first, visited, recursionStack)) {
      return false;
    }
  }

  return true;
}

bool kp::hasOnlyOneComponent(const std::map<std::string, std::vector<std::string>>& jobs) {
  std::unordered_map<std::string, std::vector<std::string>> adjacencyList;
  std::set<std::string> visited;

  for (const auto& job : jobs) {
    const auto& dependencies = job.second;

    for (const auto& dependency : dependencies) {
      adjacencyList[dependency].push_back(job.first);
      adjacencyList[job.first].push_back(dependency);
    }
  }

  int componentCount = 0;

  for (const auto& job : jobs) {
    if (visited.count(job.first) == 0) {
      std::set<std::string> component;
      std::queue<std::string> q;

      q.push(job.first);
      visited.insert(job.first);

      while (!q.empty()) {
        std::string currentJob = q.front();
        q.pop();
        component.insert(currentJob);

        for (const auto& neighbor : adjacencyList[currentJob]) {
          if (visited.count(neighbor) == 0) {
            q.push(neighbor);
            visited.insert(neighbor);
          }
        }
      }

      componentCount++;
    }
  }

  return componentCount > 1;
}

bool kp::hasStartAndEndJobs(const std::map<std::string, std::vector<std::string>>& jobs) {
  std::set<std::string> startJobs;
  std::set<std::string> endJobs;

  for (const auto& job : jobs) {
    const auto& dependencies = job.second;
    if (dependencies.empty()) {
      startJobs.insert(job.first);
    }

    for (const auto& dependency : dependencies) {
      endJobs.erase(dependency);
    }

    endJobs.insert(job.first);
  }

  return !startJobs.empty() && !endJobs.empty();
}