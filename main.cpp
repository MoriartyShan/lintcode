#include "code.h"



int main() {
  Solution test;
  ListNode a(0), b(5), c(4), d(3), e(2), f(1), g(6);
  a.next = &b;
  b.next = &c;
  c.next = &d;
  d.next = &e;
  e.next = &f;
  f.next = &g;

//  3->3->1->2->4->null
  ListNode *p = &a;

  a.show(20);
  p = test.sortList(&a);
  p->show(20);

    return 0;
}