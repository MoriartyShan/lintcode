#include "code.h"



int main() {
  Solution test;
  ListNode a(3), b(3), c(1), d(2), e(4);
  a.next = &b;
  b.next = &c;
  c.next = &d;
  d.next = &e;
  e.next = nullptr;
//  3->3->1->2->4->null
  ListNode *p = &a;
  while (p != nullptr) {
    std::cout << p->val << "->";
    p = p->next;
  }
  std::cout << std::endl;
  p = test.partition(&a, 3);

  while (p != nullptr) {
    std::cout << p->val << "->";
    p = p->next;
  }

    return 0;
}