#include <iostream>
#include <queue>
#include <set>
#include <string>

void Add(std::queue<int>& deque, std::multiset<int>& pref, int var) {
  deque.push(var);
  pref.insert(var);
  std::cout << "ok\n";
}

void Front(std::queue<int>& deque) {
  if (deque.empty()) {
    std::cout << "error\n";
  } else {
    std::cout << deque.front() << std::endl;
  }
}

void Min(std::multiset<int>& multiset) {
  if (multiset.empty()) {
    std::cout << "error\n";
  } else {
    std::cout << *(multiset.begin()) << std::endl;
  }
}

void Del(std::queue<int>& deque, std::multiset<int>& multiset) {
  if (deque.empty()) {
    std::cout << "error\n";
  } else {
    int tmp = deque.front();
    std::cout << tmp << std::endl;
    deque.pop();
    multiset.erase(multiset.find(tmp));
  }
}

int main() {
  int number;
  std::cin >> number;
  std::multiset<int> multiset;
  std::queue<int> deque;
  for (int i = 0; i < number; ++i) {
    std::string str;
    std::cin >> str;
    if (str == "enqueue") {
      int x;
      std::cin >> x;
      Add(deque, multiset, x);
    }
    if (str == "dequeue") {
      Del(deque, multiset);
    }
    if (str == "front") {
      Front(deque);
    }
    if (str == "size") {
      std::cout << (int)deque.size() << std::endl;
    }
    if (str == "clear") {
      multiset.clear();
      while (!deque.empty()) {
        deque.pop();
      }
      std::cout << "ok\n";
    }
    if (str == "min") {
      Min(multiset);
    }
  }
  return 0;
}
