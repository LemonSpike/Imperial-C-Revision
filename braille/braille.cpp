#include "braille.h"

int encode_character(char ch, char *braille) {

  braille[0]='\0';
  int size = 0;

  if (isalpha(ch)) {
    if (isupper(ch)) {
      size += 6;
      strcpy(braille, ".....0");
    }

    size += 6;
    switch (toupper(ch)) {
    case 'A':
      strcat(braille, "0....."); return size;
    case 'B':
        strcat(braille, "00...."); return size;
    case 'C':
        strcat(braille, "0..0.."); return size;
    case 'D':
        strcat(braille,  "0..00."); return size;
    case 'E':
        strcat(braille, "0...0."); return size;
    case 'F':
        strcat(braille, "00.0.."); return size;
    case 'G':
        strcat(braille, "00.00."); return size;
   case 'H':
      strcat(braille, "00..0."); return size;
    case 'I':
      strcat(braille, ".0.0.."); return size;
    case 'J':
      strcat(braille, ".0.00."); return size;
    case 'K':
      strcat(braille, "0.0..."); return size;
    case 'L':
      strcat(braille, "000..."); return size;
    case 'M':
      strcat(braille, "0.00.."); return size;
    case 'N':
      strcat(braille, "0.000."); return size;
    case 'O':
      strcat(braille, "0.0.0."); return size;
    case 'P':
      strcat(braille, "0000.."); return size;
    case 'Q':
      strcat(braille, "00000."); return size;
    case 'R':
      strcat(braille, "000.0."); return size;
    case 'S':
      strcat(braille, ".000.."); return size;
    case 'T':
      strcat(braille, ".0000."); return size;
    case 'U':
      strcat(braille, "0.0..0"); return size;
    case 'V':
      strcat(braille, "000..0"); return size;
    case 'W':
      strcat(braille, ".0.000"); return size;
    case 'X':
      strcat(braille, "0.00.0"); return size;
    case 'Y':
      strcat(braille, "0.0000"); return size;
    case 'Z':
      strcat(braille, "0.0.00"); return size;
    default:
      strcat(braille, "......"); return size;
    }
  }

  if (ispunct(ch)) {
    size += 6;
    switch (ch) {
    case '.':
      strcpy(braille, ".0..00"); return size;
    case ',':
      strcpy(braille, ".0...."); return size;
    case ';':
      strcpy(braille, ".00..."); return size;
    case '-':
      strcpy(braille, "..0..0"); return size;
    case '!':
      strcpy(braille, ".00.0."); return size;
    case '?':
      strcpy(braille, ".00..0"); return size;
    case ')':
    case '(':
      strcpy(braille, ".00.00"); return size;
    default:
      strcpy(braille, "......"); return size;
    }
  }

  if (isdigit(ch)) {
    switch(ch) {
    case '1':
      strcpy(braille,"..00000....."); return 12;
    case '2':
      strcpy(braille,"..000000...."); return 12;
    case '3':
      strcpy(braille,"..00000..0.."); return 12;
    case '4':
      strcpy(braille,"..00000..00."); return 12;
    case '5':
      strcpy(braille,"..00000...0."); return 12;
    case '6':
      strcpy(braille,"..000000.0.."); return 12;
    case '7':
      strcpy(braille,"..000000.00."); return 12;
    case '8':
      strcpy(braille,"..000000..0."); return 12;
    case '9':
      strcpy(braille,"..0000.0.0.."); return 12;
    case '0':
      strcpy(braille,"..0000.0.00."); return 12;
    }
  }

  return -1;
}

void encode(const char *plaintext, char *braille) {
  if (plaintext[0] == '\0')
    return;
  int size = encode_character(plaintext[0], braille);
  encode(plaintext + 1, braille + size);
}

void print_braille(const char *braille, ostream &stream) {
  char encoded[100];
  encode(braille, encoded);

  int len;
  for (len = 0; encoded[len] != '\0'; len++);

  string line1;
  for (int i = 0; i < len; i += 3) {
    line1 += encoded[i];
  }

  string line2;
  for (int i = 1; i < len; i += 3) {
    line2 += encoded[i];
  }

  string line3;
  for (int i = 2; i < len; i += 3) {
    line3 += encoded[i];
  }

  stream << line1 << endl;

  stream << line2 << endl;

  stream << line3 << endl;

  for (int i = 0; braille[i]!='\0'; i++){
    if(isupper(braille[i]) ||
       isdigit(braille[i])){
      stream << "  ";
    }
    stream << " " << braille[i];
  }

  stream << endl;
}
