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

using namespace std;

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

#define LOG cout << __FILE__ << ":" << __LINE__ << ":"
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
   * @return: nothing
   */

  /**
 * @param head: The head of linked list.
 * @return: You should return the head of the sorted linked list, using constant space complexity.
 */
  ListNode * sortList(ListNode * head);

  void reorderList(ListNode * head) {
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
};
#endif //LINTCODE_CODE_H
