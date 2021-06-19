#pragma once
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <cryptopp/seed.h>
#include <cryptopp/pwdbased.h>
#include "cryptopp/modes.h"
#include <string>
#include <fstream>
using namespace std;
using namespace CryptoPP;

class seed
{
private:
    string in;
    string out;
    string pass;
    string IVector;
public:
    seed(const string f_in, const string f_out, const string Pass);
    seed(const string f_in, const string f_out, const string f_iv, const string Pass);
    void encryptSeed ();
    void decryptSeed ();
};
