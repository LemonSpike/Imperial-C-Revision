#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "minesweeper.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load mine positions from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || buffer[n] == '*' || buffer[n] == ' ' || buffer[n] == '?' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << "|";
  for (int i=0; i<9; i++) 
    cout << ( (data[i]=='.') ? ' ' : data[i]);
  cout << "|" << endl;
}

/* pre-supplied function to display a minesweeper board */
void display_board(const char board[9][9]) {
  cout << "  ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r);
  cout <<  endl;
  cout << " +---------+" << endl;
  for (int r=0; r<9; r++) 
    print_row(board[r],r);
  cout << " +---------+" << endl;
}

/* pre-supplied function to initialise playing board */ 
void initialise_board(char board[9][9]) {
  for (int r=0; r<9; r++)
    for (int c=0; c<9; c++)
      board[r][c] = '?';
}

/* add your functions here */

bool is_complete(char mines[9][9], char revealed[9][9]) {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (revealed[i][j] == '?' and mines[i][j] != '*')
        return false;
    }
  }
  return true;
}

int count_mines(const char *pos, char mines[9][9]) {
  int row = pos[0] - 'A';
  int col = pos[1] - '1';

  vector<int> rows;
  if (row - 1 >= 0)
    rows.push_back(row - 1);
  rows.push_back(row);
  if (row + 1 <= 8)
    rows.push_back(row + 1);

  vector<int> cols;
  if (col - 1 >= 0)
    cols.push_back(col - 1);
  cols.push_back(col);
  if (col + 1 <= 8)
    cols.push_back(col + 1);

  int count = 0;
  for (unsigned int i = 0; i < rows.size(); i++) {
    for (unsigned int j = 0; j < cols.size(); ++j) {
      if (rows[i] == row and cols[j] == col)
        continue;
      if (mines[rows[i]][cols[j]] == '*')
        ++count;
    }
  }
  return count;
}

void make_recursive_moves(char revealed[9][9], char mines[9][9],
                          int row, int col) {
  vector<int> rows;
  if (row - 1 >= 0)
    rows.push_back(row - 1);
  rows.push_back(row);
  if (row + 1 <= 8)
    rows.push_back(row + 1);

  vector<int> cols;
  if (col - 1 >= 0)
    cols.push_back(col - 1);
  cols.push_back(col);
  if (col + 1 <= 8)
    cols.push_back(col + 1);

  for (unsigned int i = 0; i < rows.size(); i++) {
    for (unsigned int j = 0; j < cols.size(); ++j) {
      char move[3] = { rows[i] + 'A', cols[j] + '1', '\0' };
      make_move(move, mines, revealed);
    }
  }
}

MoveResult make_move(const char *pos, char mines[9][9], char revealed[9][9]) {
  if (strlen(pos) < 2)
    return INVALID_MOVE;
  if (pos[0] < 'A' or pos[0] > 'I')
    return INVALID_MOVE;
  if (pos[1] < '1' or pos[1] > '9')
    return INVALID_MOVE;
  if (strlen(pos) == 3 and pos[2] != '*')
    return INVALID_MOVE;

  int row = pos[0] - 'A';
  int col = pos[1] - '1';

  if (revealed[row][col] != '?')
    return REDUNDANT_MOVE;

  if (strlen(pos) == 3 and pos[2] == '*') {
    revealed[row][col] = '*';
    return VALID_MOVE;
  }

  if (mines[row][col] == '*')
    return BLOWN_UP;

  int count = count_mines(pos, mines);
  if (!count) {
    revealed[row][col] = ' ';
    make_recursive_moves(revealed, mines, row, col);
  } else {
    revealed[row][col] = count + '0';
  }

  if (is_complete(mines, revealed)) {
    return SOLVED_BOARD;
  } else {
    return VALID_MOVE;
  }
}

bool find_safe_move(char revealed[9][9], char move[4]) {
  for (int r = 0; r < 9; ++r) {
    for (int c = 0; c < 9; ++c) {
      
    }
  }
}
