#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
using namespace CryptoPP;
int main ()
{
    SHA1 hash;
    cout <<"Name: " << hash.AlgorithmName() << endl;
    cout << "Diget size:" << hash.DigestSize() << endl;
    cout << "Block size:" << hash.BlockSize() << endl;
    string str, contents;
    fstream f;
    f.open("/home/student/hash.txt");
    while(true) {
        getline(f, str);
        if (f.fail())
            break;
        contents = contents + str;
    }
    cout << "Содержимое файла: " << contents << endl;

    vector<byte> digest (hash.DigestSize());
    
    hash.Update((const byte*)(contents.data()),contents.size());
    hash.Final(digest.data());
    
    cout << "Digest format HEX: ";
    StringSource(digest.data(),digest.size(),true, new  HexEncoder(new  FileSink(cout)));
    cout << endl;
    return 0;
}
