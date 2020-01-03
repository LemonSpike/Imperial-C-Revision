#ifndef BRAILLE_H
#define BRAILLE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

int encode_character(char ch,char *braille);
void encode(const char *plaintext, char *braille);
void print_braille(const char *braille, ostream &stream);

#endif
