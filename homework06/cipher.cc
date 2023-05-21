#include "cipher.h"

/* Cheshire smile implementation.
   It only contains the cipher alphabet
 */
struct Cipher::CipherCheshire {
    string cipher_alpha;
};

/* This function checks the cipher alphabet
   to make sure it's valid
 */
bool is_valid_alpha(string alpha);


// -------------------------------------------------------
// Cipher implementation
/* Default constructor
   This will actually not encrypt the input text
   because it's using the unscrambled alphabet
 */
Cipher::Cipher()
{
	smile = new CipherCheshire;
	// use unscrambled alphabet for default constructor
	smile->cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
}

/* This constructor initiates the object with a
   input cipher key
 */
Cipher::Cipher(string cipher_alpha)
{
	if (is_valid_alpha(cipher_alpha) == true) {
		smile = new CipherCheshire;
		smile->cipher_alpha = cipher_alpha;
	}
}

/* Destructor
 */
Cipher::~Cipher()
{
	delete smile;
}

/* This member function encrypts the input text 
   using the intialized cipher key
 */
string Cipher::encrypt(string raw)
{
    cout << "Encrypting...";
    string retStr;
    for (size_t i = 0; i < raw.length(); i++) {
	    // 5.ii.b: retain spaces
	    // push_back method standard for appending single chars
	    if (raw[i] == ' ') {
		    retStr.push_back(' ');
		    continue;
	    }
	    // cipher is all lowercase so convert if necessary
	    size_t cipher_idx = find_pos(smile->cipher_alpha, LOWER_CASE(raw[i]));
	    char working_char = smile->cipher_alpha[cipher_idx];
	    // 5.ii.a: retain the case
	    // conditional checks if raw is within ASCII uppercase range
	    if (raw[i] >= 'A' && raw[i] <= 'Z')
		    working_char = UPPER_CASE(working_char);
	    retStr.push_back(working_char);
    }

    cout << "Done" << endl;

    return retStr;
}


/* This member function decrypts the input text 
   using the intialized cipher key
 */
string Cipher::decrypt(string enc)
{
    string retStr;
    cout << "Decrypting...";
    for (size_t i = 0; i < enc.length(); i++) {
	    if (enc[i] == ' ') {
		    retStr.push_back(' ');
		    continue;
	    }
	    // finding position of encrypted letter in cipher directs us to
	    // decrypted letter
	    size_t cipher_idx = find_pos(smile->cipher_alpha, LOWER_CASE(enc[i]));
	    char working_char = smile->cipher_alpha[cipher_idx];
	    if (enc[i] >= 'A' && enc[i] <= 'Z')
		    working_char = UPPER_CASE(working_char);
	    retStr.push_back(working_char);

    }

    cout << "Done" << endl;

    return retStr;

}
// -------------------------------------------------------


//  Helper functions 
/* Find the character c's position in the cipher alphabet/key
 */
unsigned int find_pos(string alpha, char c)
{
    unsigned int pos = 0;
    for (size_t i = 0; i < (size_t)ALPHABET_SIZE; i++) {
	    if (alpha[i] == c) {
		    pos = i;
		    break;
	    }
    }
    return pos;
}

/* Make sure the cipher alphabet is valid - 
   a) it must contain every letter in the alphabet 
   b) it must contain only one of each letter 
   c) it must be all lower case letters 
   ALL of the above conditions must be met for the text to be a valid
   cipher alphabet.
 */
bool is_valid_alpha(string alpha)
{
    bool is_valid = true;
    if(alpha.size() != ALPHABET_SIZE) {
        is_valid = false; 
    } else {
        unsigned int letter_exists[ALPHABET_SIZE];
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            letter_exists[i] = 0;
        }
        for(unsigned int i = 0; i < alpha.size(); i++) {
            char c = alpha[i];
            if(!((c >= 'a') && (c <= 'z'))) {
                is_valid = false;
            } else {
                letter_exists[(c - 'a')]++;
            }
        }
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            if(letter_exists[i] != 1) {
                is_valid = false;
            }
        }
    }

    return is_valid;
}
