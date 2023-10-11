#include <iostream>
#include <vector>

using namespace std;

const int kMaxn = 1e7 + 100, kA = 123, kB = 45, kMod = 1e7 + 4321;

int Kth(std::vector<int>& ar, int left, int right, int var_k) {
  if (right - left <= 1) {
    return ar[left];
  }
  int medium = (right + left) / 2;
  int var_i = left;
  int var_j = right - 1;
  if (ar[left] > ar[medium]) {
    swap(ar[left], ar[medium]);
  }
  if (ar[medium] > ar[var_j]) {
    swap(ar[medium], ar[var_j]);
  }
  if (ar[left] > ar[medium]) {
    swap(ar[left], ar[medium]);
  }
  auto var_x = ar[medium];
  while (var_i <= var_j) {
    while (ar[var_i] < var_x) {
      ++var_i;
    }
    while (ar[var_j] > var_x) {
      --var_j;
    }
    if (var_i >= var_j) {
      break;
    }
    swap(ar[var_i], ar[var_j]);
    var_i++;
    var_j--;
  }
  if (var_k < (var_i - left)) {
    return Kth(ar, left, var_i, var_k);
  }
  return Kth(ar, var_i, right, var_k - (var_i - left));
}


int main() {
  int var_n;
  int var_k;
  std::vector<int> ar(var_n + 1);
  cin >> var_n >> var_k >> ar[0] >> ar[1];
  for (int i = 2; i <= var_n; ++i) {
    ar[i] = (kA * ar[i - 1] + kB * ar[i - 2]) % kMod;
  }
  cout << Kth(ar, 0, var_n, var_k - 1);
  return 0;
}

