#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "move.h"
#include "pg.h"
#include "sll.h"
#include "square.h"

char olddir = ' ';

struct pg* pac;
struct pg* g1;
struct pg* g2;
struct pg* g3;
struct pg* g4;

void setAll(struct pg* p, struct pg* gst1, struct pg* gst2, struct pg* gst3, struct pg* gst4) {
    pac = p;
    g1 = gst1;
    g2 = gst2;
    g3 = gst3;
    g4 = gst4;
}

char f_namesPacman[] = {'u', 'd', 'l', 'r'};

//char f_namesGhost[] = {'u', 'd', 'l', 'r'};

int (*funcsPacman[])(struct pg*, char) = {moveUp, moveDown, moveLeft, moveRight};

//void (*funcsGhost[])(struct pg*) = {upGhost, downGhost, leftGhost, rightGhost};

//extern int score;

void moveG(struct pg* ghost, char direction) {
    if (direction == 'u') {
        ghost->square_node->value = ghost->temp;
        ghost->square_node = ghost->square_node->up;
        ghost->temp = ghost->square_node->value;
        ghost->square_node->value = ghost->type;
        ghost->y = ghost->y - 1;
    }
    if (direction == 'd') {
        ghost->square_node->value = ghost->temp;
        ghost->square_node = ghost->square_node->down;
        ghost->temp = ghost->square_node->value;
        ghost->square_node->value = ghost->type;
        ghost->y = ghost->y + 1;
    }
    if (direction == 'l') {
        ghost->square_node->value = ghost->temp;
        ghost->square_node = ghost->square_node->left;
        ghost->temp = ghost->square_node->value;
        ghost->square_node->value = ghost->type;
        ghost->x = ghost->x - 1;
    }
    if (direction == 'r') {
        ghost->square_node->value = ghost->temp;
        ghost->square_node = ghost->square_node->right;
        ghost->temp = ghost->square_node->value;
        ghost->square_node->value = ghost->type;
        ghost->x = ghost->x + 1;
    }
}

void moveP(struct pg* pac, char direction) {
    if (direction == 'u') {
        pac->square_node->value = ' ';
        pac->square_node = pac->square_node->up;
        pac->temp = pac->square_node->value;
        pac->square_node->value = pac->type;
        pac->y = pac->y - 1;
    }
    if (direction == 'd') {
        pac->square_node->value = ' ';
        pac->square_node = pac->square_node->down;
        pac->temp = pac->square_node->value;
        pac->square_node->value = pac->type;
        pac->y = pac->y + 1;
    }
    if (direction == 'l') {
        pac->square_node->value = ' ';
        pac->square_node = pac->square_node->left;
        pac->temp = pac->square_node->value;
        pac->square_node->value = pac->type;
        pac->x = pac->x - 1;
    }
    if (direction == 'r') {
        pac->square_node->value = ' ';
        pac->square_node = pac->square_node->right;
        pac->temp = pac->square_node->value;
        pac->square_node->value = pac->type;
        pac->x = pac->x + 1;
    }
}

int moveUp(struct pg* pg, char item) {
    struct square* sq_node = pg->square_node->up;
    if (item == 'p') {
        int flag_move = 0;
        if (pg->state == 'n') {
            flag_move = is_not_wall(sq_node);
        }
        if (pg->state == 'p') {
            flag_move = is_not_wall_power(sq_node);
        }

        if (flag_move) {
            if (sq_node->value == 's') {
                pg->score = pg->score + 1;
            }
            if (sq_node->value == 'S') {
                pg->score = pg->score + 5;
                pg->state = 'p';
            }
            if (sq_node->value == 'f' || sq_node->value == 'F') {
                pg->score = pg->score + 3;
            }
            if (sq_node->value == 'g' || sq_node->value == 'G') {
                pg->score = pg->score + 7;
                if (g1->square_node == sq_node) {
                    g1->isDead = 1;
                }
                if (g2->square_node == sq_node) {
                    g2->isDead = 1;
                }
                if (g3->square_node == sq_node) {
                    g3->isDead = 1;
                }
                if (g4->square_node == sq_node) {
                    g4->isDead = 1;
                }
            }
            moveP(pg, 'u');
            return 1;
        }
    }
    if (item == 'g') {
        if (pg->isDead == 0) {
            if (is_not_wall(sq_node)) {
                if (sq_node->value == 'p') {
                    pac->isDead = 1;
                }
                moveG(pg, 'u');
                return 1;
            }
        }
    }
    return 0;
}

int moveDown(struct pg* pg, char item) {
    struct square* sq_node = pg->square_node->down;
    if (item == 'p') {
        int flag_move = 0;
        if (pg->state == 'n') {
            flag_move = is_not_wall(sq_node);
        }
        if (pg->state == 'p') {
            flag_move = is_not_wall_power(sq_node);
        }

        if (flag_move) {
            if (sq_node->value == 's') {
                pg->score = pg->score + 1;
            }
            if (sq_node->value == 'S') {
                pg->score = pg->score + 5;
                pg->state = 'p';
            }
            if (sq_node->value == 'f' || sq_node->value == 'F') {
                pg->score = pg->score + 3;
            }
            if (sq_node->value == 'g' || sq_node->value == 'G') {
                pg->score = pg->score + 7;
                if (g1->square_node == sq_node) {
                    g1->isDead = 1;
                }
                if (g2->square_node == sq_node) {
                    g2->isDead = 1;
                }
                if (g3->square_node == sq_node) {
                    g3->isDead = 1;
                }
                if (g4->square_node == sq_node) {
                    g4->isDead = 1;
                }
            }
            moveP(pg, 'd');
            return 1;
        }
    }
    if (item == 'g') {
        if (pg->isDead == 0) {
            if (is_not_wall(sq_node)) {
                if (sq_node->value == 'p') {
                    pac->isDead = 1;
                }
                moveG(pg, 'd');
                return 1;
            }
        }
    }
    return 0;
}

int moveLeft(struct pg* pg, char item) {
    struct square* sq_node = pg->square_node->left;
    if (item == 'p') {
        int flag_move = 0;
        if (pg->state == 'n') {
            flag_move = is_not_wall(sq_node);
        }
        if (pg->state == 'p') {
            flag_move = is_not_wall_power(sq_node);
        }

        if (flag_move) {
            if (sq_node->value == 's') {
                pg->score = pg->score + 1;
            }
            if (sq_node->value == 'S') {
                pg->score = pg->score + 5;
                pg->state = 'p';
            }
            if (sq_node->value == 'f' || sq_node->value == 'F') {
                pg->score = pg->score + 3;
            }
            if (sq_node->value == 'g' || sq_node->value == 'G') {
                pg->score = pg->score + 7;
                if (g1->square_node == sq_node) {
                    g1->isDead = 1;
                }
                if (g2->square_node == sq_node) {
                    g2->isDead = 1;
                }
                if (g3->square_node == sq_node) {
                    g3->isDead = 1;
                }
                if (g4->square_node == sq_node) {
                    g4->isDead = 1;
                }
            }
            moveP(pg, 'l');
            return 1;
        }
    }
    if (item == 'g') {
        if (pg->isDead == 0) {
            if (is_not_wall(sq_node)) {
                if (sq_node->value == 'p') {
                    pac->isDead = 1;
                }
                moveG(pg, 'l');
                return 1;
            }
        }
    }
    return 0;
}

int moveRight(struct pg* pg, char item) {
    struct square* sq_node = pg->square_node->right;
    if (item == 'p') {
        int flag_move = 0;
        if (pg->state == 'n') {
            flag_move = is_not_wall(sq_node);
        }
        if (pg->state == 'p') {
            flag_move = is_not_wall_power(sq_node);
        }

        if (flag_move) {
            if (sq_node->value == 's') {
                pg->score = pg->score + 1;
            }
            if (sq_node->value == 'S') {
                pg->score = pg->score + 5;
                pg->state = 'p';
            }
            if (sq_node->value == 'f' || sq_node->value == 'F') {
                pg->score = pg->score + 3;
            }
            if (sq_node->value == 'g' || sq_node->value == 'G') {
                pg->score = pg->score + 7;
                if (g1->square_node == sq_node) {
                    g1->isDead = 1;
                }
                if (g2->square_node == sq_node) {
                    g2->isDead = 1;
                }
                if (g3->square_node == sq_node) {
                    g3->isDead = 1;
                }
                if (g4->square_node == sq_node) {
                    g4->isDead = 1;
                }
            }
            moveP(pg, 'r');
            return 1;
        }
    }
    if (item == 'g') {
        if (pg->isDead == 0) {
            if (is_not_wall(sq_node)) {
                if (sq_node->value == 'p') {
                    pac->isDead = 1;
                }
                moveG(pg, 'r');
                return 1;
            }
        }
    }
    return 0;
}

int pacmanFP(int (*funcs)(struct pg*, char), struct pg *pac, char item) {
    return funcs(pac, item);
}

void movePacman(struct pg *pac, char item) {
    for (int i = 0; i < sizeof (funcsPacman) / sizeof (*funcsPacman); i++) {
        if (f_namesPacman[i] == pac->direction) {
            pacmanFP(funcsPacman[i], pac, item);
        }
    }
}

//Nguyen

char chasePacmanEuclidean(struct pg* ghost, struct pg * pac) {
    //at intersection
    double up = ((((ghost->y - 1) - pac->y) * ((ghost->y - 1) - pac->y)) + ((ghost->x - pac->x)*(ghost->x - pac->x)));
    double left = (((ghost->y - pac->y)*(ghost->y - pac->y))+ (((ghost->x - 1) - pac->x)* ((ghost->x - 1) - pac->x)));
    double right = (((ghost->y - pac->y)*(ghost->y - pac->y))+ (((ghost->x + 1) - pac->x)* ((ghost->x + 1) - pac->x)));

    if (up < left) {
        if (up < right) {
            ghost->direction = 'u';
        } else {
            ghost->direction = 'r';
        }
    }

    if (up < right) {
        if (up < left) {
            ghost->direction = 'u';
        } else {
            ghost->direction = 'l';
        }
    }

    return ghost->direction;
}

char randomDir(struct pg* ghost, struct pg * pac) {
    char right = ghost->square_node->right->value;
    char left = ghost->square_node->left->value;
    char up = ghost->square_node->up->value;
    char down = ghost->square_node->down->value;

    //ghost is at intersection
    if ((right == 's' || right == ' ') && (left == 's' || left == ' ') && (up == 's' || up == ' ') && (down == 's' || down == ' ')) {
        ghost->direction = chasePacmanEuclidean(ghost, pac);
    }
    // one way
    if ((right == 's' || right == ' ' || right == 'S' || right == 'f') && ghost->direction != 'l') {
        ghost->direction = 'r';
    } else if ((left == 's' || left == ' ' || left == 'S' || left == 'f') && ghost->direction != 'r') {
        ghost->direction = 'l';
    } else if ((up == 's' || up == ' ' || up == 'S' || up == 'f') && ghost->direction != 'd') {
        ghost->direction = 'u';
    } else if ((down == 's' || down == ' ' || down == 'S' || down == 'f') && ghost->direction != 'u') {
        ghost->direction = 'd';
    } else if (ghost->direction == 'l' && (left != 's' || left != ' ')) {
        if (up == 's' || up == ' ') {
            ghost->direction = 'u';
        } else if (down == 's' || down == ' ') {
            ghost->direction = 'd';
        } else {
            ghost->direction = 'r';
        }
    } else if (ghost->direction == 'u' && (up != 's' || up == ' ')) {
        if (left == 's' || left == ' ') {
            ghost->direction = 'l';
        } else if (right == 's' || right == ' ') {
            ghost->direction = 'r';
        } else {
            ghost->direction = 'd';
        }
    } else if (ghost->direction == 'r' && (right != 's' || right != ' ')) {
        if (up == 's' || up == ' ') {
            ghost->direction = 'u';
        } else if (down == 's' || down == ' ') {
            ghost->direction = 'd';
        } else {
            ghost->direction = 'l';
        }
    } else if (ghost->direction == 'd' && (down != 's' || down != ' ')) {
        if (right == 's' || right == ' ') {
            ghost->direction = 'r';
        } else if (left == 's' || left == ' ') {
            ghost->direction = 'l';
        } else {
            ghost->direction = 'u';
        }

    }

    return ghost->direction;
}

char chasePacman1(struct pg* ghost, struct pg * pac) {
    if (ghost->x == pac->x) {
        if (pac->y < ghost->y) {
            ghost->direction = 'u';
        } else {
            ghost->direction = 'd';
        }
    }
    if (ghost->y == pac->y) {
        if (pac->x < ghost->x) {
            ghost->direction = 'l';
        } else {
            ghost->direction = 'r';
        }
    }
    return ghost->direction;
}

char avoidPacman1(struct pg* ghost, struct pg * pac) {
    if (ghost->x == pac->x) {
        if (pac->y < ghost->y) {
            ghost->direction = 'd';
        } else {
            ghost->direction = 'u';
        }
    }
    if (ghost->y == pac->y) {
        if (pac->x < ghost->x) {
            ghost->direction = 'r';
        } else {
            ghost->direction = 'l';
        }
    }

    return ghost->direction;
}

void moveghost1(struct pg* ghost, struct pg * pac) {
    if (pac->state != 'p') {
        if (ghost->x == pac->x || ghost->y == pac->y) {
            ghost->direction = chasePacman1(ghost, pac);
        } else {
            ghost->direction = randomDir(ghost, pac);
        }
    } else {
        if (ghost->x == pac->x || ghost->y == pac->y) {
            ghost->direction = avoidPacman1(ghost, pac);
        } else {
            ghost->direction = randomDir(ghost, pac);
        }
    }

    if (ghost->direction == 'u') {
        moveUp(ghost, 'g');
    }
    if (ghost->direction == 'd') {
        moveDown(ghost, 'g');
    }
    if (ghost->direction == 'r') {
        moveRight(ghost, 'g');
    }
    if (ghost->direction == 'l') {
        moveLeft(ghost, 'g');
    }


}
// Done Nguyen

//Hung

char randomDir2() {
    char dir = ' ';
    int r = rand() % 4;
    if (r == 0) {
        dir = 'l';
    } else if (r == 1) {
        dir = 'r';
    } else if (r == 2) {
        dir = 'u';
    } else {
        dir = 'd';
    }
    return dir;
}

char squareValue(struct pg* pg, char direction) {
    char right = pg->square_node->right->value;
    char left = pg->square_node->left->value;
    char up = pg->square_node->up->value;
    char down = pg->square_node->down->value;

    //check the direction then return the value	
    if (direction == 'l') {
        return left;
    } else if (direction == 'r') {
        return right;
    } else if (direction == 'u') {
        return up;
    }
    return down;
}

bool hasNoWall(char value) {

    if (value == 's' || value == 'S' || value == 'f' || value == 'F' || value == ' ' || value == 'p') {
        return TRUE;
    }
    return FALSE;
}

char checkGhostWhenStuck(struct pg* ghost, char direction) {
    // check if the down square has wall
    if (hasNoWall(squareValue(ghost, 'd'))) {
        //check if the previous direction is up	then just go up			
        if (olddir == 'u') {
            olddir = 'u';
        } else {
            olddir = 'd';
        }
        return olddir;
        // check if the up square has wall

    } else if (hasNoWall(squareValue(ghost, 'u'))) {
        //check if the previous direction is down then just go down	
        if (olddir == 'd') {
            olddir = 'd';
        } else {
            olddir = 'u';
        }
        return olddir;
    } else {
        if (direction == 'l') {
            olddir = 'r';
        } else {
            olddir = 'l';
        }
        return olddir;
    }
    return olddir;
}

char chasePacman2(struct pg* ghost, struct pg * pac) {
    // ghost will follow pacman by reduce the different in x then y
    //check the different in x
    if (ghost->x > pac->x) {
        //check if the left node has wall value
        if (hasNoWall(squareValue(ghost, 'l'))) {
            // if the value of the square is not a wall then allow it to move 
            olddir = 'l';
            return olddir;
        } else {
            return checkGhostWhenStuck(ghost, 'l');
        }
    } else if (ghost->x < pac->x) {
        //check if the right node has wall value
        if (hasNoWall(squareValue(ghost, 'r'))) {
            // if the value of the square is not a wall then allow it to move 
            olddir = 'r';
            return olddir;
        } else {
            return checkGhostWhenStuck(ghost, 'r');
        }
        //check the different in y	
    } else if (ghost->y > pac->y) {
        //check if the up node has wall value		
        if (hasNoWall(squareValue(ghost, 'u'))) {
            // if the value of the square is not a wall then allow it to move 
            olddir = 'u';
        } else {
            ghost->direction = randomDir2();
            int count = 0;
            while (!hasNoWall(squareValue(ghost, ghost->direction))) {
                count++;
                ghost->direction = randomDir2();
                if (count == 4) {
                    break;
                }
            }
            olddir = ghost->direction;
        }
        return olddir;
    } else if (ghost->y < pac->y) {
        //check if the down node has wall value		
        if (hasNoWall(squareValue(ghost, 'd'))) {
            // if the value of the square is not a wall then allow it to move 
            olddir = 'd';
            return olddir;
        } else {
            ghost->direction = randomDir2();
            int count = 0;
            while (!hasNoWall(squareValue(ghost, ghost->direction))) {
                count++;
                ghost->direction = randomDir2();
                if (count == 4) {
                    break;
                }
            }
            olddir = ghost->direction;
        }
        return olddir;
    }
    return ghost->direction;
}

void moveByDirection(struct pg * pg) {
    if (pg->direction == 'u') {
        moveUp(pg, 'g');
    }
    if (pg->direction == 'd') {
        moveDown(pg, 'g');
    }
    if (pg->direction == 'r') {
        moveRight(pg, 'g');
    }
    if (pg->direction == 'l') {
        moveLeft(pg, 'g');
    }
}

char avoidPacman2(struct pg* ghost, char dir) {
    if (dir == 'l') {
        ghost->direction = 'r';
    } else if (dir == 'r') {
        ghost->direction = 'l';
    } else if (dir == 'u') {
        ghost->direction = 'd';
    } else {
        ghost->direction = 'u';
    }
    return ghost->direction;
}

void moveghost2(struct pg* ghost, struct pg * pac) {

    if (pac->x >= ghost->x - 10 && pac->x <= ghost->x + 10 && pac->y >= ghost->y - 10 && pac->y < ghost->y + 10) {
        ghost->direction = chasePacman2(ghost, pac);
    } else {
        ghost->direction = randomDir2();
        int count = 0;
        while (!hasNoWall(squareValue(ghost, ghost->direction))) {
            count++;
            ghost->direction = randomDir2();
            if (count == 4) {
                break;
            }
        }
    }

    if (pac->state == 'p') {
        ghost->direction = avoidPacman2(ghost, ghost->direction);
    }
    moveByDirection(ghost);
    /* if(pac->x == 40 && pac->y == 20) {
          pac->live = pac->live - 1;
          }*/
}

//Done Hung

//Luan

bool isMoveable(struct square * node) {
    if (node->value == ' ' || node->value == 's' || node->value == 'S' || node->value == 'f' || node->value == 'p') {
        return true;
    }
    return false;
}

char chaseDir(struct pg *ghost, struct pg * pacman) {
    char dir;

    //ghost phia tren, pacman phia duoi
    if (ghost->y < pacman->y) {
        if (isMoveable(ghost->square_node->down) == true) {
            dir = 'd';
        } else {
            //ghost ben trai, pacman ben phai
            if (ghost->x < pacman->x && ghost->sameColChase == false) {
                if (isMoveable(ghost->square_node->right) == true) {
                    dir = 'r';
                } else if (isMoveable(ghost->square_node->left) == true) {
                    dir = 'l';
                }
            }//ghost ben phai, pacman ben trai
            else if (ghost->x > pacman->x && ghost->sameColChase == false) {
                if (isMoveable(ghost->square_node->left) == true) {
                    dir = 'l';
                } else if (isMoveable(ghost->square_node->right) == true) {
                    dir = 'r';
                }
            }//pacman vs ghost same col
            else {
                ghost->sameColChase = true;

                //random left
                dir = 'l';

            }

        }
    }//ghost phia duoi, pacman phia tren
    else if (ghost->y > pacman->y) {
        if (isMoveable(ghost->square_node->up) == true) {
            dir = 'u';
        } else {
            //ghost ben trai, pacman ben phai
            if (ghost->x < pacman->x && ghost->sameColChase == false) {
                if (isMoveable(ghost->square_node->right) == true) {
                    dir = 'r';
                } else if (isMoveable(ghost->square_node->left) == true) {
                    dir = 'l';
                }
            }//ghost ben phai, pacman ben trai
            else if (ghost->x > pacman->x && ghost->sameColChase == false) {
                if (isMoveable(ghost->square_node->left) == true) {
                    dir = 'l';
                } else if (isMoveable(ghost->square_node->right) == true) {
                    dir = 'r';
                }
            }//pacman vs ghost same col
            else {
                ghost->sameColChase = true;

                //random left
                dir = 'l';

            }
        }
    }//ghost same row vs pacman
    else if (pacman->y == ghost->y) {
        //ghost trai, pacman phai
        if (ghost->x < pacman->x) {
            if (isMoveable(ghost->square_node->right) == true) {
                dir = 'r';
            }
        }//ghost phai, pacman trai
        else if (ghost->x > pacman->x) {
            if (isMoveable(ghost->square_node->left) == true) {
                dir = 'l';
            }
        }
    }

    return dir;
}

void moveghost3(struct pg* ghost, struct pg * pacman) {

    if (pacman->state == 'n') {
        ghost->direction = chaseDir(ghost, pacman);
    } else {
        ghost->direction = avoidPacman3(ghost, pacman);
    }


    if (ghost->direction == 'u') {
        moveUp(ghost, 'g');
    }
    if (ghost->direction == 'd') {
        moveDown(ghost, 'g');
    }
    if (ghost->direction == 'r') {
        moveRight(ghost, 'g');
    }
    if (ghost->direction == 'l') {
        moveLeft(ghost, 'g');
    }
}

char avoidPacman3(struct pg* ghost, struct pg * pacman) {
    char dir;

    //ghost phia tren, pacman phia duoi
    if (ghost->y < pacman->y) {
        if (isMoveable(ghost->square_node->up) == true) {
            dir = 'u';
        } else {
            //ghost ben trai, pacman ben phai
            if (ghost->x < pacman->x && ghost->sameColChase == false) {
                if (isMoveable(ghost->square_node->left) == true) {
                    dir = 'l';
                }
            }//ghost ben phai, pacman ben trai
            else if (ghost->x > pacman->x && ghost->sameColChase == false) {
                if (isMoveable(ghost->square_node->right) == true) {
                    dir = 'r';
                }
            }//pacman vs ghost same col
            else {
                ghost->sameColChase = true;

                if (isMoveable(ghost->square_node->left) == true) {
                    dir = 'l';
                } else if (isMoveable(ghost->square_node->right) == true) {
                    dir = 'r';
                }

            }

        }
    }//ghost phia duoi, pacman phia tren
    else if (ghost->y > pacman->y) {
        if (isMoveable(ghost->square_node->down) == true) {
            dir = 'd';
        } else {
            //ghost ben trai, pacman ben phai
            if (ghost->x < pacman->x && ghost->sameColChase == false) {
                if (isMoveable(ghost->square_node->left) == true) {
                    dir = 'l';
                }
            }//ghost ben phai, pacman ben trai
            else if (ghost->x > pacman->x && ghost->sameColChase == false) {
                if (isMoveable(ghost->square_node->right) == true) {
                    dir = 'r';
                }
            }//pacman vs ghost same col
            else {
                ghost->sameColChase = true;

                if (isMoveable(ghost->square_node->left) == true) {
                    dir = 'l';
                } else if (isMoveable(ghost->square_node->right) == true) {
                    dir = 'r';
                }

            }
        }
    }//ghost same row vs pacman
    else if (pacman->y == ghost->y) {
        //ghost trai, pacman phai
        if (ghost->x < pacman->x) {
            if (isMoveable(ghost->square_node->left) == true) {
                dir = 'l';
            } else if (isMoveable(ghost->square_node->up) == true) {
                dir = 'u';
            } else if (isMoveable(ghost->square_node->down) == true) {
                dir = 'd';
            }
        }//ghost phai, pacman trai
        else if (ghost->x > pacman->x) {
            if (isMoveable(ghost->square_node->right) == true) {
                dir = 'r';
            } else if (isMoveable(ghost->square_node->up) == true) {
                dir = 'u';
            } else if (isMoveable(ghost->square_node->down) == true) {
                dir = 'd';
            }
        }
    }

    return dir;
}


// Nhan
// Return 1 for wall

int is_wall_power(struct square * sq_node) {
    char va = sq_node->value;
    if (va == 's' || va == 'S' || va == 'f' || va == 'F' || va == ' ' || va == 'p' || va == 'P' || va == 'g' || va == 'G') {
        return 0;
    }
    return 1;
}

int is_not_wall_power(struct square * sq_node) {
    if (is_wall_power(sq_node)) {
        return 0;
    }
    return 1;
}

int is_wall(struct square * sq_node) {
    char va = sq_node->value;
    if (va == 's' || va == 'S' || va == 'f' || va == 'F' || va == ' ' || va == 'p' || va == 'P') {
        return 0;
    }
    return 1;
}

int is_not_wall(struct square * sq_node) {
    if (is_wall(sq_node)) {
        return 0;
    }
    return 1;
}

// Return >1 for true

int is_conner(struct square* sq_node, char previous) {
    int conner = 0;
    if (previous == 'l') {
        conner += is_not_wall(sq_node->up);
        conner += is_not_wall(sq_node->down);
    }
    if (previous == 'r') {
        conner += is_not_wall(sq_node->up);
        conner += is_not_wall(sq_node->down);
    }
    if (previous == 'u') {
        conner += is_not_wall(sq_node->left);
        conner += is_not_wall(sq_node->right);
    }
    if (previous == 'd') {
        conner += is_not_wall(sq_node->left);
        conner += is_not_wall(sq_node->right);
    }
    return conner;
}

struct square * nextleft(struct square * sq_pac) {
    if (sq_pac->left != NULL) {
        if (is_wall(sq_pac->left)) return sq_pac;
        if (is_conner(sq_pac, 'l')) {
            return sq_pac;
        } else {
            return nextleft(sq_pac->left);
        }
    } else {
        return sq_pac;
    }
}

struct square * nextright(struct square * sq_pac) {
    if (sq_pac->right != NULL) {
        if (is_wall(sq_pac->right)) return sq_pac;
        if (is_conner(sq_pac, 'r')) {
            return sq_pac;
        } else {
            return nextright(sq_pac->right);
        }
    } else {
        return sq_pac;
    }
}

struct square * nextup(struct square * sq_pac) {
    if (sq_pac->up != NULL) {
        if (is_wall(sq_pac->up)) return sq_pac;
        if (is_conner(sq_pac, 'u')) {
            return sq_pac;
        } else {
            return nextup(sq_pac->up);
        }
    } else {
        return sq_pac;
    }
}

struct square * nextdown(struct square * sq_pac) {
    if (sq_pac->down != NULL) {
        if (is_wall(sq_pac->down)) return sq_pac;
        if (is_conner(sq_pac, 'd')) {
            return sq_pac;
        } else {
            return nextdown(sq_pac->down);
        }
    } else {
        return sq_pac;
    }
}

struct square * findConner(struct pg * pac) {
    if (pac->direction == 'l') {
        return nextleft(pac->square_node);
    }
    if (pac->direction == 'r') {
        return nextright(pac->square_node);
    }
    if (pac->direction == 'u') {
        return nextup(pac->square_node);
    }
    if (pac->direction == 'd') {
        return nextdown(pac->square_node);
    }
    return pac->square_node;
}

/*
int findWay(struct square* sq_g4, struct square* sq_pac, struct sll* path, int count_node) {
    if (sq_pac == sq_g4) {
        return count_node;
    } else {
        printf("%d", count_node);
        int min = 0;
        int up = 0;
        int down = 0;
        int left = 0;
        int right = 0;
        struct sll* up_path = sll_create_null();
        struct sll* down_path = sll_create_null();
        struct sll* left_path = sll_create_null();
        struct sll* right_path = sll_create_null();

        //Go down
        if (sq_g4->down != NULL) {
            if (is_not_wall(sq_g4->down)) {
                if (sll_is_not_exist(path, sq_g4->down)) {
                    sll_add_sll(down_path, path);
                    sll_add_square(down_path, sq_g4->down);
                    printf("d");
                    down = findWay(sq_g4->down, sq_pac, down_path, count_node + 1);
                }
            }
        }
        //Go up
        if (sq_g4->up != NULL) {
            if (is_not_wall(sq_g4->up)) {
                if (sll_is_not_exist(path, sq_g4->up)) {
                    sll_add_sll(up_path, path);
                    sll_add_square(up_path, sq_g4->up);
                    printf("u");
                    up = findWay(sq_g4->up, sq_pac, up_path, count_node + 1);
                }
            }
        }


        //Go left
        if (sq_g4->left != NULL) {
            if (is_not_wall(sq_g4->left)) {
                if (sll_is_not_exist(path, sq_g4->left)) {
                    sll_add_sll(left_path, path);
                    sll_add_square(left_path, sq_g4->left);
                    printf("l");
                    left = findWay(sq_g4->left, sq_pac, left_path, count_node + 1);
                }
            }
        }


        //Go right
        if (sq_g4->right != NULL) {
            if (is_not_wall(sq_g4->right)) {
                if (sll_is_not_exist(path, sq_g4->right)) {
                    sll_add_sll(right_path, path);
                    sll_add_square(right_path, sq_g4->right);
                    printf("r");
                    right = findWay(sq_g4->right, sq_pac, right_path, count_node + 1);
                }
            }
        }

        char select = ' ';
        if (up > 1) {
            min = up;
            select = 'u';
        }
        if (down > 1) {
            min = down;
            select = 'd';
        }
        if (left > 1) {
            min = left;
            select = 'l';
        }
        if (right > 1) {
            min = right;
            select = 'r';
        }

        if (min > up && up > 0) {
            min = up;
            select = 'u';
        }
        if (min > down && down > 0) {
            min = down;
            select = 'd';
        }
        if (min > left && left > 0) {
            min = left;
            select = 'l';
        }
        if (min > right && right > 0) {
            min = right;
            select = 'r';
        }

        if (select == 'u') path = up_path;
        if (select == 'd') path = down_path;
        if (select == 'l') path = left_path;
        if (select == 'r') path = right_path;
        return min;
    }
}
 */

/*
void findpath(struct sll* path, struct square* sq_pac) {

    //Return condition
    struct square* last_sq = sll_get_last(path);
    if (last_sq == sq_pac) return;
    
        if (sll_is_exist(path, last_sq->up)) return;
        if (sll_is_exist(path, last_sq->down)) return;
        if (sll_is_exist(path, last_sq->left)) return;
        if (sll_is_exist(path, last_sq->right)) return;
     

    //Clone path to sub path
    struct sll* up_path = sll_create_null();
    struct sll* down_path = sll_create_null();
    struct sll* left_path = sll_create_null();
    struct sll* right_path = sll_create_null();
    sll_add_sll(up_path, path);
    sll_add_sll(down_path, path);
    sll_add_sll(left_path, path);
    sll_add_sll(right_path, path);

    //Recursive find path
    if (last_sq->up != NULL) {
        if (is_not_wall(last_sq->up) && sll_is_not_exist(path, last_sq->up)) {
            sll_add_square(up_path, last_sq->up);
            findpath(up_path, sq_pac);
        }
    }
    if (last_sq->down != NULL) {
        if (is_not_wall(last_sq->down) && sll_is_not_exist(path, last_sq->down)) {
            sll_add_square(down_path, last_sq->down);
            findpath(down_path, sq_pac);
        }
    }
    if (last_sq->left != NULL) {
        if (is_not_wall(last_sq->left) && sll_is_not_exist(path, last_sq->left)) {
            sll_add_square(left_path, last_sq->left);
            findpath(left_path, sq_pac);
        }
    }
    if (last_sq->right != NULL) {
        if (is_not_wall(last_sq->right) && sll_is_not_exist(path, last_sq->right)) {
            sll_add_square(right_path, last_sq->right);
            findpath(up_path, sq_pac);
        }
    }
    
    //Find shortest path
    char sl = 'u';
    int min = sll_count(up_path);
    if (min > sll_count(down_path) && sll_count(down_path) > sll_count(path)) {
        min = sll_count(down_path);
        sl = 'd';
    }
    if (min > sll_count(left_path) && sll_count(left_path) > sll_count(path)) {
        min = sll_count(left_path);
        sl = 'l';
    }
    if (min > sll_count(right_path) && sll_count(right_path) > sll_count(path)) {
        min = sll_count(right_path);
        sl = 'r';
    }

    //Return shortest path
    if (sl == 'u') sll_add_sll(path, up_path);
    if (sl == 'd') sll_add_sll(path, down_path);
    if (sl == 'l') sll_add_sll(path, left_path);
    if (sl == 'r') sll_add_sll(path, right_path);
}
 */
int find2(struct square* sq_g4, struct square* sq_pac, struct sll* path, struct sll* pac_path, int count_path, struct pg* g4, struct pg* pac) {
    struct square* old_up = sq_g4;
    struct square* old_down = sq_g4;
    struct square* old_left = sq_g4;
    struct square* old_right = sq_g4;

    struct square* new_up = old_up;
    struct square* new_down = old_down;
    struct square* new_left = old_left;
    struct square* new_right = old_right;

    if (new_up->up != NULL) {
        if (is_not_wall(new_up->up)) {
            new_up = nextup(new_up->up);
        }
    }
    if (new_down->down != NULL) {
        if (is_not_wall(new_down->down)) {
            new_down = nextdown(new_down->down);
        }
    }
    if (new_left->left != NULL) {
        if (is_not_wall(new_left->left)) {
            new_left = nextleft(new_left->left);
        }
    }
    if (new_right->right != NULL) {
        if (is_not_wall(new_right->right)) {
            new_right = nextright(new_right->right);
        }
    }

    //Flag
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    //check exist
    if (new_up != old_up) {
        if (sll_is_not_exist(path, new_up)) {
            sll_add_square(path, new_up);
            up = 1;
        }
    }
    if (new_down != old_down) {
        if (sll_is_not_exist(path, new_down)) {
            sll_add_square(path, new_down);
            down = 1;
        }
    }
    if (new_left != old_left) {
        if (sll_is_not_exist(path, new_left)) {
            sll_add_square(path, new_left);
            left = 1;
        }
    }
    if (new_right != old_right) {
        if (sll_is_not_exist(path, new_right)) {
            sll_add_square(path, new_right);
            right = 1;
        }
    }

    //prepare for recursive
    struct square* pre_up = old_up;
    struct square* pre_down = old_down;
    struct square* pre_left = old_left;
    struct square* pre_right = old_right;

    //count for check pacman
    int count_up = 0;
    int count_down = 0;
    int count_left = 0;
    int count_right = 0;

    //check pacman
    while (old_up != new_up) {
        if (sq_pac == old_up) {
            while (old_up != pre_up) {
                sll_add_square(pac_path, old_up);
                old_up = old_up->down;
            }
            return count_up + count_path;
        }
        old_up = old_up->up;
        count_up++;
    }
    while (old_down != new_down) {
        if (sq_pac == old_down) {
            while (old_down != pre_down) {
                sll_add_square(pac_path, old_down);
                old_down = old_down->up;
            }
            return count_down + count_path;
        }
        old_down = old_down->down;
        count_down++;
    }
    while (old_left != new_left) {
        if (sq_pac == old_left) {
            while (old_left != pre_left) {
                sll_add_square(pac_path, old_left);
                old_left = old_left->right;
            }
            return count_left + count_path;
        }
        old_left = old_left->left;
        count_left++;
    }
    while (old_right != new_right) {
        if (sq_pac == old_right) {
            while (old_right != pre_right) {
                sll_add_square(pac_path, old_right);
                old_right = old_right->left;
            }
            return count_right + count_path;
        }
        old_right = old_right->right;
        count_right++;
    }

    //Prepare sub path for recursive
    struct sll* up_path = sll_create_null();
    struct sll* down_path = sll_create_null();
    struct sll* left_path = sll_create_null();
    struct sll* right_path = sll_create_null();
    sll_add_sll(up_path, path);
    sll_add_sll(down_path, path);
    sll_add_sll(left_path, path);
    sll_add_sll(right_path, path);

    //Recursive
    int flag = 0;
    int min = 0;
    char sl = ' ';
    //test
    if (pre_down != new_down) {
        if (down) {
            int temp = find2(new_down, sq_pac, path, pac_path, count_path + count_down, g4, pac);
            if (temp) {
                if (min == 0) {
                    min = temp;
                    sl = 'd';
                } else {
                    if (min > temp) {
                        min = temp;
                        sl = 'd';
                    }
                }
                flag = 1;
            }
        }
    }
    if (pre_up != new_up) {
        if (up) {
            int temp = find2(new_up, sq_pac, path, pac_path, count_path + count_up, g4, pac);
            if (temp) {
                if (min == 0) {
                    min = temp;
                    sl = 'u';
                } else {
                    if (min > temp) {
                        min = temp;
                        sl = 'u';
                    }
                }
                flag = 1;
            }
        }
    }
    if (pre_right != new_right) {
        if (right) {
            int temp = find2(new_right, sq_pac, path, pac_path, count_path + count_right, g4, pac);
            if (temp) {
                if (temp) {
                    if (min == 0) {
                        min = temp;
                        sl = 'r';
                    } else {
                        if (min > temp) {
                            min = temp;
                            sl = 'r';
                        }
                    }
                }
                flag = 1;
            }
        }
    }
    if (pre_left != new_left) {
        if (left) {
            int temp = find2(new_left, sq_pac, path, pac_path, count_path + count_left, g4, pac);
            if (temp) {
                if (temp) {
                    if (min == 0) {
                        min = temp;
                        sl = 'l';
                    } else {
                        if (min > temp) {
                            min = temp;
                            sl = 'l';
                        }
                    }
                }
                flag = 1;
            }
        }
    }
    //done
    /*
    if (g4->y < pac->y) {
        if (pre_down != new_down) {
            if (down) {
                int temp = find2(new_down, sq_pac, path, pac_path, count_path + count_down, g4, pac);
                if (temp) {
                    if (min == 0) {
                        min = temp;
                        sl = 'd';
                    } else {
                        if (min > temp) {
                            min = temp;
                            sl = 'd';
                        }
                    }
                    flag = 1;
                }
            }
        }
        if (pre_up != new_up) {
            if (up) {
                int temp = find2(new_up, sq_pac, path, pac_path, count_path + count_up, g4, pac);
                if (temp) {
                    if (min == 0) {
                        min = temp;
                        sl = 'u';
                    } else {
                        if (min > temp) {
                            min = temp;
                            sl = 'u';
                        }
                    }
                    flag = 1;
                }
            }
        }
    } else {
        if (pre_up != new_up) {
            if (up) {
                int temp = find2(new_up, sq_pac, path, pac_path, count_path + count_up, g4, pac);
                if (temp) {
                    if (min == 0) {
                        min = temp;
                        sl = 'u';
                    } else {
                        if (min > temp) {
                            min = temp;
                            sl = 'u';
                        }
                    }
                    flag = 1;
                }
            }
        }
        if (pre_down != new_down) {
            if (down) {
                int temp = find2(new_down, sq_pac, path, pac_path, count_path + count_down, g4, pac);
                if (temp) {
                    if (min == 0) {
                        min = temp;
                        sl = 'd';
                    } else {
                        if (min > temp) {
                            min = temp;
                            sl = 'd';
                        }
                    }
                    flag = 1;
                }
            }
        }
    }
    if (g4->x < pac->x) {
        if (pre_right != new_right) {
            if (right) {
                int temp = find2(new_right, sq_pac, path, pac_path, count_path + count_right, g4, pac);
                if (temp) {
                    if (temp) {
                        if (min == 0) {
                            min = temp;
                            sl = 'r';
                        } else {
                            if (min > temp) {
                                min = temp;
                                sl = 'r';
                            }
                        }
                    }
                    flag = 1;
                }
            }
        }
        if (pre_left != new_left) {
            if (left) {
                int temp = find2(new_left, sq_pac, path, pac_path, count_path + count_left, g4, pac);
                if (temp) {
                    if (temp) {
                        if (min == 0) {
                            min = temp;
                            sl = 'l';
                        } else {
                            if (min > temp) {
                                min = temp;
                                sl = 'l';
                            }
                        }
                    }
                    flag = 1;
                }
            }
        }
    } else {
        if (pre_left != new_left) {
            if (left) {
                int temp = find2(new_left, sq_pac, path, pac_path, count_path + count_left, g4, pac);
                if (temp) {
                    if (temp) {
                        if (min == 0) {
                            min = temp;
                            sl = 'l';
                        } else {
                            if (min > temp) {
                                min = temp;
                                sl = 'l';
                            }
                        }
                    }
                    flag = 1;
                }
            }
        }
        if (pre_right != new_right) {
            if (right) {
                int temp = find2(new_right, sq_pac, path, pac_path, count_path + count_right, g4, pac);
                if (temp) {
                    if (temp) {
                        if (min == 0) {
                            min = temp;
                            sl = 'r';
                        } else {
                            if (min > temp) {
                                min = temp;
                                sl = 'r';
                            }
                        }
                    }
                    flag = 1;
                }
            }
        }
    }*/
    if (flag) {
        if (sl == 'u') {
            while (new_up != pre_up) {
                sll_add_square(pac_path, new_up);
                new_up = new_up->down;
            }
        }
        if (sl == 'd') {
            while (new_down != pre_down) {
                sll_add_square(pac_path, new_down);
                new_down = new_down->up;
            }
        }
        if (sl == 'l') {
            while (new_left != pre_left) {
                sll_add_square(pac_path, new_left);
                new_left = new_left->right;
            }
        }
        if (sl == 'r') {
            while (new_right != pre_right) {
                sll_add_square(pac_path, new_right);
                new_right = new_right->left;
            }
        }
    }
    return min;
}

void moveghost4(struct pg* ghost4, struct pg* ghost1, struct pg* ghost2, struct pg* ghost3, struct pg* pacman, struct sll* pac_path, int cal_pacpath) {
    //ok
    struct square *next_sq = findConner(pacman);
    if (ghost4->isDead != 1) {
        if (pacman->state == 'p') {
            //if (sll_is_not_exist(pac_path, next_sq)) {
            //move
            //movetonode();
            //} else {
            char ran = randomDir2();
            struct square* g4_next;
            if (ran == 'u') {
                g4_next = nextup(ghost4->square_node);
                if (g4_next != next_sq) {
                    moveUp(ghost4, 'g');
                }
            }
            if (ran == 'd') {
                g4_next = nextdown(ghost4->square_node);
                if (g4_next != next_sq) {
                    moveDown(ghost4, 'g');
                }
            }
            if (ran == 'l') {
                g4_next = nextleft(ghost4->square_node);
                if (g4_next != next_sq) {
                    moveLeft(ghost4, 'g');
                }
            }
            if (ran == 'r') {
                g4_next = nextright(ghost4->square_node);
                if (g4_next != next_sq) {
                    moveRight(ghost4, 'g');
                }
            }
            //}
        }
    }
    if (pacman->state == 'n') {
        struct sll* path = sll_create(ghost4->square_node);
        int count_path = 0;
        //path
        if (sll_is_not_exist(pac_path, pacman->square_node) || cal_pacpath) {
            sll_free(path);
            path = sll_create(ghost4->square_node);
            //sll_free(pac_path);
            //pac_path = sll_create_null();
            find2(ghost4->square_node, next_sq, path, pac_path, count_path, ghost4, pacman);
        }
        //move
        if (pac_path != NULL) {
            struct square* g4_next = sll_take_last(pac_path);
            if (g4_next != NULL) {
                if (ghost4->square_node->up == g4_next) {
                    if (moveUp(ghost4, 'g') == 0) {
                        sll_free(path);
                        path = sll_create(ghost4->square_node);
                        find2(ghost4->square_node, next_sq, path, pac_path, count_path, ghost4, pacman);
                    }
                }
                if (ghost4->square_node->down == g4_next) {
                    if (moveDown(ghost4, 'g') == 0) {
                        sll_free(path);
                        path = sll_create(ghost4->square_node);
                        find2(ghost4->square_node, next_sq, path, pac_path, count_path, ghost4, pacman);
                    }
                }
                if (ghost4->square_node->left == g4_next) {
                    if (moveLeft(ghost4, 'g') == 0) {
                        sll_free(path);
                        path = sll_create(ghost4->square_node);
                        find2(ghost4->square_node, next_sq, path, pac_path, count_path, ghost4, pacman);
                    }
                }
                if (ghost4->square_node->right == g4_next) {
                    if (moveRight(ghost4, 'g') == 0) {
                        sll_free(path);
                        path = sll_create(ghost4->square_node);
                        find2(ghost4->square_node, next_sq, path, pac_path, count_path, ghost4, pacman);
                    }
                }

            }
        }
    }
}


