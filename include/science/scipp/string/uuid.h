#pragma once

#include <string>

namespace science {

std::string uuid();

class UuidInstance {
 public:
  UuidInstance(const UuidInstance&) = delete;
  UuidInstance& operator=(const UuidInstance&) = delete;

  [[nodiscard]] static auto get() -> UuidInstance&  {
    static UuidInstance instance;
    return instance;
  }

  [[nodiscard]] auto uuid() -> std::string { return uuid_; }

 private:
  UuidInstance();  // NOLINT(modernize-use-equals-delete)
  std::string uuid_;
};

}  // namespace science
