#include "code.h"
#include <list>



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

namespace lintcode {

template<>
void show_vector<std::vector<std::string>>(const std::vector<std::vector<std::string>>& v) {
  for (auto m : v) {
    show_vector(m);
  }
}

template<>
void show_vector<std::vector<int>>(const std::vector<std::vector<int>>& v) {
  for (auto &sub : v) {
    show_vector(sub);
  }
}

bool Solution::isInterleave(const char *s[], int *l, int start) {
  if (l[0] == l[1] && l[0] == 0 && l[2] == 0) return true;
  if (l[0] + l[1] != l[2]) {
    return false;
  }
  if (failed.count((uint64_t(l[0]) << 32) ^ l[1]) > 0) return false;
  int sl[3] = {l[0], l[1], l[2]};\
        const char *ss[3] = {s[0], s[1], s[2]};\

  if (l[0] >= 0 && l[1] >= 0) {
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
  int length[3] = {(int) s1.length(), (int) s2.length(), (int) s3.length()};
  const char *str[3] = {s1.c_str(), s2.c_str(), s3.c_str()};
  return isInterleave(str, length);
};


/**
* @param intervals: Sorted interval list.
* @param newInterval: new interval.
* @return: A new interval list.
*/
vector<Interval>
Solution::insert(vector<Interval> &intervals, Interval newInterval) {
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
    for (int i = 0; i < s; i++) {
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
  } while (next_number());
  if (res.size() < size) {
    exit(0);
  }
  return res;
}

//the max sum value that pass root
int _maxPathSum(const TreeNode *root, int *cur_max) {
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

int Solution::maxPathSum(TreeNode *root) {
  // write your code here
  int cur_max = std::numeric_limits<int>::lowest();
  _maxPathSum(root, &cur_max);
  return cur_max;
}


void
_backPack2(const int m, const int n, const int *A, const int size, int *cur_max,
           std::vector<bool> &flag) {
  if (m == *cur_max || size == 0 || m == 0 || n >= m) {
    return;
  }

  for (int i = 0; i < size; i++) {
    int sum = (A[i] + n);
    if (sum <= m && (!flag[sum])) {
      *cur_max = std::max(sum, *cur_max);
      LOG << "sum = " << *cur_max << std::endl;
      flag[sum] = true;

      _backPack2(m, sum, A + i + 1, size - i - 1, cur_max, flag);
    }
  }
  return;
}


///believe that this one can run currect, but it cost too much time.
int _backPack(int m, const int *A, const int size, int *cur) {
  int c = 0;
  if (m == 0 || size == 0) {
    return c;
  }
  if (*cur == 0) {
    return c;
  }
  for (int i = 0; i < size; i++) {
    if (A[i] <= m) {
      int left = m - A[i];
      *cur = std::min(*cur, left);
      c++;
      c += _backPack(left, A + i + 1, size - i - 1, cur);
    }
  }
  return c;
}


/**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
int Solution::backPack(int m, vector<int> &A) {
  // write your code here
#if 0
  int res = std::numeric_limits<int>::max();
  _backPack(m, A.data(), A.size(), &res);
  if (m > res)
    return m - res;
  return 0;
#else
  int res = std::numeric_limits<int>::lowest();
  std::vector<bool> flag(m, false);

  _backPack2(m, (int) 0, A.data(), (int) A.size(), &res, flag);
  return res;
#endif
}

bool
isValidBST(TreeNode *root, const int max, const int min, const bool has_max,
           const bool has_min) {
  bool res = true;
  if (root == nullptr) {
    return res;
  }

  if (root->left != nullptr) {
    if (root->val > root->left->val
        && (!has_min || root->left->val > min)
        && (!has_max || root->left->val < max)) {
      res = isValidBST(root->left, root->val, min, true, has_min);
    } else {
      res = false;
    }
  }

  if (res && root->right != nullptr) {
    if (root->val < root->right->val
        && (!has_min || root->right->val > min)
        && (!has_max || root->right->val < max)) {
      res = isValidBST(root->right, max, root->val, has_max, true);
    } else {
      res = false;
    }
  }

  return res;
}

/**
     * @param root: The root of binary tree.
     * @return: True if the binary tree is BST, or false
     */
bool Solution::isValidBST(TreeNode *root) {
  // write your code here
  return lintcode::isValidBST(root, std::numeric_limits<int>::max(),
                      std::numeric_limits<int>::lowest(), false, false);
}


ListNode *
partition(ListNode *head, const int x, ListNode **left, ListNode **right) {
  if (head == nullptr) {
    if ((*left) != nullptr) {
      (*left) = nullptr;
    }

    if ((*right) != nullptr) {
      (*right) = nullptr;
    }
    return head;
  } else if (head->val >= x) {

    *right = head;
    return partition(head->next, x, left, &head->next);
  }

  *left = head;
  return partition(head->next, x, &head->next, right);
}

/**
 * @param head: The first node of linked list
 * @param x: An integer
 * @return: A ListNode
 */
ListNode *Solution::partition(ListNode *head, int x) {
  // write your code here
  ListNode *left = nullptr, *right = nullptr;
  lintcode::partition(head, x, &left, &right);
  right->show(5);
  left->show(5);
  {
    ListNode *left_tail = left;
    while (left_tail != nullptr && left_tail->next != nullptr) {
      left_tail = left_tail->next;
    }
    if (left_tail != nullptr) {
      left_tail->next = right;
    } else {
      left = right;
    }
  }

  return left;

}

/**
* @param root: The root of binary tree.
* @return: An integer
*/
int Solution::maxDepth(TreeNode *root) {
  // write your code here
#if 0
  if (root == nullptr) {
      return 0;
  }
  int left = 1 + maxDepth(root->left);
  int right = 1 + maxDepth(root->right);
  return (left > right) ? left : right;
#else
  int depth = 0;
  while (root != nullptr) {
    depth++;

  }


#endif
}

int find_min(ListNode *head) {
  int max = head->val;
  int min = head->val;
}


ListNode *
partition(ListNode *head, const int x, ListNode **left, ListNode **equal,
          ListNode **right) {
  if (head == nullptr) {
    if ((*left) != nullptr) {
      (*left) = nullptr;
    }
    if ((*equal) != nullptr) {
      (*equal) = nullptr;
    }
    if ((*right) != nullptr) {
      (*right) = nullptr;
    }
    return head;
  } else if (head->val > x) {

    *right = head;
    return partition(head->next, x, left, equal, &head->next);
  } else if (head->val == x) {
    *equal = head;
    return partition(head->next, x, left, &head->next, right);
  }

  *left = head;
  return partition(head->next, x, &head->next, equal, right);
}

/**
 * @param head: The head of linked list.
 * @return: You should return the head of the sorted linked list, using constant space complexity.
 */
ListNode *Solution::sortList(ListNode *head) {
  // write your code here
  auto cat = [](ListNode *left, ListNode *right) {
    ListNode *left_tail = left;
    while (left_tail != nullptr && left_tail->next != nullptr) {
      left_tail = left_tail->next;
    }
    if (left_tail != nullptr) {
      left_tail->next = right;
    } else {
      left = right;
    }
    return left;
  };

  if (head != nullptr) {
    ListNode *left = nullptr, *right = nullptr, *equal = nullptr;
    lintcode::partition(head, head->val, &left, &equal, &right);
    left = sortList(left);
    right = sortList(right);

    equal = cat(equal, right);
    left = cat(left, equal);
    return left;
  }
  return nullptr;
}

void Solution::reorderList(ListNode *head) {
  // write your code here

  uint32_t size = 0;
  ListNode *tmp = head, *tmp2 = nullptr;
  while (tmp != nullptr) {
    size++;
    tmp = tmp->next;
  }

  const uint32_t split_pos = (size + 1) >> 1;
  const uint32_t right_size = size - split_pos;
  tmp = head;
  size = 0;
  while (size != split_pos) {
    size++;
    tmp2 = tmp;
    tmp = tmp->next;
  }
  if (tmp2 != nullptr) {
    //new tail of head
    tmp2->next = nullptr;
  }


  ///reverse
  ListNode *right_head = nullptr;
  while (tmp != nullptr) {
    tmp2 = tmp->next;
    tmp->next = right_head;
    right_head = tmp;
    tmp = tmp2;
  }

  head->show(10);
  right_head->show(10);


  tmp = head;
  for (size_t i = 0; i < right_size; i++) {
    tmp2 = tmp->next;
    tmp->next = right_head;
    right_head = right_head->next;
    tmp->next->next = tmp2;
    tmp = tmp2;
  }
}

/*
   * @param nums: An ineger array
   * @return: An integer
   */
int Solution::removeDuplicates(vector<int> &nums) {
  // write your code here
  const size_t size = nums.size();
  int *ptr = nums.data();
  int begin = -1, end = -1;
  for (size_t i = 1; i < size; i++) {
    if (begin < 0) {
      if (ptr[i] == ptr[i - 1]) {
        begin = i - 1;
      }
    } else if (ptr[i] != ptr[i - 1]) {
      end = i - 1;
    }
    if (end >= 0) {
      for (size_t j = begin; j < end; j++) {
        ptr[j] = std::numeric_limits<int>::max();
      }
      begin = -1;
      end = -1;
    }
  }
  if (begin >= 0) {
    for (size_t i = begin + 1; i < size; i++) {
      ptr[i] = std::numeric_limits<int>::max();
    }
  }

  int cur = 0;
  for (size_t i = 0; i < size; i++) {
    if (ptr[i] == std::numeric_limits<int>::max()) {
      continue;
    } else if (i == cur) {
      cur++;
      continue;
    }
    ptr[cur] = ptr[i];
    cur++;
  }
  nums.resize(cur);
  return cur;
}

int Solution::removeDuplicates2(vector<int> &nums) {
  // write your code here
  const size_t size = nums.size();
  if (size == 0) {
    return 0;
  }
  int *ptr = nums.data();
  int begin = -1, cur_pos = 1;
  for (size_t i = 1; i < size; i++) {
    if (ptr[i] == ptr[i - 1]) {
      if (begin < 0) {
        begin = i;

        if (i != cur_pos) {
          ptr[cur_pos] = ptr[i];
        }
        cur_pos++;
      } else {
        continue;
      }
    } else if (i != cur_pos) {
      begin = -1;
      ptr[cur_pos] = ptr[i];
      cur_pos++;
    } else {
      begin = -1;
      cur_pos++;
    }
  }

  nums.resize(cur_pos);
  return cur_pos;
}

bool Solution::hasCycle(ListNode *head) {
  // write your code here
#if 0
  std::set<ListNode *> nodes;
  while (head != nullptr) {
    if (nodes.count(head) > 0) {
      return true;
    }
    nodes.insert(head);
    head = head->next;
  }
    return false;
#else
  //fast and low ptr

  if (head == nullptr) {
    return false;
  }
  ListNode *fast = head->next, *slow = head;

  while (true) {
    if (fast == nullptr) {
      return false;
    } else if (slow == fast) {
      return true;
    }

    fast = fast->next;
    if (fast != nullptr) {
      fast = fast->next;
    }
    slow = slow->next;

  }

  return true;
#endif

}

ListNode *Solution::mergeKLists(vector<ListNode *> &lists) {
  // write your code here
  /////Todo::merge each two lists may be faster
  ListNode *first = nullptr, **current = &first;
  while (true) {
    int pos = -1;
    for (int i = 0; i < lists.size(); i++) {
      if (lists[i] != nullptr) {
        if (pos < 0 || lists[i]->val < lists[pos]->val) {
          pos = i;
        }
      }
    }
    if (pos >= 0) {
      *current = lists[pos];
      current = &(*current)->next;
      lists[pos] = lists[pos]->next;
    } else {
      break;
    }
  }
  return first;
}

const RandomListNode *
searchFromOrigin(const RandomListNode *origin, const RandomListNode *current,
                 const RandomListNode *aim) {
  if (aim != nullptr && current != nullptr) {
    if (origin == aim) {
      return current;
    }
    auto res = searchFromOrigin(origin->next, current->next, aim);
    if (res != nullptr) {
      return res;
    }

    res = searchFromOrigin(origin->random, current->random, aim);
    if (res != nullptr) {
      return res;
    }
  }
  return nullptr;
}

void copyRandomList(
  RandomListNode **new_head,
  const RandomListNode *old_head,
  RandomListNode **current,
  RandomListNode *copy) {
  if (copy != nullptr && (*current) == nullptr) {
    auto res = searchFromOrigin(old_head, *new_head, copy);
    if (res == nullptr) {
      res = new RandomListNode(copy->label);
    }
    *current = (RandomListNode *) res;

    copyRandomList(new_head, old_head, &(*current)->next, copy->next);
    copyRandomList(new_head, old_head, &(*current)->random, copy->random);
  }
  return;
}

string Solution::serialize(TreeNode *root) {
  // write your code here
  string res = "{";
  std::queue<TreeNode *> keep;
  if (root)
    keep.push(root);
  while (keep.size() > 0) {
    root = keep.front();
    keep.pop();
    if (root != nullptr) {
      res += (std::to_string(root->val) + ",");
      keep.push(root->left);
      keep.push(root->right);
    } else {
      res += "#,";
    }
  }

  int last = res.length();
  if (last >= 2) {
    while (res.substr(last - 2, 2) == "#,") {
      last = last - 2;
    }
    res.erase(last);
    res[last - 1] = '}';
  } else {
    res += "}";
  }

  res[last - 1] = '}';
  return res;
}

/**
 * This method will be invoked second, the argument data is what exactly
 * you serialized at method "serialize", that means the data is not given by
 * system, it's given by your own serialize method. So the format of data is
 * designed by yourself, and deserialize it here as you serialize it in
 * "serialize" method.
 */
TreeNode *Solution::deserialize(string &data) {
  // write your code here

  auto findLast = [](
    std::queue<TreeNode *> &cur,
    std::queue<TreeNode *> &buf) {
    TreeNode *current = nullptr;
    if (cur.size() == 0) {
      buf.swap(cur);
    }
    if (cur.size() > 0) {
      current = cur.front();
      cur.pop();
    }
    return current;
  };


  int cur = 0, subLength = 0;
  cur++;
  const int l = data.length();
  std::queue<TreeNode *> current_, swap_;
  TreeNode *root = nullptr, *tmp = nullptr;
  bool cur_side = true; //true=>left, false=>right

  auto UpdateValue = [&](TreeNode *NewNode) {
    if (cur_side) {
      tmp = findLast(current_, swap_);
      if (tmp == nullptr) {
//          LOG(ERROR) << "Touch end";
        exit(0);
      }
      tmp->left = NewNode;
    } else {
      tmp->right = NewNode;
    }
    cur_side = !cur_side;
  };

  while (cur < l) {
    if (data[cur + subLength] == ',' || data[cur + subLength] == '}') {
      if (subLength > 0) {
        std::string substring = data.substr(cur, subLength);
        int val = std::atoi(substring.c_str());
//          LOG(ERROR) << "Get value = " << val << " origin = " << substring;
//          LOG(ERROR) << "[" << cur << "," << subLength << "]";
        TreeNode *cNode = new TreeNode(val);

        if (root == nullptr) {
          current_.push(cNode);
          root = cNode;
        } else {
          UpdateValue(cNode);
          swap_.push(cNode);
        }
      }
      cur += (subLength + 1);
      subLength = 0;
//        LOG(ERROR) << "[" << cur << "," << subLength << "]";
    } else if (data[cur + subLength] == '#') {
      UpdateValue(nullptr);
      cur++;
//        LOG(ERROR) << "[" << cur << "," << subLength << "]";
    } else {
      //'-' && 'number'
      subLength++;
//        LOG(ERROR) << "[" << cur << "," << subLength << "]";
    }
  }
  return root;
}

TreeNode *sortedListToBST(ListNode **_head_ptr, const int num) {
  ListNode *head = *_head_ptr;
  ///check head != nullptr outside this function

  if (num == 0) {
    return nullptr;
  } else if (num == 1) {
    TreeNode *node = new TreeNode(head->val);
    (*_head_ptr) = head->next;
    return node;
  }

  TreeNode *left = sortedListToBST(_head_ptr, num >> 1);
  TreeNode *middle = sortedListToBST(_head_ptr, 1);
  TreeNode *right = sortedListToBST(_head_ptr, num - 1 - (num >> 1));

  middle->left = left;
  middle->right = right;
  return middle;
}

TreeNode *Solution::sortedListToBST(ListNode *head) {
  // write your code here

  ///count size
  ListNode *cur = head;
  int size = 0;
  while (cur != nullptr) {
    size++;
    cur = cur->next;
  }
  cur = head;

  return lintcode::sortedListToBST(&cur, size);
}

bool wordBread(
  const size_t from, const string &s, const unordered_set<string> &wordSet,
  std::vector<bool> &memory) {
  const size_t length = s.length();
  if (from == length) {
    return true;
  }

  if (memory[from]) {
    return false;
  }
  memory[from] = true;
  for (size_t i = from; i < length; i++) {
    const std::string sub = s.substr(from, i - from + 1);
    if ((wordSet.find(sub) != wordSet.end()) &&
        wordBread(i + 1, s, wordSet, memory)) {
      return true;
    }
  }
  return false;
}

bool Solution::wordBreak(string &s, unordered_set<string> &wordSet) {
  // write your code here
  if (s.empty()) {
    return true;
  }
  if (wordSet.empty()) {
    return false;
  }

  std::vector<bool> memory(s.length(), false);
  return wordBread(0, s, wordSet, memory);
}

int minCut(const string &s, std::vector<std::vector<int8_t>> &memory,
           std::vector<int> &min_cuts, const int from) {
//    LOG << "from :" << from << std::endl;
  const int length = s.length() - from;
  if (length < 2) {
    return 0;
  }

  if (min_cuts[from] >= 0) {
    return min_cuts[from];
  }

  auto isPalindrome = [&](const int to) {
    for (int i = from, j = to; i < j; i++, j--) {
      if (s[i] != s[j]) {
        return false;
      }
    }
    return true;
  };
  int min_cut = -1;
  for (int i = length - 1; i >= 0; i--) {
//      LOG << "i = " << i << std::endl;
    int8_t &flag = memory[from][i];
    if (flag == 0) {
      if (isPalindrome(i + from)) {
        flag = 1;
      } else {
        flag = -1;
      }
    }
    if (flag == 1) {
      int cur_cut = minCut(s, memory, min_cuts, i + from + 1);

      if (i < (length - 1)) {
        cur_cut++;
      }

      if (min_cut < 0 || min_cut > cur_cut) {
        min_cut = cur_cut;
      }
    }
  }
  LOG << "mincut[" << from << "] = " << min_cut << std::endl;
  min_cuts[from] = min_cut;
  return min_cut;
}

/**
* @param s: A string
* @return: An integer
*/
int Solution::minCut(string &s) {
  // write your code here
  const size_t length = s.length();
  std::vector<std::vector<int8_t>> memory(length,
      std::vector<int8_t>(length, 0));
  std::vector<int> min_cuts(length, -1);
  return lintcode::minCut(s, memory, min_cuts, 0);
}

int Solution::minimumTotal(vector<vector<int>> &triangle) {
  // write your code here
  const int level_num = triangle.size();
  if (level_num == 0) {
    return 0;
  } else if (level_num == 1) {
    return triangle[0][0];
  }

  vector<vector<int>> memory;
  for (auto& t : triangle) {
    memory.emplace_back(vector<int>(t.size(), -1));
  }
  memory.back() = triangle.back();

  for (int i = level_num - 2; i >= 0; i--) {
    const int num_size = i + 1;
    const vector<int> &t = triangle[i];
    vector<int> &m = memory[i];
    const vector<int> &m_next = memory[i + 1];

    for (int j = 0; j < num_size; j++) {
      if (m_next[j] < m_next[j + 1]) {
        m[j] = t[j] + m_next[j];
      } else {
        m[j] = t[j] + m_next[j + 1];
      }
    }
  }

  return memory[0][0];
}

int minPathSum(vector<vector<int>> &grid, vector<vector<int>> &memory, const int x, const int y) {
  // write your code here
  if (x >= grid.size() || y >= grid.front().size()) {
    return -1;
  }


  int &m = memory[x][y];
  if (m < 0) {
    int right = minPathSum(grid, memory, x+1, y);
    int down = minPathSum(grid, memory, x, y+1);
    if (right >= 0) {
      m = right;
    }
    if (down >= 0) {
      if (m >= 0 && down > m) {

      } else {
        m = down;
      }
    }
    m = m + grid[x][y];
  }
  return m;
}
/**
* @param grid: a list of lists of integers
* @return: An integer, minimizes the sum of all numbers along its path
*/
int Solution::minPathSum(vector<vector<int>> &grid) {
  // write your code here
  vector<vector<int>> memory = vector<vector<int>>(grid.size(), vector<int>(grid.front().size(), -1));
  memory.back().back() = grid.back().back();
  int s = lintcode::minPathSum(grid, memory, 0, 0);
  return s < 0 ? 0 : s;
}

int Solution::climbStairs(int n) {
  // write your code here
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else if (n == 2) {
    return 2;
  }

  std::vector<int> memory(n, -1);

  memory[0] = 1;
  memory[1] = 2;

  for (int i = 2; i < n; i++) {
    memory[i] = memory[i - 2] + memory[i - 1];
  }

  return memory[n - 1];
}

ListNode * Solution::deleteDuplicates(ListNode * head) {
  // write your code here
  if (head == nullptr) {
    return nullptr;
  }
  ListNode *cur_tail = head, *cur_next = head->next;

  while (cur_next != nullptr) {
    if (cur_tail->val == cur_next->val) {
      cur_next = cur_next->next;
    } else {
      if (cur_tail->next != cur_next) {
        cur_tail->next = cur_next;
      }
      cur_tail = cur_tail->next;
      cur_next = cur_next->next;
    }
  }
  cur_tail->next = nullptr;
  return head;
}

ListNode *Solution::deleteDuplicates2(ListNode * head) {
  // write your code here

  auto removeHead = [&head]() {
    bool remove_head = false;
    if (head == nullptr) {
      return remove_head;
    }
    while(head->next != nullptr && head->val == head->next->val) {
      head = head->next;
      remove_head = true;
    }
    if (remove_head) {
      head = head->next;
      LOG << "head is duplicated" << std::endl;
      return true;
    }
    return false;
  };

  while (removeHead()) {
  }

  if (head == nullptr) {
    return nullptr;
  }
  ListNode *cur_tail = head, *cur_next = head->next, *duplicate = nullptr;


  int dul = 0;
  while (cur_next != nullptr) {
    if (duplicate != nullptr) {
      if (cur_next->val == duplicate->val) {
        cur_next = cur_next->next;
        dul++;
      } else {
        LOG << "duplicate: " << duplicate->val << "," << dul << std::endl;
        dul = 0;
        duplicate = nullptr;
      }
    }
    if (duplicate == nullptr) {
      if (cur_next->next != nullptr) {
        if (cur_next->val == cur_next->next->val) {
          duplicate = cur_next;
          cur_next = cur_next->next->next;
          dul = 2;
          LOG << "found duplicate " << duplicate->val << std::endl;
        } else {
          LOG << "attach " << cur_next->val << "" << std::endl;
          cur_tail->next = cur_next;
          cur_tail = cur_next;
          cur_next = cur_next->next;
        }
      } else {
        LOG << "attach " << cur_next->val << "" << std::endl;
        cur_tail->next = cur_next;
        cur_tail = cur_next;
        cur_next = cur_next->next;
      }
    }
  }

  cur_tail->next = nullptr;
  return head;
}


int uniquePaths(std::vector<std::vector<int>> &memory, int m, int n) {
  if ((memory.size() <= (m)) || (memory.front().size() <= (n))) {
    return 0;
  }
  auto &mem = memory[m][n];
  if (mem < 0) {
    int right = lintcode::uniquePaths(memory, m, n + 1);
    int down = lintcode::uniquePaths(memory, m + 1, n);
    LOG << "right[" << m << "," << n+1 << "] = " << right << std::endl;
    LOG << "down[" << m + 1 << "," << n << "] = " << down << std::endl;
    mem = right + down;
  }
  LOG << "mem[" << m << "," << n << "] = " << mem << std::endl;
  return mem;
}

/**
* @param m: positive integer (1 <= m <= 100)
* @param n: positive integer (1 <= n <= 100)
* @return: An integer
*/
int Solution::uniquePaths(int m, int n) {
  // write your code here

  if (m == 1 || n == 1) {
    return 1;
  } else if (m == 0 || n == 0) {
    return 0;
  }

  std::vector<std::vector<int>> memory(
    std::vector<std::vector<int>>(m, std::vector<int>(n, -1)));
  memory.back() = std::vector<int>(n, 1);

  return lintcode::uniquePaths(memory, 0, 0);
}


int uniquePathsWithObstacles(
  const vector<vector<int>> &obstacleGrid,
  std::vector<std::vector<int>> &memory, int m, int n) {
  if ((memory.size() <= (m)) || (memory.front().size() <= (n))) {
    return 0;
  }
  auto &mem = memory[m][n];
  if (mem < 0) {
    if (obstacleGrid[m][n] == 0) {
      int right = lintcode::uniquePathsWithObstacles(obstacleGrid, memory, m, n + 1);
      int down = lintcode::uniquePathsWithObstacles(obstacleGrid, memory, m + 1, n);
//        LOG << "right[" << m << "," << n+1 << "] = " << right << std::endl;
//        LOG << "down[" << m + 1 << "," << n << "] = " << down << std::endl;
      mem = right + down;
    } else {
      mem = 0;
    }
  }
//    LOG << "mem[" << m << "," << n << "] = " << mem << std::endl;
  return mem;
}

/**
 * @param obstacleGrid: A list of lists of integers
 * @return: An integer
 */
int Solution::uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
  // write your code here
  if (1 == obstacleGrid.back().back() || obstacleGrid.empty() || obstacleGrid.front().empty()) {
    return 0;
  }
  std::vector<std::vector<int>> memory(
    std::vector<std::vector<int>>(
      obstacleGrid.size(), std::vector<int>(obstacleGrid.front().size(), -1)));
  memory.back().back() = 1;
  return lintcode::uniquePathsWithObstacles(obstacleGrid, memory, 0, 0);
}

bool canJump(const vector<int> &A, vector<int> &B) {


}

/**
* @param A: A list of integers
* @return: A boolean
*/
bool Solution::canJump(vector<int> &A) {
  // write your code here
  const int size = A.size();
  if (size <= 1) {
    return true;
  }

  std::vector<int8_t> B(size, -1);

  for (int i = size - 1; i >= 0; i--) {
    int dist = size - i - 1;
    if (A[i] >= dist) {
      B[i] = 1;
      LOG << "B[" << i << "] can\n";
    } else if (A[i] == 0) {
      B[i] = 0;
      LOG << "B[" << i << "] cannot\n";
    } else {
      const int last = A[i] + i;
      for (int j = i + 1; j <= last; j++) {
        if (B[j] == 1) {
          B[i] = 1;
          LOG << "B[" << i << "] can\n";
          break;
        }
      }
      if (B[i] != 1) {
        B[i] = 0;
        LOG << "B[" << i << "] cannot\n";
      }
    }
  }
  return (B[0] == 1);

}

int Solution::jump(vector<int> &A) {
  // write your code here

  const int size = A.size();
  if (size <= 1) {
    return 0;
  }

  std::vector<int> B(size, -1);

  for (int i = size - 1; i >= 0; i--) {
    int dist = size - i - 1;
    if (A[i] >= dist) {
      B[i] = 1;
//        LOG << "B[" << i << "] can\n";
    } else if (A[i] == 0) {
      B[i] = 0;
//        LOG << "B[" << i << "] cannot\n";
    } else {
      const int last = A[i] + i;
      for (int j = i + 1; j <= last; j++) {
        if (B[j] > 0) {
          if (B[i] < 0 || B[i] > (B[j] + 1)) {
            B[i] = B[j] + 1;
          }
//            LOG << "B[" << i << "] can\n";
        }
      }
      if (B[i] < 0) {
        B[i] = 0;
//          LOG << "B[" << i << "] cannot\n";
      }
    }
  }

  show_vector(B);

  return (B[0]);
}



int numDistinct(
    const string &S, const string &T,
    std::vector<std::vector<int>>& memory,
    const int from, const int to) {
  const int Sl = S.length();
  const int Tl = T.length();
  if (Tl <= to) {
    return 1;
  }

  if (Sl <= from) {
    return 0;
  }

  if (Sl < Tl) {
    memory[from][to] = 0;
  }

  if (memory[from][to] >= 0) {
    return memory[from][to];
  }

  int c = 0;

  if (from == 4 && to == 4) {
    LOG << "detect\n";
  }

  for (size_t i = from; i < Sl; i++) {
    if (S[i] == T[to]) {
      c += numDistinct(S, T, memory, i + 1, to + 1);
    } else {
      numDistinct(S, T, memory, i + 1, to);
    }
  }

  memory[from][to] = c;
  LOG << "from " << from << "," << to << " = " << c << std::endl;
  return c;
}

/**
* @param S: A string
* @param T: A string
* @return: Count the number of distinct subsequences
*/
int Solution::numDistinct(string &S, string &T) {
  // write your code here
  int size = S.length();
  for (int i = size - 1; i >= 0; i--) {
    if (std::string::npos == T.find(S[i])) {
      S.erase(i, 1);
    }
  }
  std::vector<std::vector<int>> memory(S.size(), std::vector<int>(T.size(), -1));
  return lintcode::numDistinct(S, T, memory, 0, 0);
}

int Solution::minDistance(string &word1, string &word2) {
  // write your code here
  int n = word1.length();
  int m = word2.length();

  vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

  for(int i = 0; i <= n; i++){
    dp[i][0] = i;
  }

  for(int j = 0; j <= m; j++){
    dp[0][j] = j;
  }

  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      if(word1[i-1] == word2[j-1])
        dp[i][j] = min(dp[i-1][j-1], 1 + min(dp[i-1][j], dp[i][j-1]));

      else
        dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
    }
  }

  return dp[n][m];
}

/**
* @param height: A list of integer
* @return: The area of largest rectangle in the histogram
*/
int Solution::largestRectangleArea(vector<int> &heights) {
  // write your code here
#if BAD_ALGORITHM
  const int l = heights.size();

    //std::vector<std::vector<int>> memory(heights.size(), std::vector<int>(heights.size(), -1));
    int max = 0, cur;
    for (int i = 0; i < l; i++) {
      int min_height = heights[i];
      cur = heights[i];
      if (max < cur) {
        max = cur;
      }
      for (int j = i + 1; j < l; j++) {
        if (min_height > heights[j]) {
          min_height = heights[j];
        }
        cur = (j - i + 1) * min_height;
        if (max < cur) {
          max = cur;
        }
      }
    }
    return max;

#else
  heights.push_back(-1);
  stack<int> st;
  int ret = 0, top;
  for (int i = 0; i < heights.size(); i++)
  {
    if (st.empty() || heights[st.top()] <= heights[i])
    {
      st.push(i);
      LOG << "push " << heights[i] << std::endl;
    }
    else
    {
      while (!st.empty() && heights[st.top()] > heights[i])
      {
        top = st.top();
        st.pop();
        //i-top指的是当前矩形的宽度，heights[top]就是当前的高度
        //再次强调栈中现在为单调递增
        int tmp = (i - top)*heights[top];

        LOG << "tmp = (" << i << "-" << top << ") * " << heights[top] << "=" << tmp << std::endl;

        if (tmp > ret)
          ret = tmp;
      }
      st.push(top);
      LOG << "push " << heights[top] << " to " << heights[i] << std::endl;
      heights[top] = heights[i];
      show_vector(heights);
    }
  }
  return ret;
#endif
}

int stringDistance(
    const std::string &a,
    const std::string &b) {
  int d = 0;
  const int l = a.length();
  for (int i = 0; i < l; i++) {
    if (a[i] == b[i]) {
      d++;
    }
  }
  return l - d;
};

/*
* @param start: a string
* @param end: a string
* @param dict: a set of string
* @return: An integer
*/
int Solution::ladderLength(string &start, string &end, unordered_set<string> &dict) {
  // write your code here
  std::queue<std::string> queue[2];
  queue[0].push(start);
  dict.emplace(end);
  dict.erase(start);

  int c = 0;
  while ((!queue[c % 2].empty()) && (!dict.empty())) {
    auto &from = queue[c % 2];
    auto &to = queue[(c + 1) % 2];
//      LOG << "push " << from.size() << std::endl;
    while((!from.empty()) && (!dict.empty())) {
      std::string _string = from.front();
      from.pop();
//        LOG << "search " << _string << std::endl;
      for (auto iter = dict.begin(); iter != dict.end();) {
        if (stringDistance(_string, *iter) == 1) {
          to.push(*iter);
//            LOG << "push " << *iter << std::endl;
          if ((*iter) == end) {
            return (c > 0) ? (c + 2) : 2;
          }

          iter = dict.erase(iter);
        } else {
          iter++;
        }
      }
    }
    c++;
  }

  return 0;
};

/*
* @param start: a string
* @param end: a string
* @param dict: a set of string
* @return: a list of lists of string
*/
vector<vector<string>> Solution::findLadders(string &start, string &end, unordered_set<string> &dict) {
  // write your code here
  std::queue<std::vector<std::string>> queue[2];
  queue[0].push({start});
  dict.emplace(end);
  dict.erase(start);

  int c = 0;
  std::vector<std::vector<std::string>> result;
  while ((!queue[c % 2].empty()) && (!dict.empty())) {
    auto &from = queue[c % 2];
    auto &to = queue[(c + 1) % 2];
    std::unordered_set<std::string> this_level_remove;
    LOG << "push " << from.size() << std::endl;
    while((!from.empty()) && (!dict.empty())) {
      auto _string = from.front().back();

      LOG << "search " << _string << std::endl;
      for (auto iter = dict.begin(); iter != dict.end(); iter++) {
        if (stringDistance(_string, *iter) == 1) {
          auto _strings = from.front();
          _strings.emplace_back(*iter);

          LOG << "push " << *iter << std::endl;
          if ((*iter) == end) {
            result.emplace_back(_strings);
            break;
          } else {
            to.push(_strings);
            this_level_remove.insert(*iter);
          }

        }

      }
      from.pop();
    }
    if (!result.empty()) {
      break;
    }

    for (auto &s : this_level_remove) {
      dict.erase(s);
    }

    c++;
  }
  return result;
}

int Solution::longestConsecutive(vector<int> &num) {
  // write your code here
  if (num.size() < 2) {
    return num.size();
  }
  std::set<int> nums(num.begin(), num.end());

  int count = 1, max = 1;
  auto iter = nums.begin(), iter_2 = iter;
  iter_2++;

  for (; iter_2 != nums.end(); iter_2++, iter++) {
    if ((*iter + 1) == (*iter_2)) {
      count++;
    } else {
      if (count > max) {
        max = count;
      }
      count = 1;
    }
  }


  if (count > max) {
    max = count;
  }
  return max;
}

bool dfs(
    vector<vector<char>> &board,
    string &word,
    const uint64_t row,
    const uint64_t col,
    const int pos,
    std::set<uint64_t>& sets) {

  uint64_t key = (row << 32) ^ col;
  if (sets.count(key) > 0) {
    return false;
  }

  const uint64_t rows = board.size();
  const uint64_t cols = board.front().size();
  const int next = (pos + 1);
  if (word.length() == pos) {

    LOG << "length " << sets.size() << "," << pos << std::endl;
    for (auto &s : sets) {
      std::cout << (s >> 32) << "," << (uint32_t)s << std::endl;
    }

    return true;
  }
  LOG << " test " << row << "," << col << std::endl;
  if (board[row][col] == word[pos]) {
    if (next == word.length()) {
      return true;
    }

    sets.insert(key);
    LOG << " insert " << row << "," << col << std::endl;
    if (row > 0 && dfs(board, word, row - 1, col, next, sets)) {
      return true;
    }

    if (col > 0 && dfs(board, word, row, col - 1, next, sets)) {
      return true;
    }

    if (row + 1 < rows && dfs(board, word, row + 1, col, next, sets)) {
      return true;
    }

    if (col + 1 < cols && dfs(board, word, row, col + 1, next, sets)) {
      return true;
    }

    sets.erase(key);
    LOG << " erase " << row << "," << col << std::endl;
  }
  return false;
}

bool Solution::exist(vector<vector<char>> &board, string &word) {
  // write your code here
  std::set<uint64_t> sets;
  for (int r = 0; r < board.size(); r++) {
    for (int c = 0; c < board[r].size(); c++) {
      if (dfs(board, word, r, c, 0, sets)) {
        return true;
      }
    }
  }

  return false;
}


void backPackII(
  const int *A, const int *V, const size_t size, const int m,
  int sum, int value, std::vector<int> &memory, int *cur_max_val) {
  for (size_t i = 0; i < size; i++) {
    int s = sum + A[i];
    if (s <= m) {
      int v = value + V[i];
      LOG << A << " s[" << s << "] = " << v << std::endl;
      if (memory[s] < v) {
        memory[s] = v;
        if (*cur_max_val < v) {
          *cur_max_val = v;
        }
      }
      backPackII(A + i + 1, V + i + 1, size - i - 1, m, s, v, memory, cur_max_val);
    }
  }
}

void backPackII(int m, vector<int> &A, vector<int> &V, std::vector<int>& memory) {

}

/**
* @param m: An integer m denotes the size of a backpack
* @param A: Given n items with size A[i]
* @param V: Given n items with value V[i]
* @return: The maximum value
*/
int Solution::backPackII(int m, vector<int> &A, vector<int> &V) {
  // write your code here
#if 0
  std::vector<int> memory(m + 1, 0);
  int max = 0;
  backPackII(A.data(), V.data(), A.size(), m, 0, 0, memory, &max);
  return max;
#else
  std::vector<int> memory(m + 1, 0);
  int max = 0;
  const int size = A.size();
  for (int i = 0; i < size; i++) {
    ///if you do this from A[i] to m, memory[A[i] + k]
    /// may add memory[A[i] + k - p], which has been added this time
    for (int j = m; j >= A[i]; j--) {
      int tmp = memory[j - A[i]] + V[i];
//      LOG << "j " << j << "," << A[i] << "," << V[i] << "," << memory[j - A[i]] << std::endl;
      if (memory[j] < tmp) {
        memory[j] = tmp;
        if (max < tmp) {
          max = tmp;
        }
      }
    }
  }

  return max;
#endif
}

int Solution::hashCode(string &key, int HASH_SIZE) {
  // write your code here
  ///[(a * h + moda) (b * h + modb) (c * h + modc) *...] % h = (moda * modb * modc *...) % h
  const int l = key.length();
  int res = 0;
  int64_t pow_mod = 1;
  int mod_base = 33 % HASH_SIZE;
  for (int i = l - 1; i >= 0; i--){
    int modb = key[i] % HASH_SIZE;
    res = (res + ((modb * pow_mod) % HASH_SIZE)) % HASH_SIZE;
    pow_mod = (pow_mod * mod_base) % HASH_SIZE;
  }

  return res;
}

vector<ListNode*> Solution::rehashing(vector<ListNode*> hashTable) {
  // write your code here
  auto hashcode = [](int key, int capacity) {
    int code = key % capacity;
    if (code < 0) {
      code += capacity;
    }
    return code;
  };

  const int cap = hashTable.size() * 2;
  vector<std::vector<ListNode*>> Table(cap);
  for (auto node : hashTable) {
    while (node != nullptr) {
      int code = hashcode(node->val, cap);
      Table[code].emplace_back(node);
      node = node->next;
    }
  }
  std::vector<ListNode*> newTable;
  newTable.reserve(cap);
  for (auto &bucket : Table) {
    ListNode *head = nullptr;
    if (!bucket.empty()) {
      head = bucket[0];
      for (int i = 1; i < bucket.size(); i++) {
        bucket[i - 1]->next = bucket[i];
      }
      bucket.back()->next = nullptr;
    }
    newTable.emplace_back(head);
  }

  return newTable;
}
TreeNode *Solution::maxTree(vector<int> &A) {
  // write your code here
  std::stack<TreeNode *> tree;
//    for element in A:
//    node = TreeNode(element)
//    while len(stack) != 0 and element > stack[-1].val:
//    node.left = stack.pop()
//    if len(stack) != 0:
//    stack[-1].right = node
//    stack.append(node)
  for (int i = 0; i < A.size(); i++) {
    auto node = new TreeNode(A[i]);
    while(!tree.empty() && tree.top()->val < node->val) {
      node->left = tree.top();
      tree.pop();
    }
    if (!tree.empty()) {
      tree.top()->right = node;
    }
    tree.push(node);
  }

  return tree.top();

}


/**
* @param buildings: A list of lists of integers
* @return: Find the outline of those buildings
*/
vector<vector<int>> Solution::buildingOutline(vector<vector<int>> &buildings) {
  // write your code here
#if 0
  ///too slow
    if (buildings.empty()) {
      return vector<vector<int>>();
    }
    std::map<int, int> height;

    for (auto &b : buildings) {
      for (int i = b[0]; i < b[1]; i++) {
        if (height.count(i) == 0) {
          height.emplace(i, b[2]);
        } else if (height.at(i) < b[2]) {
          height.at(i) = b[2];
        }
      }
    }

    vector<vector<int>> Outline;
    vector<int> build;

    for (auto &m : height) {
      LOG << m.first << "," << m.second << "\n";
      if (build.empty()) {
        build = {m.first, m.first + 1, m.second};
      } else if (build[1] != m.first || build[2] != m.second) {
        Outline.emplace_back(build);
        build = {m.first, m.first + 1, m.second};
      } else {
        build[1] = m.first + 1;
      }
    }
    Outline.emplace_back(build);
    return Outline;
#elif 0
  ///still slow
    if (buildings.empty()) {
      return vector<vector<int>>();
    }
    struct Comare{
      bool operator()(const vector<int> *_left, const vector<int> *_right) {
        const vector<int>&left = *_left, &right = *_right;
        if (left[0] < right[0]) {
          return true;
        } else if (left[0] > right[0]) {
          return false;
        }
        if (left[1] < right[1]) {
          return true;
        } else if (left[1] > right[1]) {
          return false;
        }
        if (left[2] < right[2]) {
          return true;
        }
        return false;

      }
    };

    Comare cmp;
    vector<vector<int>> outlines;
    std::set<vector<int> *, Comare> set_buildings;
    std::set<int> lines;
    for (auto &b : buildings) {
      set_buildings.emplace(&b);
      lines.emplace(b[0]);
      lines.emplace(b[1]);
    }
    show_set(lines);

    auto _left = lines.begin(), _right = _left;
    _right++;
    std::stack<vector<int> *> stack;
    for (; _right != lines.end(); _left++, _right++) {
      int left = *_left, right = *_right;
      vector<int> outline = {left, right, 0};

      std::stack<vector<int> *> stack_;
      while(!stack.empty()) {
        auto &building = *stack.top();
        stack.pop();
        if (outline[2] < building[2]) {
          outline[2] = building[2];
        }

        if (right < building[1] && right > building[0]) {
          building[0] = right;
          stack_.push(&building);
        }
      }
      stack_.swap(stack);

      auto iter = set_buildings.begin();
      while (iter != set_buildings.end() && (**iter)[0] >= left && (**iter)[0] < right) {
        auto &building = **iter;
        if (outline[2] < building[2]) {
          outline[2] = building[2];
        }
//        LOG << "merging:";
        show_vector(building);

        iter = set_buildings.erase(iter);

        if (right < building[1] && right > building[0]) {
          building[0] = right;
          stack.push(&building);
        }
      }
      if (outline[2] > 0) {
//        show_vector(outline);
//        LOG << "outline size = " << outline.size() << std::endl;
        if ((outlines.size() > 0) && (outlines.back()[2] == outline[2]) && (outlines.back()[1] == outline[0])) {
          outlines.back()[1] = outline[1];
        } else {
          outlines.emplace_back(outline);
        }
      }


    }
    return outlines;
#else

  vector<vector<int>> ret;

		if (buildings.empty())
		{
			return ret;
		}

		auto func = [](vector<int> &left, vector<int> &right) {
			if (left[0] == right[0] && left[2] == right[2])
			{
				return left[1] < right[1];
			}

			if (left[0] == right[0])
			{
				return left[2] < right[2];
			}

			return left[0] > right[0];
		};
		// 建堆;
		make_heap(buildings.begin(), buildings.end(), func);

		pop_heap(buildings.begin(), buildings.end(), func);
		vector<int> cur_outline = *buildings.rbegin();
		buildings.pop_back();

		while (buildings.empty() == false)
		{
			pop_heap(buildings.begin(), buildings.end(), func);
			vector<int> building = *buildings.rbegin();
			buildings.pop_back();

			if (building[0] > cur_outline[1])
			{
				// 建筑与当前轮廓分离;
				ret.push_back(cur_outline);
				cur_outline = building;
			}
			else if (building[2] > cur_outline[2])
			{
				// 建筑与当前轮廓未分离，并且高度比当前高;
				if (building[1] < cur_outline[1])
				{
					// 该建筑没有当前轮廓宽，生成新的建筑;
					vector<int> new_building = { building[1], cur_outline[1], cur_outline[2] };
					buildings.push_back(new_building);
					push_heap(buildings.begin(), buildings.end(), func);
				}

				cur_outline[1] = building[0];
				ret.push_back(cur_outline);
				cur_outline = building;
			}
			else if (building[2] == cur_outline[2])
			{
				// 建筑与当前轮廓未分离，并且高度相等，则看是否合并轮廓;
				cur_outline[1] = max(cur_outline[1], building[1]);
			}
			else if (building[2] < cur_outline[2])
			{
				// 建筑与当前轮廓未分离，并且高度比当前小;
				if (building[0] == cur_outline[1])
				{
					// 正好在边缘;
					ret.push_back(cur_outline);
					cur_outline = building;
				}
				else if (building[1] > cur_outline[1])
				{
					// 有重叠，并且该建筑比当前轮廓宽，生成新的建筑;
					vector<int> new_building = { cur_outline[1], building[1], building[2] };
					buildings.push_back(new_building);
					push_heap(buildings.begin(), buildings.end(), func);
				}
			}
		}

		ret.push_back(cur_outline);
		return ret;
#endif
}

/*
* @param A: Given an integer array
* @return: nothing
*/
void Solution::heapify(vector<int> &A) {
  // write your code here
  const int size = A.size();
  for (int i = 0; i < size; i++) {
    int child = i;
    int father = ((child + 1) >> 1) - 1;
    while (father >= 0 && (A[father] > A[child])) {
      std::swap(A[father], A[child]);
      child = father;
      father = ((child + 1) >> 1) - 1;
    }
  }
};

class LRUCache {
public:
  std::list<std::pair<int, int>> _cache; //key, value
  std::map<int, std::list<std::pair<int, int>>::iterator> _map;//or unordered_map
  int _capacity;
  /*
  * @param capacity: An integer
  */
  LRUCache(int capacity) {
    // do intialization if necessary
    _capacity = capacity;
  }

  /*
   * @param key: An integer
   * @return: An integer
   */
  int get(int key) {
    // write your code here
    auto iter = _map.find(key);
    if (iter == _map.end()) {
      return -1;
    }
    std::pair<int, int> ret = *iter->second;
    auto begin = _cache.begin();
    if (iter->second != begin) {
      _cache.erase(iter->second);
//      LOG << "erase " << iter->first << "," << *iter->second << std::endl;
      _cache.emplace_front(ret);
      iter->second = _cache.begin();
    }

    return ret.second;
  }

  /*
   * @param key: An integer
   * @param value: An integer
   * @return: nothing
   */
  void set(int key, int value) {
    // write your code here
    auto iter = _map.find(key);
    if (iter != _map.end()) {
      _cache.erase(iter->second);
//      LOG << "erase " << iter->first << "," << *iter->second << std::endl;
      _map.erase(iter);
    }

    _cache.emplace_front(std::pair<int, int>(key, value));
    _map.emplace(key, _cache.begin());
    if (_cache.size() > _capacity) {
      _map.erase(_cache.back().first);
//      LOG << "erase " << iter->first << "," << *iter->second << std::endl;
      _cache.resize(_capacity);
    }
  }
};

int combinationSum(
    set<int> &candidates, int target,
    std::vector<std::vector<std::vector<int>>>& memory,
    std::vector<int> &result) {
  if (target == 0) {
    LOG << "target 0\n";
    return 1;
  }
  LOG << "target " << target << std::endl;
  if (result[target] > 0) {
    LOG << "return target 1 " << target << std::endl;
    return 1;
  } else if (result[target] < 0) {
    LOG << "return target -1 " << target << std::endl;
    return -1;
  }

  for (auto &i : candidates) {
    LOG << "target " << target << "," << i << std::endl;
    if (i <= target) {
      if (1 == combinationSum(
          candidates, target - i, memory, result)) {
        auto t = memory[target - i];

        for (auto iter = t.begin(); iter != t.end();){
          if (iter->empty() || iter->back() <= i) {
            iter->emplace_back(i);
            iter++;
          } else {
            iter = t.erase(iter);
          }
        }
//          LOG << "insert target " << target << std::endl;
        memory[target].insert(memory[target].end(), t.begin(), t.end());
//          show_vector(memory[target]);
      }
    }
  }
  if (memory[target].empty()) {
    result[target] = 0;
//      LOG << "finish target " << target << " is empty\n";
    return 0;
  } else {
    result[target] = 1;
//      LOG << "finish target " << target << "\n";
//      show_vector(memory[target]);
    return 1;
  }
}

vector<vector<int>> Solution::combinationSum(vector<int> &candidates, int target) {
  // write your code here
  std::vector<std::vector<std::vector<int>>> memory(target + 1);
  std::vector<int> result(target + 1, 0);
  result[0] = 1;
  memory[0] = std::vector<std::vector<int>>(1, std::vector<int>());
  set<int> _candidates(candidates.begin(), candidates.end());

  lintcode::combinationSum(_candidates, target, memory, result);
  return memory.back();
}

vector<string> Solution::longestWords(vector<string> &dictionary) {
  // write your code here
  vector<string> ret;
  int cur = 0;
  for (auto &word : dictionary) {
    int length = word.length();
    if (length == cur) {

      ret.emplace_back(word);
    } else if (length > cur) {
      ret.resize(1);
      ret[0] = word;
      cur = length;
    }
  }
  return ret;
}


bool search_word(vector<vector<char>> &board, string &word,
                 std::set<uint64_t>& memory, int row, int col, uint32_t index) {

  if (index == word.length()) {
    return true;
  }
  if (row < 0 || row >= board.size() || col < 0 || col >= board.front().size()) {
    return false;
  }
  if (word[index] == board[row][col]) {
    int next[4][2] = {{0, 1},{0, -1}, {1, 0}, {-1, 0}};
    uint64_t key = (uint64_t)row ^ ((uint64_t)col) << 32;
    if (memory.count(key) > 0) {
      return false;
    }
    LOG << "in = " << row << "," << col << "," << key << std::endl;
    memory.insert(key);

    for (int i = 0; i < 4; i++) {
      if (search_word(board, word, memory, row + next[i][0], col + next[i][1], index + 1)) {
        return true;
      }
    }
    LOG << "out = " << row << "," << col << "," << key << std::endl;
    memory.erase(key);
  }

  return false;
}

vector<string> Solution::wordSearchII(vector<vector<char>> &board, vector<string> &words) {
  // write your code here
  vector<string> ret;
  std::set<uint64_t> memory;
  for (auto &word : words) {
    memory.clear();
    LOG << "start " << word << "," << std::endl;
    show_set(memory);
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board.front().size();j++) {
        if (search_word(board, word, memory, i, j, 0)) {
          ret.emplace_back(word);
          i = board.size();
          break;
        }
      }
    }
  }
  return ret;
}

bool partition(
    const string &s,
    std::vector<std::vector<std::vector<std::string>>> &memory,
    std::vector<int> &flags, const int from) {
  if (s.length() == from || (flags[from] > 0)) {
    return true;
  }
  if (flags[from] < 0) {
    return false;
  }

  auto isPalindrome = [&](const int to) {
    for (int i = from, j = to; i < j; i++, j--) {
      if (s[i] != s[j]) {
        return false;
      }
    }
    return true;
  };
//    LOG << "from " <<  s.length() << "," << from << std::endl;

  const int length = s.length() - from;
  for (int i = length - 1; i >= 0; i--) {
//      LOG << "i = " << i << std::endl;
    if (isPalindrome(from + i)) {
      std::string sub = s.substr(from, i + 1);
//        LOG << "good " << sub << std::endl;
      if (partition(s, memory, flags, from + i + 1)) {
        auto m = memory[from + i + 1];
        for (auto &sm : m) {
          sm.insert(sm.begin(), sub);
        }
        memory[from].insert(memory[from].end(), m.begin(), m.end());
      }
    }
  }

  if (memory[from].empty()) {
    flags[from] = -1;
    return false;
  }

  flags[from] = 1;
  return true;
}

vector<vector<string>> Solution::partition(string &s) {
  // write your code here
  std::vector<std::vector<std::vector<std::string>>> memory(s.length() + 1);
  std::vector<int> flags(s.length() + 1, 0);
  flags.back() = 1;
  memory.back() = std::vector<std::vector<std::string>>(1, std::vector<std::string>());

  lintcode::partition(s, memory, flags, 0);
  return memory[0];
}


void cloneGraph(
    UndirectedGraphNode* node,
    std::map<UndirectedGraphNode *, UndirectedGraphNode *>& o_to_new) {
  if (node == nullptr) return;
  o_to_new.emplace(node, new UndirectedGraphNode(node->label));
  for (auto neighbor : node->neighbors) {
    if (o_to_new.count(neighbor) == 0) {
      cloneGraph(neighbor, o_to_new);
    }
  }
  return;
}

UndirectedGraphNode* Solution::cloneGraph(UndirectedGraphNode* node) {
  // write your code here
  if (node == nullptr) return nullptr;
  std::map<UndirectedGraphNode *, UndirectedGraphNode *> o_to_new;

  lintcode::cloneGraph(node, o_to_new);
  for (auto on : o_to_new) {
    auto &neighbor = on.second->neighbors;
    for (auto n : on.first->neighbors) {
      neighbor.emplace_back(o_to_new.find(n)->second);
    }
  }
  return o_to_new.find(node)->second;
}

}//namespace lintcode