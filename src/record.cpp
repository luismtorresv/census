#include "record.hpp"
#include <iomanip>
#include <sstream>

using namespace std::chrono;

Record::Record(std::string operation, std::int64_t timeInMilliseconds,
               std::int64_t memoryInKiloBytes)
    : operation_(std::move(operation)), timeInMilliseconds_(timeInMilliseconds),
      memoryInKiloBytes_(memoryInKiloBytes) {}

const std::string &Record::operation() const noexcept { return operation_; }
std::int64_t Record::timeInMilliseconds() const noexcept {
  return timeInMilliseconds_;
}
std::int64_t Record::memoryInKiloBytes() const noexcept {
  return memoryInKiloBytes_;
}