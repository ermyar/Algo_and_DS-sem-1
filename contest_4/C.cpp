#include <cstddef>
#include <iostream>
#include <string>

const int kMod = 1e9 + 7, kAlp = 137;

struct Node {
  Node* left;
  Node* right;
  int val;
  int height;
  int dif;
  int mx;
  std::string str;
  Node() = default;

  Node(int value, const std::string& strr) {
    left = nullptr;
    right = nullptr;
    val = value;
    height = 1;
    dif = 0;
    mx = value;
    str = strr;
  }

  ~Node() {
    delete left;
    delete right;
  }
};

int GetG(Node* tmp) {
  if (tmp == nullptr) {
    return 0;
  }
  return tmp->height;
}

void Update(Node* tmp) {
  if (tmp == nullptr) {
    return;
  }
  tmp->height = std::max(GetG(tmp->left), GetG(tmp->right)) + 1;
  tmp->dif = GetG(tmp->left) - GetG(tmp->right);
  tmp->mx = tmp->val;
  if (tmp->left != nullptr) {
    tmp->mx = std::max(tmp->val, tmp->left->mx);
  }
  if (tmp->right != nullptr) {
    tmp->mx = std::max(tmp->val, tmp->right->mx);
  }
}

void Print(Node* tmp) {
  if (tmp == nullptr) {
    return;
  }
  std::cout << " + left\n";
  Print(tmp->left);
  std::cout << " - left\n";
  std::cout << tmp->val << '\n';
  std::cout << " + right\n";
  Print(tmp->right);
  std::cout << " - right\n";
}

Node* Rotate(Node* tmp) {
  if (abs(GetG(tmp->left) - GetG(tmp->right)) <= 1) {
    return tmp;
  }
  if (tmp->dif == -2) {
    if (tmp->right->dif == 1) {
      Node* pp = tmp->right;
      Node* pq = pp->left;
      pp->left = pq->right;
      tmp->right = pq->left;
      pq->left = tmp;
      pq->right = pp;
      Update(pp);
      Update(tmp);
      Update(pq);
      return pq;
    }
    Node* pp = tmp->right;
    Node* pq = tmp->right->left;
    tmp->right = pq;
    pp->left = tmp;
    Update(tmp);
    Update(pp);
    return pp;
  }
  if (tmp->left->dif == -1) {
    Node* pp = tmp->left;
    Node* pq = pp->right;
    pp->right = pq->left;
    tmp->left = pq->right;
    pq->right = tmp;
    pq->left = pp;
    Update(pp);
    Update(tmp);
    Update(pq);
    return pq;
  }
  Node* pp = tmp->left;
  Node* pq = tmp->left->right;
  tmp->left = pq;
  pp->right = tmp;
  Update(tmp);
  Update(pp);
  return pp;
}

Node* Add(Node* tmp, int val, const std::string& str) {
  if (tmp == nullptr) {
    return new Node(val, str);
  }
  if (tmp->val < val) {
    tmp->right = Add(tmp->right, val, str);
    Update(tmp->right);
    Update(tmp);
    tmp = Rotate(tmp);
    return tmp;
  }
  tmp->left = Add(tmp->left, val, str);
  Update(tmp->left);
  Update(tmp);
  tmp = Rotate(tmp);
  return tmp;
}

Node* Query(Node* tmp, int val) {
  if (tmp == nullptr) {
    return nullptr;
  }
  if (tmp->val >= val) {
    if (tmp->left == nullptr) {
      return tmp;
    }
    if (tmp->left->mx >= val) {
      return Query(tmp->left, val);
    }
    return tmp;
  }
  if (tmp->right == nullptr) {
    return tmp;
  }
  if (tmp->right->mx >= val) {
    return Query(tmp->right, val);
  }
  return tmp;
}

int Hsh(const std::string& str) {
  long long ans = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    ans *= kAlp;
    ans += str[i] - 'a' + 1;
    ans %= kMod;
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int number;
  std::cin >> number;
  Node* tree1 = nullptr;
  Node* tree2 = nullptr;
  for (int i = 0; i < number; ++i) {
    std::string strs;
    std::string strt;
    std::cin >> strs >> strt;
    int hs1 = Hsh(strs);
    int hs2 = Hsh(strt);
    tree1 = Add(tree1, hs1, strt);
    tree2 = Add(tree2, hs2, strs);
  }
  int ququ;
  std::cin >> ququ;
  for (int i = 0; i < ququ; ++i) {
    std::string str;
    std::cin >> str;
    int val = Hsh(str);
    Node* tmp1 = Query(tree1, val);
    Node* tmp2 = Query(tree2, val);
    if (tmp1 == nullptr) {
      std::cout << "\n";
    } else if (tmp1->val == val) {
      std::cout << tmp1->str << '\n';
    } else if (tmp2->val == val) {
      std::cout << tmp2->str << '\n';
    }
  }
  delete tree1;
  delete tree2;
  return 0;
}
