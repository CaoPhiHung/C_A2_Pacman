#include <stdlib.h>
#include "square.h"

struct square *create_square_NULL() {
    struct square *node = malloc(sizeof (struct square));
    node->value = ' ';
    node->up = NULL;
    node->down = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct square *create_square(char value, int label, struct square *up, struct square *down, struct square *left, struct square *right) {
    struct square *node = malloc(sizeof (struct square));
    node->label = label;
    node->value = value;
    node->up = up;
    node->down = down;
    node->left = left;
    node->right = right;
    return node;
}

void insert_right(struct square *current_node, struct square *right_node) {
    if (current_node->right == NULL) {
        current_node->right = right_node;
        right_node->left = current_node;
    } else {
        insert_right(current_node->right, right_node);
    }
}

void insert_down(struct square *current_node, struct square *down_node) {
    if (current_node->down == NULL) {
        current_node->down = down_node;
        down_node->up = current_node;
    } else {
        insert_down(current_node->down, down_node);
    }
}

void square_free(struct square *current_node) {
    free(current_node);
}
