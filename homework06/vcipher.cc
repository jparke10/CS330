#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"

struct VCipher::CipherCheshire {
	string key;
};

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

VCipher::VCipher() {
	smile = new CipherCheshire;
	// generate blank key for keyword var
	smile->key.insert(smile->key.begin(), MAX_LENGTH, 'a');
}

VCipher::VCipher(string key) {
	try {
		if (key.empty())
			throw key;
		for (string::iterator i = key.begin(); i < key.end(); i++)
			if (!isalpha(*i))
				throw key;
	}
	catch (string key) {
		cerr << "Error: not a valid Vigenere key word" << endl;
		exit(EXIT_FAILURE);
	}
	smile = new CipherCheshire;
	smile->key = key;
}

VCipher::~VCipher() { delete smile; }

string VCipher::encrypt(string raw) {
	cout << "Encrypting...";
	string retStr;
	string::iterator ki, pi;
	for (ki = smile->key.begin(), pi = raw.begin(); pi < raw.end();) {
		// if iterator hits the end of the keyword, go back to beginning
		if (ki >= smile->key.end()) {
			ki = smile->key.begin();
			continue;
		} else if (*pi == ' ') {
			// 5.ii.b
			retStr.push_back(' ');
			pi++;
			continue;
		}
		// same algorithm as kcipher
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unsigned int idx = find_pos(alphabet, LOWER_CASE(*pi));
		rotate_string(alphabet, (*ki - 'a'));
		// 5.ii.a
		if (*pi >= 'A' && *pi <= 'Z')
			retStr.push_back(UPPER_CASE(alphabet[idx]));
		else
			retStr.push_back(alphabet[idx]);
		ki++; pi++;
	}
	cout << "Done" << endl;
	return retStr;
}

string VCipher::decrypt(string enc) {
	cout << "Decrypting...";
	string retStr;
	string::iterator ki, pi;
	for (ki = smile->key.begin(), pi = enc.begin(); pi < enc.end();) {
		if (ki >= smile->key.end()) {
			ki = smile->key.begin();
			continue;
		} else if (*pi == ' ') {
			retStr.push_back(' ');
			pi++;
			continue;
		}
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unsigned int idx = find_pos(alphabet, LOWER_CASE(*pi));
		rotate_string(alphabet, -(*ki - 'a'));
		if (*pi >= 'A' && *pi <= 'Z')
			retStr.push_back(UPPER_CASE(alphabet[idx]));
		else
			retStr.push_back(alphabet[idx]);
		ki++; pi++;
	}
	cout << "Done" << endl;
	return retStr;
}
