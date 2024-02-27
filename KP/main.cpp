#include <iostream>
#include <fstream>

#include "solution.hpp"

int main() {
  std::string config_file_name;
  std::cin >> config_file_name;
  std::ifstream file(config_file_name);

  inipp::Ini<char> ini;
  ini.parse(file);

  auto parsed_config = ini.sections.at("jobs");
  std::map<std::string, std::vector<std::string>> job_map;

  for (auto& el : parsed_config) {
    job_map.insert({el.first, kp::split(el.second)});
  }

  if (!kp::isValidDAG(job_map)) {
    throw std::runtime_error("DAG contains a cycle ");
  }

  if (kp::hasOnlyOneComponent(job_map)) {
    throw std::runtime_error("DAG has more than one connectivity component");
  }

  if (!kp::hasStartAndEndJobs(job_map)) {
    throw std::runtime_error("DAG doesn't exist first oe end job");
  }

  std::cout << "DAG is valid!" << std::endl << std::endl;
  sleep(1);

  std::vector<std::string> jobs;

  jobs.reserve(job_map.size());
  for (const auto& job : job_map) {
    jobs.push_back(job.first);
  }

  std::unordered_set<std::string> visitedJobs;

  for (const std::string& job : jobs) {
    kp::processJob(job, job_map, visitedJobs);
  }

  std::cout << "All jobs completed!" << std::endl;

  return 0;
}