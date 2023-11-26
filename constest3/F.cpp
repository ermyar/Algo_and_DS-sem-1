#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
  Node* left;
  Node* right;
  int sum = 0;
  int type = 0;

  void Update() { sum = left->sum + right->sum; }

  Node(int val = 0) {
    left = nullptr;
    right = nullptr;
    sum = val;
  }

  Node(Node* lx, Node* rx) {
    left = lx;
    right = rx;
    sum = lx->sum + rx->sum;
  }

  ~Node() {
    if (type >= 2) {
      delete right;
    }
    if (type % 2 == 1) {
      delete left;
    }
  }

  void Build(std::vector<int>& ar, int lx, int rx) {
    if (rx - lx == 1) {
      sum = ar[lx];
      return;
    }
    int mx = (rx + lx) / 2;
    left = new Node;
    right = new Node;
    left->Build(ar, lx, mx);
    right->Build(ar, mx, rx);
    type = 3;
    Update();
  }

  int Get(int lx, int rx, int lq, int rq) const {
    if (lq <= lx && rx <= rq) {
      return sum;
    }
    if (lq >= rx || lx >= rq) {
      return 0;
    }
    int mid = (lx + rx) / 2;
    return left->Get(lx, mid, lq, rq) + right->Get(mid, rx, lq, rq);
  }

  int Get(Node* other, int lx, int rx, int lq, int rq) const {
    if (lq <= lx && rx <= rq) {
      return sum - other->sum;
    }
    if (lq >= rx || lx >= rq) {
      return 0;
    }
    int mid = (lx + rx) / 2;
    return left->Get(other->left, lx, mid, lq, rq) +
           right->Get(other->right, mid, rx, lq, rq);
  }

  Node* Update(int lx, int rx, int pos, int val) const {
    if (rx - lx == 1) {
      return new Node(sum + val);
    }
    int mid = (lx + rx) / 2;
    if (pos < mid) {
      auto* tmp = new Node(left->Update(lx, mid, pos, val), right);
      tmp->type = 1;
      return tmp;
    }
    auto* tmp = new Node(left, right->Update(mid, rx, pos, val));
    tmp->type = 2;
    return tmp;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int nu;
  int qu;
  std::cin >> nu >> qu;
  std::vector<int> ar(nu);
  std::vector<int> cnt(nu, 0);
  for (int i = 0; i < nu; ++i) {
    std::cin >> ar[i];
  }
  std::vector<Node*> st;
  st.push_back(new Node);
  st[0]->Build(cnt, 0, nu);
  for (int i = 0; i < nu; ++i) {
    st.push_back(st.back()->Update(0, nu, ar[i] - 1, 1));
  }
  for (int i = 0; i < qu; ++i) {
    int lx;
    int rx;
    int lq;
    int rq;
    std::cin >> lx >> rx >> lq >> rq;
    --lx;
    --lq;
    std::cout << st[rx]->Get(st[lx], 0, nu, lq, rq) << '\n';
  }
  for (int i = 0; i <= nu; ++i) {
    delete st[i];
  }
}