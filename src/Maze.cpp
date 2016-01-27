#include "Maze.h"

#include <cstdlib>
#include <algorithm>
#include <ctime>

Maze::Maze() {
    /* Initialize height and width */
    HEIGHT = 9;
    WIDTH = 9;
}

void Maze::recursion(int row, int column, int** maze) {
    /* 4 random directions */
    int* randDirections = new int[4];

    /* Initialize with 1-4 */
    for(int i = 0; i < 4; i++) {
        randDirections[i] = i + 1;
    }

    /* Shuffle */
    random_shuffle(&randDirections[0], &randDirections[3]);

    /* Examine each direction */
    for(int i = 0; i < sizeof(randDirections); i++) {
        switch(randDirections[i]) {
            /* Up */
            case 1:
                /* Whether 2 cells up is out or not */
                if(row - 2 <= 0)
                    continue;
                if(maze[row - 2][column] != 0) {
                    maze[row - 2][column] = 0;
                    maze[row - 1][column] = 0;
                    recursion(row - 2, column, maze);
                }
                break;
            /* Right */
            case 2:
                /* Whether 2 cells right is out or not */
                if(column + 2 >= WIDTH - 1)
                    continue;
                if(maze[row][column + 2] != 0) {
                    maze[row][column + 2] = 0;
                    maze[row][column + 1] = 0;
                    recursion(row, column + 2, maze);
                }
                break;
            /* Down */
            case 3:
                /* Whether 2 cells down is out or not */
                if(row + 2 >= HEIGHT - 1)
                    continue;
                if(maze[row + 2][column] != 0) {
                    maze[row + 2][column] = 0;
                    maze[row + 1][column] = 0;
                    recursion(row + 2, column, maze);
                }
                break;
            /* Left */
            case 4:
                /* Whether 2 cells up is out or not */
                if(column - 2 <= 0)
                    continue;
                if(maze[row][column - 2] != 0) {
                    maze[row][column - 2] = 0;
                    maze[row][column - 1] = 0;
                    recursion(row, column - 2, maze);
                }
                break;
        }
    }
}

int** Maze::generateMaze() {
    /* Time for randomizer */
    srand(time(0));

    /* Maze and Random*/
    int** maze = new int*[HEIGHT];

    /* Initialize the Maze */
    for(int h = 0; h < HEIGHT; h++) {
        maze[h] = new int[WIDTH];
        for(int w = 0; w < WIDTH; w++) {
            maze[h][w] = 1;
        }
    }

    /* Generate random row */
    int row = rand() % HEIGHT;
    while(row % 2 == 0) {
        row = rand() % HEIGHT;
    }

    /* Generate random column */
    int column = rand() % WIDTH;
    while(column % 2 == 0) {
        column = rand() % WIDTH;
    }

    /* Starting cell */
    maze[row][column] = 0;

    /* Allocate the maze recursively */
    recursion(row, column, maze);

    return maze;
}
