#ifndef SLL
#define SLL

struct sll {
    struct square* square_node;
    struct sll* next;
    struct sll* previous;
};
/** this function will create a singly link list with null value
  * @return sll* which is the singlt link list
  */
struct sll* sll_create_null();

/** this function will create a singly link list with the first value in the parameter
  * @param struct square* sq_node is the first value of singly link list
  * @return sll* which is the singlt link list
  */
struct sll* sll_create(struct square* sq_node);

/** this function will add a square to a singly link list.
  * @param struct sll *sll_node is the singly link list that will be added
  * @param struct square* sq_node is the value that will be add to singly link list.
  */
void sll_add_square(struct sll *sll_node, struct square *sq_node);

/** this function will check that a square value is already exist in the singly linked list or not
  * @param struct square* sq_node is the first value of singly link list
  * @param struct square* sq_node is the value that will be add to singly link list.
  * @return int 1 is consider is true
  */
int sll_is_not_exist(struct sll *sll_node, struct square *sq_node);

/** this function will add a singly linked list to an existed one.
  * @param struct sll *sll_old is the singly link list of the exist one
  * @param struct sll *sll_new is the singly link list that will be take value to the others.
  */
void sll_add_sll(struct sll* sll_old, struct sll *sll_new);

/** this function will count the total number of elements in the list.
  * @param struct sll *sll_node is the singly link list of the exist one
  * @return int 1 is consider is true
  */
int sll_count(struct sll* sll_node);

/** this function take the next value in the list and return that square.
  * then it will free and remove that element.
  * @param struct sll *sll_node is the list that will be used.
  * @return struct square* 
  */
struct square* sll_next_square(struct sll* sll_node);

/** this function take the last value in the list and return that square.
  * then it will free and remove that element.
  * @param struct sll *sll_node is the list that will be used.
  * @return struct square* 
  */
struct square* sll_take_last(struct sll* sll_node);

/** this function take the last value in the list and return that square.
  * then it will not free and remove that element.
  * @param struct sll *sll_node is the list that will be used.
  * @return struct square* 
  */
struct square* sll_get_last(struct sll* sll_node);

/** this function will free a singly linked list.
  * @param struct sll *sll_node is the singly link list that will be used
  */
void sll_free(struct sll* sll_node);

#endif
