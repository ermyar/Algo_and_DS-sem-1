#include <iostream>
#include <string>
#include <vector>

const int kInf = 1e9 + 100;

struct Heap {
  std::vector<int> value;
  std::vector<int> pos;
  std::vector<int> heap;
  int cnt = 0;
  int sign = 1;

  void Siftup(int ind) {
    while (value[heap[ind]] < value[heap[(ind - 1) / 2]]) {
      std::swap(heap[(ind - 1) / 2], heap[ind]);
      std::swap(pos[heap[(ind - 1) / 2]], pos[heap[ind]]);
      ind = (ind - 1) / 2;
    }
  }

  void Siftdown(int ind) {
    while (2 * ind + 1 < cnt) {
      int tmp = 2 * ind + 1;
      if ((tmp + 1) < cnt) {
        if (value[heap[tmp]] > value[heap[tmp + 1]]) {
          tmp++;
        }
      }
      if (value[heap[ind]] <= value[heap[tmp]]) {
        return;
      }
      std::swap(pos[heap[tmp]], pos[heap[ind]]);
      std::swap(heap[tmp], heap[ind]);
      ind = tmp;
    }
  }

  void Insert(int val) {
    int ind = value.size();
    value.push_back(val);
    pos.push_back(heap.size());
    heap.push_back(ind);
    cnt++;
    Siftup(pos[ind]);
  }

  int Extract(bool flag) {
    if (cnt == 0) {
      if (flag) {
        std::cout << "error\n";
      }
      return -1;
    }
    int tmp = heap[0];
    std::swap(heap[0], heap.back());
    std::swap(pos[heap[0]], pos[heap.back()]);
    pos[heap.back()] = 0;
    heap.pop_back();
    cnt--;
    Siftdown(0);
    if (flag) {
      std::cout << (sign * value[tmp]) << '\n';
    }
    return tmp;
  }

  void Get() {
    if (cnt == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << (sign * value[heap[0]]) << "\n";
  }

  void Clear() {
    cnt = 0;
    value.clear();
    pos.clear();
    heap.clear();
  }

  void Delete(int ind) {
    if (ind == -1) {
      return;
    }
    if (cnt == 0) {
      return;
    }
    value[ind] = -kInf;
    Siftup(pos[ind]);
    Extract(false);
  }
};

int main() {
  int query;
  std::cin >> query;
  std::string str;
  Heap mini;
  Heap maxi;
  maxi.sign = -1;
  for (int i = 0; i < query; ++i) {
    std::cin >> str;
    if (str == "insert") {
      int val;
      std::cin >> val;
      mini.Insert(val);
      maxi.Insert(-val);
      std::cout << "ok\n";
    }
    if (str == "extract_min") {
      int ind = mini.Extract(true);
      maxi.Delete(ind);
    }
    if (str == "extract_max") {
      int ind = maxi.Extract(true); 
      mini.Delete(ind);
    }
    if (str == "size") {
      std::cout << mini.cnt << '\n';
    }
    if (str == "clear") {
      mini.Clear();
      maxi.Clear();
      std::cout << "ok\n";
    }
    if (str == "get_min") {
      mini.Get();
    }
    if (str == "get_max") {
      maxi.Get();
    }
  }
}
