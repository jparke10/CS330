#include <string>
#include <iostream>
#include <vector>
// added algorithm for remove function
#include <algorithm>
#include "kcipher.h"
// added ccipher for rotate_string function
// added cipher for find_pos function




/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

KCipher::KCipher() : Cipher() {
	// by default, generate a blank key (all A's) at page 1 (idx 0)
	id = 0;
	key[id].insert(key[id].begin(), MAX_LENGTH, 'a');
}

KCipher::KCipher(string page1) : Cipher() {
	id = 0;
	// remove all spaces and casing from page, for encryption step
	key[id] = page1;
	transform(key[id].begin(), key[id].end(), key[id].begin(), ::tolower);
	remove(key[id].begin(), key[id].end(), ' ');
}

// destructor in header, no memory allocated

void KCipher::add_key(string page) {
	string trim = page;
	transform(trim.begin(), trim.end(), trim.begin(), ::tolower);
	remove(trim.begin(), trim.end(), ' ');
	key.push_back(trim);
}

void KCipher::set_id(unsigned int page) {
	try {
		if (page < key.size())
			throw page;
	}
	catch (unsigned int page) {
		cerr << "Warning: Invalid id: " << page << endl;
	}
	id = page - 1;
}

string KCipher::encrypt(string raw) {
	string retStr = raw;
	// standardize input
	transform(retStr.begin(), retStr.end(), retStr.begin(), ::tolower);
	remove(retStr.begin(), retStr.end(), ' ');
	for (size_t i = 0; i < retStr.length(); i++) {
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unsigned int idx = find_pos(alphabet, retStr[i]);
		// rotating standard alphabet gives us our tabula recta
		rotate_string(alphabet, (key[id][i] - 'a'));
		retStr[i] = alphabet[idx];
	}
	// 5.ii: re-add case and spaces from raw
	// probably a way to do this in O(n) but oh well
	for (size_t i = 0; i < raw.length(); i++) {
		if (raw[i] == ' ')
			retStr.insert(i, 1, ' ');
		else if (raw[i] >= 'A' && raw[i] <= 'Z')
			retStr[i] = UPPER_CASE(retStr[i]);
	}
	return retStr;
}

string KCipher::decrypt(string enc) {
	string retStr = enc;
	transform(retStr.begin(), retStr.end(), retStr.begin(), ::tolower);
	remove(retStr.begin(), retStr.end(), ' ');
	for (size_t i = 0; i < retStr.length(); i++) {
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		unsigned int idx = find_pos(alphabet, retStr[i]);
		rotate_string(alphabet, -(key[id][i] - 'a'));
		retStr[i] = alphabet[idx];
	}
	for (size_t i = 0; i < enc.length(); i++) {
		if (enc[i] == ' ')
			retStr.insert(i, 1, ' ');
		else if (raw[i] >= 'A' && raw[i] <= 'Z')
			retStr[i] = UPPER_CASE(retStr[i]);
	}
	return retStr;
}
