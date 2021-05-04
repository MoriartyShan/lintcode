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
  RandomListNode a(1), b(2), c(3), d(4), e(5);
  a.next = &b;
  b.next = &c;
  c.next = &d;
  d.next = &e;


  a.random = &e;
  b.random = &d;
  c.random = &c;
  d.random = &b;
  e.random = &a;


  RandomListNode* n = test.copyRandomList(&a);
  LOG << "-" << n << std::endl;
  RandomListNode::show(10, n);

  return 0;
}