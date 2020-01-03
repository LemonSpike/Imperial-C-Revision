#include "soundex.h"

void encode(const char *surname, char soundex[5]) {
  int i = 0;
  int j = 0;

  while (surname[i] != '\0') {
    if (!i) {
      soundex[j++] = surname[i++];
      continue;
    }
    switch (surname[i]) {
    case 'b':
    case 'f':
    case 'p':
    case 'v':
      if (++i and soundex[j-1] == '1') {
        continue;
      }
      soundex[j++] = '1';
      continue;
    case 'c':
    case 'g':
    case 'j':
    case 'k':
    case 'q':
    case 's':
    case 'x':
    case 'z':
      if (++i and soundex[j-1] == '2') {
        continue;
      }
      soundex[j++] = '2';
      continue;
    case 'd':
    case 't':
      if (++i and soundex[j-1] == '3') {
        continue;
      }
      soundex[j++] = '3';
      continue;
    case 'l':
      if (++i and soundex[j-1] == '4') {
        continue;
      }
      soundex[j++] = '4';
      continue;
    case 'm':
    case 'n':
      if (++i and soundex[j-1] == '5') {
        continue;
      }
      soundex[j++] = '5';
      continue;
    case 'r':
      if (++i and soundex[j-1] == '6') {
        continue;
      }
      soundex[j++] = '6';
      continue;
    default:
      ++i;
    }
  }

  while (j < 4) {
    soundex[j++] = '0';
  }
  soundex[4] = '\0';
}

int compare(const char *one, const char *two) {
  if (one[0] == '\0' and two[0] == '\0')
    return 1;
  if (one[0] != two[0])
    return 0;
  else
    return compare(one+1, two+1);
}

int count(const char *surname, const char *sentence) {
  int start = 0;
  int i = 0;
  int count = 0;

  while (sentence[i] != '\0') {
    while (sentence[start] != '\0' and !isalpha(sentence[start]))
      start++;

    i = start;
    while (sentence[i] != '\0' and isalpha(sentence[i]))
      i++;

    if (i == start) {
      continue;
    }

    char *word = new char[i - start];

    for (int j = start; j < i; j++) {
      word[j - start] = sentence[j];
    }
    start = i;

    char sound[5];
    char name_sound[5];
    encode(word, sound);
    encode(surname, name_sound);
    if (compare(name_sound, sound))
      count++;

    delete [] word;
  }
  return count;
}
