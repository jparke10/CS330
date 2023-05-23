#ifndef VCIPHER_H_
#define VCIPHER_H_
//#include "cipher.h"
#include "kcipher.h"

using namespace std;

/* A class that implements a
   Vigenere cipher class. It 
   inherts KCipher */
class VCipher : public KCipher {
	private:
		string key;
	public:
		VCipher();
		VCipher(string keyword);
		~VCipher();
		string encrypt(string raw) override;
		string decrypt(string enc) override;
};
#endif
