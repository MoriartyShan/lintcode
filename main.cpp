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
  std::string s = "ababababababababababababcbabababababababababababa";
  int res = test.minCut(s);

  LOG << res << std::endl;

  return 0;
}