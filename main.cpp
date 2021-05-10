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
  std::string s = "aaab";
  unordered_set<string> wordSet;
  wordSet.emplace("a");wordSet.emplace("b");
 bool res = test.wordBreak(s, wordSet);

  LOG << res << std::endl;

  return 0;
}