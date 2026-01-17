#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * 08. Convert Sorted Array to Binary Search Tree
  * Given an integer array nums where the elements are
  *  sorted in ascending order, convert it to a height-balanced 
  * binary search tree
  * Input: nums = [-10,-3,0,5,9]
  * Output: [0,-3,9,-10,null,5]
  * Explanation: [0,-10,5,null,-3,null,9] is also accepted:
  * 
  * Constraints:
  * 1 <= nums.length <= 10^4
  * -10^4 <= nums[i] <= 10^4
  * nums is sorted in a strictly increasing order.
  * 
  * 
  *  Algorithm
  * 1: find the center, or a center.
  * 2: make that our root node
  * 3: find a center to the left
  * 4: make that our left node
  * 5: find a center to the right
  * 6: make that our right node
  * 7: repeat
  * 
  * Tasks
  * 1: Create a tree node initializer function
  * 2: make a tree linker function
  * 3: create a tree printer function for debugging
  * 4: implement the algorithm
 */

enum Direction {
    LEFT = 0,
    RIGHT = 1
};

struct TreeNode*
initNode(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if(NULL == node) {
        (void) exit(-1);
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct TreeNode*
linkNodes(struct TreeNode *root, struct TreeNode *child, enum Direction direction) {
    switch(direction) {
        case LEFT : {
            root->left = child;
            break;
        }
        case RIGHT : {
            root->right = child;
            break;
        }
        default : {
            break;
        }
    }
    return root;
}

void
printTree(struct TreeNode *node) {
    if(NULL == node) {
        return;
    }
    (void) printTree(node->left);

    (void) printf("%d ", node->val);

    (void) printTree(node->right);

    return;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define QUEUE_SIZE 10000

struct Queue {
    int value[QUEUE_SIZE];
    int front;
    int rear;
    size_t size;
};

struct Queue q;

void
initQueue() { 
    q.front = 0;
    q.rear = -1;
    q.size = 0;
}

void
enque(int value) {
    q.rear++;
    q.value[q.rear] = value;
    q.size++;
}

void
dequeue() {
    if(0 == q.size) {
        return;
    }
    q.front++;
    q.size--;
}


struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    assert(0 != numsSize);
    switch(numsSize) {
        case 1 : {
            struct TreeNode *root = initNode(nums[0]);
            return root;
            break; }
        case 2 : {
            struct TreeNode *node_left = initNode(nums[0]);
            struct TreeNode *root = initNode(nums[1]);
            root = linkNodes(root, node_left, LEFT);
            return root;
            break;
        }
        case 3 : {
            struct TreeNode *node_left = initNode(nums[0]);
            struct TreeNode *root = initNode(nums[1]);
            struct TreeNode *node_right = initNode(nums[2]);
            root = linkNodes(root, node_left, LEFT);
            root = linkNodes(root, node_right, RIGHT);
            return root;
            break;
        }
        default: {
            break;
        }
    }

    /*
    create sufficient q in static memory

    a := [-10,-3, 0, 5, 9]

    create hashmap for nodes?
    create array of nodes?

    struct q_tree_node {
      node
      left tree array front index, tree array end index
      right tree array front index, tree array end index
    }

    enque all

    use front
    find middle, range left, range right
      current middle is node
      enque(range left)
      look ahead to middle left, attach as node left
      enque(range right)
      look ahead to middle right, attach as node right
    deque
    if q not empty, repeat
    */
    
    return NULL;
}

int
main(int argument_count, char **argument_vector) {
    /*
    * Input: nums = [-10,-3,0,5,9]
    * Output: [0,-3,9,-10,null,5]
             0
           /   \
          -3    9
         /     /
      -10     5

  * Explanation: [0,-10,5,null,-3,null,9]
            0
          /   \
        -10    5
          \     \
          -3     9
  */

  int nums[] = {-10,-3,0,5,9};
  int numsSize =5;

  return EXIT_SUCCESS;
}