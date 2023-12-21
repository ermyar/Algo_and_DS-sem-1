#include <algorithm>
#include <iostream>
#include <vector>

class Fenwick {
 public:
  void Update(int val, int tmp) {
    int rx = std::lower_bound(vals.begin(), vals.end(), val) - vals.begin();
    for (int j = rx; j < (int)tr.size(); j |= (j + 1)) {
      tr[j] += tmp;
    }
  }

  long long Get(int val) {
    if (val < vals[0]) {
      return 0;
    }
    int rx = std::upper_bound(vals.begin(), vals.end(), val) - vals.begin() - 1;
    long long ans = 0;
    for (int j = rx; j > 0; j = (j & (j + 1)) - 1) {
      ans += tr[j];
    }
    if (rx == 0) {
      ans = tr[0];
    }
    return ans;
  }

  void Build(const std::vector<int>& st) {
    tr.resize(st.size() + 1, 0);
    for (auto i : st) {
      vals.push_back(i);
    }
  }

 private:
  std::vector<long long> tr;
  std::vector<int> vals;
};

struct FenOfFen {
  std::vector<Fenwick> tr;

  void Update(int rx, int val, int weight) {
    for (int i = rx; i < (int)tr.size(); i |= (i + 1)) {
      tr[i].Update(val, weight);
    }
  }

  long long Get(int rx, int val) {
    long long ans = 0;
    for (int j = rx; j > 0; j = (j & (j + 1)) - 1) {
      ans += tr[j].Get(val);
    }
    if (rx == 0) {
      ans = tr[0].Get(val);
    }
    return ans;
  }

  void Build(const std::vector<std::vector<int>>& st) {
    tr.resize(st.size());
    for (int i = 0; i < st.size(); ++i) {
      tr[i].Build(st[i]);
    }
  }
};

void Input(int nu, std::vector<int>& ar_x, std::vector<int>& ar_y,
           std::vector<int>& ar_w, std::vector<int>& st_x) {
  for (int i = 0; i < nu; ++i) {
    int var_x;
    int var_y;
    int var_w;
    std::cin >> var_x >> var_y >> var_w;
    st_x.push_back(var_x);
    ar_x.push_back(var_x);
    ar_y.push_back(var_y);
    ar_w.push_back(var_w);
  }
}

void Compress(int nu, std::vector<int>& st_x, std::vector<int>& ar_x,
              std::vector<int>& ar_y, FenOfFen& tmp) {
  std::sort(st_x.begin(), st_x.end());
  st_x.erase(std::unique(st_x.begin(), st_x.end()), st_x.end());
  for (int i = 0; i < nu; ++i) {
    ar_x[i] =
        std::lower_bound(st_x.begin(), st_x.end(), ar_x[i]) - st_x.begin();
  }
  std::vector<std::vector<int>> st(st_x.size());
  for (int i = 0; i < nu; ++i) {
    for (int j = ar_x[i]; j < (int)st_x.size(); j |= (j + 1)) {
      st[j].push_back(ar_y[i]);
    }
  }
  tmp.tr.resize(st.size());
  for (int i = 0; i < (int)st.size(); ++i) {
    std::sort(st[i].begin(), st[i].end());
    st[i].erase(std::unique(st[i].begin(), st[i].end()), st[i].end());
  }
  tmp.Build(st);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int nu;
  std::cin >> nu;
  std::vector<int> st_x;
  std::vector<int> ar_x;
  std::vector<int> ar_y;
  std::vector<int> ar_w;
  Input(nu, ar_x, ar_y, ar_w, st_x);
  FenOfFen tmp;
  Compress(nu, st_x, ar_x, ar_y, tmp);
  for (int i = 0; i < nu; ++i) {
    tmp.Update(ar_x[i], ar_y[i], ar_w[i]);
  }
  int qu;
  std::cin >> qu;
  for (int i = 0; i < qu; ++i) {
    std::string str;
    std::cin >> str;
    int tmp_x;
    int tmp_y;
    std::cin >> tmp_x >> tmp_y;
    if (str == "get") {
      int rx =
          std::upper_bound(st_x.begin(), st_x.end(), tmp_x) - st_x.begin() - 1;
      std::cout << tmp.Get(rx, tmp_y) << '\n';
    } else {
      --tmp_x;
      int rx = ar_x[tmp_x];
      tmp.Update(rx, ar_y[tmp_x], tmp_y - ar_w[tmp_x]);
      ar_w[tmp_x] = tmp_y;
    }
  }
}
