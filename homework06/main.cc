#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <getopt.h>
#include "cipher.h"
#include "ccipher.h"
#include "rcipher.h"
#include "kcipher.h"
#include "vcipher.h"


using namespace std;


const char* const short_opt = ":hm:i:o:";
const struct option long_opt[] = {
    {"help",           0, NULL, 'h'},
    {"method",         0, NULL, 'm'},
    {"input",          1, NULL, 'i'},
    {"output",         1, NULL, 'o'},
    {NULL,             0, NULL,  0}
};

enum write_mode {
   wr,
   ap
};

void usage(char* argv);
// Substitution cipher
void substitution_enc(string ifile_name, string ofile_name);
void load_subs_input(string ifile_name, string& cipher_alpha, 
                     string& plain_text);
// Caesar cipher 
void caesar_enc(string ifile_name, string ofile_name);
void load_caes_input(string ifile_name, int& offset, string& plain_text);

// ROT13 cipher 
void rot13_enc(string ifile_name, string ofile_name);
void load_rot13_input(string ifile_name, string& plain_text);

// Runnign Key cipher
void rk_enc(string ifile_name, string ofile_name);
void load_rk_input(string ifile_name, unsigned int& page, vector<string>& cont,
                   string& plain_text);

// Vigenere Cipher
void vigenere_enc(string ifile_name, string ofile_name);
void load_vig_input(string ifile_name, string& keyword, string& plain_text);

// Helper function 
// stores the cipher text and decrypted text to an output file
void store_output(string ofile_name, string cipher_text, string decrypt_text,
                  write_mode wm);


/* Main function 
 */
int main(int argc, char **argv)
{
    int c = 0;
    string ifile_name;
    string ofile_name;
    string enc_method;

    if(argc < 2) {
        usage(argv[0]);
        return 0;
    }

    while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
        switch(c) {
            case 'h':
                usage(argv[0]);
                return 0;
            case 'm':
                enc_method = optarg;
                break;
            case 'i':
                ifile_name = optarg;
                break;
            case 'o':
                ofile_name = optarg;
                break;
            default:
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    char method = enc_method.at(0);
    switch(method) {
        case 's':
            substitution_enc(ifile_name, ofile_name);
            break;
        case 'c':
            caesar_enc(ifile_name, ofile_name);
            break;
        case 'r':
            rot13_enc(ifile_name, ofile_name);
            break;
        case 'k':
            rk_enc(ifile_name, ofile_name);
            break;
        case 'v':
            vigenere_enc(ifile_name, ofile_name);
            break;
        default:
            cerr << "Invalid encryption method: " << method << endl;
            exit(EXIT_FAILURE);
    }

    return 0;
}


/* Print information on how to properly use this program
 */
void usage(char* call)
{
    cout << "Usage: " << call << endl;
    cout << "Options:" << endl;
    cout << "\t-h or --help            Display this information" << endl;
    cout << "\t-m or --method [scrkv]  Encryption method" << endl;
    cout << "\t\t s: substitution" << endl;
    cout << "\t\t c: Caesar" << endl;
    cout << "\t\t r: ROT13" << endl;
    cout << "\t\t k: Running Key" << endl;
    cout << "\t\t v: Vigenere" << endl;
    cout << "\t-i or --input ifname    Input file" << endl;
    cout << "\t-o or --output ofname   Output file" << endl;
}


/* This function encrypts and decrypts the input (plain) text
   using the substitution cipher and the given cipher
   alphabet
 */
void substitution_enc(string ifile_name, string ofile_name)
{
    string cipher_alpha;
    string plain_text;
    // Read in the cipher alphabet and the plain text to encrypt
    // The input file for ths substitution cipher MUST have the
    // cipher alphabet in line 1, and the plain text to encrypt
    // in line 2
    load_subs_input(ifile_name, cipher_alpha, plain_text);

    // Create a substitution cipher class object and use it to encrypt and 
    // decrypt the plain text
    Cipher my_cipher(cipher_alpha);
    string cipher_text = my_cipher.encrypt(plain_text);
    string decrypt_text = my_cipher.decrypt(cipher_text);

    // Also, create a substitution cipher class object using the default 
    // constructor to initialize it
    // The default initialized object should use a cipher alphabet such that
    // when the plain text is encrypted, the cipher text should be identical
    // to the plain text
    Cipher my_def_cipher;
    string def_cipher_text = my_def_cipher.encrypt(plain_text);
    string def_decrypt_text = my_def_cipher.decrypt(def_cipher_text);

    // Store the output to files
    store_output(ofile_name, cipher_text, decrypt_text, wr);
    store_output(ofile_name, def_cipher_text, def_decrypt_text, ap);
}
void load_subs_input(string ifile_name, string& cipher_alpha, 
                     string& plain_text)
{
    ifstream inFile(ifile_name);

    string line;
    // Read in the cipher alphabet
    getline(inFile, line);
    cipher_alpha = line;

    // Read in the plain text you want to encrypt 
    getline(inFile, line);
    plain_text = line;

    inFile.close();
}

/* This function encrypts and decrypts the input (plain) text
   using the Caesar cipher and the given shift/offset/rotation value
 */
void caesar_enc(string ifile_name, string ofile_name)
{
    // "Uncomment* this by repladcing 0 with 1 when you are ready to 
    // implement it. Leave it uncommented when you submit it.
    #if 1
    int offset;
    string plain_text;
    // Read in the shift/offset/rotation value and the plain text to encrypt
    // The input file for ths Caesar cipher MUST have the
    // shift/offset/rotation value in line 1, and the plain text to encrypt
    // in line 2
    load_caes_input(ifile_name, offset, plain_text);

    // Create a Caesar Cipher class object with the provided shift value and 
    // use it to encrypt and decrypt the plain text
    CCipher my_ccipher(offset);
    string cipher_text = my_ccipher.encrypt(plain_text);
    string decrypt_text = my_ccipher.decrypt(cipher_text);

    // Also, create a Caesar Cipher class object using the default constructor
    // Again, this should produce a cipher text that is identical to the 
    CCipher my_def_ccipher;
    string def_cipher_text = my_def_ccipher.encrypt(plain_text);
    string def_decrypt_text = my_def_ccipher.decrypt(def_cipher_text);

    // Store the output to files
    store_output(ofile_name, cipher_text, decrypt_text, wr);
    store_output(ofile_name, def_cipher_text, def_decrypt_text, ap);
    #endif
}
void load_caes_input(string ifile_name, int& offset, string& plain_text)
{
    ifstream inFile(ifile_name);

    // Read in the shift/offset/rotation value using string stream
    string line;
    getline(inFile, line);
    stringstream off(line);
    off >> offset;

    // Read in the plain text you want to encrypt
    getline(inFile, line);
    plain_text = line;

    inFile.close();
}

/* This function encrypts and decrypts the input (plain) text
   using the ROT13 cipher.
 */
void rot13_enc(string ifile_name, string ofile_name)
{
    // "Uncomment* this by repladcing 0 with 1 when you are ready to 
    // implement it. Leave it uncommented when you are ready to submit it.
    #if 1
    string plain_text;
    // Read in the plain text to encrypt
    // The input file for ths ROT13 cipher MUST have only the
    // the plain text to encrypt in line 1
    load_rot13_input(ifile_name, plain_text);

    // Create a ROT13 Cipher class object and use it to encrypt and decrypt
    // the plain text. Use the default constructor.
    RCipher my_rcipher;
    string cipher_text = my_rcipher.encrypt(plain_text);
    string decrypt_text = my_rcipher.decrypt(cipher_text);

    // By definition, there is no way to use ROT13 and produce a cipher text 
    // that is identical to the plain text. Therefore, there is no default
    // constructor test

    // Store the output to a file
    store_output(ofile_name, cipher_text, decrypt_text, wr);
    #endif
}
void load_rot13_input(string ifile_name, string& plain_text)
{
    ifstream inFile(ifile_name);

    // Read in the plain text you want to encrypt
    string line;
    getline(inFile, line);
    plain_text = line;

    inFile.close();
}

/* This function encrypts and decrypts the input (plain) text
   using the running key cipher.
 */
void rk_enc(string ifile_name, string ofile_name)
{
    // "Uncomment* this by repladcing 0 with 1 when you are ready to 
    // implement it. Leave it uncommented when you are ready to submit it.
    #if 1
    string plain_text;
    unsigned int page;
    vector<string> cont;
    // Read in the cipher key. For the Running Key cipher, this is typically
    // a book and a page number. The input file must contain
    // the page number in line 1, and 
    // the book in the next N lines. The book consists of N pages, where each
    // line is considered a page.
    // The last line should contain the plain text.
    // Use a vector to store the book, where each element in the vector
    // corresponds to a page
    load_rk_input(ifile_name, page, cont, plain_text);

    // Create a Cipher class object and use it to encrypt and decrypt
    // the plain text
    // First, initialize it with the first page of the book
    KCipher my_kcipher(cont[0]);
    // Then add the subsequent pages using a loop and the add_key member 
    // function
    for(unsigned int i = 1; i < cont.size(); i++) {
        my_kcipher.add_key(cont[i]);
    }
    // Lastly, set the page. If the page is not set, the default page should be
    // 1 (or 0, since we are using C/C++)
    my_kcipher.set_id(page);

    // Encrypt andd decrypt the plain text.
    string cipher_text = my_kcipher.encrypt(plain_text);
    string decrypt_text = my_kcipher.decrypt(cipher_text);

    // Also, create a Running Key Cipher class object using the default 
    // constructor
    // This should be a one-page book, and the page should be MAX_LENGTH 
    // characters long. The key should be such that when the plain text
    // is encrypted, the cipher text should be identical to the plain text
    KCipher my_def_kcipher;
    string def_cipher_text = my_def_kcipher.encrypt(plain_text);
    string def_decrypt_text = my_def_kcipher.decrypt(def_cipher_text);

    // Store the output to files
    store_output(ofile_name, cipher_text, decrypt_text, wr);
    store_output(ofile_name, def_cipher_text, def_decrypt_text, ap);
    #endif
}
void load_rk_input(string ifile_name, unsigned int& page, vector<string>& cont,
                   string& plain_text)
{
    ifstream inFile(ifile_name);

    string line;
    // Read in the page number
    getline(inFile, line);
    stringstream p(line);
    p >> page;
   
    // Read in the book, one page (or line) at a time, and store
    // it in the vector
    while(getline(inFile, line)) {
        cont.push_back(line);
    }

    // Since the last page is the plain text, copy it to
    // plain_text and then remove it from the vector
    plain_text = cont.back();
    cont.erase(cont.end() - 1);
    inFile.close();
}


/* This function encrypts and decrypts the input (plain) text
   using the Vigenere cipher.
 */
void vigenere_enc(string ifile_name, string ofile_name)
{
    // "Uncomment* this by repladcing 0 with 1 when you are ready to 
    // implement it. Leave it uncommented when you are ready to submit it.
    #if 0
    string plain_text;
    string keyword;
    // Read in the cipher alphabet and the plain text to encrypt
    // The input file must contain 
    // the cipher key in line 1, and
    // the plain text to encrypt in line 2
    load_vig_input(ifile_name, keyword, plain_text);

    // Create a VCipher class object and use it to encrypt and decrypt
    // the plain text
    VCipher my_vcipher(keyword);
    string cipher_text = my_vcipher.encrypt(plain_text);
    string decrypt_text = my_vcipher.decrypt(cipher_text);

    // Also, create a Cipher class object using the default constructor
    VCipher my_def_vcipher;
    string def_cipher_text = my_def_vcipher.encrypt(plain_text);
    string def_decrypt_text = my_def_vcipher.decrypt(def_cipher_text);

    // Store the output to files
    store_output(ofile_name, cipher_text, decrypt_text, wr);
    store_output(ofile_name, def_cipher_text, def_decrypt_text, ap);
    #endif
}
void load_vig_input(string ifile_name, string& keyword, string& plain_text)
{
    ifstream inFile(ifile_name);

    // Read in the cipher key
    string line;
    getline(inFile, line);
    keyword = line;

    // Read in the plain text
    getline(inFile, line);
    plain_text = line;
    inFile.close();

}


void store_output(string ofile_name, string cipher_text, string decrypt_text,
                  write_mode wm)
{
    if(wm == wr) {
        ofstream outFile(ofile_name);
        outFile << cipher_text << endl;
        outFile << decrypt_text << endl;
        outFile.close();
    } else {
        ofstream outFile;
        outFile.open(ofile_name, ios::app);
        outFile << cipher_text << endl;
        outFile << decrypt_text << endl;
        outFile.close();
    }
}

