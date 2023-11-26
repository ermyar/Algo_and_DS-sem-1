#include <algorithm>
#include <iostream>
#include <vector>

class SegTree {
 public:
  void Combine(int ve) {
    std::merge(t_[2 * ve + 1].begin(), t_[2 * ve + 1].end(),
               t_[2 * ve + 2].begin(), t_[2 * ve + 2].end(),
               std::back_inserter(t_[ve]));
  }

  long long Get(int ve, std::pair<int, int> lr, std::pair<int, int> lrx, int lq,
                int rq) {
    auto [l, r] = lr;
    auto [lx, rx] = lrx;
    if (lx <= l && r <= rx) {
      return (std::upper_bound(t_[ve].begin(), t_[ve].end(), rq) -
              std::lower_bound(t_[ve].begin(), t_[ve].end(), lq));
    }
    if (lx >= r || l >= rx) {
      return 0;
    }
    int mid = (l + r) / 2;
    return Get(2 * ve + 1, {l, mid}, {lx, rx}, lq, rq) +
           Get(2 * ve + 2, {mid, r}, {lx, rx}, lq, rq);
  }

  void Init(int size) { t_.resize(4 * size); }

  void Build(std::vector<int>& ar, int ve, int lx, int rx) {
    if (rx - lx == 1) {
      t_[ve].push_back(ar[lx]);
      return;
    }
    int mid = (lx + rx) / 2;
    Build(ar, 2 * ve + 1, lx, mid);
    Build(ar, 2 * ve + 2, mid, rx);
    Combine(ve);
  }

 private:
  std::vector<std::vector<int>> t_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int nu;
  int qu;
  std::cin >> nu >> qu;
  std::vector<int> ar(nu);
  for (int i = 0; i < nu; ++i) {
    std::cin >> ar[i];
  }
  SegTree tmp;
  tmp.Init(nu);
  tmp.Build(ar, 0, 0, nu);
  for (int i = 0; i < qu; ++i) {
    int lx;
    int rx;
    int lq;
    int rq;
    std::cin >> lx >> rx >> lq >> rq;
    --lx;
    std::cout << tmp.Get(0, {0, nu}, {lx, rx}, lq, rq) << '\n';
  }
}