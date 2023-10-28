#include <iostream>

const int kMaxn = 1e6 + 100, kMaxl = 8, kSmth = 270;

int GetByte(long long vx, int vk) {
  long long tmp = (vx >> (kMaxl * vk));
  tmp %= (1 << kMaxl);
  return static_cast<int>(tmp);
}

void Sort(int lx, int rx, int vk, long long* ar, long long* br, int* cnt) {
  for (int i = 0; i < kSmth; ++i) {
    cnt[i] = 0;
  }
  for (int i = lx; i < rx; ++i) {
    ++cnt[GetByte(ar[i], vk)];
  }
  for (int i = 1; i < kSmth; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = rx - 1; i >= lx; --i) {
    int tmp = GetByte(ar[i], vk);
    br[cnt[tmp] - 1] = ar[i];
    cnt[tmp]--;
  }
  for (int i = lx; i < rx; ++i) {
    ar[i] = br[i];
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
