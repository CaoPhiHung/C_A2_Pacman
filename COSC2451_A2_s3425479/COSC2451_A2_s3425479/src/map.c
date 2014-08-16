#include <stdlib.h>
#include "map.h"
#include "square.h"
#include <stdio.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

struct map *create_map(int inrow, int incol) {
    struct map *map_node = malloc(sizeof (struct map));
    map_node->row = inrow;
    map_node->col = incol;
    map_node->square_node = create_square_NULL();
	map_node->lives = 3;
	map_node->score = 0;

    //Create map with given row and col
    //First col
    for (int j = 1; j < inrow; j++) {
        struct square *temp_row_square = create_square_NULL();
        insert_down(map_node->square_node, temp_row_square);
    }

    //Second col to the rest
    for (int i = 1; i < incol; i++) {
        struct square *temp_col_square = create_square_NULL();
        for (int j = 1; j < inrow; j++) {
            struct square *temp_row_square = create_square_NULL();
            insert_down(temp_col_square, temp_row_square);
        }
        insert_right(map_node->square_node, temp_col_square);
    }

    //Link second row to the rest
    struct square *current_row = map_node->square_node;
    struct square *current_col = map_node->square_node->right;
    struct square *temp_row = current_row;
    struct square *temp_col = current_col;

    for (int j = 1; j < inrow; j++) {
        current_col = map_node->square_node->right;
        temp_col = current_col;
        current_row = current_row->down;
        temp_row = current_row;
        for (int i = 1; i < incol; i++) {
            for (int z = 0; z < j; z++) {
                temp_col = temp_col->down;
            }
            temp_row->right = temp_col;
            temp_col->left = temp_row;
            temp_row = temp_row->right;
            current_col = current_col->right;
            temp_col = current_col;
        }

    }
    return map_node;
}

void map_edit(struct map *map, int row, int col, char value) {
    struct square *current_node = map->square_node;
    for (int i = 0; i < row; i++) {
        current_node = current_node->down;
    }
    for (int j = 0; j < col; j++) {
        current_node = current_node->right;
    }
    current_node->value = value;
}

int fileExist(char *filename) {
    struct stat buffer;
    char filePath[1024] = "levels/";
    strcat(filePath, filename);
    return (stat(filePath, &buffer) == 0);
}

void map_write(struct map *map,int num) {
    int actualRow = 0;
    int actualCol = 0;
    int tempcol = 1;
    int temprow = 1;

    char filePath[1024] = "levels/";
    struct square *current_node = map->square_node;
    struct square *pivot = current_node;
    struct square *rpivot = current_node;
    FILE *fp;
	
	if(num == 1){
		map->filename = "save.pac";
	}
	
    if (map->filename == NULL) {
        printw("Please define filename!\n");
    } else {
        strcat(filePath, map->filename);
        fp = fopen(filePath, "w");
        fprintf(fp, "%s\n", map->author);
        fprintf(fp, "%s\n", map->level);

        pivot = rpivot;
        while (rpivot->down != NULL) {
            tempcol = 1;
            rpivot = rpivot->down;
            temprow++;
            pivot = rpivot;
            while (pivot->right != NULL) {
                pivot = pivot->right;
                tempcol++;
                if ((tempcol > actualCol)&&(pivot->value != ' ')) {
                    actualCol = tempcol;
                }
                if ((temprow > actualRow)&&(pivot->value != ' ')) {
                    actualRow = temprow;
                }
            }


        }

        map->row = actualRow;
        map->col = actualCol;
		
		if(num == 1){
			fprintf(fp, "%d\n", map->row);
        	fprintf(fp, "%d\n", map->col);
			fprintf(fp, "%d\n", map->score);
        	fprintf(fp, "%d\n", map->lives);
        }else{
        	fprintf(fp, "%d\n", map->row);
        	fprintf(fp, "%d\n", map->col);
        }
        pivot = current_node;

        for (int i = 0; i < map->row; i++) {
            for (int j = 0; j < map->col; j++) {
                if (pivot->value != ' ' && pivot->value != '\n') {
                    fprintf(fp, "%c", pivot->value);
                } else {
                    fprintf(fp, " ");
                }
                pivot = pivot->right;
            }
            fprintf(fp, "\n");
            current_node = current_node->down;
            pivot = current_node;
        }
        fprintf(fp, "\n");
        fclose(fp);
    }
}

char* map_read_string(FILE * fo, char* str, int* cap) {
    char c;
    int c_count = 0;
    c = fgetc(fo);
    while (c != '\n') {
        *(str + c_count) = c;
        c_count++;
        if (c_count == (*cap) - 1) {
            (*cap) = (*cap) * 2;
            str = realloc(str, (*cap) * sizeof (char));
        }
        c = fgetc(fo);
    }
    *(str + c_count) = '\0';
    return strdup(str);
}

void map_read(struct map *map, char *filename,int num) {
    FILE *fo;
    char ch[8];
    char filePath[1024] = "levels/";
    char c;
    int cap = 100;

    strcat(filePath, filename);
    fo = fopen(filePath, "r");
    char *str = malloc(sizeof (char)* (cap));
    map->author = map_read_string(fo, str, &cap);
    free(str);
    str = malloc(sizeof (char)* (cap));
    map->level = map_read_string(fo, str, &cap);
    free(str);
    map->row = atoi(fgets(ch, 1000, fo));
    map->col = atoi(fgets(ch, 1000, fo));
    if(num == 1){
    map->score = atoi(fgets(ch, 1000, fo));
    map->lives = atoi(fgets(ch, 1000, fo));
    }
    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < map->col + 1; j++) {
            c = fgetc(fo);
            if (c != EOF && c != '\n') {
                map_edit(map, i, j, c);
            }
        }
    }
    fclose(fo);

}

void free_col(struct square *current_node) {
    if (current_node->down != NULL) {
        free_col(current_node->down);
    }
    square_free(current_node);
}

void free_row(struct square *current_node) {
    if (current_node->right != NULL) {
        free_row(current_node->right);
    }
    free_col(current_node);
}

void map_free(struct map *map) {
    free_row(map->square_node);
    free(map);
}


