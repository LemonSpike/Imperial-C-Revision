#include "maze.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";
    for (int c=0; c<width; c++)
      cout << m[r][c];
    cout << endl;
  }
}

bool find_marker(char marker, char **maze, int height, int width, int &row,
                 int &column) {
  for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; ++c) {
      if (maze[r][c] == marker) {
        row = r;
        column = c;
        return true;
      }
    }
  }
  row = -1;
  column = -1;
  return false;
}

bool move(const char dir, int pos[2], char **maze, int height, int width) {
  int pos_orig[2] = { pos[0], pos[1] };
  switch (dir) {
  case 'W':
    pos[1] -= 1;
    break;
  case 'S':
    pos[0] += 1;
    break;
  case 'E':
    pos[1] += 1;
    break;
  case 'N':
    pos[0] -= 1;
    break;
  default:
    break;
  }
  if (position_invalid(pos, maze, height, width)) {
    pos[0] = pos_orig[0];
    pos[1] = pos_orig[1];
    return false;
  }
  return true;
}

bool position_invalid(int pos[2], char **maze, int height, int width) {
  if (pos[0] < 0 or pos[0] >= height)
    return true;
  if (pos[1] < 0 or pos[1] >= width)
    return true;
  if (maze[pos[0]][pos[1]] == '-')
    return true;
  if (maze[pos[0]][pos[1]] == '|')
    return true;
  if (maze[pos[0]][pos[1]] == '+')
    return true;
  if (maze[pos[0]][pos[1]] == 'U')
    return true;
  return false;
}

bool valid_solution(const char *path, char **maze, int height, int width) {
  int startR = -1, startC = -1;
  if (!find_marker('>', maze, height, width, startR, startC))
    return false;

  int endR = -1, endC = -1;
  if (!find_marker('X', maze, height, width, endR, endC))
    return false;

  int position[2] = { startR, startC };
  while (*path != '\0') {
    if (!move(*path, position, maze, height, width))
      return false;
    path++;
  }
  return ((position[0] == endR) and (position[1] == endC));
}

std::string find_path(char** maze, int height, int width, char start, char end) {
  int row, col;
  find_marker(start, maze, height, width, row, col);
  maze[row][col] = ' ';

  std::string path;
  if (!find_path(maze, height, width, row, col, end, path)) {
    path = "no solution";
  }
  return path;
}

bool find_path(char** maze, int height, int width, int row, int col, char end, std::string& path) {
  if (row < 0 || row >= height || col < 0 || col >= width) {
    return false;
  }
  if (maze[row][col] == end) {
    maze[row][col] = '#';
    return true;
  }
  if (maze[row][col] != ' ') {
    return false;
  }

  maze[row][col] = '#';

  // try north, south, east, west individually in series. if 1 succeeds, return with path
  if (find_path(maze, height, width, row-1, col, end, path)) {
    path += "N";
    return true;
  }
  if (find_path(maze, height, width, row+1, col, end, path)) {
    path += "S";
    return true;
  }
  if (find_path(maze, height, width, row, col+1, end, path)) {
    path += "E";
    return true;
  } 
  if (find_path(maze, height, width, row, col-1, end, path)) {
    path += "W";
    return true;
  }
  maze[row][col] = ' ';
  return false;
}
