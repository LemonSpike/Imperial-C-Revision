#include <iostream>

using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */
void text_to_binary(const char *str, char *binary) {
  int i = 0;
  while (str[i] != '\0') {
    ascii_to_binary(str[i++], binary);
    binary += 8;
  }
}

void binary_to_text(const char *binary, char *str) {
  if (*binary == '\0') {
    strcpy(str, binary);
    return;
  }
  char chPointer = binary_to_ascii(binary);
  strcpy(str, &chPointer);
  binary_to_text(binary + 8, str + 1);
}

void add_error_correction(const char *data, char *corrected) {
  char *initial = corrected;
  while (*corrected != '\0') {
    *corrected = '\0';
    corrected++;
  }
  corrected = initial;
  while (*data != '\0') {
    int d1 = data[0] - 48;
    data++;
    int d2 = data[0] - 48;
    data++;
    int d3 = data[0] - 48;
    data++;
    int d4 = data[0] - 48;
    data++;

    char c1 = ((d1 + d2 + d4) % 2) + 48;
    char c2 = ((d1 + d3 + d4) % 2) + 48;
    char c3 = ((d2 + d3 + d4) % 2) + 48;

    char section[8] = {c1, c2, d1 + 48, c3, d2 + 48, d3 + 48, d4 + 48, '\0' };
    strcat(corrected, section);
    corrected += 7;
  }
}

int decode(const char *received, char *decoded) {
  char *initial = decoded;
  while (*decoded != '\0') {
    *decoded = '\0';
    decoded++;
  }
  decoded = initial;
  int count = 0;
  while (*received != '\0') {
    int b1 = received[0] - 48;
    received++;
    int b2 = received[0] - 48;
    received++;
    int b3 = received[0] - 48;
    received++;
    int b4 = received[0] - 48;
    received++;
    int b5 = received[0] - 48;
    received++;
    int b6 = received[0] - 48;
    received++;
    int b7 = received[0] - 48;
    received++;

    char p1 = ((b4 + b5 + b6 + b7) % 2) + 48;
    char p2 = ((b2 + b3 + b6 + b7) % 2) + 48;
    char p3 = ((b1 + b3 + b5 + b7) % 2) + 48;

    if (p1 == '0' and p2 == '0' and p3 == '0') {
      char section[5] = { b3 + 48, b5 + 48, b6 + 48, b7 + 48, '\0' };
      strcat(decoded, section);
    } else {
      int position = 4*(p1-'0') + 2*(p2-'0') + (p3-'0');
      switch (position) {
      case 3:
        b3 = (b3 == 0) ? 1 : 0; break;
      case 5:
        b5 = (b5 == 0) ? 1 : 0; break;
      case 6:
        b6 = (b6 == 0) ? 1 : 0; break;
      case 7:
        b7 = (b7 == 0) ? 1 : 0; break;
      default:
        break;
      }
      ++count;
      char section[5] = { b3 + 48, b5 + 48, b6 + 48, b7 + 48, '\0' };
      strcat(decoded, section);
    }
    decoded += 4;
  }
  return count;
}
