- How you decided to render the maze
I followed the depth first search implementation in the link included in the instructions paper to find a path from a start point in a 2 dimensional array. Then with the results i used 2 loops to go through the rows and columns of the 2D array to Draw cubes whenever it is equal to 1 (wall).

- Decisions and tradeoffs you made
Problem with the DFS algorithm i used is that it works best with an odd numbered Height and Width. So i had to make the maze 9x9 instead of 8x8. Otherwise the Maze will not look good around the sides. Because of how it checks whether the path is outside or not by increasing by 2 every time. (Did not try to change it)

- Describe any extra features you added and how to access them
I did not add any extra features
