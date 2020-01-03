#include "soundex.h"

int main() {
  char soundex[5];
  encode("Jackson", soundex);
  std::cout << soundex << std::endl;
  encode("Washington", soundex);
  std::cout << soundex << std::endl;
  encode("Lee", soundex);
  std::cout << soundex << std::endl;

  int comp = compare("W252", "W252");
  std::cout << comp << std::endl;
  comp = compare("W252", "W250");
  std::cout << comp << std::endl;

  int counter = count("Leeson", "Linnings, Leasonne, Lesson and Lemon.");
  std::cout << counter << std::endl;
}
