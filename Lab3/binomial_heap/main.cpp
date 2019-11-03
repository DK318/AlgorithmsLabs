#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

struct Node {
  int key;
  Node* parent;
  Node* child;
  Node* sibling;
  int degree;
};

class binomial {
 public:
  Node* head;
  binomial(Node *head) : head(head) {}
  Node* newNode(int key) {
    Node *temp = new Node;
    temp->key = key;
    temp->degree = 0;
    temp->child = temp->parent = temp->sibling = nullptr;
    return temp;
  }
  binomial merge(binomial h1, binomial h2) {
    if (h1.head == nullptr) {
      return h2;
    }
    if (h2.head == nullptr) {
      return h1;
    }
    Node* curH = nullptr;
    Node* curH1 = h1.head;
    Node* curH2 = h2.head;
    while (curH1 != nullptr && curH2 != nullptr) {
      if (curH1->degree < curH1->degree) {
        curH->sibling = curH1;
        curH = curH1;
        curH1 = curH1->sibling;
      } else {
        curH->sibling = curH2;
        curH = curH2;
        curH2 = curH2->sibling;
      }
    }
    if (curH1 == nullptr) {
      while (curH2 != nullptr) {
        curH->sibling = curH2;
        curH2 = curH2->sibling;
      }
    } else {
      while (curH1 != nullptr) {
        curH->sibling = curH1;
        curH1 = curH1->sibling;
      }
    }
    while (curH->sibling != nullptr) {
      if (curH->degree == curH->sibling->degree) {
        curH->parent = curH->sibling;
        Node* tmp = curH->sibling;
        curH->sibling = curH->sibling->child;
        curH = tmp;
        continue;
      }
      curH = curH->sibling;
    }
    return binomial(curH);
  }
};

int main() {

  return 0;
}