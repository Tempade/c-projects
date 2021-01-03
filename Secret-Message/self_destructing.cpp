#include <iostream>
using std::endl;
using std::ostream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <stdexcept>
using std::invalid_argument;
using std::out_of_range;
#include <sstream>
using std::stringstream;
#include "redact.h"
#include "self_destructing.h"

// 2 Parameter Constructor
SelfDestructingMessage::SelfDestructingMessage(vector<string> messages,
                                               long number_of_allowed_views) {
  int size = messages.size();
  messages_ = messages;
  number_of_allowed_views_ = number_of_allowed_views;
  for (int i = 0; i < size; i++) {
    remaining_views.push_back(number_of_allowed_views);
  }
}

// Methods

int SelfDestructingMessage::size() {
  int output = 0;
  for (auto message : messages()) {
    ++output;
  }
  return output;
}

vector<string> SelfDestructingMessage::get_redacted() {
  vector<string> redacted_form;
  for (auto message : messages()) {
    redacted_form.push_back(redact_alphabet_digits(message));
  }
  return redacted_form;
}

long SelfDestructingMessage::number_of_views_remaining(int index) {
  return remaining_views.at(index);
}

void SelfDestructingMessage::add_array_of_lines(string arr[], long size) {
  for (int n = 0; n < size; ++n) {
    messages_.push_back(arr[n]);
    remaining_views.push_back(number_of_allowed_views());
  }
}

void SelfDestructingMessage::addMessage(string message) {
  this->messages_.push_back(message);
}

// Overloaded Operators

string const &SelfDestructingMessage::operator[](size_t index) {
  long signed_index = index;
  long size = messages().size();
  if (signed_index > size || signed_index < 0)
    throw out_of_range("Out of Range");
  else if (remaining_views.at(signed_index) == 0)
    throw invalid_argument("Invalid Argument");
  else {
    --remaining_views.at(signed_index);
    string const &message = messages().at(signed_index);
    return message;
  }
}

ostream &operator<<(ostream &out, const SelfDestructingMessage &sdm) {
  int size = sdm.messages().size();
  for (int i = 0; i < size; i++) {
    out << "0" << sdm.remaining_views.at(i) << ": "
        << redact_alphabet_digits(sdm.messages().at(i)) << endl;
  }
  return out;
}

istream &operator>>(istream &ss, SelfDestructingMessage &sdm) {
  string line;             // Needed string
  std::getline(ss, line);  // Reads correct line
  sdm.addMessage(line);
  sdm.remaining_views.push_back(sdm.number_of_allowed_views());  // Correct
  return ss;
}

SelfDestructingMessage &SelfDestructingMessage::operator=(
    SelfDestructingMessage &sdm) {
  messages_ = sdm.messages_;
  number_of_allowed_views_ = sdm.number_of_allowed_views_;
  remaining_views = sdm.remaining_views;
  vector<long> zero_sdm(sdm.remaining_views.size(), 0);
  sdm.remaining_views = zero_sdm;
  return *this;
}

// Copy Constructor

SelfDestructingMessage::SelfDestructingMessage(SelfDestructingMessage &sdm) {
  messages_ = sdm.messages_;
  number_of_allowed_views_ = sdm.number_of_allowed_views_;
  remaining_views = sdm.remaining_views;
  vector<long> zero_sdm(sdm.remaining_views.size(), 0);
  sdm.remaining_views = zero_sdm;
}