#include "playfair.h"

void prepare(const char *input, char *output) {
  int i = 0, j = 0;
  while (input[i] != '\0') {
    if (isalnum(input[i])) {
      output[j++] = toupper(input[i]);
    }
    i++;
  }
  if (j % 2 == 1)
    output[j++] = 'X';
  output[j] = '\0';
}

bool removeFrom(vector<char> &chars, char c) {
  vector<char>::iterator it;
  int i = 0;
  for (it = chars.begin(); it != chars.end(); it++) {
    if (*it == c) {
      chars.erase(chars.begin() + i);
      return true;
    }
    i++;
  }
  return false;
}

char getChar(vector<char> &chars, const char *codeword, int &i) {
  while (codeword[i] != '\0') {
    if (removeFrom(chars, codeword[i])) {
      return codeword[i++];
    }
    i++;
  }
  char res = chars.back();
  chars.pop_back();
  return res;
}

void grid(const char *codeword, char square[][GRID_DIM]) {
  vector<char> chars;
  for (char c = '9'; c >= '0'; c--) {
    chars.push_back(c);
  }
  for (char c = 'Z'; c >= 'A'; --c) {
    chars.push_back(c);
  }

  int i = 0;
  for (int row = 0; row < GRID_DIM; row++) {
    for (int col = 0; col < GRID_DIM; col++) {
      square[row][col] = getChar(chars, codeword, i);
    }
  }
}

void bigram(char square[][GRID_DIM], char in1, char in2, char &out1, char &out2)
{
  int r1 = -1, c1 = -1, r2 = -1, c2 = -1;
  for (int r = 0; r < GRID_DIM; ++r) {
    for (int c = 0; c < GRID_DIM; ++c) {
      if (square[r][c] == in1) {
        r1 = r;
        c1 = c;
      } else if (square[r][c] == in2) {
        r2 = r;
        c2 = c;
      }
    }
  }
  out1 = square[r1][c2];
  out2 = square[r2][c1];
}

void encode(char square[][GRID_DIM], char *prepared, char *encoded) {
  if (*prepared == '\0')
    return;
  bigram(square, *prepared, *(prepared+1), *encoded, *(encoded+1));
  encode(square, prepared+2, encoded+2);
}
