#pragma once
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <cryptopp/rc6.h>
#include <cryptopp/pwdbased.h>
#include "cryptopp/modes.h"
#include <string>
#include <fstream>
using namespace std;
using namespace CryptoPP;

class Rc6
{
private:
    string in;
    string out;
    string pass;
    string IVector;
public:
    Rc6(const string f_in, const string f_out, const string Pass);
    Rc6(const string f_in, const string f_out, const string f_iv, const string Pass);
    void encryptRc6 ();
    void decryptRc6 ();
};
