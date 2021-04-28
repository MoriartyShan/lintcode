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
  std::vector<int> m = {-15,-7,-6,-1,1,2,6,11,15,15};
  int n = test.removeDuplicates(m);
  LOG << "-" << n << std::endl;
  show_vector(m);
  return 0;
}