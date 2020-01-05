#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <cstring>
#include <iostream>
#include <vector>
#include <cctype>
#include "constants.h"
using namespace std;

void prepare(const char *input, char *output);
void grid(const char *codeword, char square[][GRID_DIM]);
void bigram(char square[][GRID_DIM], char in1, char in2,
            char &out1, char &out2);
void encode(char square[][GRID_DIM], char *prepared, char *encoded);

#endif
