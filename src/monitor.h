#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Monitor {
public:
    void startTimer();
    double stopTimer();
    long getMemoryUsage();

    void record(const std::string& operation, double time, long memory);
    void showRecord(const std::string& operation, double time, long memory);
    void showSummary();
    void exportCSV(const std::string& filename = "statistics.csv");

private:
    struct Entry {
        std::string operation;
        double timeMs;
        long memoryKB;
    };

    std::chrono::high_resolution_clock::time_point start;
    std::vector<Entry> entries;
    double totalTime = 0;
    long peakMemory = 0;
};
