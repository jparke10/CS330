#include <string>
#include <iostream>
#include "rcipher.h"

// -------------------------------------------------------
// ROT13 Cipher implementation
// -------------------------------------------------------

RCipher::RCipher() : CCipher(13) {}

RCipher::~RCipher() {}

// no need to overload CCipher encrypt/decrypt functions
