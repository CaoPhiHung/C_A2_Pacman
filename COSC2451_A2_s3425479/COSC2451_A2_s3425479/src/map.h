#ifndef MAP
#define MAP
#include <stdlib.h>
#include <stdio.h>
struct map {
    char *author;
    char *level;
    char *filename;
    int row;
    int col;
    int lives;
	int score;
    struct square *square_node;
};
struct map *create_map(int row, int col);
/**
 * to put a character in a specific location on the map
 * @param map the struct map
 * @param row the number of row
 * @param col the number of cols
 * @param value the value that user puts in the map		 			
 */
void map_edit(struct map *map, int row, int col, char value);

/**
 * write the current map to text file
 * @param map the struct map		
 */
void map_write(struct map *map, int num);

/**
 * in order to free the map's collums
 * @param current_node type square		
 */
void free_col(struct square *current_node);

/**
 * in order to free the row's collums
 * @param current_node type square		
 */
void free_row(struct square *current_node);

/**
 * in order to free the map after done writng or reading
 * @param struct map		
 */
void map_free(struct map *map);

/** 
 * to read the map from the file and print to the terminal
 * @param struct map
 * @param filename type char 			
 */
void map_read(struct map *map, char *filename,int num);

/**
 * to identify if the file exists
 * @param char filename of the map user is looking for to read 
 */
int fileExist(char *filename);
#endif

