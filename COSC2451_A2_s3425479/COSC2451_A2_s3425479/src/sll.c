#include <stdlib.h>
#include "map.h"
#include "square.h"
#include "pg.h"
#include "sll.h"
#include "move.h"
#include <stdio.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

struct sll* sll_create_null() {
    struct sll* sll_node = malloc(sizeof (struct sll));
    sll_node->square_node = NULL;
    sll_node->next = NULL;
    sll_node->previous = NULL;
    return sll_node;
}

struct sll* sll_create(struct square* sq_node) {
    struct sll* sll_node = sll_create_null();
    sll_node->square_node = sq_node;
    sll_node->next = NULL;
    sll_node->previous = NULL;
    return sll_node;
}

void sll_add_square(struct sll *sll_node, struct square *sq_node) {
    struct sll* node = sll_node;
    if (node->square_node == NULL) {
        node->square_node = sq_node;
    } else {
        while (node->next != NULL) {
            node = node->next;
        }
        struct sll* new_node = sll_create(sq_node);
        node->next = new_node;
        new_node->previous = node;
    }
}

int sll_is_not_exist(struct sll *sll_node, struct square *sq_node) {
    struct sll *node = sll_node;
    while (node != NULL) {
        if (node->square_node == sq_node) {
            return 0;
        }
        node = node->next;
    }
    return 1;
}

void sll_add_sll(struct sll* sll_old, struct sll *sll_new) {
    struct sll *sll_node = sll_new;
    while (sll_node != NULL) {
        sll_add_square(sll_old, sll_node->square_node);
        sll_node = sll_node->next;
    }
}

int sll_count(struct sll* sll_node) {
    int count = 0;
    struct sll* current_sll = sll_node;
    while (current_sll != NULL) {
        count++;
        current_sll = current_sll->next;
    }
    return count;
}

struct square* sll_next_square(struct sll* sll_node) {
    struct square* current_square = sll_node->square_node;
    sll_node->square_node = NULL;
    if (sll_node->next != NULL) {
        sll_node = sll_node->next;
        //free(current_sll);
    }
    return current_square;
}

struct square* sll_take_last(struct sll* sll_node){
    struct sll* node = sll_node;
    while (node->next != NULL) {
        node = node->next;
    }
    struct square* sq_node = node->square_node;
    node->previous->next = NULL;
    free(node);
    return sq_node;
}

struct square* sll_get_last(struct sll* sll_node) {
    struct sll* node = sll_node;
    while (node->next != NULL) {
        node = node->next;
    }
    return node->square_node;
}

void sll_free(struct sll* sll_node) {
    if (sll_node->next == NULL) {
        free(sll_node);
    } else {
        sll_free(sll_node->next);
    }
}