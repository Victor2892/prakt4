#include "seed.h"
seed::seed(const string f_in, const string f_out, const string Pass)
{
    in = f_in;
    out = f_out;
    pass = Pass;
}
seed::seed(const string f_in, const string f_out, const string  f_iv, const string Pass)
{
    in = f_in;
    out = f_out;
    IVector = f_iv;
    pass = Pass;
}
void seed::encryptSeed ()
{
    string salt = "qqqewxvcv.bml;hjgf;khj;lk;";
    SecByteBlock key(SEED::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA512> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)pass.data(), pass.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);

    byte iv[SEED::BLOCKSIZE];
    ofstream IV(string(out + ".iVector").c_str(), ios::out | ios::binary);
    IV.write((char*)iv, SEED::BLOCKSIZE);
    IV.clear();
    IV.close();
    cout << "Файл c вектором инициализации успешно создан. Его путь: " << out << ".iVector" << endl;

    CBC_Mode<SEED>::Encryption encr;
    encr.SetKeyWithIV(key, key.size(), iv);
    FileSource fs(in.c_str(), true, new StreamTransformationFilter(encr, new FileSink(out.c_str())));
    cout << "Шифрование проведено успешно.\nРезультат находится по следующему пути: " << out << endl;
}
void seed::decryptSeed ()
{
    string salt = "qqqewxvcv.bml;hjgf;khj;lk;";
    SecByteBlock key(SEED::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA512> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)pass.data(), pass.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);

    byte iv[SEED::BLOCKSIZE];
    ifstream IV(IVector.c_str(), ios::in | ios::binary);
    IV.read((char*)(&iv), SEED::BLOCKSIZE);
    IV.clear();
    IV.close();

    CBC_Mode<SEED>::Decryption decr;
    decr.SetKeyWithIV(key, key.size(), iv);
    FileSource fs(in.c_str(), true, new StreamTransformationFilter(decr, new FileSink(out.c_str())));
    cout << "Расшифрование проведено успешно.\nРезультат находится по следующему пути: " << out << endl;
}
