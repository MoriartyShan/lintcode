#include "code.h"

void show_vector(const std::vector<int>& v) {
    LOG << "vector:";
    for (auto m : v) {
        std::cout << m << ",";
    }
    std::cout << std::endl;
}

int main() {
  Solution test;
  ListNode a(4), b(21), c(25), d(25), e(31);
  a.next = &b;
  b.next = &c;

  c.next = &d;
  d.next = &e;
  b.next = nullptr;
  TreeNode* n = test.sortedListToBST(&a);

  LOG << test.serialize(n);

  return 0;
}