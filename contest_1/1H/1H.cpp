#include <iostream>
#include <vector>

using namespace std;

const int kMaxn = 1e6 + 100;

int ar[kMaxn];

void Sort(int vl, int vr) {
  if (vr - vl <= 1) {
    return;
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
  int vx = ar[vm];
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
  Sort(vl, vi);
  Sort(vi, vr);
}

int vn;

int main() {
  cin >> vn;
  for (int i = 0; i < vn; ++i) {
    cin >> ar[i];
  }
  Sort(0, vn);
  for (int i = 0; i < vn; ++i) {
    cout << ar[i] << ' ';
  }
  cout << endl;
  return 0;
}

