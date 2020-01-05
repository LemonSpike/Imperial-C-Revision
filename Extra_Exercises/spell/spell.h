# ifndef SPELL_H
# define SPELL_H

# include <iostream>
# include <fstream>
# include <map>
# include <vector>
# include <cstring>
# include <limits.h>

# define MAX_LENGTH 512

int frequency(std::string target);
int edit_distance(const char *from, const char *to);
int edit_helper(const char *from, int fIndex, const char *to, int tIndex,
                int max);
bool spell_correct(std::string word, char *fixed);

# endif
