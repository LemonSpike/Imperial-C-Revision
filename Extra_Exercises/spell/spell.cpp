# include "spell.h"

std::map<std::string, int> word_map;
std::map<std::vector<int>, int> e_distances;

int frequency(std::string target) {

  int count = word_map.count(target);
  if (count != 0) {
    return word_map[target];
  }

  std::ifstream in("words.dat");

  if (!in) {
    std::cout << "Opening target file words.dat failed." << std::endl;
    return -1;
  } else if (in.peek() == EOF) {
    std::cout << "Target words.dat file was empty." << std::endl;
    return -1;
  }

  int returned_count = 0;
  while (!in.eof()) {
    int count = 0;
    in >> count;
    if (!in.eof()) {
      std::string word;
      in >> word;
      word_map.insert(std::pair<std::string, int>(word, count));
      if (!std::strcmp((const char *)target.c_str(), word.c_str()))
        returned_count = count;
    } else
      break;
  }
  return returned_count;
}

int edit_distance(const char *from, const char *to) {
  e_distances.clear();

  int from_s = std::strlen(from);
  int to_s = std::strlen(to);

  return edit_helper(from, from_s, to, to_s, 20);
}

int edit_helper(const char *from, int fIndex, const char *to, int tIndex, int max) {
  std::vector<int> indices;
  indices.push_back(fIndex);
  indices.push_back(tIndex);

  if (e_distances.count(indices) != 0)
    return e_distances[indices];

  if (!std::min(fIndex, tIndex) || max < 0) {
    int value = std::max(fIndex, tIndex);
    e_distances.insert(std::pair<std::vector<int>, int>(indices, value));
    return value;
  }

  int dOne = edit_helper(from, fIndex-1, to, tIndex, max-1) + 1;
  int dTwo = edit_helper(from, fIndex, to, tIndex-1, max-1) + 1;
  int ind = (from[fIndex-1] == to[tIndex-1]) ? 0 : 1;
  int dThree = edit_helper(from, fIndex-1, to, tIndex-1, max-1) + ind;

  if (fIndex > 1 and tIndex > 1 and (from[fIndex-1] == to[tIndex-2])
      and (from[fIndex-2] == to[tIndex-1])) {
    int dFour = edit_helper(from, fIndex-2, to, tIndex-2, max-1) + 1;
    int eDist = std::min(std::min(dOne, dTwo), std::min(dThree, dFour));
    e_distances.insert(std::pair<std::vector<int>, int>(indices, eDist));
    return eDist;
  }

  int eDist = std::min(std::min(dOne, dTwo), dThree);
  e_distances.insert(std::pair<std::vector<int>, int>(indices, eDist));
  return eDist;
}

bool spell_correct(std::string word, char *fixed) {
  if (word_map.count(word) != 0) {
    std::strcpy(fixed, (const char *) word.c_str());
    return false;
  }

  int min_freq = 0;
  std::map<std::string, int>::iterator it;
  for (it = word_map.begin(); it != word_map.end(); it++) {
    std::string tempWord = it -> first;
    int freq = it -> second;
    if (edit_distance((const char *) tempWord.c_str(),
                      (const char *) word.c_str()) == 1 and
        freq > min_freq) {
      min_freq = freq;
      std::strcpy(fixed, (const char *) tempWord.c_str());
    }
  }
  if (min_freq) {
    return true;
  }

  for (it = word_map.begin(); it != word_map.end(); it++) {
    std::string tempWord = it -> first;
    int freq = it -> second;
    if (edit_distance((const char *) tempWord.c_str(),
                      (const char *) word.c_str()) == 2 and
        freq > min_freq) {
      min_freq = freq;
      std::strcpy(fixed, (const char *) tempWord.c_str());
    }
  }
  if (min_freq) {
    return true;
  } else {
    std::strcpy(fixed, (const char *) word.c_str());
    return false;
  }
}
