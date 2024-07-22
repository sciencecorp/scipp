#pragma once

#include <string>
#include <utility>

#include "science/scipp/logging.h"

namespace science {

/**
 * @brief Library-agnostic status codes for return values of functions or other operations.
 * 
 * These codes are 1:1 with the abseil / gRPC status codes.
 */
enum class StatusCode : int {
  // Standard status codes
  kOk = 0,
  kCancelled = 1,
  kUnknown = 2,
  kInvalidArgument = 3,
  kDeadlineExceeded = 4,
  kNotFound = 5,
  kAlreadyExists = 6,
  kPermissionDenied = 7,
  kResourceExhausted = 8,
  kFailedPrecondition = 9,
  kAborted = 10,
  kOutOfRange = 11,
  kUnimplemented = 12,
  kInternal = 13,
  kUnavailable = 14,
  kDataLoss = 15,
  kUnauthenticated = 16,
  kDoNotUse = 20,

  // Custom status codes
  // kCustomExample = 101,
};

/**
 * Status, containing a status code and an optional message.
 * 
 * To be used as a return value for functions that may fail.
 */
class Status {
 public:
  explicit Status(StatusCode code) : code_(code) {}

  Status() = default;

  Status(StatusCode code, std::string message) : code_(code), message_(std::move(message)) {}

  [[nodiscard]] bool ok() const { return code_ == StatusCode::kOk; }

  [[nodiscard]] StatusCode code() const { return code_; }

  [[nodiscard]] std::string message() const { return message_; }

  static auto Log(Logger* log, StatusCode code, std::string message) -> Status {
    if (code == StatusCode::kOk) {
      LOG_INFO(log, "{}", message);
    } else {
      LOG_ERROR(log, "{}", message);
    }
    return { code, message };
  }

 private:
  StatusCode code_{StatusCode::kOk};
  std::string message_{};
};

}  // namespace science
