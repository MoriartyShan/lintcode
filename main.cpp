#include "code.h"



int main() {
  Solution test;
  TreeNode a(3), b(1), c(0), d(2), e(5), f(4), g(6);
  a.left = &b;
  a.right = &e;
  b.left = &c;
  b.right = &d;
  e.left = &f;
  e.right = &g;

  LOG << test.isValidBST( &a) << std::endl;

    return 0;
}