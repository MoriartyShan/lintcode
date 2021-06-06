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
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <map>
using namespace std;

#define LOG cout << __FILE__ << ":" << __LINE__ << ":"

/**
 * Definition for singly-linked list with a random pointer.
 */
namespace lintcode{
template<typename _T>
void show_vector(const std::vector<_T>& v) {
  LOG << "vector:";
  for (auto m : v) {
    std::cout << m << ",";
  }
  std::cout << std::endl;
}
template<typename _T>
void show_set(const std::set<_T>& v) {
  std::string contains = "set:";
  for (auto m : v) {
    contains += (std::to_string(m) + ",");
  }
  std::cout << contains << std::endl;
}

template<>
void show_vector<std::vector<std::string>>(const std::vector<std::vector<std::string>>& v);
template<>
void show_vector<std::vector<int>>(const std::vector<std::vector<int>>& v);

struct UndirectedGraphNode {
  int label;
  vector<UndirectedGraphNode *> neighbors;
  UndirectedGraphNode(int x) : label(x) {};
};

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
    std::cout << "nullptr" << std::endl;
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

  /**
 * @param triangle: a list of lists of integers
 * @return: An integer, minimum path sum
 */
  int minimumTotal(vector<vector<int>> &triangle);

    /**
   * @param grid: a list of lists of integers
   * @return: An integer, minimizes the sum of all numbers along its path
   */
  int minPathSum(vector<vector<int>> &grid);


  /**
* @param n: An integer
* @return: An integer
*/
  int climbStairs(int n);

  /**
 * @param head: head is the head of the linked list
 * @return: head of linked list
 */
  ListNode * deleteDuplicates(ListNode * head);

  /**
 * @param head: head is the head of the linked list
 * @return: head of the linked list
 */
  ListNode * deleteDuplicates2(ListNode * head);

  /**
 * @param m: positive integer (1 <= m <= 100)
 * @param n: positive integer (1 <= n <= 100)
 * @return: An integer
 */
  int uniquePaths(int m, int n);


  /**
   * @param obstacleGrid: A list of lists of integers
   * @return: An integer
   */
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid);

  /**
 * @param A: A list of integers
 * @return: A boolean
 */
  bool canJump(vector<int> &A);

  /**
 * @param A: A list of integers
 * @return: An integer
 */
  int jump(vector<int> &A);

  /**
 * @param S: A string
 * @param T: A string
 * @return: Count the number of distinct subsequences
 */
  int numDistinct(string &S, string &T);

  /**
 * @param word1: A string
 * @param word2: A string
 * @return: The minimum number of steps.
 */
  int minDistance(string &word1, string &word2);

  /**
 * @param height: A list of integer
 * @return: The area of largest rectangle in the histogram
 */
  int largestRectangleArea(vector<int> &heights);

  /*
 * @param start: a string
 * @param end: a string
 * @param dict: a set of string
 * @return: An integer
 */
  int ladderLength(string &start, string &end, unordered_set<string> &dict);

  /*
 * @param start: a string
 * @param end: a string
 * @param dict: a set of string
 * @return: a list of lists of string
 */
  vector<vector<string>> findLadders(string &start, string &end, unordered_set<string> &dict);

  /**
 * @param board: A list of lists of character
 * @param word: A string
 * @return: A boolean
 */
  bool exist(vector<vector<char>> &board, string &word);

  /**
 * @param num: A list of integers
 * @return: An integer
 */
  int longestConsecutive(vector<int> &num);


  void backPackII(
      const int *A, const int *V, const size_t size, const int m,
      int sum, int value, std::vector<int> &memory, int *cur_max_val);

  /**
 * @param m: An integer m denotes the size of a backpack
 * @param A: Given n items with size A[i]
 * @param V: Given n items with value V[i]
 * @return: The maximum value
 */
  int backPackII(int m, vector<int> &A, vector<int> &V);

  /**
 * @param key: A string you should hash
 * @param HASH_SIZE: An integer
 * @return: An integer
 */
  int hashCode(string &key, int HASH_SIZE);

  /**
 * @param hashTable: A list of The first node of linked list
 * @return: A list of The first node of linked list which have twice size
 */
  vector<ListNode*> rehashing(vector<ListNode*> hashTable);


  /**
 * @param A: Given an integer array with no duplicates.
 * @return: The root of max tree.
 */
  TreeNode * maxTree(vector<int> &A);


  /**
 * @param buildings: A list of lists of integers
 * @return: Find the outline of those buildings
 */
  vector<vector<int>> buildingOutline(vector<vector<int>> &buildings);

  /*
 * @param A: Given an integer array
 * @return: nothing
 */
  void heapify(vector<int> &A);

  /**
 * @param board: A list of lists of character
 * @param words: A list of string
 * @return: A list of string
 */
  vector<string> wordSearchII(vector<vector<char>> &board, vector<string> &words);

  /*
 * @param dictionary: an array of strings
 * @return: an arraylist of strings
 */
  vector<string> longestWords(vector<string> &dictionary);


  /**
 * @param candidates: A list of integers
 * @param target: An integer
 * @return: A list of lists of integers
 */
  vector<vector<int>> combinationSum(vector<int> &candidates, int target);

  /*
 * @param s: A string
 * @return: A list of lists of string
 */
  vector<vector<string>> partition(string &s);


  /**
 * @param node: A undirected graph node
 * @return: A undirected graph node
 */
  UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node);

  /**
 * @param nums: A list of integers
 * @return: A list of integers includes the index of the first number and the index of the last number
 */
  vector<int> subarraySum(vector<int> &nums);

};

}//namespace lintcode
#endif //LINTCODE_CODE_H
