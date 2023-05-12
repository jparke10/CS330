/*************************************

CIS330: Lab 6

The goal of this lab is to use C++ classes and inheritance to create simple
letter filters.

Instructions:

(1) Read this file and understand the basic operations and interactions
    between these objects.
(2) Define and implement the ToLower class as described below.
(3) Modify `getFilter` to test your ToLower class.
(4) Define and implement the Encrypt class as described below.
(5) Modify `getFilter` to test your Encrypt class.
      Note: If you want to verify your Encrypt filter, instantiate with a
            shift of 13 and pipe a message through the filter twice.

*************************************/

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//
// This is the base class for our filters.
// 
class Filter
{
  //
  // This method determines a filter's behavior.
  // It is `virtual` so the compiler knows to always call the overriden
  // version in our more interesting filters. The base class's implementation
  // here just passes each character unchanged.
  //
  virtual char FilterLetter(char ch) { return ch; }

public:
  //
  // Function to execute the filter on a given input string.
  //
  string Exec(string input);
};

//
// Function to execute the filter on a given input string.
//
string Filter::Exec(string input)
{
  stringstream res;
  for (int i = 0; i < input.size(); i++) {

    if (isalpha(input[i])) {

      // Note that the call to FilterLetter will execute the implementation of
      // FilterLetter for the class of the object on which this method is
      // invoked. This allows us to use this same code for each filter which
      // inherits from the base Filter class.
      res << FilterLetter(input[i]);

    } else {

      // Pass non-alphabetic characters unchanged
      res << input[i];
    }
  }

  // Convert the stringstream to a string object and return
  return res.str();
}


//
// An example of inheriting from the Filter base class to implement a filter
// which makes each alphabetic character uppercase
//
class ToUpper : public Filter
{
  //
  // All we need to do is override the FilterLetter() method.
  // The super class takes care of everything else!
  //
  char FilterLetter(char ch) { return toupper(ch); }
};


//
// TODO (1) Define a ToLower class which inherits from Filter and makes each
// character lowercase
//

class ToLower : public Filter {
	char FilterLetter(char ch) {return tolower(ch);}
};

//
// This is a simple function to implement a shift cypher.
// Each character is converted to uppercase then shifted a fixed number of
// letters.
//
char
shift_cypher(char ch, int offset)
{
  return (toupper(ch) - 'A' + offset) % 26 + 'A';
}

//
// TODO (2) Define an Encrypt filter which uses the above shift_cypher()
// function to encode its input letters.
// This class should have a constructor that takes the shift offset which will
// be handed to shift_cypher when the filter is executed.
//

class Encrypt : public Filter {
	private:
		int offset;
	public:
		Encrypt(int shift) {
			offset = shift;
		}
		char FilterLetter(char ch) {return shift_cypher(ch, offset);}
};

//
// This function allocates a particular filter and returns a pointer to it
// Modify this function to test your filters.
//
Filter *
getFilter()
{
  return new Encrypt(5);
}

//
// Main function
// DO NOT CHANGE!
//
int
main()
{
  // Temporary string for holding input
  string temp;

  // Get filter to apply
  Filter *theFilter = getFilter();

  // Apply filter till no more input
  while (getline(cin, temp)) {
    cout << theFilter->Exec(temp) << endl;
  }

  return 0;
}
