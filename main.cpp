#include "code.h"



int main() {
  Solution test;
  ListNode a(3), b(2), c(1), d(0), e(4);
  a.next = &b;
  b.next = &c;
  c.next = &d;
  d.next = &e;
  e.next = nullptr;
//  3->3->1->2->4->null
  ListNode *p = &a;
  c.next = nullptr;
  a.show(10);
  test.reorderList(&a);
  a.show(10);
  return 0;
}