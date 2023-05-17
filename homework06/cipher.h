#ifndef CIPHER_H_
#define CIPHER_H_
#include <string>
#include <iostream>

using namespace std;

const unsigned int ALPHABET_SIZE = 26;

/* A class that implements a
   basic substitution cipher
 */
class Cipher {
protected: 
    struct CipherCheshire;
    CipherCheshire *smile;
public:
    Cipher();
    Cipher(string cipher_alpha);
    ~Cipher();
    virtual string encrypt(string raw);
    virtual string decrypt(string enc);
};

/* Helper function headers 
 */
unsigned int find_pos(string alpha, char c);
inline char UPPER_CASE(char c) {
    return toupper(c);
}
inline char LOWER_CASE(char c) {
    return tolower(c);
}
#endif
