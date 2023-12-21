#include <algorithm>
#include <iostream>
#include <vector>

const int kLen = 30;

class SparceTable {
 public:
  SparceTable(std::vector<int>& ar) {
    value_ = ar;
    size_ = ar.size();
    lg_.resize(size_ + 1);
    lg_[0] = -1;
    for (int i = 0; i < size_; ++i) {
      lg_[i + 1] = lg_[(i + 1) / 2] + 1;
    }
    for (int i = 0; i < kLen; ++i) {
      for (int j = 0; j + (1 << i) <= size_; ++j) {
        if (i == 0) {
          st_[0].push_back(j);
        } else {
          if (ar[st_[i - 1][j]] > ar[st_[i - 1][j + (1 << (i - 1))]]) {
            st_[i].push_back(st_[i - 1][j + (1 << (i - 1))]);
          } else {
            st_[i].push_back(st_[i - 1][j]);
          }
        }
      }
    }
  }

  int Query(int lx, int rx) {
    int len = lg_[rx - lx];
    int pos1 = st_[len][lx];
    int pos2 = st_[len][rx - (1 << len)];
    if (value_[pos1] < value_[pos2]) {
      return pos1;
    }
    return pos2;
  }
  
 private:
  int size_;
  std::vector<int> value_;
  std::vector<int> lg_;
  std::vector<int> st_[kLen];
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
