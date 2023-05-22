#ifndef RCIPHER_H_ 
#define RCIPHER_H_
#include "ccipher.h"

using namespace std;

/* A class that implements a
   ROT13 cipher class. It 
   inherts class CCipher */

class RCipher : public CCipher {
	private:
		int offset;
	public:
		RCipher();
		~RCipher();
		// no changes made to encrypt/decrypt, no need for declaration
};

#endif

