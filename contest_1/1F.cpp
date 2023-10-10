#include <iostream>
#include <vector>

#define pii pair<int, int>

using namespace std;

const int kMaxn = 1e7 + 100, kA = 123, kB = 45, kMod = 1e7 + 4321;

int ar[kMaxn];

int Kth(int vl, int vr, int vk) {
  if (vr - vl <= 1) {
    return ar[vl];
  }
  int vm = (vr + vl) / 2;
  int vi = vl;
  int vj = vr - 1;
  if (ar[vl] > ar[vm]) {
    swap(ar[vl], ar[vm]);
  }
  if (ar[vm] > ar[vj]) {
    swap(ar[vm], ar[vj]);
  }
  if (ar[vl] > ar[vm]) {
    swap(ar[vl], ar[vm]);
  }
  auto vx = ar[vm];
  while (vi <= vj) {
    while (ar[vi] < vx) {
      ++vi;
    }
    while (ar[vj] > vx) {
      --vj;
    }
    if (vi >= vj) {
      break;
    }
    swap(ar[vi], ar[vj]);
    vi++;
    vj--;
  }
  if (vk < (vi - vl)) {
    return Kth(vl, vi, vk);
  }
  return Kth(vi, vr, vk - (vi - vl));
}

int vn;
int vk;

int main() {
  cin >> vn >> vk >> ar[0] >> ar[1];
  for (int i = 2; i <= vn; ++i) {
    ar[i] = (kA * ar[i - 1] + kB * ar[i - 2]) % kMod;
  }
  cout << Kth(0, vn, vk - 1);
  return 0;
}

