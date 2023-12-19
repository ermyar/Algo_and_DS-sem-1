#include <algorithm>
#include <iostream>
#include <vector>

const long long kInf = 1e9 + 100;

struct Node {
  int x;
  int psh = 0;
  int val;
};

class SegTree {
 public:
  void Combine(int ve) {
    if (t_[2 * ve + 1].x > t_[2 * ve + 2].x) {
      t_[ve].x = t_[2 * ve + 2].x;
      t_[ve].val = t_[2 * ve + 2].val;
    } else if (t_[2 * ve + 1].x < t_[2 * ve + 2].x) {
      t_[ve].x = t_[2 * ve + 1].x;
      t_[ve].val = t_[2 * ve + 1].val;
    } else {
      t_[ve].x = t_[2 * ve + 1].x;
      t_[ve].val = t_[2 * ve + 1].val + t_[2 * ve + 2].val;
    }
  }

  void Push(int ve) {
    if (t_[ve].psh == 0) {
      return;
    }
    t_[2 * ve + 1].x += t_[ve].psh;
    t_[2 * ve + 2].x += t_[ve].psh;
    t_[2 * ve + 1].psh += t_[ve].psh;
    t_[2 * ve + 2].psh += t_[ve].psh;
    t_[ve].psh = 0;
  }

  void Update(int ve, std::pair<int, int> lr, std::pair<int, int> lrx,
              int val) {
    auto [l, r] = lr;
    auto [lx, rx] = lrx;
    if (lx <= l && r <= rx) {
      t_[ve].x += val;
      t_[ve].psh += val;
      return;
    }
    if (l >= rx || lx >= r) {
      return;
    }
    Push(ve);
    int mid = (l + r) / 2;
    Update(2 * ve + 1, {l, mid}, {lx, rx}, val);
    Update(2 * ve + 2, {mid, r}, {lx, rx}, val);
    Combine(ve);
  }

  std::pair<int, int> Get(int ve, std::pair<int, int> lr, int lx, int rx) {
    auto [l, r] = lr;
    if (lx <= l && r <= rx) {
      return {t_[ve].x, t_[ve].val};
    }
    if (lx >= r || l >= rx) {
      return {kInf, 0};
    }
    Push(ve);
    int mid = (l + r) / 2;
    auto [p1, q1] = Get(2 * ve + 1, {l, mid}, lx, rx);
    auto [p2, q2] = Get(2 * ve + 2, {mid, r}, lx, rx);
    if (p1 > p2) {
      return {p2, q2};
    }
    if (p1 < p2) {
      return {p1, q1};
    }
    return {p1, q1 + q2};
  }

  void Build(std::vector<int>& ar, int ve, int lx, int rx) {
    if (rx - lx == 1) {
      t_[ve].x = 0;
      t_[ve].val = ar[rx] - ar[lx];
      t_[ve].psh = 0;
      return;
    }
    int mid = (lx + rx) / 2;
    Build(ar, 2 * ve + 1, lx, mid);
    Build(ar, 2 * ve + 2, mid, rx);
    Combine(ve);
  }

  void Init(int sz) { t_.resize(4 * sz, {0, 0, 0}); }

 private:
  std::vector<Node> t_;
};

struct Query {
  int lx;
  int rx;
  int time;
  int val;
};

bool operator<(Query& ax, Query& bx) { return (ax.time < bx.time); }

void Compress(int nu, std::vector<int>& stt, std::vector<Query>& st) {
  sort(stt.begin(), stt.end());
  stt.erase(std::unique(stt.begin(), stt.end()), stt.end());
  for (int i = 0; i < 2 * nu; ++i) {
    st[i].lx = lower_bound(stt.begin(), stt.end(), st[i].lx) - stt.begin();
    st[i].rx = lower_bound(stt.begin(), stt.end(), st[i].rx) - stt.begin();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int nu;
  std::cin >> nu;
  if (nu == 0) {
    std::cout << 0;
    return 0;
  }
  std::vector<Query> st;
  std::vector<int> stt;
  for (int i = 0; i < nu; ++i) {
    Query tmp1;
    Query tmp2;
    std::cin >> tmp1.lx >> tmp1.time >> tmp1.rx >> tmp2.time;
    tmp2.lx = tmp1.lx;
    tmp2.rx = tmp1.rx;
    tmp1.val = 1;
    tmp2.val = -1;
    st.push_back(tmp1);
    st.push_back(tmp2);
    stt.push_back(tmp1.lx);
    stt.push_back(tmp1.rx);
  }
  Compress(nu, stt, st);
  SegTree tmp;
  int sz = stt.size() - 1;
  if (sz == 0) {
    std::cout << 0;
    return 0;
  }
  tmp.Init(sz);
  tmp.Build(stt, 0, 0, sz);
  sort(st.begin(), st.end());
  long long lst = -1;
  long long lval = 0;
  long long ans = 0;
  for (int i = 0; i < 2 * nu; ++i) {
    tmp.Update(0, {0, sz}, {st[i].lx, st[i].rx}, st[i].val);
    if (i + 1 < 2 * nu && st[i + 1].time != st[i].time) {
      auto gt = tmp.Get(0, {0, sz}, 0, sz);
      int len = stt.back() - stt[0];
      if (gt.first == 0) {
        len -= gt.second;
      }
      if (lst == -1) {
        lst = st[i].time;
      }
      ans += (st[i].time - lst) * lval;
      lst = st[i].time;
      lval = len;
    }
    if (i == 2 * nu - 1) {
      ans += (st[i].time - lst) * lval;
    }
  }
  std::cout << ans;
}