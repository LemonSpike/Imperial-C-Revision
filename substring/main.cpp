#include "substring.h"

int main() {
  cout << (is_prefix("this", "thisisbdkansdjkansj") ? "True" : "False") << endl;
  cout << (is_prefix("this", "this") ? "True" : "False") << endl;

  cout << substring_position("this", "this is a simple exercise") << endl;
  cout << substring_position("is", "this is a simple exercise") << endl;
  cout << substring_position("is a", "this is a simple exercise") << endl;
  cout << substring_position("is an", "this is a simple exercise") << endl;
  cout << substring_position("exercise", "this is a simple exercise") << endl;
  cout << substring_position("simple exercise", "this is a simple") << endl;
  cout << substring_position("", "this is a simple exercise") << endl;
  cout << substring_position("", "") << endl;

  return 0;
}
