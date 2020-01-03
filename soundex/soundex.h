#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <iostream>
#include <cctype>

void encode(const char *surname, char soundex[5]);
int compare(const char *one, const char *two);
int count(const char *surname, const char *sentence);

#endif
