#ifndef TERMINALMANAGERPASSWORDS_FILE_H
#define TERMINALMANAGERPASSWORDS_FILE_H

#include <string>
#include <vector>
#include <fstream>
#include "../Date_Type/Date_Type.h"
#include "../Encryption/Encryption.h"

struct Error_with_open {
    std::string name;
};

class File {
    std::string name;

public:
    File() {
        name = "dates.txt";
    }


    void add(Encryptor &enc, Entry &account) {
        std::ofstream file;

        file.open(name, std::ios::app | std::ios::binary);

        if (!file.is_open()) { throw Error_with_open("Error"); }

        enc.encrypt(account.nickname);
        enc.encrypt(account.password);

        file << account.service << "\t" << account.nickname << "\t" << account.password << "\n";

        file.close();
    }

    void add(Encryptor &enc, const std::string &service, const std::string &nickname, const std::string &pass) {
        Entry temp = { service, nickname, pass };

        add(enc, temp);
    }


    void list(Encryptor &enc) {
        std::ifstream file(name, std::ios::in | std::ios::binary);

        if (!file.is_open()) { throw Error_with_open("Error"); }
        std::string temp_a, temp_b, temp_c;

        while (std::getline(file, temp_a, '\t')
            && std::getline(file, temp_b, '\t')
            && std::getline(file, temp_c, '\n') ) {

            enc.encrypt(temp_b);
            enc.encrypt(temp_c);

            std::cout << "Service: " << temp_a << " User name: " << temp_b << " Password: " << temp_c << "\n";

        }

        file.close();
    }


    void remove(Encryptor &enc, std::string target_service) {
        //OPEN FILE TO READ
        Entry temp;

        std::ifstream file_read;

        file_read.open(name, std::ios::in | std::ios::binary);
        if (!file_read.is_open()) { throw Error_with_open("Error"); }

        std::vector<Entry> accounts;

        while (std::getline(file_read, temp.service, '\t')
            && std::getline(file_read, temp.nickname, '\t')
            && std::getline(file_read, temp.password, '\n')) {

            enc.encrypt(temp.nickname);
            enc.encrypt(temp.password);

            accounts.push_back(temp);
        }

        file_read.close();

        //DELETE ACCOUNT WHICH WE NEEDN'T

        for (auto i = accounts.begin(); i != accounts.end();) {
            if (i->service == target_service) {
                i = accounts.erase(i);
            }
            else {
                enc.encrypt(i->nickname);
                enc.encrypt(i->password);
                ++i;
            }

        }

        //REWRITE UPDATE IN US FILE

        std::ofstream file_write;

        file_write.open(name, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!file_write.is_open()) { throw Error_with_open("Error"); }

        for (auto i = accounts.begin(); i != accounts.end(); i++) {
            file_write << i->service << "\t" << i->nickname << "\t" << i->password << "\n";
        }

        file_write.close();

    }
};

#endif //TERMINALMANAGERPASSWORDS_FILE_H
