/*************************************************************

CIS330: Lab 7
Introduction to C++ Templates

Instructions:

  (1) Read the code in this file, figure out what it is doing (or trying to
      do), compile and run to verify. Ask questions if you don't understand
      something.

  (2) Write getPositiveNumber(float &), add a test call in main, compile and
      run to verify.

  (3) Complete the template function getNegativeNumber(), compile and run to
      verify. Test calls to getNegativeNumber() with different types are
      already made in main(). You may assume this template function will only
      be called with numeric types (e.g. int, float, anything else that has <,
      >, and !=)

*************************************************************/

#include <iostream>
#include <string>

// Bring the std namespace "into view".
// Without this we have to write `std::` before anything we use from the std
// namespace (e.g. std::cout)
using namespace std;

//
// Note that in C++ this creates a new type `CheckOp`
// much the same as if we had used typedef in C.
// The same holds for `struct` and C++'s `class`.
//
enum CheckOp {
  CheckOpPositive,
  CheckOpNegative,
  CheckOpNonzero
};

//
// This is a template function which can take any type supporting >, <, and !=
// as its first argument. Note the second argument is given a default value and
// is hence optional when calling.
//
template<class T>
bool
validate(T input, CheckOp check = CheckOpPositive)
{
  switch (check) {
    case CheckOpPositive:
      return input > 0;
      break;
    case CheckOpNegative:
      return input < 0;
      break;
    case CheckOpNonzero:
      return input != 0;
      break;
    default:
      cerr << "This shouldn't happen!" << endl;
      break;
  }
  return false;
}

//
// The parameter of this function is passed by reference.
// Basically this means that whatever happens to the parameter inside the
// function will directly impact whatever variable was passed as an argument
// when the function is called. In C we would have had to have used pointers
// and referencing / dereferencing to get this behavior.
//
int
getPositiveNumber(int &result)
{
  // This is essentially C++ for `fprintf(stdout, "Enter a positive integer: ");`
  cout << "Enter a positive integer: ";

  // This is essentially C++ for `fscanf(stdin, "%d", &result);`
  cin >> result;

  if (validate(result)) {
    return 0;
  } else {
    return -1;
  }
}

//
// Overloading is when we write a new function with the same name as a previous
// function, but give different parameters.
// Here we add a parameter and if the entered number is not positive, set the
// result before returning.
//
int
getPositiveNumber(int &result, int setOnError)
{
  int rv = 0;
  if ((rv = getPositiveNumber(result)) != 0) {
    result = setOnError;
  }
  return rv;
}

//
// This declaration of `getPositiveNumber` overloads the previous declarations
// of `getPositiveNumber` because the parameter has a different type.
// The compiler will decide which function to execute based on the type of the
// argument when the function is called.
//
int
getPositiveNumber(float &result)
{
  // TODO: Enter your code here
  cout << "Enter a positive float: ";
  cin >> result;

  if (validate(result, CheckOpPositive)) {
	  return 0;
  } else {
	  return -1;
  }
  return -1;
}


//
// This template function implements the same functionality as above but
// making sure the result is negative.
// Use the same validate() function with a different value from the CheckOp enum.
// Note that in the function body, T refers to the type of the argument.
//
template<class T>
int
getNegativeNumber(T &result)
{
  // TODO: Enter your code here
  cout << "Enter a negative number: ";
  cin >> result;
  if (validate(result, CheckOpNegative)) {
	  return 0;
  } else {
	  return -1;
  }
  return -1;
}



int
main()
{
  int i;
  float f;

  // The compiler will call getPositiveNumber(int) because i is an int here
  if (getPositiveNumber(i) != 0) {
    cerr << "Invalid input" << endl;
  } else {

    // This is essentialy C++'s version of `fprintf(stdout, "You entered the
    // positive integer: %d\n", i);`
    cout << "You entered the positive integer: " << i << endl;
  }
  cout << endl;

  // The compiler will call getPositiveNumber(int, int) because of the
  // arguments and their types
  if (getPositiveNumber(i, 10) != 0) {
    cerr << "Invalid input" << endl;
  }
  cout << "i is now " << i << endl;
  cout << endl;


  // TODO Make a test call to your getPositiveNumber(float) function
  if (getPositiveNumber(f) != 0) {
	  cerr << "Invalid input" << endl;
  } else {
	  cout << "You entered the positive float: " << f << endl;
  }
  cout << endl;

  // The compiler will generate code from the template for
  // getNegativeNumber(int) because i is an int here.
  if (getNegativeNumber<int>(i) != 0) {
    cerr << "Invalid input" << endl;
  } else {
    cout << "You entered the negative integer: " << i << endl;
  }
  cout << endl;

  // The compiler will generate code from the template for
  // getNegativeNumber(float) because f is a float here.
  if (getNegativeNumber<float>(f) != 0) {
    cerr << "Invalid input" << endl;
  } else {
    cout << "You entered the negative floating point number: " << f << endl;
  }
  cout << endl;

  return 0;
}
