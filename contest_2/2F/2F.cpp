#include <iostream>
#include <map>
#include <string>
#include <vector>

class Heap {
 private:
  std::vector<long long> value_;
  std::vector<int> pos_;
  std::vector<int> heap_;
  int cnt_ = 0;

 public:
  void Init(int number) {
    pos_.resize(number);
    value_.resize(number);
  }

  void Siftup(int ind) {
    while (value_[heap_[ind]] < value_[heap_[(ind - 1) / 2]]) {
      std::swap(heap_[(ind - 1) / 2], heap_[ind]);
      std::swap(pos_[heap_[(ind - 1) / 2]], pos_[heap_[ind]]);
      ind = (ind - 1) / 2;
    }
  }

  void Siftdown(int ind) {
    while (2 * ind + 1 < cnt_) {
      int tmp = 2 * ind + 1;
      if ((tmp + 1) < cnt_) {
        if (value_[heap_[tmp]] > value_[heap_[tmp + 1]]) {
          tmp++;
        }
      }
      if (value_[heap_[ind]] <= value_[heap_[tmp]]) {
        return;
      }
      std::swap(pos_[heap_[tmp]], pos_[heap_[ind]]);
      std::swap(heap_[tmp], heap_[ind]);
      ind = tmp;
    }
  }

  void Insert(int ind) {
    std::cin >> value_[ind];
    pos_[ind] = heap_.size();
    heap_.push_back(ind);
    cnt_++;
    Siftup(pos_[ind]);
  }

  void Extract() {
    std::swap(heap_[0], heap_.back());
    std::swap(pos_[heap_[0]], pos_[heap_.back()]);
    pos_[heap_.back()] = 0;
    heap_.pop_back();
    cnt_--;
    Siftdown(0);
  }

  void Get() { std::cout << value_[heap_[0]] << '\n'; }

  void Delete(int ind, int delta) {
    value_[ind] -= delta;
    Siftup(pos_[ind]);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int query;
  std::cin >> query;
  Heap hp;
  hp.Init(query);
  std::string str;
  std::map<std::string, int> mp;
  mp["insert"] = 0;
  mp["getMin"] = 1;
  mp["extractMin"] = 2;
  mp["decreaseKey"] = 3;
  for (int i = 0; i < query; ++i) {
    std::cin >> str;
    switch (mp[str]) {
      case (0):
        hp.Insert(i);
        break;
      case (1):
        hp.Get();
        break;
      case (2):
        hp.Extract();
        break;
      case (3):
        int ind;
        long long delta;
        std::cin >> ind >> delta;
        --ind;
        hp.Delete(ind, delta);
        break;
    }
  }
  return 0;
}
