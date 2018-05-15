/*
The following line of code implements a Maze Solving Algorithm
in which we are using recursive backtracking to find a solution
to the a given maze. The correct solution part is given by *
and the path that was traversed but is not a solution path is
given by ~
*/


#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)     // function to create maze
{
    // Your code here. Make sure to replace following line with your own code.
    maze_t *struct_pointer = (maze_t *)malloc(sizeof(maze_t));  // allocating memory for the structure
    char c;
    FILE *infile;                        // infile is a pointer to the start of the file
    infile = fopen(fileName,"r") ;       // opening file as read only
    if(infile == NULL)                   // if file is not there / not exist
      return NULL;
    int height, width, i, j;             // declaring variables for struct height and width
    fscanf(infile, "%d %d", &height, &width);
    struct_pointer->height = height;     // assigning heigh and width to the structure
    struct_pointer->width = width;
    struct_pointer->cells = malloc(sizeof(char *) * height); // allocating memory space for the cells
    for(i=0;i<width;i++){                // creating a 2D Array by assigning each cell pointer to every column
      struct_pointer->cells[i] = malloc(sizeof(char)*width);
    }
    for(i=0;i<height;i++){
      for(j=0;j<width;j++){
        c = fgetc(infile);              // reading a character from the file
        if(c == '\n')
          c = fgetc(infile);
        struct_pointer->cells[i][j] = c; // assinging each cell in the array the respective character
        if(c == START){
          struct_pointer->startRow = i; // getting the posiiton of S
          struct_pointer->startColumn = j;
        }
        if(c == END){
          struct_pointer->endRow = i;  // getting the position of E
          struct_pointer->endColumn = j;
        }
      }
    }

    return struct_pointer;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for(i=0;i<maze->height;i++){
      free(maze->cells[i]);    // freeing memory associated/assigned to every column of structure
    }
    free(maze);                // freeing the memory associated with the structure
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int height = maze->height;     // getting the height of the maze
    int width = maze->width;       // getting the width of the maze
    int i,j;
    for(i=0;i<height;i++){         // traversing through every row and column of the maze
      for(j=0;j<width;j++){
        if(i == maze->startRow && j == maze->startColumn)
          printf("%c", START);     // printing out the maze on to the screen
        else
          printf("%c", maze->cells[i][j]);
      }
      printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    if(row<0 || col<0 || row>=maze->height || col>=maze->width)
      return 0;                                   // check if we are looking within the maze bounds
    if(col == maze->endColumn && row == maze->endRow)
      return 1;                                   // check if we have reached the END or not
    if(maze->cells[row][col] == WALL || maze->cells[row][col] == PATH || maze->cells[row][col] == VISITED)
      return 0;                                   // check if the cells are EMPTY or not
    maze->cells[row][col] = PATH;                 // considering that the current cell is a solution path
    if(solveMazeManhattanDFS(maze, col-1, row) == 1){
      return 1;                                   // looking for the left available empty cell
    }
    if(solveMazeManhattanDFS(maze, col, row+1) == 1){
      return 1;                                   // looking for the up available empty cell
    }
    if(solveMazeManhattanDFS(maze, col+1, row) == 1){
      return 1;                                   // looking for the right available empty cell
    }
    if(solveMazeManhattanDFS(maze, col, row-1) == 1){
      return 1;                                   // looking for the dowm available empty cell
    }
    maze->cells[row][col] = VISITED;              // if current cell is not a valid solution path, assign ~
    return 0;
}
