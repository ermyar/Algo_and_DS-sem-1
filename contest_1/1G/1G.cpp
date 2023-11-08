#include <iostream>

const int kMaxn = 1e6 + 100;
const int kMaxl = 8;
const int kSmth = 270;

int GetByte(long long vx, int vk) {
  long long tmp = (vx >> (kMaxl * vk));
  tmp %= (1 << kMaxl);
  return static_cast<int>(tmp);
}

void Sort(int left, int right, int var_k, long long* arr_a, long long* arr_b, int* count) {
  for (int i = 0; i < kSmth; ++i) {
    count[i] = 0;
  }
  for (int i = left; i < right; ++i) {
    ++count[GetByte(arr_a[i], var_k)];
  }
  for (int i = 1; i < kSmth; ++i) {
    count[i] += count[i - 1];
  }
  for (int i = right - 1; i >= left; --i) {
    int tmp = GetByte(arr_a[i], var_k);
    arr_b[count[tmp] - 1] = arr_a[i];
    count[tmp]--;
  }
  for (int i = left; i < right; ++i) {
    arr_a[i] = arr_b[i];
  }
}

signed main() {
  int nu;
  std::cin >> nu;
  long long* ar = new long long[kMaxn];
  long long* br = new long long[kMaxn];
  int* cnt = new int[kSmth];
  for (int i = 0; i < nu; ++i) {
    std::cin >> ar[i];
  }
  for (int i = 0; i < kMaxl; ++i) {
    Sort(0, nu, i, ar, br, cnt);
  }
  for (int j = 0; j < nu; ++j) {
    std::cout << ar[j] << ' ';
  }
  std::cout << std::endl;
  return 0;
}
