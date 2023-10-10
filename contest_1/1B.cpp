#include <cmath>
#include <iomanip>
#include <iostream>

const int kMaxn = 1e6 + 100, kEps = 6;

double ar[kMaxn];
double pref[kMaxn];

int main() {
  std::cout << std::fixed << std::setprecision(kEps);
  int nu;
  std::cin >> nu;
  for (int i = 0; i < nu; ++i) {
    std::cin >> ar[i];
    pref[i + 1] = pref[i] + std::log(ar[i]);
  }
  int qu;
  std::cin >> qu;
  while ((qu--) != 0) {
    int lx;
    int rx;
    std::cin >> lx >> rx;
    double val = pref[rx + 1] - pref[lx];
    val /= (double)(rx - lx + 1);
    double ans = std::exp(val);
    std::cout << ans << std::endl;
  }
}
