#ifndef MAZE_H
#define MAZE_H

using namespace std;

class Maze
{
    public:
        Maze();

    int** generateMaze();

    int getHeight() { return HEIGHT; }
    int getWidth() { return WIDTH; }

    private:
        int HEIGHT;
        int WIDTH;

        int** maze;

        void recursion(int row, int column, int** maze);
};

#endif // MAZE_H
