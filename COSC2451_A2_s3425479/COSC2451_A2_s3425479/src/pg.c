#include <stdlib.h>
#include "map.h"
#include "square.h"
#include "pg.h"
#include <stdio.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

struct pg *create_pg(char *title, char direction, char state, char type) {
    struct pg *pg = malloc(sizeof (struct pg));
    pg->title = title;
    pg->direction = direction;
    pg->state = state;
    pg->temp = ' ';
    pg->type = type;
    pg->square_node = NULL;
    pg->square_old = NULL;
    pg->score = 0;
    pg->live = 3;
    pg->isDead = 0;
    return pg;
}

int find_max_pellet(struct map *map) {
    struct square *current_node = map->square_node;
    struct square *pivot = current_node;
    int max_pellet = 0;
    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < map->col; j++) {
            if (pivot->value == 's') {
                max_pellet += 1;
            }
            pivot = pivot->right;
        }
        current_node = current_node->down;
        pivot = current_node;
    }

    return max_pellet;
}

struct square * setpacman(struct map *map, struct pg *pg) {
    struct square *current_node = map->square_node;
    struct square *pivot = current_node;
    pg->x = 0;
    pg->y = 0;
    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < map->col; j++) {
            if (pivot->value == 'p' || pivot->value == 'P') {
                pg->square_node = pivot;
                pg->square_old = pivot;
                pg->oldx = pg->x;
                pg->oldy = pg->y;
                return pivot;
            }
            pg->x = pg->x + 1;
            if (pg->x > map->col) {
                pg->x = pg->x % map->col;
            }
            pivot = pivot->right;
        }
        pg->y = pg->y + 1;
        current_node = current_node->down;
        pivot = current_node;
    }
    pg->oldx = pg->x;
    pg->oldy = pg->y;
    return pivot;
}

struct square* setGhost1(struct map *map, struct pg *pg) {
    struct square *current_node = map->square_node;
    struct square *pivot = current_node;
    pg->x = 0;
    pg->y = 0;
    int count = 1;
    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < map->col; j++) {
            if (pivot->value == 'g' || pivot->value == 'G') {
                if (count == 1) {
                    pg->square_node = pivot;
                    pg->square_old = pivot;
                    pg->oldx = pg->x;
                    pg->oldy = pg->y;
                    return pivot;
                }
                count++;
            }
            pg->x = pg->x + 1;
            if (pg->x > map->col) {
                pg->x = pg->x % map->col;
            }
            pivot = pivot->right;
        }
        pg->y = pg->y + 1;
        current_node = current_node->down;
        pivot = current_node;
    }
    pg->oldx = pg->x;
    pg->oldy = pg->y;
    return pivot;
}

struct square * setGhost2(struct map *map, struct pg *pg) {
    struct square *current_node = map->square_node;
    struct square *pivot = current_node;
    pg->x = 0;
    pg->y = 0;
    int count = 1;
    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < map->col; j++) {
            if (pivot->value == 'g' || pivot->value == 'G') {
                if (count == 2) {
                    pg->square_node = pivot;
                    pg->square_old = pivot;
                    pg->oldx = pg->x;
                    pg->oldy = pg->y;
                    return pivot;
                }
                count++;
            }

            pg->x = pg->x + 1;
            if (pg->x > map->col) {
                pg->x = pg->x % map->col;
            }

            pivot = pivot->right;

        }

        pg->y = pg->y + 1;

        current_node = current_node->down;
        pivot = current_node;
    }
    pg->oldx = pg->x;
    pg->oldy = pg->y;
    return pivot;
}

struct square * setGhost3(struct map *map, struct pg *pg) {
    struct square *current_node = map->square_node;
    struct square *pivot = current_node;
    pg->x = 0;
    pg->y = 0;
    int count = 1;
    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < map->col; j++) {
            if (pivot->value == 'g' || pivot->value == 'G') {
                if (count == 3) {
                    pg->square_node = pivot;
                    pg->square_old = pivot;
                    pg->oldx = pg->x;
                    pg->oldy = pg->y;
                    return pivot;
                }
                count++;
            }
            pg->x = pg->x + 1;
            if (pg->x > map->col) {
                pg->x = pg->x % map->col;
            }
            pivot = pivot->right;
        }
        pg->y = pg->y + 1;
        current_node = current_node->down;
        pivot = current_node;
    }
    pg->oldx = pg->x;
    pg->oldy = pg->y;
    return pivot;
}

struct square * setGhost4(struct map *map, struct pg *pg) {
    struct square *current_node = map->square_node;
    struct square *pivot = current_node;
    pg->x = 0;
    pg->y = 0;
    int count = 1;
    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < map->col; j++) {
            if (pivot->value == 'g' || pivot->value == 'G') {
                if (count == 4) {
                    pg->square_node = pivot;
                    pg->square_old = pivot;
                    pg->oldx = pg->x;
                    pg->oldy = pg->y;
                    return pivot;
                }
                count++;
            }
            pg->x = pg->x + 1;
            if (pg->x > map->col) {
                pg->x = pg->x % map->col;
            }
            pivot = pivot->right;
        }
        pg->y = pg->y + 1;
        current_node = current_node->down;
        pivot = current_node;
    }
    pg->oldx = pg->x;
    pg->oldy = pg->y;
    return pivot;
}
