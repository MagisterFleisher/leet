#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Queue {
    int head;
    int tail;
    size_t size;
    struct TreeNode *node[5000];
    uint16_t depth[5000];
};

struct Queue q = {.head = 0, .tail = 0, .size = 0};

struct TreeNode*
initNode(int val, struct TreeNode *left, struct TreeNode *right) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if(NULL == node) {
        exit(-1);
    }
    node->val = val;
    node->left = left;
    node->right = right;

    return node;
}

void
printTree(struct TreeNode *root) {
    if(NULL == root) {
        return;
    }
    printTree(root->left);
    (void) printf("%d\n", root->val);
    printTree(root->right);

    return;
}

void
sizeTree(struct TreeNode *node, uint16_t *size) {
    if(NULL == node) {
        return;
    }
    sizeTree(node->left, size);
    ++*size;
    sizeTree(node->right, size);
    return;
}


void
enQ(struct Queue *q, struct TreeNode *node, uint16_t depth) {
    if(0 == q->size) {
        q->node[0] = node;
        q->size = 1;
        q->depth[0] = 1;
        return;
    }
    ++q->tail;
    q->node[q->tail] = node;
    q->depth[q->tail] = depth;
    ++q->size;
    return;
}

void
deQ(struct Queue *q) {
    if(0 == q->size) {
        return;
    }
    ++q->head;
    --q->size;
    return;
}

void
printQ(struct Queue *q) {
    (void) printf("%d : %s\n", __LINE__, __FUNCTION__);
    for(uint16_t i = 0; i < q->size; ++i) {
        (void) printf("node: %d : depth: %d ||\t", q->node[q->head]->val, q->depth[q->head]);
    }
    (void) printf("\n");
    return;
}

void
treeToQ(struct Queue *q, struct TreeNode *node) {
    (void) printf("%d : %s\n", __LINE__, __FUNCTION__);
    uint16_t depth = 0;
    bool left = false;
    bool right = false;
    uint16_t min_depth = 0;
    uint16_t max_depth = 0;
    // insert root node into q
    enQ(q, node, depth);
    printQ(q);
    // enq left and right nodes from q head
    struct TreeNode *head_node = node;
    while(0 < q->size) {
        (void) printf("Node val: %d\n", head_node->val);
        depth = q->depth[q->head];
        if(NULL != head_node->left) {
            enQ(q, head_node->left, depth + 1);
        } else {
            if(false == left && false == right) { // Has not yet hit a NULL
                min_depth = depth;
            }
            left = true;
        }
        if(NULL != head_node->right) {
            enQ(q, head_node->right, depth + 1);
        } else {
            if(false == right && false == left) {
                min_depth = depth;
            }
            right = true;
        }
        max_depth = depth;
        deQ(q);
        if(0 != q->size) {
            head_node = q->node[q->head];
            printQ(q);
        }
    }
    if(2 < q->depth[q->head] - min_depth) {
        (void) printf("Unbalanced.\n\n");
        return;
    }
    (void) printf("Min depth: %d\t\t", min_depth);
    (void) printf("Max depth: %d\n\n", max_depth);
    if(1 < (max_depth - min_depth)) {
        (void) printf("Unbalanced.\n\n");
    } else {
        (void) printf("Balanced.\n\n");
    }
    return;
}

bool
isBalanced(struct TreeNode* root) {
    uint16_t depth = 0;
    bool balanced = true;
    bool left = false;
    bool right = false;
    uint16_t min_depth = 0;
    uint16_t max_depth = 0;
    // insert root node into q
    struct TreeNode *node = root;
    if(NULL == root) {
        return balanced;
    }
    enQ(&q, node, depth);
    printQ(&q);
    // enq left and right nodes from q head
    struct TreeNode *head_node = node;
    while(0 < q.size) {
        (void) printf("Node val: %d\n", head_node->val);
        depth = q.depth[q.head];
        if(NULL != head_node->left) {
            enQ(&q, head_node->left, depth + 1);
        } else {
            if(false == left && false == right) { // Has not yet hit a NULL
                min_depth = depth;
            }
            left = true;
        }
        if(NULL != head_node->right) {
            enQ(&q, head_node->right, depth + 1);
        } else {
            if(false == right && false == left) {
                min_depth = depth;
            }
            right = true;
        }
        max_depth = depth;
        deQ(&q);
        if(0 != q.size) {
            head_node = q.node[q.head];
            printQ(&q);
        }
    }
    if(2 < q.depth[q.head] - min_depth) {
        (void) printf("Unbalanced.\n\n");
        balanced = false;
        return balanced;
    }
    (void) printf("Min depth: %d\t\t", min_depth);
    (void) printf("Max depth: %d\n\n", max_depth);
    if(1 < (max_depth - min_depth)) {
        balanced = false;
        (void) printf("Unbalanced.\n\n");
    } else {
        balanced = true;
        (void) printf("Balanced.\n\n");
    }
    return balanced;
}


/** Should return true */
bool
testCase1(void) {
    /**
     *        3
     *      /  \ 
     *     9    20
     *         /   \ 
     *        15   7
     */
    struct TreeNode *node7 = initNode(7, NULL, NULL);
    struct TreeNode *node15 = initNode(15, NULL, NULL);
    struct TreeNode *node20 = initNode(20, node15, node7);
    struct TreeNode *node9 = initNode(9, NULL, NULL);
    struct TreeNode *node3 = initNode(3, node9, node20);

    printTree(node3);
    bool is_balanced = isBalanced(node3);
    uint16_t tree_size = 0;
    sizeTree(node3, &tree_size);
    (void) printf("Tree size: %d\n", tree_size);
    
    //treeToQ(&q, node3);
    
    (void) printf("\n");

    free(node3);
    free(node9);
    free(node20);
    free(node15);
    free(node7);

    return is_balanced;
}

/** Should return false */
bool
testCase2(void) {
    /**
     *       1
     *      /  \ 
     *     2    2
     *    / \        
     *   3   3
     *  /  \ 
     * 4    4 
     */
    struct TreeNode *node4_l = initNode(4, NULL, NULL);
    struct TreeNode *node4_r = initNode(4, NULL, NULL);
    struct TreeNode *node3_l = initNode(3, node4_l, node4_r);
    struct TreeNode *node3_r = initNode(3, NULL, NULL);
    struct TreeNode *node2_l = initNode(2, node3_l, node3_r);
    struct TreeNode *node2_r = initNode(2, NULL, NULL);
    struct TreeNode *node1 = initNode(1, node2_l, node2_r);

    printTree(node1);
    bool is_balanced = isBalanced(node1);
    //treeToQ(&q, node1);
    

    free(node4_l);
    free(node4_r);
    free(node3_l);
    free(node3_r);
    free(node2_l);
    free(node2_r);
    free(node1);

    return is_balanced;
}


int main(int argument_count, char **argument_vector) {
    #if 0
    if(false == testCase1()) {
        (void) printf("Error case1\n");
    } 
    #endif
    #if 1
    if(true == testCase2()) {
        (void) printf("Error case1\n");
    }
    #endif
    return false;
}