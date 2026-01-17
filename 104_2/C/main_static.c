#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * The number of nodes in the tree is in the range [0, 10^4].
 * -100 <= Node.val <= 100
 */

#define QUEUE_SIZE 10000

struct Queue {
    uint_fast16_t depth[QUEUE_SIZE];
    struct TreeNode *node[QUEUE_SIZE];
    int front;
    int rear;
    size_t size;
};

enum Direction {
    LEFT = 1,
    RIGHT = 2
};

struct Queue q;

struct TreeNode*
initTreeNode(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if(NULL == node) { exit(-1); }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode*
linkTreeNodes(struct TreeNode* root, struct TreeNode* child, enum Direction direction) {
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
initQueue() {
    q.front = 0;
    q.rear = -1;
    q.size = 0;
}

void
enqueue(struct TreeNode *node, uint_fast16_t depth) {
    ++q.rear;
    ++q.size;
    q.node[q.rear] = node;
    q.depth[q.rear] = depth;
}

void
dequeue() {
    ++q.front;
    --q.size;
}

void
printQueue() {
    (void) printf("Queue Size: %ju\n", q.size);
    for(int index = q.front; index <= q.rear; index++) {
        (void) printf("Node: %d | Depth : %zu\n", q.node[index], q.depth[index]);
    }
}

int
maxDepth(struct TreeNode *root) {
    if(NULL == root) {
        return 0;
    }
    if((NULL == root->left) && (NULL == root->right)) {
        return 1;
    }
    initQueue();
    uint_fast16_t depth = 1;
    enqueue(root, depth);
    struct TreeNode *current_node = root;

    while(NULL != current_node) {
        if(NULL != current_node->left) {
            enqueue(current_node->left, (1 + depth));
        }
        if(NULL != current_node->right) {
            enqueue(current_node->right, (1 + depth));
        }
        printQueue();
        if(1 == q.size) {
            current_node = NULL;
        } else {
            dequeue();
            depth = q.depth[q.front];
            current_node = q.node[q.front]; 
        }
    }

    return depth;
}

int
main(int argument_count, char **argument_vector) {
    /*
            1
           / \
          2   3
         /  \ 
        4    5        
    */


    (void) initQueue();
    struct TreeNode *node1 = initTreeNode(1);
    struct TreeNode *node2 = initTreeNode(2);
    struct TreeNode *node3 = initTreeNode(3);
    struct TreeNode *node4 = initTreeNode(4);
    struct TreeNode *node5 = initTreeNode(5);

    node1 = linkTreeNodes(node1, node2, LEFT);
    node1 = linkTreeNodes(node1, node3, RIGHT);
    node2 = linkTreeNodes(node2, node4, LEFT);
    node2 = linkTreeNodes(node2, node5, RIGHT);
    
    int max_depth = maxDepth(node1);

    (void) printf("%d : %s>\tMax Depth: %d\n", __LINE__, __FUNCTION__, max_depth);

    (void) free(node1);
    (void) free(node2);
    (void) free(node3);
    (void) free(node4);
    (void) free(node5);


    return EXIT_SUCCESS;
}