#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::set<std::string> words;
  rawWords = convToLower(rawWords);
  //if each side of punc is not 2+, drop that side
  string word = "";
  for (size_t i = 0; i < rawWords.size(); i++) {
    char a = rawWords[i]; //get char to add to the string
    if (isspace(a) || ispunct(a)) { //check if it's a separator
      if (word.size() > 1) { //if greater than 1
        words.insert(word); //add to set
        word = ""; //reset
      }
      //reset if not long enough
      else {
        word = "";
      }
    }
    else {
      //add to set and keep going
      word += a;
    }
  }

  if (word.size() > 1) {
    words.insert(word);
  }

  return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
