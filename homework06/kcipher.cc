#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"

struct KCipher::CipherCheshire {
	vector<string> key;
	int id;
};

/* Helper function definitions
 */

// just for input validation at this point 
void remove_spaces(string& in_string) {
	size_t idx;
	while ((idx = in_string.find(' ')) != string::npos) {
		string replacer = in_string.substr(idx + 1);
		in_string.erase(idx, string::npos);
		in_string += replacer;
	}
}

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

KCipher::KCipher() : Cipher() {
	smile = new CipherCheshire;
	smile->id = 0;
	// by default, generate a blank key (all A's) at page 1 (idx 0)
	string page1;
	page1.insert(page1.begin(), MAX_LENGTH, 'a');
	smile->key.push_back(page1);
}

KCipher::KCipher(string page1) : Cipher() {
	smile = new CipherCheshire;
	smile->id = 0;
	// validate key is not an empty string
	try {
		if (page1.empty())
			throw page1;
		// validate key does not contain any non-alpha (with the exception
		// of spaces) characters
		// string iterator explained at :98
		for (string::iterator i = page1.begin(); i < page1.end(); i++)
			if (!isalpha(*i) && *i != ' ')
				throw page1;
	}
	catch (string page1) {
		cerr << "Invalid Running key: " << page1 << endl;
		exit(EXIT_FAILURE);
	}
	smile->key.push_back(page1);
}

KCipher::~KCipher() { delete smile; }

void KCipher::add_key(string page) {
	try {
		if (page.empty())
			throw page;
		for (string::iterator i = page.begin(); i < page.end(); i++)
			if (!isalpha(*i) && *i != ' ')
				throw page;
	}
	catch (string page) {
		cerr << "Invalid Running key: " << page << endl;
		exit(EXIT_FAILURE);
	}
	smile->key.push_back(page);
}

void KCipher::set_id(unsigned int page) {
	// validate id to be used is not outside bounds of vector
	try {
		if (page >= smile->key.size())
			throw page;
	}
	catch (unsigned int page) {
		cerr << "Warning: Invalid id: " << page << endl;
		exit(EXIT_FAILURE);
	}
	smile->id = page;
}

string KCipher::encrypt(string raw) {
	// validate key is shorter than input string
	try {
		string key_trimmed = smile->key[smile->id];
		string raw_trimmed = raw;
		remove_spaces(key_trimmed);
		remove_spaces(raw_trimmed);
		if (key_trimmed.length() < raw_trimmed.length())
			throw key_trimmed;
	}
	catch (string key_trimmed) {
		cerr << "Error: Key length is shorter than entered text: " << key_trimmed << endl;
		exit(EXIT_FAILURE);
	}
	cout << "Encrypting...";
	string retStr;
	// use string iterators to "point" to each character in the string
	// allows for skipping spaces seamlessly, easier dereferencing
	string::iterator ki, pi;
	for (ki = smile->key[smile->id].begin(), pi = raw.begin(); pi < raw.end();) {
		// if key has a space, skip - if in str has a space,
		// add it to retStr and skip
		if (*ki == ' ') {
			ki++;
			continue;
		} else if (*pi == ' ') {
			// 5.ii.b
			retStr.push_back(' ');
			pi++;
			continue;
		}
		// find the current plaintext char in the alphabet
		// (first column of tabula recta)
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unsigned int idx = find_pos(alphabet, LOWER_CASE(*pi));
		// rotating standard alphabet n times (where n is the index
		// of the current key letter in the standard alphabet) gives us
		// the correct column of the tabula recta
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

string KCipher::decrypt(string enc) {
	cout << "Decrypting...";
	string retStr;
	// we could validate the enc string with the key here too
	// but it's not necessary in this implementation
	string::iterator ki, pi;
	for (ki = smile->key[smile->id].begin(), pi = enc.begin(); pi < enc.end();) {
		if (*ki == ' ') {
			ki++;
			continue;
		} else if (*pi == ' ') {
			retStr.push_back(' ');
			pi++;
			continue;
		}
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unsigned int idx = find_pos(alphabet, LOWER_CASE(*pi));
		// rotating the standard alphabet -n times (:117)
		// gives us our original letter back, as the encrypted
		// letter was essentially Caesar ciphered with n rotations
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
