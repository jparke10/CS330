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

string CCipher::encrypt(string raw) {
	// seems safer to work with new string
	string enc = raw;
	rotate_string(enc, offset);
	return enc;
}

string CCipher::decrypt(string enc) {
	string dec = enc;
	rotate_string(dec, 0 - offset);
	return dec;
}

// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
	for (size_t i = 0; i < in_str.length(); i++) {
		// 5.ii.b
		if (in_str[i] == ' ')
			continue;
		char working_char = LOWER_CASE(in_str[i]);
		// work through ASCII table, use order of operations and
		// loop around alphabet with modulo
		char rotated_char = ((working_char - 'a') + rot) % 26 + 'a';
		// 5.ii.a
		if (in_str[i] >= 'A' && in_str[i] <= 'Z')
			in_str[i] = UPPER_CASE(rotated_char);
		else
			in_str[i] = rotated_char;
	}
}
