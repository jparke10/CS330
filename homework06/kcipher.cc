#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"




/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

KCipher::KCipher() : Cipher() {
	// by default, generate a blank key (all A's) at page 1 (idx 0)
	id = 0;
	string page1;
	page1.insert(page1.begin(), MAX_LENGTH, 'a');
	key.push_back(page1);
}

KCipher::KCipher(string page1) : Cipher() {
	id = 0;
	// remove all spaces and casing from page, for encryption step
//	remove_spaces(page1);
	key.push_back(page1);
}

KCipher::~KCipher() {}

void KCipher::add_key(string page) {
//	remove_spaces(page);
	key.push_back(page);
}

void KCipher::set_id(unsigned int page) {
	try {
		if (page > key.size())
			throw page;
	}
	catch (unsigned int page) {
		cerr << "Warning: Invalid id: " << page << endl;
	}
	id = page - 1;
}

string KCipher::encrypt(string raw) {
	try {
		string key_trimmed = key[id];
		string raw_trimmed = raw;
		remove_spaces(key_trimmed);
		remove_spaces(raw_trimmed);
		if (key_trimmed.length() < raw_trimmed.length())
			throw key[id];
	}
	catch (string key[id]) {
		cerr << "Error: Key length is shorter than entered text" << endl;
	}
	string retStr = "";
	string::iterator ki, pi;
	for (ki = key[id].begin(), ki = raw.begin(); pi < raw.end(); ki++, pi++) {
		if (*ki == ' ') {
			retStr.push_back(' ');
			ki++;
			continue;
		} else if (*pi == ' ') {
			pi++;
			continue;
		}
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unsigned int idx = find_pos(alphabet, *pi);
		// rotating standard alphabet gives us our tabula recta
		rotate_string(alphabet, (*ki - 'a'));
		retStr.push_back(alphabet[idx]);
	}
	// 5.ii: re-add case and spaces from raw
	// probably a way to do this in O(n) but oh well
	/*
	for (size_t i = 0; i < retStr.length(); i++) {
		if (raw[i] >= 'A' && raw[i] <= 'Z')
			retStr[i] = UPPER_CASE(retStr[i]);
	}
	*/
	return retStr;
}

string KCipher::decrypt(string enc) {
	
	string retStr = enc;
	/*
	transform(retStr.begin(), retStr.end(), retStr.begin(), ::tolower);
	remove_spaces(retStr);
	for (size_t i = 0; i < retStr.length(); i++) {
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unsigned int idx = find_pos(alphabet, retStr[i]);
		rotate_string(alphabet, -(key[id][i] - 'a'));
		retStr[i] = alphabet[idx];
	}
	for (size_t i = 0; i < enc.length(); i++) {
		if (enc[i] == ' ')
			retStr.insert(i, 1, ' ');
		else if (enc[i] >= 'A' && enc[i] <= 'Z')
			retStr[i] = UPPER_CASE(retStr[i]);
	}
	*/
	return retStr;
}

void remove_spaces(string& in_string) {
	size_t idx;
	while ((idx = in_string.find(' ')) != string::npos) {
		string replacer = in_string.substr(idx + 1);
		in_string.erase(idx, string::npos);
		in_string += replacer;
	}
}
