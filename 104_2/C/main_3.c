#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct QueueNode {
    unsigned int depth;
    struct QueueNode *next;
    struct TreeNode *tree_node;
};

struct Queue {
    size_t queue_size;
    struct QueueNode *front;
    struct QueueNode *rear;
};

/**
 * @brief Init a tree node
 * @param value an integer
 * @return struct TreeNode* pointer to memory containing tree node struct
 */
struct TreeNode*
initTreeNode(int value) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if(NULL == node) { exit(-1); }
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * @brief links a root to its branches
 * @param root
 * @param left
 * @param right
 * @return struct TreeNode* - the root
 */
struct TreeNode*
linkTreeNodes(struct TreeNode *root, struct TreeNode *left, struct TreeNode *right) {
    root->left = left;
    root->right = right;
    return root;
}

/**
 * @brief Init a node with a tree node and the depth of that node
 * @param tree_node a pointer to the tree node (in memory)
 * @param depth the depth of the node
 * @return a pointer to the queue node struct in memory
 */
struct QueueNode*
initQueueNode(struct TreeNode *tree_node, unsigned int depth) {
    struct QueueNode *q_node = malloc(sizeof(struct QueueNode));
    if(NULL == q_node) { exit(-1); }

    q_node->tree_node = tree_node;
    q_node->depth = depth;
    q_node->next = NULL;
    return q_node;
}

/**
 * @brief inits a queue struct.  The Queue has no members.  If a queue without members falls in the woods, does it make a sound?
 * @param void no parameters.  Use void to make sure nothing goes funky.
 * @return returns a pointer to a Queue struct in memory.
 */
struct Queue*
initQueue(void) {
    struct Queue *q = malloc(sizeof(struct Queue));
    if(NULL == q) { exit(-1); }
    q->queue_size = 0;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

/**
 * @brief
 * @param
 * @return
 */
struct Queue*
enqueue(struct Queue *q, struct QueueNode *q_node) {
    switch(q->queue_size) {
        case 0 : {
            q->front = q_node;
            q->rear = q_node;
            q->queue_size = 1;
            break;
        };
        case 1 : {
            q->front->next = q_node;
            q->rear = q_node;
            ++q->queue_size;
            break;
        };
        default : {
            q->rear->next = q_node;
            q->rear = q_node;
            ++q->queue_size;
            break;
        }
    }
    return q;
}

/**
 * @brief
 * @param
 * @return
 */
struct Queue*
deque(struct Queue *q) {
    switch(q->queue_size) {
        case 0 : {
            break;
        };
        case 1 : {
            struct QueueNode *q_temp = q->front;
            (void) free(q_temp);
            q->front = NULL;
            q->rear = NULL;
            --q->queue_size;
            break;
        };
        default : {
            struct QueueNode *q_temp = q->front;
            q->front = q->front->next;
            (void) free(q_temp);
            --q->queue_size;
            break;
        };
    }
    return q;
}

/**
 * @brief
 * @param
 * @return
 */
unsigned int
printQueue(struct Queue *q) {
    unsigned int print_size = 0;
    if(0 == q->queue_size) {
        return print_size;
    }
    struct QueueNode *current_q_node = q->front;
    while(NULL != current_q_node) {
        (void) printf("\n%d : %s >\tq node value: %d\tq node depth: %d\n", __LINE__, __FUNCTION__, current_q_node->tree_node->val, current_q_node->depth);
        print_size++;
        current_q_node = current_q_node->next;
    }
    return print_size;
}

int 
maxDepth(struct TreeNode* root) {
    if(NULL == root) {
        return 0;
    }
    struct Queue *q = initQueue();
    /** root */
    int depth = 1;
    struct QueueNode* current_node = initQueueNode(root, depth);
    
    while(NULL != current_node) {
        depth++;
        if(NULL != current_node->tree_node->left) {
            /** left */
            q = enqueue(q, initQueueNode(current_node->tree_node->left, depth));
        }

        if(NULL != current_node->tree_node->right) {
            q = enqueue(q, initQueueNode(current_node->tree_node->right, depth));
        }
        
        /**  check the  q*/
        (void) printQueue(q);
        if(1 != q->queue_size) {
            depth = q->rear->depth; }
                
        /** switch current to front of q */
        (void) deque(q);

        if(0 == q->queue_size) {
            current_node = NULL;
        } else {
            current_node = q->front;
        }
        (void) printf("\n%d : %s>\tDepth: %d\n", __LINE__, __FUNCTION__, depth);
    }
    
    (void) free(q);
    
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
    struct TreeNode *node1 = initTreeNode(1);
    struct TreeNode *node2 = initTreeNode(2);
    struct TreeNode *node3 = initTreeNode(3);
    struct TreeNode *node4 = initTreeNode(4);
    struct TreeNode *node5 = initTreeNode(5);

    node1 = linkTreeNodes(node1, node2, node3);
    node2 = linkTreeNodes(node2, node4, node5);

    int max_depth = maxDepth(node1);

    (void) printf("%d : %s>\tMax Depth: %d\n", __LINE__, __FUNCTION__, max_depth);

    (void) free(node1);
    (void) free(node2);
    (void) free(node3);
    (void) free(node4);
    (void) free(node5);
}