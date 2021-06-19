#include "Rc6.h"
Rc6::Rc6(const string f_in, const string f_out, const string Pass)
{
    in = f_in;
    out = f_out;
    pass = Pass;
}
Rc6::Rc6(const string f_in, const string f_out, const string  f_iv, const string Pass)
{
    in = f_in;
    out = f_out;
    IVector = f_iv;
    pass = Pass;
}
void Rc6::encryptRc6 ()
{
    string salt = "dsagjfdkljghkmbvc.bml;hjgf;khj;lk;";
    SecByteBlock key(RC6::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA384> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)pass.data(), pass.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);

    byte iv[RC6::BLOCKSIZE];
    ofstream IV(string(out + ".iVector").c_str(), ios::out | ios::binary);
    IV.write((char*)iv, RC6::BLOCKSIZE);
    IV.clear();
    IV.close();
    cout << "Файл c вектором инициализации успешно создан. Его путь: " << out << ".iVector" << endl;

    CBC_Mode<RC6>::Encryption encr;
    encr.SetKeyWithIV(key, key.size(), iv);
    FileSource fs(in.c_str(), true, new StreamTransformationFilter(encr, new FileSink(out.c_str())));
    cout << "Шифрование проведено успешно.\nРезультат находится по следующему пути: " << out << endl;
}
void Rc6::decryptRc6 ()
{
    string salt = "dsagjfdkljghkmbvc.bml;hjgf;khj;lk;";
    SecByteBlock key(RC6::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA384> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)pass.data(), pass.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);

    byte iv[RC6::BLOCKSIZE];
    ifstream IV(IVector.c_str(), ios::in | ios::binary);
    IV.read((char*)(&iv), RC6::BLOCKSIZE);
    IV.clear();
    IV.close();

    CBC_Mode<RC6>::Decryption decr;
    decr.SetKeyWithIV(key, key.size(), iv);
    FileSource fs(in.c_str(), true, new StreamTransformationFilter(decr, new FileSink(out.c_str())));
    cout << "Расшифрование проведено успешно.\nРезультат находится по следующему пути: " << out << endl;
}
