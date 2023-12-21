#include <iostream>

const int kMod = 1e9;

struct Node {
  Node* left;
  Node* right;
  int val;
  int height;
  int dif;
  int mx;
  Node() = default;

  Node(int value) {
    left = nullptr;
    right = nullptr;
    val = value;
    height = 1;
    dif = 0;
    mx = value;
  }

  ~Node() {
    delete left;
    delete right;
  }
};

class AVLtree {
 public:
  
  void Insert(int val) {
    root = Add(root, val);
  }

  int GetAns(int val) {
    return Query(root, val);
  }
 
  ~AVLtree() {
    delete root;
  }

 private: 

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

  Node* Add(Node* tmp, int val) {
    if (tmp == nullptr) {
      return new Node(val);
    }
    if (tmp->val < val) {
      tmp->right = Add(tmp->right, val);
      Update(tmp->right);
      Update(tmp);
      tmp = Rotate(tmp);
      return tmp;
    }
    tmp->left = Add(tmp->left, val);
    Update(tmp->left);
    Update(tmp);
    tmp = Rotate(tmp);
    return tmp;
  }

  int Query(Node* tmp, int val) {
    if (tmp == nullptr) {
      return -1;
    }
    if (tmp->val >= val) {
      if (tmp->left == nullptr) {
        return tmp->val;
      }
      if (tmp->left->mx >= val) {
        return Query(tmp->left, val);
      }
      return tmp->val;
    }
    if (tmp->right == nullptr) {
      return tmp->val;
    }
    if (tmp->right->mx >= val) {
      return Query(tmp->right, val);
    }
    return tmp->val;
  }


  Node* root = nullptr;
};

int main() {
  int number;
  std::cin >> number;
  AVLtree tmp;
  int lst = -2;
  for (int i = 0; i < number; ++i) {
    char ch;
    int vx;
    std::cin >> ch >> vx;
    if (ch == '+') {
      if (lst != -2) {
        vx = (vx + lst) % kMod;
      }
      tmp.Insert(vx);
      lst = -2;
    } else {
      lst = tmp.GetAns(vx);
      if (lst < vx) {
        lst = -1;
      }
      std::cout << lst << '\n';
    }
  }
  return 0;
}
