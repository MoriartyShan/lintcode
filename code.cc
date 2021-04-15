#include "code.h"



#define  JUDGE(kk) while (l[kk] > 0 && s[kk][0] == s[2][0]) {\
    l[kk]--;\
    l[2]--;\
    s[kk]++;\
    s[2]++;\
    int il[3] = {l[0], l[1], l[2]};\
    const char* is[3] = {s[0], s[1], s[2]};\
    if (isInterleave(is, il, 2 - 1 - kk)) {\
            return true;\
        }\
    }
bool Solution::isInterleave(const char* s[],  int* l, int start) {
  if (l[0] == l[1] && l[0] == 0 && l[2] == 0) return true;
  if (l[0] + l[1] != l[2]) {
    return false;
  }
  if (failed.count((uint64_t(l[0]) << 32) ^ l[1]) > 0) return false;
  int sl[3] = {l[0], l[1], l[2]};\
        const char* ss[3] = {s[0], s[1], s[2]};\

  if(l[0] >= 0 && l[1] >= 0) {
    if (start == 0) {
      JUDGE(0);
      JUDGE(1);
    } else {
      JUDGE(1);
      JUDGE(0);
    }
  }
  failed.emplace((uint64_t(sl[0]) << 32) ^ sl[1]);
  return false;
}

/**
   * @param s1: A string
   * @param s2: A string
   * @param s3: A string
   * @return: Determine whether s3 is formed by interleaving of s1 and s2
   */
bool Solution::isInterleave(string &s1, string &s2, string &s3) {
  // write your code here
  failed.clear();
  int length[3] = {(int)s1.length(), (int)s2.length(), (int)s3.length()};
  const char *str[3] = {s1.c_str(), s2.c_str(), s3.c_str()};
  return isInterleave(str, length);
};


/**
* @param intervals: Sorted interval list.
* @param newInterval: new interval.
* @return: A new interval list.
*/
vector<Interval> Solution::insert(vector<Interval> &intervals, Interval newInterval) {
  // write your code here

  auto merge = [&intervals](Interval &a, Interval &b) {
    if (a.start <= b.start && a.end >= b.start) {
      if (a.end <= b.end) {
        return 1;
      } else {
        //a is bigger than b
        return 2;
      }
    }
    if (a.end < b.start) {
      return -1;
    } else if (a.start > b.end) {
      return -2;
    }
    return 0;
  };
  int tmp = 0;
  int i;
  for (i = 0; i < intervals.size(); i++) {
    int res = merge(intervals[0], newInterval);

    if (tmp == -1 && res == -2) {
      intervals.insert(intervals.begin() + i, newInterval);
      return intervals;
    }

    tmp = res;

    if (res == 1) {
      newInterval.start = intervals[0].start;
      intervals.erase(intervals.begin() + i);
      i--;
      continue;
    } else if (res == 2) {
      break;
    }
    if (i == 0 && res == -2) {
      intervals.insert(intervals.begin(), newInterval);
      return intervals;
    }
//            else if (i == (intervals.size() - 1) && res == -1) {
//
//                break;
//            }
    res = merge(newInterval, intervals[0]);
    if (res == 2) {
      intervals.erase(intervals.begin() + i);
      i--;
      continue;
    } else if (res == 1) {
      newInterval.end = intervals[i].end;
      intervals.erase(intervals.begin() + i);
      i--;
      continue;
    }

  }

  if (i == intervals.size()) {
    intervals.emplace_back(newInterval);
  }
  return intervals;
}



/*
 * @param n: The number of queens
 * @return: All distinct solutions
 */
vector<vector<string>> Solution::solveNQueens(int n) {
  // write your code here
  vector<int> numbers(n);
  auto next_number = [&numbers]() {
    for (int i = 1; i < numbers.size(); i++) {
      if (numbers[i - 1] < numbers[i]) {
        int idx = i - 1, max = numbers[idx];
        for (int j = idx - 1; j >= 0; j--) {
          if (numbers[j] > numbers[idx] && numbers[j] < numbers[i]) {
            idx = j;
            max = numbers[j];
          }
        }
        numbers[idx] = numbers[i];
        numbers[i] = max;
        sort(numbers.begin(), numbers.begin() + i);
        return true;
      }
    }
    return false;
  };

  auto nQ = [](int s, int k) {
    std::string res;
    for (int i = 0; i < s; i ++) {
      if (i == k) {
        res += "Q";
      } else {
        res += ",";
      }
    }
    return res;
  };

  vector<string> use(n);
  for (int i = 0; i < n; i++) {
    use[i] = nQ(n, i);
  }

  int size = 1;
  for (int i = 0; i < n; i++) {
    numbers[i] = i;
    size *= (i + 1);
  }
  vector<vector<string>> res;

  if (n == 0) return res;

  res.reserve(size);
  do {
    res.emplace_back(vector<string>());
    auto &cur = res.back();
    for (int i = 0; i < n; i++) {
      cur.emplace_back(use[numbers[i]]);
    }
    if (res.size() > size) {
      LOG << "size not right " << size << " " << res.size() << std::endl;
      return res;
    }
  } while(next_number());
  if (res.size() < size) {
    exit(0);
  }
  return res;
}

//the max sum value that pass root
int _maxPathSum(const TreeNode* root, int *cur_max){
  if (root == nullptr) {
    return 0;
  }
  int res;
  int l = _maxPathSum(root->left, cur_max);
  int r = _maxPathSum(root->right, cur_max);
  if (l < 0) {
    l = 0;
  }
  if (r < 0) {
    r = 0;
  }

  LOG << "v= " << root->val << "," << l << "," << r << std::endl;
  if (l < r) {
    res = root->val + r;
  } else {
    res = root->val + l;
  }

//  int max = std::max(root->val + l + r, std::max(root->val + l, std::max(root->val + r, root->val)));
  *cur_max = std::max(root->val + l + r, *cur_max);

  return res;
}

int Solution::maxPathSum(TreeNode * root) {
  // write your code here
  int cur_max = std::numeric_limits<int>::lowest();
  _maxPathSum(root, &cur_max);
  return cur_max;
}