#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */
// TODO: Implement this function
class KCipher : public Cipher {
	private:
		unsigned int id;
		vector<string> key;
		void add_key(string page);
		void set_id(unsigned int page);
	public:
		KCipher();
		KCipher(string page1);
		~KCipher();
		string encrypt(string raw) override;
		string decrypt(string enc) override;
};
#endif

