#include "process_scheduler.hpp"
#include <fstream>
#include <iostream>

int main(void) {
  std::ifstream file("mock/picos_cpu.dat");

  if (!file.is_open()) {
    std::cerr << "Erro ao abrir o arquivo." << std::endl;
    return 1;
  }

  std::vector<Process> processes = get_process_list(file);
  file.close();

  std::cout << "** First Came, First Served **" << std::endl;
  fcfs_schedule(processes);
  std::cout << "** Shortest Job First **" << std::endl;
  sjf_schedule(processes);
  std::cout << "** Round Robin **" << std::endl;
  std::cout << "-- using quantum=10" << std::endl;
  rr_schedule(processes, 10);
  std::cout << "** Round Robin **" << std::endl;
  std::cout << "-- using quantum=100" << std::endl;
  rr_schedule(processes, 100);
  std::cout << "** Round Robin **" << std::endl;
  std::cout << "-- using quantum=200" << std::endl;
  rr_schedule(processes, 200);

  return 0;
}