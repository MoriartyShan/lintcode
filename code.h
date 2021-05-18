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
#include <unordered_set>
using namespace std;

#define LOG cout << __FILE__ << ":" << __LINE__ << ":"

/**
 * Definition for singly-linked list with a random pointer.
 */
namespace lintcode{
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
    lintcode::copyRandomList(current, old_head, current, head);
    return new_head;
  }

  /**
   * This method will be invoked first, you should design your own algorithm
   * to serialize a binary tree which denote by a root node to a string which
   * can be easily deserialized by your own "deserialize" method later.
   */
  string serialize(TreeNode * root);
  /**
   * This method will be invoked second, the argument data is what exactly
   * you serialized at method "serialize", that means the data is not given by
   * system, it's given by your own serialize method. So the format of data is
   * designed by yourself, and deserialize it here as you serialize it in
   * "serialize" method.
   */
  TreeNode * deserialize(string &data);



  /*
    * @param head: The first node of linked list.
    * @return: a tree node
    */
  TreeNode * sortedListToBST(ListNode * head);



  /**
     * @param s: A string
     * @param wordSet: A dictionary of words dict
     * @return: A boolean
     */
  bool wordBreak(string &s, unordered_set<string> &wordSet);




  /**
 * @param s: A string
 * @return: An integer
 */
  int minCut(string &s);
};

}//namespace lintcode
#endif //LINTCODE_CODE_H
