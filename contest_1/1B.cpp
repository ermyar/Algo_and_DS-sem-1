#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

const int kEps = 6;

void DoQuest(std::vector<double>& pref) {
  int lx;
  int rx;
  std::cin >> lx >> rx;
  double val = pref[rx + 1] - pref[lx];
  val /= (double)(rx - lx + 1);
  double ans = std::exp(val);
  std::cout << ans << std::endl;
}

int main() {
  std::cout << std::fixed << std::setprecision(kEps);
  int number;
  std::cin >> number;
  std::vector<double> ar(number);
  std::vector<double> pref(number + 1);
  pref[0] = 0;
  for (int i = 0; i < number; ++i) {
    std::cin >> ar[i];
    pref[i + 1] = pref[i] + std::log(ar[i]);
  }
  int quest_count;
  std::cin >> quest_count;
  for (int i = 0; i < quest_count; ++i) {
    DoQuest(pref);
  }
}
