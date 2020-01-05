#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */

bool valid_step(const char *current_word, const char *next_word) {
  if (!dictionary_search(next_word))
    return false;
  int i = 0;
  bool letterHasChanged = false;
  while (current_word[i] != '\0') {
    if (current_word[i] != next_word[i] and letterHasChanged)
      return false;
    else if (current_word[i] != next_word[i])
      letterHasChanged = true;
    ++i;
  }
  return letterHasChanged;
}

void convertUpper(char *word) {
  while (*word != '\0') {
    *word = toupper(*word);
    word++;
  }
}

void convertLower(char *word) {
  while (*word != '\0') {
    *word = tolower(*word);
    word++;
  }
}

bool display_chain(const char *chain[], ostream &output_stream) {
  int i = 0;
  while (chain[i] != NULL) {
    if (output_stream.fail())
      return false;
    char word[100];
    strcpy(word, chain[i++]);
    if (!(i-1) or (chain[i] == NULL)) {
      convertUpper(word);
    } else {
      convertLower(word);
    }
    output_stream << word << endl;
  }
  return chain[i] == NULL;
}

bool valid_chain(const char *chain[]) {
  int i = 0;
  while (chain[i] != NULL and chain[i+1] != NULL) {
    char word[100];
    strcpy(word, chain[i++]);
    convertUpper(word);

    char wordTwo[100];
    strcpy(wordTwo, chain[i++]);
    convertUpper(wordTwo);

    if (!valid_step(word, wordTwo)) {
      return false;
    }
  }
  return true;
}

bool swap_letter(char *start_word, int index, char replacement) {
  char next[100];
  strcpy(next, start_word);
  next[index] = replacement;
  if (valid_step((const char *) start_word, (const char *) next)) {
    start_word[index] = replacement;
    return true;
  } else {
    return false;
  }
}

void add_to_chain(char *start, const char **answer_chain, int index) {
  answer_chain[index] = start;
  answer_chain[index + 1] = NULL;
}

bool find_chain(const char *start_word, const char *target_word,
                const char **answer_chain, int max_steps, int index) {
  if (index == 0) {
    char *first_word = new char[strlen(start_word)];
    strcpy(first_word, start_word);
    answer_chain[0] = first_word;
    answer_chain[1] = NULL;
  }

  if (max_steps < 0) {
    return false;
  }

  if (!strcmp(start_word, target_word)) {
      return true;
  }

  char *start = new char[strlen(start_word)];
  strcpy(start, start_word);
  for (size_t i = 0; i < strlen(start); ++i) {
    char temp = start[i];
    for (char c = 'A'; c < 'Z'; ++c) {
      if (!swap_letter(start, i, c)) {
        continue;
      }
      add_to_chain(start, answer_chain, index + 1);
      if (find_chain(start, target_word, answer_chain,
                     max_steps - 1, index + 1))
        return true;
    }
    start[i] = temp;
    answer_chain[index + 1] = NULL;
  }
  delete [] start;
  return false;
}
