#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

const int kEps = 6;

void DoQuest(std::vector<double>& pref) {
  int left;
  int right;
  std::cin >> left >> right;
  double value = pref[right + 1] - pref[left];
  value /= (right - left + 1);
  double answer = std::exp(value);
  std::cout << answer << std::endl;
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
