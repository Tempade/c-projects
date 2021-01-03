#ifndef REDACT_H
#define REDACT_H

#include <string>
using std::string;
#include <vector>
using std::vector;

string redact_all_chars(string const &input);
string redact_alphabet_digits(string const &input);
string redact_words(string const &input, vector<string> const &words);

#endif
