#ifndef TERMINALMANAGERPASSWORDS_ENCRYPTION_H
#define TERMINALMANAGERPASSWORDS_ENCRYPTION_H

#include <iostream>
#include <string>

class Encryptor {
    std::string master_pass;
    int key;

public:
    Encryptor(std::string master_pass) : master_pass(master_pass) {
        key = 0;
        for (int i = 0; i < master_pass.length(); i++) {
            key += (int) master_pass[i] * (i + 1);
        }
    }

    Encryptor() : Encryptor("") {}

    void operator=(const Encryptor &other) {
        this->master_pass = other.master_pass;
        this->key = other.key;
    }

    void encrypt(std::string &line) {
        char byte_key = static_cast<char>(key % 256);
        for (int i = 0; i < line.length(); i++) {
            line[i] ^= byte_key;
        }
    }
};

#endif //TERMINALMANAGERPASSWORDS_ENCRYPTION_H
