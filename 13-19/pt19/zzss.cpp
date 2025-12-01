#include <iostream>
#include <map>
#include <vector>

class Mode {
  std::map<int, int> count_;
  int mode_value_;

  void updateMode() {
    int bestCount = -1;
    for (const auto &kv : count_) {
      if (kv.second > bestCount) {
        bestCount = kv.second;
        mode_value_ = kv.first;
      }
    } 
  }

public:
  explicit Mode(const std::vector<int> &nums) : mode_value_(0) {
    for (int v : nums) {
      ++count_[v];
    }
    updateMode();
  }
  void Insert(int value) {
    ++count_[value];
    if (count_[value] > count_[mode_value_]) {
      mode_value_ = value;
    }
  }

  void Print() const {
    for (const auto &kv : count_) {
      std::cout << "(" << kv.first << ", " << kv.second << ") ";
    }
    std::cout << "\n当前众数：" << mode_value_ << '\n';
  }
};

int main() {
  std::vector<int> nums = {1, 3, 3, 2, 5, 3, 2, 2};
  Mode mode(nums);
  mode.Print();

  for (int v : {5, 5, 5}) {
    mode.Insert(v);
  }
  std::cout << "\n插入 5,5,5 后：\n";
  mode.Print();
  return 0;
}
