#ifndef CORRECT_H
#define CORRECT_H

#include <iostream>
#include <cstring>
using namespace std;

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(const char *binary);
char text_to_binary(const char *str, char *binary);
char binary_to_text(const char *binary, char *str);
void add_error_correction(const char *data, char *corrected);
int decode(const char *received, char *decoded);
#endif
