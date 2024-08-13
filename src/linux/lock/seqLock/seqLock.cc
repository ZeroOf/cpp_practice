
// implementation seqlock

#include <atomic>
#include <mutex>
#include <util.h>
#include <thread>
#include <array>
#include <algorithm>

template<typename T>
class Seqlock {
 public:
  void store(const T &data) {
    std::lock_guard<std::mutex> guard(mutex_);
    seq_.fetch_add(1, std::memory_order_acquire);
    data_ = data;
    seq_.fetch_add(1, std::memory_order_release);
  }

  T load() const {
    T copy;
    size_t seq0, seq1;
    do {
      seq0 = seq_.load(std::memory_order_acquire);
      copy = data_;
      seq1 = seq_.load(std::memory_order_acquire);
    } while (seq0 != seq1 || seq0 & 1);
    return copy;
  }

 private:
  mutable std::atomic<size_t> seq_{0};
  T data_;
  mutable std::mutex mutex_;
};

int main() {
  Seqlock<int> seq;
  std::array<std::thread, 2> threads{
      std::thread([&seq] {
        for (int i = 0; i < 10000; ++i) {
          seq.store(i);
        }
      }),
      std::thread([&seq] {
        for (int i = 0; i < 10000; ++i) {
          LOG_VALUE(seq.load());
        }
      })
  };
  std::for_each(threads.begin(), threads.end(), [](auto &t) { t.join(); });
  return 0;
}