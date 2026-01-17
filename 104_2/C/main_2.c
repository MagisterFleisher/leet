#include <stdio.h>
#include <stdlib.h>

/****
 * Tree struct
 */
struct Tree {
    int value;
    struct Tree *left;
    struct Tree *right;
};

struct Queue_node {
    struct Tree *node;
    struct Queue_node *front;
    struct Queue_node *rear;
    unsigned int level;
};

struct Queue {
    struct Queue_node *front;
    struct Queue_node *rear;
    size_t size;
};

/**
 * @brief construct a tree node
 * @param value an integer value for the node
 * @return struct *Tree
 */
struct Tree*
initNode(int value) {
    struct Tree *node = malloc(sizeof(struct Tree));
    if(NULL == node) {
        (void) printf("%s %d> Error allocating memory. Exiting....");
        (void) exit(-1);
    }
    node->value  = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/**
 * @brief Links the child nodes to the parent nodes
 * @param node Type: struct Tree*, Description: the parent node
 * @param left Type: struct Tree*, Description: the left child node  
 * @param right Type: struct Tree*, Description: the right child node
 * @return struct Tree*, returns the parent node  This isn't necessary, but having a return value makes it more functional (a good thing), and affords more flexibility
 * @note This could be made into a pure function.  Perhaps in the future. 
 * @note This is simple enough to inline, unless it becomes a pure function or gets added to it.
 */
struct Tree*
linkNodes(struct Tree *node, struct Tree *left, struct Tree *right) {
    node->left = left;
    node->right = right;
    return node;
}

struct Queue_node*
initQueueNode(struct Tree *node, unsigned int level) {
    struct Queue_node *queue_node = malloc(sizeof(struct Queue_node));
    if(NULL == queue_node) {
        (void) printf("%s %d> Error allocating queue_node.  Quitting the program rather than trying to handle the problem...\n");
        (void) exit(-1);
    }
    queue_node->node = node;
    queue_node->front = NULL;
    queue_node->rear = NULL;
    queue_node->level = level;
    return queue_node;
}

struct Queue*
initQueue(void) {
    struct Queue *q = malloc(sizeof(struct Queue));
    if(NULL == q) {
        (void) printf("%s %d> Error allocating memory for queue.  Quitting instead of trying to handle...", __FUNCTION__, __LINE__);
        (void) exit(-1);
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

struct Queue* 
enque(struct Queue *queue, struct Queue_node *queue_node) {
    if(0 == queue->size) {
        queue_node->front = NULL;
        queue_node->rear = NULL;
        queue->front = queue_node;
        queue->rear = queue_node;
        queue->size = 1;
        return queue;
    }
    queue_node->front = queue->rear;
    queue->rear->rear = queue_node;
    queue->size++;
    return queue;
}

struct Queue*
deque(struct Queue *queue) {
    if(0 == queue->size) {
        return queue;
    }
    struct Queue_node *old_front = queue->front;
    queue->front = queue->front->rear;
    (void) free(old_front);
    queue->size--;
    return queue;
}

unsigned int
printQueue(struct Queue *queue) {
    unsigned int printed_items = 0;
    (void) printf("%s %d> Queue Size: %ju\n", __FUNCTION__, __LINE__, queue->size);
    if(0 == queue->size) {
        return printed_items;
    }
    struct Queue_node *temp_node = queue->front; 
    for(size_t index = 0; index < queue->size; index++) {
        (void) printf("\t%s %d> Queue node level: %d\n", __FUNCTION__, __LINE__, temp_node->level);
        (void) printf("\t%s %d> Queue node value: %d\n", __FUNCTION__, __LINE__, temp_node->node->value);
        temp_node = temp_node->rear;
        printed_items++;
    }

    return printed_items;
}


int maxDepth(struct Tree* root) {
    unsigned int depth = 0;
    struct Queue *q = initQueue();
    struct Queue_node *q_node_root = initQueueNode(root, depth);
    
    q = enque(q, q_node_root);
    (void) printf("%s %d> Queue size: %ju\n\n", __FUNCTION__, __LINE__, q->size);
    (void) printf("%s %d> Depth: %d\n\n", __FUNCTION__, __LINE__, depth);
    struct Queue_node *current_q_node = q->front;

    while(NULL != current_q_node) {
        (void) printf("%s %d> Queue size: %ju\n", __FUNCTION__, __LINE__, q->size);
        if(NULL != current_q_node->node->left) {
            struct Queue_node *q_node_left = initQueueNode(current_q_node->node->left, ++current_q_node->level);
            (void) printf("%s %d> Left Node %d\n", __FUNCTION__, __LINE__, q_node_left->node->value);
            q = enque(q, q_node_left);
        }
        (void) printQueue(q);
        (void) printf("%s %d> Queue size: %ju\n", __FUNCTION__, __LINE__, q->size);

        if(NULL != current_q_node->node->right) {
            struct Queue_node *q_node_right = initQueueNode(current_q_node->node->right, ++current_q_node->level);
            (void) printf("%s %d> Right Node %d\n", __FUNCTION__, __LINE__, q_node_right->node->value);
            q = enque(q, q_node_right);
        }
        (void) printQueue(q);
        (void) printf("%s %d> Queue size: %ju\n", __FUNCTION__, __LINE__, q->size);
        (void) printf("%s %d> Depth: %d\n", __FUNCTION__, __LINE__, depth);
        (void) printQueue(q);
        depth = q->front->level;
        q = deque(q);
        current_q_node = q->front;
        (void) printQueue(q);
    }

    (void) free(q);

    return depth;
}

int
main(int argument_count, char **argument_vector) {
    /* 
         3
        / \
       9  20
          / \
         15  7
    */
   struct Tree *node3 = initNode(3);
   struct Tree *node9 = initNode(9);
   struct Tree *node20 = initNode(20);
   struct Tree *node15 = initNode(15);
   struct Tree *node7 = initNode(7);
   node3 = linkNodes(node3, node9, node20);
   node20 = linkNodes(node20, node15, node7);
   
   (void) printf("\tNode value: %d\n", node3->value);
   struct Queue_node *queue_node = initQueueNode(node3, 0);
   struct Queue *queue = initQueue();
   queue = enque(queue, queue_node);
   queue = deque(queue);
   
   
   /* (void) printf("\tQueue Front Value: %d\n", queue->front->node->value);
   (void) printf("%s %d> Queue size: %ju\n", __FUNCTION__, __LINE__, queue->size);
   (void) printQueue(queue);
    */
   //(void) free(queue_node);
   int max_depth = maxDepth(node3);
/*    (void) free(queue);
   (void) free(node3);
   (void) free(node9);
   (void) free(node20);
   (void) free(node15);
   (void) free(node7);
 */
   return EXIT_SUCCESS;
}