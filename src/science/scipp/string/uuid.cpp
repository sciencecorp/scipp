#include "science/scipp/string/uuid.h"

#include <uuid.h>

#include <array>
#include <iostream>
#include <random>

namespace science {

std::string uuid() {
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size>{};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  std::mt19937 generator(seq);

  uuids::uuid_random_generator gen{generator};
  return uuids::to_string(gen());
}

UuidInstance:: UuidInstance() {
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size>{};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  std::mt19937 generator(seq);

  uuids::uuid_random_generator gen{generator};
  uuid_ = uuids::to_string(gen());
}

}  // namespace science
