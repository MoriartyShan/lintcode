//
// Created by moriarty on 4/14/21.
//

#ifndef LINTCODE_CODE_H
#define LINTCODE_CODE_H
//
// Created by moriarty on 4/14/21.
//
#include <iostream>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define LOG cout << __FILE__ << ":" << __LINE__ << ":"

/**
 * Definition for singly-linked list with a random pointer.
 */
struct RandomListNode {
   int label;
   RandomListNode *next, *random;
   RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
  static void show(const int max, const RandomListNode* head) {
    LOG << "show list:";
    const RandomListNode* cur = head;
    int c = 0;
    while (c != max && cur != nullptr) {
      std::cout << cur->label << ",";
      cur = cur->next;
      c++;
    }
    c = 0;
    cur = head;
    std::cout << "[";
    while (c != max && cur != nullptr) {
      if (cur->random != nullptr) {
        std::cout << cur->random->label << ",";
      } else {
        std::cout << "null,";
      }
      cur = cur->next;
      c++;
    }
    std::cout << "]\n";

   }
};
void copyRandomList(
    RandomListNode **new_head,
    const RandomListNode *old_head,
    RandomListNode **current,
    RandomListNode *copy);
/**
* Definition of singly-linked-list:
 * */
class ListNode {
public:
  int val;
  ListNode *next;
  ListNode(int val) {
    this->val = val;
    this->next = NULL;
  }
  void show(const int n) const {
    const ListNode *p = this;
    int c = 0;
    while (p != nullptr) {
      std::cout << p->val << "->";
      p = p->next;
      if (c++ == n) {
        break;
      }
    }
    std::cout << std::endl;
  }
};

class TreeNode {
public:
  int val;
  TreeNode *left, *right;
  TreeNode(int val) {
    this->val = val;
    this->left = this->right = NULL;
  }

};


class Interval {
public:
  int start, end;
  Interval(int start, int end) {
    this->start = start;
    this->end = end;
  }
};


class Solution {

public:
  std::set<uint64_t> failed;
  bool isInterleave(const char* s[],  int* l, int start = 0);
  /**
   * @param s1: A string
   * @param s2: A string
   * @param s3: A string
   * @return: Determine whether s3 is formed by interleaving of s1 and s2
   */
  bool isInterleave(string &s1, string &s2, string &s3);

  /**
 * @param intervals: Sorted interval list.
 * @param newInterval: new interval.
 * @return: A new interval list.
 */
  vector<Interval> insert(vector<Interval> &intervals, Interval newInterval);


  /**
   * @param n: The number of queens
   * @return: All distinct solutions
   */
  vector<vector<string>> solveNQueens(int n);

  /**
     * @param root: The root of binary tree.
     * @return: An integer
     */
  int maxPathSum(TreeNode * root);

  /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
  int backPack(int m, vector<int> &A);

  /**
     * @param root: The root of binary tree.
     * @return: True if the binary tree is BST, or false
     */
  bool isValidBST(TreeNode * root);


  /**
   * @param head: The first node of linked list
   * @param x: An integer
   * @return: A ListNode
   */
  ListNode * partition(ListNode * head, int x);

    /**
   * @param root: The root of binary tree.
   * @return: An integer
   */
    int maxDepth(TreeNode * root);

  /**
 * @param head: The head of linked list.
 * @return: You should return the head of the sorted linked list, using constant space complexity.
 */
  ListNode * sortList(ListNode * head);

  /**
 * @param head: The head of linked list.
 * @return: nothing
 */
  void reorderList(ListNode * head);

    /*
   * @param nums: An ineger array
   * @return: An integer
   */
    int removeDuplicates(vector<int> &nums);

  /**
  * @param A: a list of integers
  * @return : return an integer
  */
  int removeDuplicates2(vector<int> &nums);

  /**
     * @param head: The first node of linked list.
     * @return: True if it has a cycle, or false
     */
  bool hasCycle(ListNode * head);

    /**
   * @param lists: a list of ListNode
   * @return: The head of one sorted list.
   */
  ListNode *mergeKLists(vector<ListNode *> &lists);

  /**
* @param head: The head of linked list with a random pointer.
* @return: A new head of a deep copy of the list.
*/
  RandomListNode *copyRandomList(RandomListNode *head) {
    // write your code here
    RandomListNode *new_head = nullptr, *old_head = head, **current = &new_head;
    ::copyRandomList(current, old_head, current, head);
    return new_head;
  }

  /**
   * This method will be invoked first, you should design your own algorithm
   * to serialize a binary tree which denote by a root node to a string which
   * can be easily deserialized by your own "deserialize" method later.
   */
  string serialize(TreeNode * root) {
    // write your code here
    string res = "{";
    std::queue<TreeNode *> keep;
    if (root)
      keep.push(root);
    while(keep.size() > 0) {
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
      while(res.substr(last - 2, 2) == "#,") {
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
  TreeNode * deserialize(string &data) {
    // write your code here

    auto findLast = [](
      std::queue<TreeNode*> &cur,
      std::queue<TreeNode*> &buf) {
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
    std::queue<TreeNode*> current_, swap_;
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

  TreeNode * sortedListToBST(ListNode **_head_ptr, const int num) {
    ListNode *head = *_head_ptr;
    ///check head != nullptr outside this function

    if (num == 0) {
      return nullptr;
    } else if (num == 1) {
      TreeNode* node = new TreeNode(head->val);
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

  /*
    * @param head: The first node of linked list.
    * @return: a tree node
    */
  TreeNode * sortedListToBST(ListNode * head) {
    // write your code here

    ///count size
    ListNode *cur = head;
    int size = 0;
    while (cur != nullptr) {
      size++;
      cur = cur->next;
    }
    cur = head;

    return sortedListToBST(&cur, size);
  }
};
#endif //LINTCODE_CODE_H
