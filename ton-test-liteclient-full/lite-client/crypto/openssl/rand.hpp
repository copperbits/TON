#pragma once
#include <string>
#include <cassert>

namespace prng {

// use this generator unless need a separate one
class RandomGen;
RandomGen &rand_gen();

class RandomGen {
 public:
  struct rand_error {};
  void randomize(bool force = true);
  void seed_add(const void *data, std::size_t size, double entropy = 0);
  bool ok() const;
  RandomGen() {
    randomize(false);
  }
  RandomGen(const void *seed, std::size_t size) {
    seed_add(seed, size);
    randomize(false);
  }
  bool rand_bytes(void *data, std::size_t size, bool strong = false);
  bool strong_rand_bytes(void *data, std::size_t size) {
    return rand_bytes(data, size, true);
  }
  template <class T>
  bool rand_obj(T &obj) {
    return rand_bytes(&obj, sizeof(T));
  }
  template <class T>
  bool rand_objs(T *ptr, std::size_t count) {
    return rand_bytes(ptr, sizeof(T) * count);
  }
  std::string rand_string(std::size_t size, bool strong = false);
};
}  // namespace prng
