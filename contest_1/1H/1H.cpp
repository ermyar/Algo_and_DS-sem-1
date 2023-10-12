#include <iostream>

const int kMaxn = 1e6 + 100, kMaxl = 63;

long long ar[kMaxn], pw[kMaxl];

void Sort(int lx, int rx, int vk) {
  if (vk == -1) {
    return;
  }
  if (rx - lx <= 1) {
    return;
  }
  int pr = rx - 1;
  int pl = lx;
  while (true) {
    while (pl < rx && (ar[pl] & pw[vk]) == 0) {
      pl++;
    }
    while (pr > lx && (ar[pr] & pw[vk]) != 0) {
      pr--;
    }

    if (pl < pr) {
      std::swap(ar[pl], ar[pr]);
    } else {
      break;
    }
  }
  Sort(lx, pl, vk - 1);
  Sort(pl, rx, vk - 1);
}

signed main() {
  pw[0] = 1;
  for (int i = 1; i < kMaxl; ++i) {
    pw[i] = pw[i - 1] * 2;
  }
  int nu;
  std::cin >> nu;
  for (int i = 0; i < nu; ++i) {
    std::cin >> ar[i];
  }
  Sort(0, nu, kMaxl - 1);
  for (int i = 0; i < nu; ++i) {
    std::cout << ar[i] << ' ';
  }
  return 0;
}