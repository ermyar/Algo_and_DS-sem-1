#include <iostream>
#include <vector>

void Insert(std::vector<int>& left, std::vector<int>& right, int val, int pos) {
  int tmp = left[pos];
  right[tmp] = val;
  left[pos] = val;
  right[val] = pos;
  left[val] = tmp;
}

void Delete(std::vector<int>& left, std::vector<int>& right, int pos) {
  right[left[pos]] = right[pos];
  left[right[pos]] = left[pos];
}

int main() {
  int number;
  std::cin >> number;
  std::vector<int> left(number + 2);
  std::vector<int> right(number + 2);
  right[0] = number + 1;
  left[number + 1] = 0;
  int middle = 0;
  int cnt = 0;
  for (int i = 0; i < number; ++i) {
    char ch;
    std::cin >> ch;
    if (ch == '+') {
      int val;
      std::cin >> val;
      Insert(left, right, val, number + 1);
      cnt++;
      if (cnt % 2 == 1) {
        middle = right[middle];
      }
    }
    if (ch == '*') {
      int val;
      std::cin >> val;
      Insert(left, right, val, right[middle]);
      cnt++;
      if (cnt % 2 == 1) {
        middle = right[middle];
      }
    }
    if (ch == '-') {
      std::cout << right[0] << "\n";
      cnt--;
      Delete(left, right, right[0]);
      if (cnt % 2 == 1) {
        middle = right[middle];
      }
      if (cnt == 0) {
        middle = 0;
      }
    }
  }
  return 0;
}
