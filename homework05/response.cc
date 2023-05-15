/*
  Implementation of methods for classes Response, AngryResponse, HappyResponse
*/
#include <iostream>
#include <string>
#include <algorithm>

#include "response.h"

using namespace std;

/*
  Implementation of Word class
  Don't worry too hard about these implementations.
  If you'd like to learn more about STL see: 
    https://www.geeksforgeeks.org/the-c-standard-template-library-stl/
*/
string Word::upper()
{
  string result(theWord);
  transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

string Word::lower()
{
  string result(theWord);
  transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

/*
  Implementation of Response methods
*/
bool Response::checkAndRespond(const string& inWord, ostream& toWhere)
{
    // TODO:
    // This method should check if the current object's keyword is in the
    // input message (inWord), and send the proper response to the toWhere
    // output stream
    // String class provides the function 'find' which you might find useful
    // use upper on 1st char to match inWord to correct syntax
    // this pointer grabs keyword from current Response class
    size_t found = inWord.find(this->keyword.upper());
    // npos means end of string here, so if inWord is not found in string skip
    if (found != string::npos) {
	    // call response and return true for exists var
	    this->respond(toWhere);
	    return true;
    }
    return false;
}

void Response::respond(ostream& toWhere)
{
    // TODO:
    // This method should 'insert' "I am neither angry nor happy: " followed by
    // the object's response word to the toWhere output stream, along with
    // a newline at the end
    toWhere << "I am neither angry nor happy: " << this->response << endl;
}


void AngryResponse::respond(ostream& toWhere)
{
  // TODO:
  // Implement the 'respond' member function for the AngryResponse class so that
  // the angry rseponse "I am angry: " followed by the object's response word 
  // is inserted to the toWhere output stream, along with a newline at the end
  toWhere << "I am angry: " << this->response << endl;
}


/*
  Implementation of HappyResponse methods
*/
// TODO:
// Implement the 'respond' member function for the HappyResponse class so that
// the happy rseponse "I am happy: " followed by the object's response word 
// is inserted to the toWhere output stream, along with a newline at the end

void HappyResponse::respond(ostream& toWhere) {
	toWhere << "I am happy: " << this->response << endl;
}
