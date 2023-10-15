#include <iostream>
#include <string>
#include <vector>

struct Heap {
  std::vector<long long> value;
  std::vector<int> pos;
  std::vector<int> heap;
  int cnt = 0;

  void Init(int number) {
    pos.resize(number);
    value.resize(number);
  }

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

  void Insert(int ind) {
    pos[ind] = heap.size();
    heap.push_back(ind);
    cnt++;
    Siftup(pos[ind]);
  }

  void Extract() {
    std::swap(heap[0], heap.back());
    std::swap(pos[heap[0]], pos[heap.back()]);
    pos[heap.back()] = 0;
    heap.pop_back();
    cnt--;
    Siftdown(0);
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
  for (int i = 0; i < query; ++i) {
    std::cin >> str;
    if (str[0] == 'i') {
      std::cin >> hp.value[i];
      hp.Insert(i);
    }
    if (str[0] == 'g') {
      std::cout << hp.value[hp.heap[0]] << '\n';
    }
    if (str[0] == 'e') {
      hp.Extract();
    }
    if (str[0] == 'd') {
      int ind;
      long long delta;
      std::cin >> ind >> delta;
      --ind;
      hp.value[ind] -= delta;
      hp.Siftup(hp.pos[ind]);
    }
  }
  return 0;
}
