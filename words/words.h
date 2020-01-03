#ifndef WORDS_H
#define WORDS_H

#include <iostream>
#include <cctype>
#include <map>
using namespace std;

void reverse(const char *str1, char *str2);
int compare(const char *one, const char *two);
int palindrome(const char *sentence);
int anagram(const char *str1, const char *str2);

#endif
