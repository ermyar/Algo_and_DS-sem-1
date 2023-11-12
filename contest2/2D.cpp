#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>

class MagicHat {
 public:
  void Add(int var) {
    deque_.push(var);
    multiset_.insert(var);
    std::cout << "ok\n";
  }

  void Front() {
    if (deque_.empty()) {
      std::cout << "error\n";
    } else {
      std::cout << deque_.front() << std::endl;
    }
  }

  void Min() {
    if (multiset_.empty()) {
      std::cout << "error\n";
    } else {
      std::cout << *(multiset_.begin()) << std::endl;
    }
  }

  void Del() {
    if (deque_.empty()) {
      std::cout << "error\n";
    } else {
      int tmp = deque_.front();
      std::cout << tmp << std::endl;
      deque_.pop();
      multiset_.erase(multiset_.find(tmp));
    }
  }

  int Size() { return deque_.size(); }

  void Clear() {
    multiset_.clear();
    while (!deque_.empty()) {
      deque_.pop();
    }
  }

 private:
  std::multiset<int> multiset_;
  std::queue<int> deque_;
};

int main() {
  int number;
  std::cin >> number;
  MagicHat magic;
  std::map<std::string, int> mp;
  mp["enqueue"] = 0;
  mp["dequeue"] = 1;
  mp["front"] = 2;
  mp["size"] = 3;
  mp["clear"] = 4;
  mp["min"] = 5;
  for (int i = 0; i < number; ++i) {
    std::string str;
    std::cin >> str;
    switch (mp[str]) {
      case (0):
        int x;
        std::cin >> x;
        magic.Add(x);
        break;
      case (1):
        magic.Del();
        break;
      case (2):
        magic.Front();
        break;
      case (3):
        std::cout << magic.Size() << std::endl;
        break;
      case (4):
        magic.Clear();
        std::cout << "ok\n";
        break;
      case (5):
        magic.Min();
        break;
    }
  }
  return 0;
}
