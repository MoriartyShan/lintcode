#include "code.h"



int main() {
    Solution test;
    TreeNode root(1), l(2), r(3);
  root.left = &l;
  root.right = &r;
    LOG << test.maxPathSum(&root);

    return 0;
}