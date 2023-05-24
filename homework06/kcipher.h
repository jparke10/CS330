#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */
class KCipher : public Cipher {
	protected:
		struct CipherCheshire;
		CipherCheshire* smile;
	public:
		KCipher();
		KCipher(string page1);
		~KCipher();
		void add_key(string page);
		void set_id(unsigned int page);
		string encrypt(string raw) override;
		string decrypt(string enc) override;
};

void remove_spaces(string& in_string);
#endif
