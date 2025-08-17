#pragma once

#include <chrono>
#include <cstdint>
#include <ostream>
#include <string>

class Record {
private:
  std::string operation_;
  std::int64_t timeInMilliseconds_; // duration of operation in ms
  std::int64_t memoryInKiloBytes_;  // memory usage in KB

public:
  // Default
  Record() = default;

  // Main constructor (time in milliseconds, memory in kilobytes)
  Record(std::string operation, std::int64_t timeInMilliseconds,
         std::int64_t memoryInKiloBytes);

  // Getters
  const std::string &operation() const noexcept;
  std::int64_t timeInMilliseconds() const noexcept;
  std::int64_t memoryInKiloBytes() const noexcept;
};