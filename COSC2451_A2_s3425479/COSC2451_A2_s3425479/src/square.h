#ifndef SQUARE
#define SQUARE

struct square {
    char value;
    char label;
    struct square *up;
    struct square *down;
    struct square *left;
    struct square *right;
};
/** To create the first square node in the map
 */
struct square *create_square_NULL();

/** Create the rest of the map*/
struct square *create_square(char value, int label, struct square *up, struct square *down, struct square *left, struct square *right);

/** 
 * insert to right square to the map
 * @param current_node 
 * @param right_node the next node to insert to the right
 */
void insert_right(struct square *current_node, struct square *right_node);

/**
 * insert the down square to the map
 * @param current_node
 * @param down_node the node the insert down the current node
 */
void insert_down(struct square *current_node, struct square *down_node);

/**
 * free the square after done writting or reading map
 * @param current_node
 */
void square_free(struct square *current_node);
#endif
