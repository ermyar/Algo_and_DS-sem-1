#include <iostream>
#include <map>
#include <string>
#include <vector>

const int kInf = 1e9 + 100;

class Heap {

 public:
  Heap(int sg) { sign_ = sg; }

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

  void Insert(int val) {
    int ind = value_.size();
    value_.push_back(val);
    pos_.push_back(heap_.size());
    heap_.push_back(ind);
    cnt_++;
    Siftup(pos_[ind]);
  }

  int Extract(bool flag) {
    if (cnt_ == 0) {
      if (flag) {
        std::cout << "error\n";
      }
      return -1;
    }
    int tmp = heap_[0];
    std::swap(heap_[0], heap_.back());
    std::swap(pos_[heap_[0]], pos_[heap_.back()]);
    pos_[heap_.back()] = 0;
    heap_.pop_back();
    cnt_--;
    Siftdown(0);
    if (flag) {
      std::cout << (sign_ * value_[tmp]) << '\n';
    }
    return tmp;
  }

  void Get() {
    if (cnt_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << (sign_ * value_[heap_[0]]) << "\n";
  }

  void Clear() {
    cnt_ = 0;
    value_.clear();
    pos_.clear();
    heap_.clear();
  }

  void Delete(int ind) {
    if (ind == -1) {
      return;
    }
    if (cnt_ == 0) {
      return;
    }
    value_[ind] = -kInf;
    Siftup(pos_[ind]);
    Extract(false);
  }

  int Size() const { return cnt_; }

  
 private:
  std::vector<int> value_;
  std::vector<int> pos_;
  std::vector<int> heap_;
  int cnt_ = 0;
  int sign_ = 1;
};

int main() {
  int query;
  std::cin >> query;
  std::string str;
  Heap mini(1);
  Heap maxi(-1);
  std::map<std::string, int> mp;
  mp["insert"] = 0;
  mp["extract_min"] = 1;
  mp["extract_max"] = 2;
  mp["size"] = 3;
  mp["clear"] = 4;
  mp["get_min"] = 5;
  mp["get_max"] = -1;
  for (int i = 0; i < query; ++i) {
    std::cin >> str;
    switch (mp[str]) {
      int ind;
      case (0):
        int val;
        std::cin >> val;
        mini.Insert(val);
        maxi.Insert(-val);
        std::cout << "ok\n";
        break;
      case (1):
        ind = mini.Extract(true);
        maxi.Delete(ind);
        break;
      case (2):
        ind = maxi.Extract(true);
        mini.Delete(ind);
        break;
      case (3):
        std::cout << mini.Size() << '\n';
        break;
      case (4):
        mini.Clear();
        maxi.Clear();
        std::cout << "ok\n";
        break;
      case (5):
        mini.Get();
        break;
      case (-1):
        maxi.Get();
        break;
    }
  }
}
