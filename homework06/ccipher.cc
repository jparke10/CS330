#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation

struct CCipher::CipherCheshire {
	int offset;
};

CCipher::CCipher() {
	smile = new CipherCheshire;
	smile->offset = 0;
}

CCipher::CCipher(int offset) {
	try {
		if (offset < 0) {
			throw offset;
		}
	}
	catch (int offset) {
		cerr << "Error: Caesar cipher is less than 0" << endl;
		exit(EXIT_FAILURE);
	}
	smile = new CipherCheshire;
	smile->offset = offset;
}

CCipher::~CCipher() {
	delete smile;
}

// -------------------------------------------------------

string CCipher::encrypt(string raw) {
	cout << "Encrypting...";
	// seems safer to work with string copy
	string ret = raw;
	rotate_string(ret, smile->offset);
	cout << "Done" << endl;
	return ret;
}

string CCipher::decrypt(string enc) {
	cout << "Decrypting...";
	string ret = enc;
	rotate_string(ret, -(smile->offset));
	cout << "Done" << endl;
	return ret;
}

// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
	size_t len = in_str.length();
	for (size_t i = 0; i < len; i++) {
		// 5.ii.b
		if (in_str[i] == ' ')
			continue;
		char working_char = LOWER_CASE(in_str[i]);
		// work through ASCII table, use order of operations and
		// loop around alphabet with modulo (add and take modulo again
		// is to allow use of negative modulo)
		char rotated_char = (((working_char - 'a' + rot) % 26)
		       		    + 26) % 26 + 'a';
		// 5.ii.a
		if (in_str[i] >= 'A' && in_str[i] <= 'Z')
			in_str[i] = UPPER_CASE(rotated_char);
		else
			in_str[i] = rotated_char;
	}
}
