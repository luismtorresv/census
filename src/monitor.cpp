#include "monitor.h"
#include <cstdio>
#include <unistd.h>

void Monitor::startTimer() {
  start = std::chrono::high_resolution_clock::now();
}

double Monitor::stopTimer() {
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  return duration.count();
}

long Monitor::getMemoryUsage() {
  FILE *file = fopen("/proc/self/statm", "r");
  if (!file) {
    perror("Error opening /proc/self/statm");
    return 0;
  }

  long size, resident, shared, text, lib, data, dt;
  if (fscanf(file, "%ld %ld %ld %ld %ld %ld %ld", &size, &resident, &shared,
             &text, &lib, &data, &dt) != 7) {
    fclose(file);
    return 0;
  }
  fclose(file);

  long page_size_kb = sysconf(_SC_PAGESIZE) / 1024;
  return resident * page_size_kb;
}

void Monitor::record(const std::string &operation, double time, long memory) {
  entries.push_back({operation, time, memory});
  totalTime += time;
  if (memory > peakMemory) {
    peakMemory = memory;
  }
}

void Monitor::showRecord(const std::string &operation, double time,
                         long memory) {
  std::cout << "\n[STATS] " << operation << " - Time: " << time << " ms, "
            << "Memory: " << memory << " KB\n";
}

void Monitor::showSummary() {
  std::cout << "\n=== SUMMARY OF STATISTICS ===";
  for (const auto &e : entries) {
    std::cout << "\n"
              << e.operation << ": " << e.timeMs << " ms, " << e.memoryKB
              << " KB";
  }
  std::cout << "\nTotal time: " << totalTime << " ms";
  std::cout << "\nPeak memory: " << peakMemory << " KB\n";
}

void Monitor::exportCSV(const std::string &filename) {
  std::ofstream file(filename);
  if (!file) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }
  file << "Operation,Time(ms),Memory(KB)\n";
  for (const auto &e : entries) {
    file << e.operation << "," << e.timeMs << "," << e.memoryKB << "\n";
  }
  file.close();
  std::cout << "Statistics exported to " << filename << "\n";
}
