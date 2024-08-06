#ifndef PROCESS_SCHEDULER_HPP
#define PROCESS_SCHEDULER_HPP

#include <fstream>
#include <string>
#include <vector>

struct Process {
  unsigned int pid;
  unsigned int cpu_peak;
  unsigned int wait_time;
  std::string state;
};

// Leitura de arquivo
std::vector<Process> get_process_list(std::ifstream &file);

// Utils
bool compare_by_cpu_peak(const Process &a, const Process &b);

// Escalonadores
void fcfs_schedule(std::vector<Process> processes);
void sjf_schedule(std::vector<Process> processes);
void rr_schedule(std::vector<Process> processes, unsigned int quantum);

#endif
