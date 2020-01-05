#include "spell.h"

int main() {

  std::cout << "====================== Question 1 ======================" << std::endl << std::endl;

  std::cout << "The frequency of the word 'a' in the corpus is " << frequency("a") << std::endl;
  
  std::cout << "The frequency of the word 'the' in the corpus is " << frequency("the") << std::endl;

  std::cout << "The frequency of the word 'bicycle' in the corpus is " << frequency("bicycle") << std::endl;

  std::cout << "The frequency of the word 'quintessential' in the corpus is " << frequency("quintessential") << std::endl;

  std::cout << "The frequency of the word 'nonexistential' is " << frequency("nonexistential") << std::endl;

  std::cout << std::endl;

  std::cout << "====================== Question 2 ======================" << std::endl << std::endl;

  std::cout << "The edit distance between 'an' and 'na' is " << edit_distance("an","na") << std::endl;

  std::cout << "The edit distance between 'spelling' and 'spelling' is " << edit_distance("spelling","spelling") << std::endl;
  
  std::cout << "The edit distance between 'speling' and 'spelling' is " << edit_distance("speling","spelling") << std::endl;

    std::cout << "The edit distance between 'speling' and 'a' is " << edit_distance("speling","a") << std::endl;
  
  std::cout << "The edit distance between 'peotryy' and 'poetry' is " << edit_distance("peotryy","poetry") << std::endl;

  std::cout << "The edit distance between 'korrectud' and 'corrected' is " << edit_distance("korrectud","corrected") << std::endl;

  std::cout << "The edit distance between 'nonexistential' and 'nonexistent' is " << edit_distance("nonexistential","nonexistent") << std::endl;

  std::cout << std::endl;

  std::cout << "====================== Question 3 ======================" << std::endl << std::endl;

  char fixed[MAX_LENGTH];

  bool corrected = spell_correct("poetry", fixed);
  std::cout << "The corrected spelling of 'poetry' is '"<< fixed << "'" << std::endl;
  std::cout << "The spell checker was " << (corrected ? "" : "NOT ") << "needed."<< std::endl <<std::endl;
  
  corrected = spell_correct("thay", fixed);
  std::cout << "The corrected spelling of 'thay' is '"<< fixed << "'" << std::endl;
  std::cout << "The spell checker was " << (corrected ? "" : "NOT ") << "needed."<< std::endl <<std::endl;

  corrected = spell_correct("korrectud", fixed);
  std::cout << "The corrected spelling of 'korrectud' is '"<< fixed << "'" << std::endl;
  std::cout << "The spell checker was " << (corrected ? "" : "NOT ") << "needed."<< std::endl <<std::endl;

  corrected = spell_correct("nonexistential", fixed);
  std::cout << "The corrected spelling of 'nonexistential' is '"<< fixed << "'" << std::endl;
  std::cout << "The spell checker was " << (corrected ? "" : "NOT ") << "needed."<< std::endl <<std::endl;

  /*  
  std::cout << "=================== Bonus Question =====================" << std::endl << std::endl;
  std::cout << "The edit distance between 'an' and 'na' is " << edit_distance_bonus("an","na") << std::endl;

  std::cout << "The edit distance between 'spelling' and 'spelling' is " << edit_distance_bonus("spelling","spelling") << std::endl;
  
  std::cout << "The edit distance between 'speling' and 'spelling' is " << edit_distance_bonus("speling","spelling") << std::endl;

    std::cout << "The edit distance between 'speling' and 'a' is " << edit_distance_bonus("speling","a") << std::endl;

  std::cout << "The edit distance between 'peotryy' and 'poetry' is " << edit_distance_bonus("peotryy","poetry") << std::endl;

  std::cout << "The edit distance between 'korrectud' and 'corrected' is " << edit_distance_bonus("korrectud","corrected") << std::endl;

  std::cout << "The edit distance between 'nonexistential' and 'nonexistent' is " << edit_distance_bonus("nonexistential","nonexistent") << std::endl;

  */
  return 0;
}
