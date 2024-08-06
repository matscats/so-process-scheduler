#include "process_scheduler.hpp"

#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

std::vector<Process> get_process_list(std::ifstream &file) {
  std::vector<Process> processes;
  Process p;

  while (file >> p.pid >> p.cpu_peak) {
    p.wait_time = 0;
    p.state = "Ready";
    processes.push_back(p);
  }
  return processes;
}

bool compare_by_cpu_peak(const Process &a, const Process &b) {
  return a.cpu_peak < b.cpu_peak;
}

void fcfs_schedule(std::vector<Process> processes) {
  unsigned int current_time = 0;
  unsigned int total_wait_time = 0;

  for (auto &process : processes) {
    process.wait_time = current_time;
    total_wait_time += process.wait_time;
    current_time += process.cpu_peak;
    process.state = "Running";

    while (process.cpu_peak > 0) {
      --process.cpu_peak;
      for (auto &p : processes) {
        if (p.pid != process.pid && p.state == "Ready") {
          p.wait_time++;
        }
      }
    }
    process.state = "Finished";
  }

  float avg_wait_time = static_cast<float>(total_wait_time) / processes.size();
  std::cout << "Tempo médio de espera: " << std::fixed << std::setprecision(2)
            << avg_wait_time << std::endl;
}

void sjf_schedule(std::vector<Process> processes) {
  unsigned int current_time = 0;
  unsigned int total_wait_time = 0;

  std::sort(processes.begin(), processes.end(), compare_by_cpu_peak);

  for (auto &process : processes) {
    process.wait_time = current_time;
    total_wait_time += process.wait_time;
    current_time += process.cpu_peak;
    process.state = "Running";

    while (process.cpu_peak > 0) {
      --process.cpu_peak;
      for (auto &p : processes) {
        if (p.pid != process.pid && p.state == "Ready") {
          p.wait_time++;
        }
      }
    }
    process.state = "Finished";
  }

  float avg_wait_time = static_cast<float>(total_wait_time) / processes.size();
  std::cout << "Tempo médio de espera: " << std::fixed << std::setprecision(2)
            << avg_wait_time << std::endl;
}

void rr_schedule(std::vector<Process> processes, unsigned int quantum) {
  unsigned int current_time = 0;

  std::deque<Process *> ready_queue;

  for (auto &process : processes) {
    process.wait_time = 0;
    process.state = "Ready";
    ready_queue.push_back(&process);
  }

  while (!ready_queue.empty()) {
    Process *current_process = ready_queue.front();
    ready_queue.pop_front();

    unsigned int exec_time = std::min(current_process->cpu_peak, quantum);

    current_process->state = "Running";
    current_process->cpu_peak -= exec_time;
    current_time += exec_time;

    for (auto &p : processes) {
      if (p.pid != current_process->pid && p.state == "Ready") {
        p.wait_time += exec_time;
      }
    }

    if (current_process->cpu_peak > 0) {
      current_process->state = "Ready";
      ready_queue.push_back(current_process);
    } else {
      current_process->state = "Finished";
    }
  }

  float avg_wait_time =
      static_cast<float>(std::accumulate(
          processes.begin(), processes.end(), 0,
          [](int sum, const Process &p) { return sum + p.wait_time; })) /
      processes.size();

  std::cout << "Tempo médio de espera: " << std::fixed << std::setprecision(2)
            << avg_wait_time << std::endl;
}