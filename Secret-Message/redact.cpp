#include "redact.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

string redact_all_chars(string const &input) {
    return string(input.size(), '#');
}

string redact_alphabet_digits(string const &input) {
  string output;
  for (auto character : input) {
    if (isalnum(character))
      output += '#';
    else
      output += character;
  }
  return output;
}

string redact_words(string const &input, vector<string> const &words) {
  // https://stackoverflow.com/questions/9053687/trying-to-replace-words-in-a-string
  string output = input;
  for (auto word : words) {
    while (output.find(word) != string::npos)
      output.replace(output.find(word), word.size(), string(word.size(), '#'));
  }
  return output;
}