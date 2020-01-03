#include "words.h"

void reverse(const char * str1, char *str2) {
  int i = 0;
  char *str3 = (char *) str1;
  while (*str3 != '\0') {
    str3 += 1;
    i += 1;
  }
  str3 -= i;

  int j = 0;
  while (j < i/2) {
    str2[j] = str1[i - 1 - j];
    str2[i - 1 - j] = str1[j];
    j++;
  }
  if (i % 2 == 1) {
    str2[i/2] = str1[i/2];
  }
  str2[i] = '\0';
}

bool ispunctuation(char character) {
  return (character == '\'' or character == ',' or character == ' '
          or character == '.' or character == '!');
}

int compare(const char * one, const char *two) {
  int i = 0, j = 0;
  while (one[i] != '\0' and two[j] != '\0') {
    if (ispunctuation(one[i])) {
      i++;
    } else if (ispunctuation(two[j])) {
      j++;
    } else if (toupper(one[i]) != toupper(two[j])) {
      return 0;
    } else {
      i++;
      j++;
    }
  }

  while (ispunctuation(one[i])) {
    i++;
  }

  while (ispunctuation(two[j])) {
    j++;
  }

  return (one[i] == '\0' and two[j] == '\0');
}

int palindrome(const char *sentence) {
  int i = 0;

  while (sentence[i] != '\0') {
    ++i;
  }
  char *reversed = new char[i+1];
  reverse(sentence, reversed);

  int result = compare(sentence, reversed);
  delete [] reversed;

  return result;
}

int anagram(const char * str1, const char * str2) {
  map<char, int> mapping;
  char c = 'A';
  while (c <= 'Z') {
    pair<char, int> pair(c, 0);
    mapping.insert(pair);
    c++;
  }

  int i = 0;
  while(str1[i] != '\0') {
    if (ispunctuation(str1[i])) {
      i++;
      continue;
    }
    char c = toupper(str1[i]);
    mapping[c] += 1;
    i++;
  }

  i = 0;
  while(str2[i] != '\0') {
    if (ispunctuation(str2[i])) {
      i++;
      continue;
    }
    char c = toupper(str2[i]);
    mapping[c] -= 1;
    i++;
  }

  c = 'A';
  while (c <= 'Z') {
    if (mapping[c]) {
      return 0;
    }
    c++;
  }

  return 1;
}
