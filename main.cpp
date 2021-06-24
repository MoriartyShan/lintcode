#include "code.h"
#include <map>
#include <list>



int main() {
  lintcode::Solution test;
  lintcode::ListNode a(-1), b(0), c(1), d(2), e(2), f(2), g(2), h(3), i(3), j(4);//0->1->1->2->3->null
  a.next = &b;
  b.next = &c;
  c.next = &d;
  d.next = &e;
  e.next = &f;
  f.next = &g;
  g.next = &h;
  h.next = &i;
  i.next = &j;
//  h.next = &f;
//  h.next = &f;
  //a.show(10);
  //lintcode::ListNode *head = test.deleteDuplicates2(&a);
  std::vector<int> v = {0};

//  string n = "m";
//  LOG << n << std::endl;
//  LOG << n.substr(1) << std::endl;

  std::string dict = "aab";
//  LOG << (int64_t)5201314*5201314<< std::endl;
  int sq = test.fastPower(27123, 5201314, 78965412);
  LOG << "sq = " << sq << std::endl << "," << 1 % 3;
//  LOG << "sqrt " << std::sqrt(2147483648.0);
  return 0;
}