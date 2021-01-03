#ifndef SELF_DESTRUCTING_H
#define SELF_DESTRUCTING_H

#include <iostream>
using std::endl;
using std::istream;
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

class SelfDestructingMessage {
 private:
  vector<string> messages_;
  long number_of_allowed_views_;

 public:
  // Member
  vector<long> remaining_views;
  // Constructors
  SelfDestructingMessage(vector<string>, long = 0);
  SelfDestructingMessage() = default;
  // Copy Constructor
  SelfDestructingMessage(SelfDestructingMessage&);
  // Destructor
  ~SelfDestructingMessage(){};
  // Getters
  vector<string> const& messages(void) const { return messages_; }
  long number_of_allowed_views() const { return number_of_allowed_views_; }
  // Methods
  int size();
  vector<string> get_redacted();
  long number_of_views_remaining(int);
  void add_array_of_lines(string[], long);
  // Appends message to list of messages
  void addMessage(string);
  // Overloaded Operator Methods
  string const& operator[](size_t);
  SelfDestructingMessage& operator=(SelfDestructingMessage&);
};

// Overloaded Operator Functions
ostream& operator<<(ostream&, const SelfDestructingMessage&);
istream& operator>>(istream&, SelfDestructingMessage&);

#endif
