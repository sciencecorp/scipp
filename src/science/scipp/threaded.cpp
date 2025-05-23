#include "science/scipp/threaded.h"

namespace science {

auto Threaded::start() -> Status {
  running_ = true;

  auto status = on_start();
  if (!status.ok()) {
    return status;
  }

  thread_ = std::make_unique<std::thread>(&Threaded::on_thread, this);

  return {};
}

auto Threaded::stop() -> Status {
  running_ = false;

  auto status = on_stop();

  if (thread_ != nullptr && thread_->joinable()) {
    thread_->join();
  }

  return status;
}

}  // namespace science
