#include <math.h>
#include <cmath>
#include <iostream>

// Discovered number of digits function from:
// https://stackoverflow.com/questions/1489830/efficient-way-to-determine-number-of-digits-in-an-integer
int number_digits(int number) {
  int digits(0);
  while (number) {
    number /= 10;
    digits++;
  }
  return digits;
}

int convert_other_base_to_decimal(int number, int base) {
  int n(number_digits(number));  // Number of digits
  int &b(base);                  // Base number
  int total(0);                      // Running total
  int saved_iteration(number);   // Current number

  // Iterate through n, in reverse
  for (int current_number(0); current_number != (n); current_number++) {
    int current_digit(saved_iteration % 10);  // Current digit
    saved_iteration /= 10;                    
    int exponent(pow(b, current_number));     // Exponent from:
    // https://www.programiz.com/cpp-programming/library-function/cmath/pow
    total += current_digit * exponent;  
  }
  return total;
}

int convert_decimal_to_other_base(int decimal, int desired_base) {
  int &n(decimal);       // Decimal Number
  int converted_n(0);              // Number to convert to
  int new_n(n);              // New value of n
  int &b(desired_base);  // Base
  int exp(0);            // Exponent

  while (new_n != 0) {
    int r = new_n % b;          // Remainder
    new_n /= b;                 
    converted_n += r * pow(10, exp);  // Add r to new number
    exp++;                  
  }
  return converted_n;
}

int math_in_other_base(int numberOne, int numberTwo, int base,
                       char expression) {
  numberOne = convert_other_base_to_decimal(numberOne, base);
  numberTwo = convert_other_base_to_decimal(numberTwo, base);
  int result(0);       // Initialize the result
  switch (expression)  // Computes the result
  {
    case '+':
      result = numberOne + numberTwo;
      break;
    case '-':
      result = numberOne - numberTwo;
      break;
    case '*':
      result = numberOne * numberTwo;
      break;
    case '/':
      result = numberOne / numberTwo;
      break;
    case '%':
      result = numberOne % numberTwo;
      break;
  }
  // Converts result to desired base
  result = convert_decimal_to_other_base(result, base);
  return result;
}

int main() {
  int result(0);
  int numberOne(0);
  int numberTwo(0);
  int base(0);
  char expression;
  std::cin >> numberOne >> numberTwo >> base >> expression;
  result = math_in_other_base(numberOne, numberTwo, base, expression);
  std::cout << result;
}