#pragma once

#include <memory>
#include <string>
#include <thread>

#include "science/scipp/status.h"

namespace science {

/**
 * @brief A base class for classes that contain one thread, and may be started and stopped.
 */
class Threaded {
 public:
  virtual ~Threaded() = default;

  [[nodiscard]] virtual auto stop() -> Status;
  [[nodiscard]] virtual auto start() -> Status;

 protected:
  std::atomic<bool> running_{false};
  std::unique_ptr<std::thread> thread_{};

  virtual auto on_thread() -> void = 0;
  [[nodiscard]] virtual auto on_start() -> Status { return {}; }
  [[nodiscard]] virtual auto on_stop() -> Status { return {}; }
};

}  // namespace science
