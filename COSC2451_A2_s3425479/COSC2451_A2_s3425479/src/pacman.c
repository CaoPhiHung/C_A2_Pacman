#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define NUM_ROW 20
#define NUM_COL 40
#define WIDTH 30
#define HEIGHT 10 
#define OPTION_WIDTH 20
#define OPTION_HEIGHT 7
#include "map.h"
#include "square.h"
#include "pg.h"
#include "move.h"
#include "sll.h"

// in the terminal configuration
#define COLOR_BACKGROUND 0
#define COLOR_WALL       7
#define COLOR_PACMAN     1
#define COLOR_GHOST1     2
#define COLOR_GHOST2     3
#define COLOR_GHOST3     6
#define COLOR_GHOST4     5


static void finish(int sig);
static void view_high_scores();
static void view_credits();
static void levels_editor();
static void start_game(int level);
char author[1000];
char level[500];
char player[500];
bool pause_game = FALSE;

//Map

struct pg *ghost1;
struct pg *ghost2;
struct pg *ghost3;
struct pg *ghost4;
int startx = 0;
int starty = 0;

char *choices[] = {
    "Start game",
    "High score",
    "Level editor",
    "Credit",
    "Exit",
};

char *levels[] = {
    "Level 1 (Easy)- Luan",
    "Level 2 (Medium)- Hung",
    "Level 3 (Medium)- Nguyen",
    "Level 4 (Hard)- Nhan",
    "Load Game",
    "Back to Menu",
};

char *options[] = {
    "Resume",
    "Save game",
    "Exit"
};

int n_choices = sizeof (choices) / sizeof (char *);
int n_levels = sizeof (levels) / sizeof (char *);
int n_options = sizeof (options) / sizeof (char *);

void printkey(int c) {
    //(void) nonl();
    if (c == '\n') {
        addch('\n');
    }
    if (c == 'q' || c == 'Q') {
        addch(ACS_ULCORNER);
    }
    if (c == 'e' || c == 'E') {
        addch(ACS_URCORNER);
    }
    if (c == 'c' || c == 'C') {
        addch(ACS_LRCORNER);
    }
    if (c == 'z' || c == 'Z') {
        addch(ACS_LLCORNER);
    }
    if (c == 'a' || c == 'd') {
        addch(ACS_VLINE);
    }
    if (c == 'w' || c == 'x') {
        addch(ACS_HLINE);
    }
    if (c == 's') {
        addch(ACS_BULLET);
    }
    if (c == 'g' || c == 'G') {
        addch(ACS_CKBOARD);
    }
    if (c == 'p' || c == 'P') {
        addch(ACS_DIAMOND);
    }
    if (c == 'f' || c == 'F') {
        addch(ACS_PI);
    }
    if (c == 'S') {
        addch(ACS_STERLING);
    }
    if (c == ' ') {
        addch(' ');
    }
    if (c == 'W') {
        addch(ACS_TTEE);
    }
    if (c == 'A') {
        addch(ACS_LTEE);
    }
    if (c == 'D') {
        addch(ACS_RTEE);
    }
    if (c == 'X') {
        addch(ACS_BTEE);
    }
}
//print from map to screen

void map_print(struct map *map, struct pg *ghost1, struct pg *ghost2, struct pg *ghost3, struct pg *ghost4, struct pg *pacman) {

    struct square *current_node = map->square_node;

    struct square *pivot = current_node;

    for (int i = 0; i < map->row; i++) {

        for (int j = 0; j < map->col; j++) {
            if (pacman -> state == 'p') {
                attrset(COLOR_PAIR(6));
                //wattron(stdscr,A_REVERSE);
            }
            //Test
            if (pivot->value == 'g' || pivot->value == 'G') {
                if (pivot == ghost1->square_node) {
                    attrset(COLOR_PAIR(2));
                    addch(ACS_PLMINUS);
                    pivot = pivot->right;
                    attrset(COLOR_PAIR(0));
                }
                if (pivot == ghost2->square_node) {
                    attrset(COLOR_PAIR(4));
                    addch(ACS_LARROW);
                    pivot = pivot->right;
                    attrset(COLOR_PAIR(0));
                }
                if (pivot == ghost3->square_node) {
                    attrset(COLOR_PAIR(5));
                    addch(ACS_RARROW);
                    pivot = pivot->right;
                    attrset(COLOR_PAIR(0));
                }
                if (pivot == ghost4->square_node) {
                    attrset(COLOR_PAIR(6));
                    addch(ACS_CKBOARD);
                    pivot = pivot->right;
                    attrset(COLOR_PAIR(0));
                }
            } else {
                printkey(pivot->value);
                pivot = pivot->right;
            }

        }
        printw("\n");
        current_node = current_node->down;
        pivot = current_node;
    }
}
//End map

void tokenize(const char* input, char** result, int * capacity) {
    char* str = strdup(input);
    int count = 0;
    char* tok = strtok(str, " ");
    while (1) {
        if (count >= (*capacity)) {
            (*capacity) = (*capacity) + 5;
            result = realloc(result, (*capacity) * sizeof (*result));
        }
        if (tok) {
            result[count++] = strdup(tok);
        } else {
            result[count++] = tok;
        }
        if (tok == NULL) {
            break;
        }
        tok = strtok(NULL, " ");
    }
}

void keypress(struct map* map, int c, int row, int col) {
    if (col == map->col - 1) {
        map_edit(map, row, col, c);
        printkey(c);
        move(row, col);
        wmove(stdscr, row, col);
        refresh();
    } else {
        map_edit(map, row, col, c);
        printkey(c);
        refresh();
    }
}

void keymove(struct map* map, int c, int row, int col) {
    if (c == KEY_RIGHT) {
        if (col + 1 < map->col) {
            move(row, col++);
            wmove(stdscr, row, col);
            refresh();
        }
    }
    if (c == KEY_DOWN) {
        if (row + 1 < map->row) {
            move(row++, col);
            wmove(stdscr, row, col);
            refresh();
        }
    }
    if (c == KEY_LEFT) {
        move(row, col--);
        wmove(stdscr, row, col);
        refresh();
    }

    if (c == KEY_UP) {
        move(row--, col);
        wmove(stdscr, row, col);
        refresh();
    }
}

char * ReadFromKeyboard(char *str, int *strm) {
    int strc = 0;

    nocbreak();
    echo();
    printw(":");
    for (;;) {
        //keypad(stdscr, FALSE);
        char c = getch();
        if (c == '\n') {
            str[strc] = '\0';
            break;
        }
        //Escape
        if (strc == (*strm) - 1) {
            (*strm) = (*strm) *2;
            str = realloc(str, (*strm) * sizeof (char));
        }
        str[strc] = c;
        strc++;
    }
    return str;
}

void print_menu(WINDOW *menu_win, int highlight, char menu) {
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    int count = 0;
    if (menu == 'y') {
        count = n_choices;
    } else if (menu == 'n') {
        count = n_levels;
    } else {
        count = n_options;
    }

    for (i = 0; i < count; ++i) {
        if (highlight == i + 1) /* High light the present choice */ {
            wattron(menu_win, A_REVERSE);
            if (menu == 'y') {
                mvwprintw(menu_win, y, x, "%s", choices[i]);
            } else if (menu == 'n') {
                mvwprintw(menu_win, y, x, "%s", levels[i]);
            } else {
                mvwprintw(menu_win, y, x, "%s", options[i]);
            }
            wattroff(menu_win, A_REVERSE);
        } else
            if (menu == 'y') {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        } else if (menu == 'n') {
            mvwprintw(menu_win, y, x, "%s", levels[i]);
        } else {
            mvwprintw(menu_win, y, x, "%s", options[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
    //hiding the cursor
    curs_set(0);
}

int main(int argc, char *argv[]) {
    (void) signal(SIGINT, finish); /* arrange interrupts to terminate */
    (void) initscr(); /* initialize the curses library */
    keypad(stdscr, TRUE); /* enable keyboard mapping */
    //(void) nonl(); /* tell curses not to do NL->CR/NL on output */
    (void) cbreak(); /* take input chars one at a time, no wait for \n */
    (void) noecho(); /* echo input - in color */


    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WALL, COLOR_BACKGROUND);
        init_pair(2, COLOR_PACMAN, COLOR_BACKGROUND);
        init_pair(3, COLOR_GHOST1, COLOR_BACKGROUND);
        init_pair(4, COLOR_GHOST2, COLOR_BACKGROUND);
        init_pair(5, COLOR_GHOST3, COLOR_BACKGROUND);
        init_pair(6, COLOR_GHOST4, COLOR_BACKGROUND);

    }
    int choice = 0;
    int highlight = 1;
    int k;

    while (choice != 5) {
        clear();
        int choice = 0;
        WINDOW *menu_win;
        startx = (80 - WIDTH) / 2;
        starty = (24 - HEIGHT) / 2;
        menu_win = newwin(HEIGHT, WIDTH, starty, startx);
        keypad(menu_win, TRUE);
        mvprintw(3, 35, "PACMAN");
        mvprintw(5, 25, "use arrow to move up and down");
        refresh();
        print_menu(menu_win, highlight, 'y');

        for (;;) {
            k = wgetch(menu_win);
            switch (k) {
                case KEY_UP:
                    if (highlight == 1)
                        highlight = n_choices;
                    else
                        --highlight;
                    break;
                case KEY_DOWN:
                    if (highlight == n_choices)
                        highlight = 1;
                    else
                        ++highlight;
                    break;
                case 10:
                    choice = highlight;
                    break;

            }
            print_menu(menu_win, highlight, 'y');
            if (choice != 0) /* User did a choice come out of the infinite loop */ {
                break;
            }
        }
        //struct map *map = create_map(NUM_ROW, NUM_COL);

        if (choice == 1) {
            clear();
            int level = 0;
            WINDOW *level_win;
            startx = (80 - WIDTH) / 2;
            starty = (24 - HEIGHT) / 2;
            level_win = newwin(HEIGHT, WIDTH, starty, startx);
            keypad(level_win, TRUE);
            mvprintw(3, 35, "PACMAN");
            mvprintw(5, 25, "use arrow to move up and down");
            refresh();
            // print the level screen
            print_menu(level_win, highlight, 'n');

            for (;;) {
                k = wgetch(level_win);
                switch (k) {
                    case KEY_UP:
                        if (highlight == 1)
                            highlight = n_levels;
                        else
                            --highlight;
                        break;
                    case KEY_DOWN:
                        if (highlight == n_levels)
                            highlight = 1;
                        else
                            ++highlight;
                        break;
                    case 10:
                        level = highlight;
                        break;

                }
                print_menu(level_win, highlight, 'n');
                if (level != 0) /* User did a choice come out of the infinite loop */ {
                    break;
                }
            }
            if (level == 6) {
                //do nothing. This will go back to the menu screen
            } else {
                //Start game
                start_game(level);
                //End game
            }
        }

        //high score
        if (choice == 2) {
            view_high_scores();
        }

        //level editor
        if (choice == 3) {
            levels_editor();
        }
        //credit
        if (choice == 4) {
            view_credits();
        }

        //exit
        if (choice == 5) {
            break;
        }
    }

    refresh();
    attrset(COLOR_PAIR(1));
    //map_free(map);
    finish(0); /* we're done */
}

void cheatCode() {
    clear();
    echo();
    nocbreak();
    //cheat mode
    printw("Cheat code\n");
    timeout(-1);
    int strm = 10;
    char *str = malloc(sizeof (char) * strm);
    str = ReadFromKeyboard(str, &strm);
    int capacity = 5;
    char **command = malloc(capacity * sizeof (*command));
    tokenize(str, command, &capacity);
    // e for escaping command mode and come back to edit mode and the previous working map will be printed.
    if (strcmp(command[0], "nhln1") == 0) {
        ghost1->isDead = 1;
        ghost2->isDead = 1;
        ghost3->isDead = 1;
        ghost4->isDead = 1;
    }
    free(str);

    cbreak();
    noecho();
    attrset(COLOR_PAIR(1));
}

void resumeSaveExit(struct map* map, bool pause_game) {
    int highlight = 1;
    int k;
    pause_game = TRUE;
    clear();
    int option = 0;
    WINDOW *option_win;
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;
    option_win = newwin(OPTION_HEIGHT, OPTION_WIDTH, starty, startx);
    keypad(option_win, TRUE);
    mvprintw(3, 35, "GAME PAUSE");
    mvprintw(5, 25, "use arrow to move up and down");
    refresh();
    // print the option screen
    print_menu(option_win, highlight, 'o');

    for (;;) {
        k = wgetch(option_win);
        switch (k) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_options;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_options)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                option = highlight;
                break;

        }
        print_menu(option_win, highlight, 'o');
        if (option != 0) /* User did a choice come out of the infinite loop */ {
            break;
        }
    }
    if (option == 1) {
        pause_game = FALSE;
    }
    if (option == 2) {
        map_write(map, 1);
        clear();
        mvprintw(3,25,"Game saves successfully");
        mvprintw(4,25,"Press any key to exit");
        timeout(-1);
        getch();
        finish(0);
    }
    if (option == 3) {
        finish(0);
    }

}

static void start_game(int level) {
    struct square *oldpac;
    struct square *oldghost1;
    struct square *oldghost2;
    struct square *oldghost3;
    struct square *oldghost4;
    struct map *map = create_map(NUM_ROW, NUM_COL);
    clear();
    ghost1 = create_pg("ghost1", ' ', 'n', 'g');
    ghost2 = create_pg("ghost2", ' ', 'n', 'g');
    ghost3 = create_pg("ghost3", ' ', 'n', 'g');
    ghost4 = create_pg("ghost4", ' ', 'n', 'g');
    struct pg *pacman = create_pg("pacman", ' ', 'n', 'p');
    //depend on the level that the user choose then draw the map

    if (level == 1) {
        map_read(map, "luan.pac", 0);
    } else if (level == 2) {
        map_read(map, "hung.pac", 0);
    } else if (level == 3) {
        map_read(map, "nguyen.pac", 0);
    } else if (level == 4) {
        map_read(map, "nhan.pac", 0);
    } else if (level == 5) {
        map_read(map, "save.pac", 1);
        pacman->score = map->score;
    }


    //boolean for ghost 3
    ghost3->sameColChase = false;

    oldpac = setpacman(map, pacman);
    oldghost1 = setGhost1(map, ghost1);
    oldghost2 = setGhost2(map, ghost2);
    oldghost3 = setGhost3(map, ghost3);
    oldghost4 = setGhost4(map, ghost4);
    //set ghost here
    map_print(map, ghost1, ghost2, ghost3, ghost4, pacman);
    struct sll* pac_path = sll_create_null();
    int cal_pac = 0;
    setAll(pacman, ghost1, ghost2, ghost3, ghost4);
    int giveLive = 1;
    int re_play = 1;
    for (;;) {
        mvprintw(0, 40, "Score: %d", map->score);
        mvprintw(1, 40, "Live: %d", pacman->live);
        /*
                mvprintw(1, 40, "Pacman: %d %d", pacman->x, pacman->y);
                mvprintw(2, 40, "Ghost1: %d %d", ghost1->x, ghost1->y);
                mvprintw(3, 40, "Ghost2: %d %d", ghost2->x, ghost2->y);
                mvprintw(4, 40, "Ghost3: %d %d", ghost3->x, ghost3->y);
         */
        mvprintw(5, 40, "Remain Pellet :%d", find_max_pellet(map));
        mvprintw(6, 40, "----------Option----------");
        mvprintw(7, 40, "Press: p to Pause the Game");
        mvprintw(8, 40, "--------------------------");
        //hiding the cursor
        curs_set(0);
        if (pacman->live != 0) {

            //setpacman(map, pacman);
            int key = getch();
            switch (key) {
                case KEY_UP:
                    pacman->direction = 'u';
                    break;
                case KEY_DOWN:
                    pacman->direction = 'd';
                    break;
                case KEY_LEFT:
                    pacman->direction = 'l';
                    break;
                case KEY_RIGHT:
                    pacman->direction = 'r';
                    break;
                    //pause game
                case 'p':
                    resumeSaveExit(map, pause_game);
                    break;
                case ':':
                    cheatCode();
                    break;
            }


            // eat power pellet or not
            if (pacman->state == 'n' && pause_game == FALSE) {
                movePacman(pacman, 'p');
                //Nguyen
                moveghost1(ghost1, pacman);
                //Hung				
                moveghost2(ghost2, pacman);
                //Luan				
                moveghost3(ghost3, pacman);
                //Nhan
                moveghost4(ghost4, ghost1, ghost2, ghost3, pacman, pac_path, cal_pac);
                cal_pac = 0;

                clear();
                map_print(map, ghost1, ghost2, ghost3, ghost4, pacman);
            }

            if (pacman->state == 'p') {
                time_t start, now;
                start = time(NULL);
                while (1) {
                    now = (time(NULL) - start) % 60;
                    mvprintw(0, 40, "Score: %d", pacman->score);
                    mvprintw(1, 40, "Live: %d", pacman->live);
                    mvprintw(2, 40, "Power end in %ds", 10 - now);
                    //setpacman(map, pacman);
                    int key = getch();
                    switch (key) {
                        case KEY_UP:
                            pacman->direction = 'u';
                            break;
                        case KEY_DOWN:
                            pacman->direction = 'd';
                            break;
                        case KEY_LEFT:
                            pacman->direction = 'l';
                            break;
                        case KEY_RIGHT:
                            pacman->direction = 'r';
                            break;
                        case 'e':
                            finish(0);
                            break;

                    }

                    movePacman(pacman, 'p');
                    //ghost behaviour when pacman eat power pellet 

                    moveghost1(ghost1, pacman);
                    moveghost2(ghost2, pacman);
                    moveghost3(ghost3, pacman);
                    moveghost4(ghost4, ghost1, ghost2, ghost3, pacman, pac_path, cal_pac);
                    cal_pac = 0;

                    clear();
                    map_print(map, ghost1, ghost2, ghost3, ghost4, pacman);

                    if (now == 10) {
                        pacman->state = 'n';
                        ghost1->isDead = 0;
                        ghost2->isDead = 0;
                        ghost3->isDead = 0;
                        ghost4->isDead = 0;
                        break;
                    }

                }
            }
            clear();
            map_print(map, ghost1, ghost2, ghost3, ghost4, pacman);
            map->score = pacman->score;

            // check pacman dead or alive 

            if (pacman->isDead) {
                pacman->live = pacman->live - 1;
                map->lives = pacman->live;
                pacman->isDead = 0;
                pacman->direction = ' ';
                mvprintw(12, 40, "Press any key for game resume");
                //pacman
                pacman->square_node->value = ' ';
                pacman->square_node = pacman->square_old;
                pacman->square_node->value = 'p';
                pacman->x = pacman->oldx;
                pacman->y = pacman->oldy;
                //setpacman(map, pacman);

                if (ghost1->temp == 'p') {
                    ghost1->temp = ' ';
                }
                if (ghost2->temp == 'p') {
                    ghost2->temp = ' ';
                }
                if (ghost3->temp == 'p') {
                    ghost3->temp = ' ';
                }
                if (ghost4->temp == 'p') {
                    ghost4->temp = ' ';
                }
                //ghost 1
                ghost1->square_node->value = ghost1->temp;
                ghost1->square_node = ghost1->square_old;
                ghost1->x = ghost1->oldx;
                ghost1->y = ghost1->oldy;
                //ghost 2
                ghost2->square_node->value = ghost2->temp;
                ghost2->square_node = ghost2->square_old;
                ghost2->x = ghost2->oldx;
                ghost2->y = ghost2->oldy;
                //ghost 3
                ghost3->square_node->value = ghost3->temp;
                ghost3->square_node = ghost3->square_old;
                ghost3->x = ghost3->oldx;
                ghost3->y = ghost3->oldy;


                //ghost 4
                ghost4->square_node->value = ghost4->temp;
                ghost4->square_node = ghost4->square_old;

                cal_pac = 1;
                ghost1->temp = ' ';
                ghost2->temp = ' ';
                ghost3->temp = ' ';
                ghost4->temp = ' ';

                timeout(-1);
                re_play = 0;
            }
            //test
            if (pacman->score > 200) {
                timeout(200);
                pacman->live += giveLive;
                giveLive = 0;
            }
            if (re_play) {
                if (pacman->score < 200) {
                    timeout(300);
                }
                if (pacman->score < 100) {
                    timeout(500);
                }
                if (pacman->score < 50) {
                    timeout(750);
                }
            } else {
                re_play = 1;
            }
            //done
        }

        //if pacman eat all pellet => win
        //if pacman has no live left => game over
        //ask for the name => write to the highscore file
        if (pacman->live == 0 || find_max_pellet(map) == 0) {
            clear();
            echo();
            timeout(-1);
            if (pacman->live == 0) {
                mvprintw(10, 20, "GAME OVER");
            }
            if (find_max_pellet(map) == 0) {
                mvprintw(10, 20, "YOU WIN");
            }
            int c = getch();
            FILE *fp;
            fp = fopen("levels/highscore.pac", "a");
            mvprintw(12, 20, "Score: %d \n", pacman->score);
            mvprintw(14, 20, "Enter your name: ");
            getstr(player);
            if (c == '\n') {
                fprintf(fp, "%s: %d \n", player, pacman->score);
                fclose(fp);
                break;
            }
        }
    }
}

static void levels_editor() {
    struct map *map = create_map(NUM_ROW, NUM_COL);
    int row, col;
    clear();
    (void) noecho();
    curs_set(1);
    for (;;) {
        getyx(stdscr, row, col);
        int c = getch();
        if (c == 'q' || c == 'Q' || c == 'e' || c == 'E' || c == 'c' || c == 'C' || c == 'z' || c == 'Z' || c == 'a' || c == 'd' || c == 'w' || c == 'x' || c == 's' || c == 'g' || c == 'G' || c == 'p' || c == 'P' || c == 'f' || c == 'F' || c == 'S' || c == 'W' || c == 'A' || c == 'D' || c == 'X' || c == ' ') {
            keypress(map, c, row, col);
        }
        if (c == KEY_RIGHT || c == KEY_LEFT || c == KEY_UP || c == KEY_DOWN) {
            keymove(map, c, row, col);
        }
        // command mode begins
        if (c == ':') {
            clear();
            //refresh();
            printw("Command mode\n");
            for (;;) {
                int strm = 10;
                char *str = malloc(sizeof (char) * strm);
                str = ReadFromKeyboard(str, &strm);
                int capacity = 5;
                char **command = malloc(capacity * sizeof (*command));
                tokenize(str, command, &capacity);
                if (command[0] == NULL) {
                    continue;
                }
                // e for escaping command mode and come back to edit mode and the previous working map will be printed.
                if (strcmp(command[0], "e") == 0) {
                    clear();
                    //map_print(map);
                    struct pg *pacman = create_pg("pac", ' ', 'A', 'r');
                    struct pg *ghost1 = create_pg("ghost1", ' ', 'A', 'r');
                    struct pg *ghost2 = create_pg("ghost2", ' ', 'A', 'r');
                    struct pg *ghost3 = create_pg("ghost3", ' ', 'A', 'r');
                    //Nhan
                    struct pg *ghost4 = create_pg("ghost4", ' ', 'A', 'r');
                    setGhost1(map, ghost1);
                    setGhost2(map, ghost2);
                    setGhost3(map, ghost3);
                    //Nhan
                    setGhost4(map, ghost4);
                    map_print(map, ghost1, ghost2, ghost3, ghost4, pacman);

                    map->row = NUM_ROW;
                    map->col = NUM_COL;
                    curs_set(1);
                    wmove(stdscr, 0, 0);
                    break;
                }
                if (strcmp(command[0], "q") == 0) {
                    map_free(map);
                    finish(0);
                }
                if (strcmp(command[0], "w") == 0) {
                    // save map for the first time with map file name.
                    if (command[1] != NULL) {
                        map->filename = command[1];
                        printw("Enter the author's name: ");
                        getstr(author);
                        map->author = author;
                        printw("Enter the level: ");
                        getstr(level);
                        map->level = level;

                    } //save map the second time or after map is created with 'n' command
                    if (command[1] == NULL && map->filename != NULL) {
                        if (map->author == NULL || map->level == NULL) {
                            printw("Enter the author's name: ");
                            getstr(author);
                            map->author = author;
                            printw("Enter the level: ");
                            getstr(level);
                            map->level = level;
                        }
                    }

                    map_write(map, 0);
                }
                if (strcmp(command[0], "wq") == 0) {
                    if (command[1] != NULL) {
                        map->filename = command[1];
                    }
                    map_write(map, 0);
                    map_free(map);
                    finish(0);
                }
                if (strcmp(command[0], "r") == 0) {
                    //clear();
                    if (command[1] != NULL) {
                        map_free(map);
                        map = create_map(NUM_ROW, NUM_COL);
                        if (fileExist(command[1])) {
                            map_read(map, command[1], 0);
                            //map_print(map);
                            map->filename = command[1];
                        } else {
                            printw("File does not exist\n");
                        }
                        //refresh();
                    } else {
                        printw("There is no filename!");
                    }
                }
                if (strcmp(command[0], "n") == 0) {
                    if (command[1] != NULL && command[2] != NULL && command[3] != NULL) {
                        // if the number of rows and cols smaller than 0 or greater than the default number of row and col,error  msg  					// for users
                        // will be printed
                        if (atoi(command[2]) <= 0 || atoi(command[3]) <= 0 || atoi(command[2]) > NUM_ROW || atoi(command[3]) > NUM_COL) {
                            printw("Invalid numbers\n");
                            continue;
                        } else {
                            map_free(map);
                            map = create_map(atoi(command[2]), atoi(command[3]));
                            map->filename = command[1];
                        }
                    }
                    //if the number of rows or columns are not specified by users, map will be created with the default number of rows and cols
                    if (command[1] != NULL && (command[2] == NULL || command[3] == NULL)) {
                        map_free(map);
                        map = create_map(NUM_ROW, NUM_COL);
                        map->filename = command[1];
                    }
                    clear();
                    break;
                }
                free(str);
            }

            cbreak();
            noecho();
        }

    }
    //end command mode
    attrset(COLOR_PAIR(1));

}

static void view_credits() {
    clear();
    FILE *ptr_file;
    char buf[1000];
    ptr_file = fopen("credit/credit.pac", "r");
    while (fgets(buf, 1000, ptr_file) != NULL) {
        printw(buf);
    }
    fclose(ptr_file);
    getch();
}

static void view_high_scores() {
    clear();
    FILE *ptr_file;
    char buf[1000];
    ptr_file = fopen("levels/highscore.pac", "r");
    while (fgets(buf, 1000, ptr_file) != NULL) {
        printw(buf);
    }
    fclose(ptr_file);
    getch();
}

static void finish(int sig) {
    endwin();
    exit(0);
}


