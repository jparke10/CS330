#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation

CCipher::CCipher() : Cipher() { offset = 0; }

CCipher::CCipher(int offset) : Cipher(), offset(offset) {}

CCipher::~CCipher() {}

// -------------------------------------------------------

string CCipher::encrypt(string raw) {}

string CCipher::decrypt(string enc) {}

// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
    // TODO: You will likely need this function. Implement it.
}
