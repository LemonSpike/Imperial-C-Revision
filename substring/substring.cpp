#include "substring.h"

bool is_prefix(const char *argOne, const char *argTwo) {
  int i = 0;
  while (argOne[i] == argTwo[i] and argTwo[i] != '\0' and ++i);
  return (argOne[i] == '\0' ? true : false);
}

int substring_position(const char *argOne, const char *argTwo) {
  int start = 0;
  while (argTwo[start] != '\0') {
    const char *newArg = &argTwo[start];
    if (is_prefix(argOne, newArg))
      return start;
    start++;
  }
  return (!start ? 0 : -1);
}
