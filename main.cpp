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
  std::vector<int> m = {1, 1, 1, 1, 2, 2, 2,2 ,2};
  int n = test.removeDuplicates2(m);
  LOG << "-" << n << std::endl;
  show_vector(m);
  return 0;
}