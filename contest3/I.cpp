#include <algorithm>
#include <iostream>
#include <vector>

const int kL = 30;

class SparceTable {
 public:
  SparceTable(std::vector<int>& ar) {
    value = ar;
    size = ar.size();
    lg.resize(size + 1);
    lg[0] = -1;
    for (int i = 0; i < size; ++i) {
      lg[i + 1] = lg[(i + 1) / 2] + 1;
    }
    for (int i = 0; i < kL; ++i) {
      for (int j = 0; j + (1 << i) <= size; ++j) {
        if (i == 0) {
          st[0].push_back(j);
        } else {
          if (ar[st[i - 1][j]] > ar[st[i - 1][j + (1 << (i - 1))]]) {
            st[i].push_back(st[i - 1][j + (1 << (i - 1))]);
          } else {
            st[i].push_back(st[i - 1][j]);
          }
        }
      }
    }
  }

  int Query(int lx, int rx) {
    int len = lg[rx - lx];
    int pos1 = st[len][lx];
    int pos2 = st[len][rx - (1 << len)];
    if (value[pos1] < value[pos2]) {
      return pos1;
    }
    return pos2;
  }
  
 private:
  int size;
  std::vector<int> value;
  std::vector<int> lg;
  std::vector<int> st[kL];
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int nu;
  int qu;
  std::cin >> nu >> qu;
  std::vector<int> ar(nu);
  for (int i = 0; i < nu; ++i) {
    std::cin >> ar[i];
  }
  SparceTable tmp(ar);
  for (int i = 0; i < qu; ++i) {
    int lx;
    int rx;
    std::cin >> lx >> rx;
    lx--;
    int top = tmp.Query(lx, rx);
    if (top == lx) {
      std::cout << ar[tmp.Query(top + 1, rx)] << '\n';
    } else if (top == rx - 1) {
      std::cout << ar[tmp.Query(lx, top)] << '\n';
    } else {
      int tmp1 = tmp.Query(lx, top);
      int tmp2 = tmp.Query(top + 1, rx);
      std::cout << std::min(ar[tmp1], ar[tmp2]) << '\n';
    }
  }
}
