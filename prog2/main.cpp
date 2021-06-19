#include "Rc6.h"
#include "seed.h"
#include <iostream>

int main(int argc, char **argv)
{
    int end = 1;
    string r;
    string f_in, f_out, iVector, pass;
    cout << "Добро пожаловать в программу!" << endl;
    cout << "Справки о  работе программы:" << endl;
    cout << "eRC6 - операция зашифрования с использованием алгоритма RC6" << endl;
    cout << "dRC6 - операция расшифрования с использованием алгоритма RC6" << endl;
    cout << "eSEED - операция зашифрования с использованием алгоритма SEED" << endl;
    cout << "dSEED - операция расшифрования с использованием алгоритма SEED" << endl;
    cout << "exit - для выхода из программы" << endl;
    while (end != 2) {
        cout << "Укажите операцию: ";
        cin >> r;
        if (r == "eRC6") {
            cout << "Укажите путь до файла: ";
            cin >> f_in;
            cout << "Укажите путь до файла для результата: ";
            cin >> f_out;
            cout << "Укажите пароль: ";
            cin >> pass;
            try {
                Rc6 e(f_in,f_out,pass);
                e.encryptRc6();
            }  catch (const CryptoPP::Exception & ex) {
                cout << ex.what() << endl;
            }
        }
        if (r == "dRC6") {
            cout << "Укажите путь до файла: ";
            cin >> f_in;
            cout << "Укажите путь до файла для результата: ";
            cin >> f_out;
            cout << "Укажите путь до файла, в котором находится вектор инициализации: ";
            cin >> iVector;
            cout << "Укажите пароль: ";
            cin >> pass;
            try {
                Rc6 d(f_in,f_out, iVector, pass);
                d.decryptRc6();
            }  catch (const CryptoPP::Exception & ex) {
                cout << ex.what() << endl;
            }
        }
        if (r == "eSEED") {
            cout << "Укажите путь до файла: ";
            cin >> f_in;
            cout << "Укажите путь до файла для результата: ";
            cin >> f_out;
            cout << "Укажите пароль: ";
            cin >> pass;
            try {
                seed e(f_in,f_out,pass);
                e.encryptSeed();
            }  catch (const CryptoPP::Exception & ex) {
                cout << ex.what() << endl;
            }
        }
        if (r == "dSEED") {
            cout << "Укажите путь до файла: ";
            cin >> f_in;
            cout << "Укажите путь до файла для результата: ";
            cin >> f_out;
            cout << "Укажите путь до файла, в котором находится вектор инициализации: ";
            cin >> iVector;
            cout << "Укажите пароль: ";
            cin >> pass;
            try {
                seed d(f_in,f_out, iVector, pass);
                d.decryptSeed();
            }  catch (const CryptoPP::Exception & ex) {
                cout << ex.what() << endl;
            }
        }
        if (r == "exit") {
            cout << "Завершение работы" << endl;
            end = 2;
            break;
        }
    }
    return 0;
}
