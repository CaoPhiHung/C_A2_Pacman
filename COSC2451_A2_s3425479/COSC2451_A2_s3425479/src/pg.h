#ifndef PG
#define PG
#include "map.h"
#include <stdbool.h>

struct pg {
    char *title; //whatever
    char direction; //u d l r only
    char type; //p g only
    char state; //n p only normal/power	
    //if pacman + normal -> gap ghost chet
    //if pacman + power -> an ghost
    //if ghost + normal -> chase
    //if ghost + power -> bo chay
    char temp;
    int x;
    int y;
    int oldx;
    int oldy;
    int score;
    int live;
    int isDead;
    bool sameColChase;
    struct square *square_old;
    struct square *square_node;
};
/** this method will create a pacman or a ghost are used the same struct pg* and distinguish by type
  * @param char *title is the title of pg
  * @param char direction is the direction of pg
  * @param char state is the state of pacman which is power mode or normal mode
  * @return struct pg* which is pacman or ghost
  */
struct pg *create_pg(char *title, char direction, char state, char type);

/** this function will find the max pellet that the map has.
  * @param struct map* map which is the current map.
  * @int which is the total number of pellet on the map.
  */
int find_max_pellet(struct map *map);

/** this function will look on the map and find the square of pacman 
  * @param struct map* map which is the current map.
  * @param struct pg *pg which is struct of pacman
  * @return square* which is the square of pacman
  */
struct square * setpacman(struct map *map, struct pg *pg);

/** this function will look on the map and find the square of ghost
  * @param struct map* map which is the current map.
  * @param struct pg *pg which is struct of ghost
  * @return square* which is the square of ghost
  */
struct square * setGhost1(struct map *map, struct pg *pg);

/** this function will look on the map and find the square of ghost
  * @param struct map* map which is the current map.
  * @param struct pg *pg which is struct of ghost
  * @return square* which is the square of ghost
  */
struct square * setGhost2(struct map *map, struct pg *pg);

/** this function will look on the map and find the square of ghost
  * @param struct map* map which is the current map.
  * @param struct pg *pg which is struct of ghost
  * @return square* which is the square of ghost
  */
struct square * setGhost3(struct map *map, struct pg *pg);

/** this function will look on the map and find the square of ghost
  * @param struct map* map which is the current map.
  * @param struct pg *pg which is struct of ghost
  * @return square* which is the square of ghost
  */
struct square * setGhost4(struct map *map, struct pg *pg);
#endif
