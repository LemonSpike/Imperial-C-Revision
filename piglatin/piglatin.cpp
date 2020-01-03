#include "piglatin.h"

int findFirstVowel(const char *word) {

  int i = 0;
  while (word[i] != '\0') {
    switch (word[i]) {
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'i':
    case 'I':
    case 'o':
    case 'O':
    case 'u':
    case 'U':
      return i;
    case 'y':
    case 'Y':
      if (i == 0 or word[i+1] == '\0') {
        i++;
        continue;
      } else
        return i;
    }
    ++i;
  }
  return -1;
}

void translateWord(const char *english, char *piglatin) {

  int i = 0;
  while (piglatin[i] != '\0') {
    piglatin[i] = '\0';
    i++;
  }

  int first = findFirstVowel(english);
  if (first == 0) {
    int i = 0;
    while (english[i] != '\0') {
      piglatin[i] = english[i];
      ++i;
    }
    piglatin[i] = 'w';
    piglatin[i+1] = 'a';
    piglatin[i+2] = 'y';
    piglatin[i+3] = '\0';
    return;
  }

  if (first == -1) {
    int i = 0;
    while (english[i] != '\0') {
      piglatin[i] = english[i];
      ++i;
    }
    piglatin[i] = 'a';
    piglatin[i+1] = 'y';
    piglatin[i+2] = '\0';
    return;
  }

  if (isdigit(english[0])) {
    int i = 0;
    while (english[i] != '\0') {
      piglatin[i] = english[i];
      ++i;
    }
    piglatin[i] = '\0';
    return;
  }

  if (first != 0) {
    char front[first];
    strncpy(front, english, first);
    bool upper = false;
    if (isupper(front[0])) {
      front[0] = tolower(front[0]);
      upper = true;
    }

    int i = first;
    while (english[i] != '\0') {
      piglatin[i - first] = english[i];
      i++;
    }
    strcat(piglatin, front);
    strcat(piglatin, "ay");
    if (upper)
      piglatin[0] = toupper(piglatin[0]);
    return;
  }
}

void translateStream(istream &inputStream, ostream &outputStream) {
  char word[64], translated[64];

  inputStream.getline(word, 64, ' ');

  if (inputStream.fail())
    return;

  else {
    translateWord(word, translated);
    outputStream << translated << " ";
    translateStream(inputStream, outputStream);
    return;
  }
}
