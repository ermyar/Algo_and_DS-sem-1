#include <iostream>
#include <vector>

void Sort(int left, int right, int* ar) {
  if (right - left <= 1) {
    return;
  }
  int mid = (right + left) / 2;
  int var_i = left;
  int var_j = right - 1;
  if (ar[left] > ar[mid]) {
    std::swap(ar[left], ar[mid]);
  }
  if (ar[mid] > ar[var_j]) {
    std::swap(ar[mid], ar[var_j]);
  }
  if (ar[left] > ar[mid]) {
    std::swap(ar[left], ar[mid]);
  }
  int var_x = ar[mid];
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
    std::swap(ar[var_i], ar[var_j]);
    var_i++;
    var_j--;
  }
  Sort(left, var_i, ar);
  Sort(var_i, right, ar);
}

int main() {
  int var_n;
  std::cin >> var_n;
  int* ar = new int[var_n];
  for (int i = 0; i < var_n; ++i) {
    std::cin >> ar[i];
  }
  Sort(0, var_n, ar);
  for (int i = 0; i < var_n; ++i) {
    std::cout << ar[i] << ' ';
  }
  delete[] ar;
  return 0;
}
