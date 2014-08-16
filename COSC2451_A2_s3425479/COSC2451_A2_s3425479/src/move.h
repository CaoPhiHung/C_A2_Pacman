#ifndef MOVE
#define MOVE

#include "pg.h"
#include "sll.h"

/** declare array with each char is a element */

void setAll(struct pg* p, struct pg* gst1, struct pg* gst2, struct pg* gst3, struct pg* gst4);

extern char f_namesPacman[];

extern char f_namesGhost[];

/** this method will move ghost 1 step in specific direction
  * this method also check whether that direction is available for ghost to go	
  * @param pg *ghost is a struct poiter of the ghost.
  * @param char direction is direction that ghost will move.
  */
void moveG(struct pg* ghost, char direction);

/** this method will move pacman 1 step in specific direction
  * this method also check whether that direction is available for pacman to go	
  * @param pg *ghost is a struct poiter of the ghost.
  * @param char direction is direction that ghost will move.
  */
void moveP(struct pg* pac, char direction);

/** this method will move either ghost or pacman up one step.
  * @param pg *pac is a struct poiter of the ghost or pacman.
  * @param char item will specify struct pg is ghost or pacman.
  */
int moveUp(struct pg *pac, char item);

/** this method will move either ghost or pacman down one step.
  * @param pg *pac is a struct poiter of the ghost or pacman.
  * @param char item will specify struct pg is ghost or pacman.
  */
int moveDown(struct pg *pac, char item);

/** this method will move either ghost or pacman left one step.
  * @param pg *pac is a struct poiter of the ghost or pacman.
  * @param char item will specify struct pg is ghost or pacman.
  */
int moveLeft(struct pg *pac, char item);

/** this method will move either ghost or pacman right one step.
  * @param pg *pac is a struct poiter of the ghost or pacman.
  * @param char item will specify struct pg is ghost or pacman.
  */
int moveRight(struct pg *pac, char item);

/** this is function pointer which will call these following functions
  * moveUp, moveDown, moveLeft, moveRight
  */
int pacmanFP(int (*funcs)(struct pg*, char), struct pg *pac, char item);

/** this method will move pacman base on the direction of pacman, which is specify in struct pg.
  * @param pg *pac is a struct poiter of the ghost or pacman.
  * @param char item will specify struct pg is ghost or pacman.
  */
void movePacman(struct pg *pac, char item);

/////////////////////////////////////////////////////////

//Nguyen
/**
move the ghost in random way, in the maze until the ghost is at the intersection, then it will calculate which way to take next 
*param struct pg* ghost represents the ghost
*param struct pg* pac represents pacman
**/
char randomDir(struct pg* ghost, struct pg* pac);

/** chase pacman only when pacman is in the same row or column with ghost else it will move randomly
*param struct pg* ghost -> ghost
*param struct pg* pac -> pacman
**/
char chasePacman1(struct pg* ghost, struct pg* pac);

/** when pacman is in the power mode the ghost will move away from the pacman when pacman and ghost in the row or column
**/
char avoidPacman1(struct pg* ghost, struct pg * pac);

/** when ghost is at intersection it will look and calculate the distance between it and pacman and choose the shortest direction toward pacmn 
**/
char chasePacmanEuclidean(struct pg* ghost, struct pg * pac);

/**use to move the ghost around in the maze according to the algorithm
**/
void moveghost1(struct pg* ghost, struct pg* pac);
//!Done Nguyen

//Hung
/**
return random direction(‘u’,’r’,’l’,’d’)
*/
char randomDir2();

/**
return value of that square by that direction
* @param struct pg* pg is a struct of ghost
* @param char direction is a direction the ghost want to go next
*/
char squareValue(struct pg* pg, char direction);

/**
return fasle when the value is a wall
*@param char value is a value of the square
*/
bool hasNoWall(char value);

/**
return the direction when the 
ghost is stuck

*@param struct pg is a struck of the ghost
*@param direction is a direction of the ghost
*/
char checkGhostWhenStuck(struct pg* ghost, char direction);

/**
return the direction when the 
ghost is chase the pacman

*@param struct ghost is a struck of the ghost
*@param struct pacman is a struck of the pacman
*/
char chasePacman2(struct pg* ghost, struct pg* pac);

/**
move the ghost by the direction
*@param struct pg is a struck of the ghost
*/
void moveByDirection(struct pg* pg);

/**
move the ghost2 
*@param struct pg is a struck of the ghost
*@param struct pac is a struck of the pacman
*/
void moveghost2(struct pg* ghost2, struct pg* pac);
//Done Hung

//Luan
/** this method checks the next square node can be moveable or not (for all 4 directions) 
  * @param square *node is a  struct used to pass the next node to check this node
  */
bool isMoveable(struct square *node);

/** this method contains simple algorithm to chase the pacman
  * @param square *ghost is a  struct of the ghost
  * @param square *pacman is a  struct of the pacman
  */
char chaseDir(struct pg *ghost, struct pg *pacman);

/** this method control 2 modes are normal and power mode, it also take the direction from the chaseDir() above to control the ghost follow the pacman
  * @param square *ghost is a  struct of the ghost
  * @param square *pacman is a  struct of the pacman
  */
void moveghost3(struct pg* ghost, struct pg* pacman);

/** this method run when the game in power mode, the ghost will run away from the pacman
  * @param square *ghost is a  struct of the ghost
  * @param square *pacman is a  struct of the pacman
  */
char avoidPacman3(struct pg* ghost, struct pg* pacman);

//Done Luan

//Nhan
/** this method contains algorithm of ghost4. It will predict the next conner that pacman will move to, then the ghost will go to there.
  * there is pac_path, which is the path that pacman will follow. This path will be re-calculate when pacman move out of the current path.
  * @param pg* ghost4 is a struct pointer of the ghost4
  * @param pg* ghost1 is a struct pointer of the ghost1
  * @param pg* ghost2 is a struct pointer of the ghost2
  * @param pg* ghost3 is a struct pointer of the ghost3
  * @param pg* pacman is a struct pointer of the pacman
  * @param sll* pac_path is a struct pointer of singly link list that used to store the path of pacman.
  */
void moveghost4(struct pg* ghost4, struct pg* ghost1, struct pg* ghost2, struct pg* ghost3, struct pg* pacman, struct sll* pac_path, int cal_pac);

/** this method will find the short path from ghost to pacman by using recursive algorithm.
  * @param square *sq_g4 is a struct pointer of the square that ghost4 is currently at.
  * @param square *sq_pac is a struct pointer of the square that pacman is currently at.
  * @param sll* path is a struct pointer of singly link list that used to store the conner that recursive function find2 use to check the path in order to return.
  * @param sll* pac_path is a struct pointer of singly link list that used to store the path of pacman.
  * @param int count_path is the number of square that ghost will go through before it reach pacman in order to find the short path.
  * @param pg* g4 is the struct pointer of the the pg ghost4
  * @param pg* pac is the struct pointer of the the pg pacman
  * @return int is the number of squares that recursive function return.
  */
int find2(struct square* sq_g4, struct square* sq_pac, struct sll* path, struct sll* pac_path, int count_path, struct pg* g4, struct pg* pac);

/** this method will return 1 which is consider true when the pointer square parameter is a wall
  * Ghost is considered a wall in this function.
  * @param square *sq_node is the square pointer of the square that need to be check
  * @return int 1 which is consider true when that square is wall
  */
int is_wall(struct square* sq_node);

/** this method will revert the function is_wall()
  * @param square *sq_node is the square pointer of the square that need to be check
  * @return int 0 which is consider true when that square is wall
  */
int is_not_wall(struct square* sq_node);

/** this method will find the next conner that pacman will move to base on it's direction. 
  * Otherwise, this function will return the current square of pacman.
  * This function will check directions that pacman could go, then call these following functions.
  * nextdown, nextleft, nextright, nextup
  * @param pg *pac is the square pointer of the square that need to be check
  * @return struct square* which is the next conner or current position of pacman.
  */
struct square * findConner(struct pg * pac);

/** this method will return 1 which is consider true when the pointer square parameter is a wall in power mode.
  * Ghost is considered not a wall in this function.
  * @param square *sq_node is the square pointer of the square that need to be check
  * @return int 1 which is consider true when that square is wall
  */
int is_wall_power(struct square * sq_node);

/** this method will revert the function is_wall_power()
  * @param square *sq_node is the square pointer of the square that need to be check
  * @return int 0 which is consider true when that square is wall
  */
int is_not_wall_power(struct square * sq_node);

/** this method will find the next conner in the down direction. 
  * Otherwise, this function will return the current square of pacman.
  * @param pg *pac is the square pointer of the square that need to be check
  * @return struct square* which is the next conner or current position of pacman.
  */
struct square * nextdown(struct square * sq_pac);

/** this method will find the next conner in the up direction. 
  * Otherwise, this function will return the current square of pacman.
  * @param pg *pac is the square pointer of the square that need to be check
  * @return struct square* which is the next conner or current position of pacman.
  */
struct square * nextup(struct square * sq_pac);

/** this method will find the next conner in the right direction. 
  * Otherwise, this function will return the current square of pacman.
  * @param pg *pac is the square pointer of the square that need to be check
  * @return struct square* which is the next conner or current position of pacman.
  */
struct square * nextright(struct square * sq_pac);

/** this method will find the next conner in the left direction. 
  * Otherwise, this function will return the current square of pacman.
  * @param pg *pac is the square pointer of the square that need to be check
  * @return struct square* which is the next conner or current position of pacman.
  */
struct square * nextleft(struct square * sq_pac);

/** this method will check whether the square parameter input is the conner or not
  * this function will return 1 which is consider true.
  * @param square* sq_node is the square pointer of the square that need to be check
  * @return int 1 which is consider true when that square is conner
  */
int is_conner(struct square* sq_node, char previous);
//void moveGhost(struct pg *pac);

#endif

