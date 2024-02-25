#include <iostream>

const int kMagicNumber = 15;

struct Node {
  Node* left;
  Node* right;
  int val;
  long long pr;
  int size;

  Node(int xx) {
    left = nullptr;
    right = nullptr;
    val = xx;
    pr = (rand() << kMagicNumber) + rand();
    size = 1;
  }

  ~Node() {
    delete left;
    delete right;
  }
};

int GetSize(Node* root) {
  if (root == nullptr) {
    return 0;
  }
  return root->size;
}

void Update(Node* root) {
  if (root == nullptr) {
    return;
  }
  root->size = GetSize(root->left) + GetSize(root->right) + 1;
}

Node* Merge(Node* root1, Node* root2) {
  if (root1 == nullptr) {
    return root2;
  }
  if (root2 == nullptr) {
    return root1;
  }
  if (root1->pr > root2->pr) {
    root1->right = Merge(root1->right, root2);
    Update(root1);
    return root1;
  }
  root2->left = Merge(root1, root2->left);
  Update(root2);
  return root2;
}

std::pair<Node*, Node*> Split(Node* root, int key) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  if (root->val <= key) {
    auto [root1, root2] = Split(root->right, key);
    root->right = root1;
    Update(root);
    return {root, root2};
  }
  auto [root1, root2] = Split(root->left, key);
  root->left = root2;
  Update(root);
  return {root1, root};
}

std::pair<Node*, Node*> Slice(Node* root, int key) {
  if (GetSize(root) <= key) {
    return {root, nullptr};
  }
  if (GetSize(root->left) >= key) {
    auto [root1, root2] = Slice(root->left, key);
    root->left = root2;
    Update(root);
    return {root1, root};
  }
  auto [root1, root2] = Slice(root->right, key - 1 - GetSize(root->left));
  root->right = root1;
  Update(root);
  return {root, root2};
}

Node* Insert(Node* root, int val) {
  auto [root12, root3] = Split(root, val);
  auto [root1, root2] = Split(root12, val - 1);
  if (root2 == nullptr) {
    root2 = new Node(val);
  }
  return Merge(root1, Merge(root2, root3));
}

Node* Erase(Node* root, int val) {
  auto [root12, root3] = Split(root, val);
  auto [root1, root2] = Split(root12, val - 1);
  delete root2;
  return Merge(root1, root3);
}

bool Check(Node*& root, int val) {
  auto [root12, root3] = Split(root, val);
  auto [root1, root2] = Split(root12, val - 1);
  bool ans = true;
  if (root2 == nullptr) {
    ans = false;
  }
  root = Merge(root1, Merge(root2, root3));
  return ans;
}

void Input(std::string& str, int val, Node*& root) {
  if (str == "insert") {
    root = Insert(root, val);
  }
  if (str == "delete") {
    root = Erase(root, val);
  }
  if (str == "exists") {
    bool tmp = Check(root, val);
    if (tmp) {
      std::cout << "true\n";
    } else {
      std::cout << "false\n";
    }
  }
  if (str == "next") {
    auto [root1, root23] = Split(root, val);
    auto [root2, root3] = Slice(root23, 1);
    if (root2 == nullptr) {
      std::cout << "none\n";
    } else {
      std::cout << root2->val << '\n';
    }
    root23 = Merge(root2, root3);
    root = Merge(root1, root23);
  }
  if (str == "prev") {
    auto [root12, root3] = Split(root, val - 1);
    auto [root1, root2] = Slice(root12, GetSize(root12) - 1);
    if (root2 == nullptr) {
      std::cout << "none\n";
    } else {
      std::cout << root2->val << '\n';
    }
    root12 = Merge(root1, root2);
    root = Merge(root12, root3);
  }
  if (str == "kth") {
    auto [root1, root23] = Slice(root, val);
    auto [root2, root3] = Slice(root23, 1);
    if (root2 == nullptr) {
      std::cout << "none\n";
    } else {
      std::cout << root2->val << '\n';
    }
    root23 = Merge(root2, root3);
    root = Merge(root1, root23);
  }
}

int main() {
  Node* root = nullptr;
  std::string str;
  int val;
  while (std::cin >> str >> val) {
    Input(str, val, root);
  }
  delete root;
  return 0;
}
