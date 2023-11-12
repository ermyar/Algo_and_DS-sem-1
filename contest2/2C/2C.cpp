#include <iostream>
#include <vector>

class Queue {
public:
  void Init(int number) {
    left_.resize(number + 2);
    right_.resize(number + 2);
    right_[0] = number + 1;
    left_[number + 1] = 0;
  }
  void Insert(int val, int pos) {
    if (pos == -1) {
      pos = right_[middle_];
    }
    int tmp = left_[pos];
    right_[tmp] = val;
    left_[pos] = val;
    right_[val] = pos;
    left_[val] = tmp;
    count_++;
    Update();
  }
  void Delete() {
    std::cout << right_[0] << "\n";
    int pos = right_[0];
    right_[left_[pos]] = right_[pos];
    left_[right_[pos]] = left_[pos];
    count_--;
    Update();
    if (count_ == 0) {
      middle_ = 0;
    }
  }
  void Update() {
    if (count_ % 2 == 1) {
      middle_ = right_[middle_];
    }
  }

 private:
  std::vector<int> left_;
  std::vector<int> right_;
  int count_ = 0;
  int middle_ = 0;
};

int main() {
  int number;
  std::cin >> number;
  Queue qu;
  qu.Init(number);
  for (int i = 0; i < number; ++i) {
    char ch;
    std::cin >> ch;
    switch (ch) {
      int val;
      case ('+'):
        std::cin >> val;
        qu.Insert(val, number + 1);
        break;
      case ('*'):
        std::cin >> val;
        qu.Insert(val, -1);
        break;
      case ('-'):
        qu.Delete();
        break;
    }
  }
  return 0;
}