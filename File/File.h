#ifndef TERMINALMANAGERPASSWORDS_FILE_H
#define TERMINALMANAGERPASSWORDS_FILE_H

#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>

#include "../Date_Type/Date_Type.h"
#include "../Encryption/Encryption.h"

struct Error_with_open {
    std::string name;
};

class File {
    std::string name;

    std::vector<std::string> smasher(std::string text) {
        std::vector<std::string> temp_vector;
        std::string temp_text;

        if (text.length() < 3) {
            temp_vector.push_back(text);
            return temp_vector;
        }

        for (unsigned int i = 0; i < text.length() - 3; i++) {
            temp_text = text.substr(i, 3);
        }

        return temp_vector;
    }

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

            std::cout << "  │ " << std::left << std::setw(8)  << temp_a.substr(0, 8)
                              << " │ " << std::left << std::setw(18) << temp_b.substr(0, 18)
                              << " │ " << std::left << std::setw(24) << temp_c.substr(0, 24)
                              << " │\n";
        }

        std::cout << "  └──────────┴────────────────────┴──────────────────────────┘\n";

        file.close();
    }


    void remove(Encryptor &enc, const std::string target_service) {

        //OPEN BLOCK FILE TO READ

        Entry temp;

        //MAKE TARGET SERVICE TO LOWER
        std::string temp_service = target_service;
        std::transform(temp_service.begin(), temp_service.end(), temp_service.begin(),
                    [] (char c) {return std::tolower(c); });

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

        //DELETE BLOCK ACCOUNT WHICH WE NEEDN'T

        for (auto i = accounts.begin(); i != accounts.end();) {
            std::string check_name = i->service;
            std::transform(check_name.begin(), check_name.end(), check_name.begin(),
                    [](char c) { return std::tolower(c); });
            if (check_name == temp_service) {
                i = accounts.erase(i);
            }
            else {
                enc.encrypt(i->nickname);
                enc.encrypt(i->password);
                ++i;
            }

        }

        //REWRITE BLOCK UPDATE IN US FILE

        std::ofstream file_write;

        file_write.open(name, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!file_write.is_open()) { throw Error_with_open("Error"); }

        for (auto i = accounts.begin(); i != accounts.end(); i++) {
            file_write << i->service << "\t" << i->nickname << "\t" << i->password << "\n";
        }

        file_write.close();

    }


    void search(Encryptor &enc, std::string target_service) {
        std::ifstream file;

        file.open(name, std::ios::in | std::ios::binary);

        if (!file.is_open()) { throw Error_with_open("Error"); }

        std::transform(target_service.begin(), target_service.end(), target_service.begin(),
                [] (char c) {return std::tolower(c); });

        std::vector<std::string> smashed_service = smasher(target_service);

        Entry temp;

        while (std::getline(file, temp.service, '\t')
                && std::getline(file, temp.nickname, '\t')
                && std::getline(file, temp.password, '\n')) {
            std::string lower_service = temp.service;
            std::transform(lower_service.begin(), lower_service.end(), lower_service.begin(),
                [] (char c) {return std::tolower(c); });

            int counter = 0;
            for (const auto &i : smashed_service) {
                if (lower_service.find(i) != std::string::npos) {
                    counter++;
                }
            }

            double score = (double)counter / (double)smashed_service.size();

            if (score > 0.5 || lower_service.find(target_service) != std::string::npos) {
                enc.encrypt(temp.nickname);
                enc.encrypt(temp.password);

                std::cout << "\033[2J\033[H";
                std::cout << "  ┌──────────────────────────────────────────────────────────┐\n";
                std::cout << "  │   CRYPT-VAULT v1.0 | ACTION: SEARCH RESULTS              │\n";
                std::cout << "  ├──────────┬────────────────────┬──────────────────────────┤\n";
                std::cout << "  │   SERVICE│      USERNAME      │         PASSWORD         │\n";
                std::cout << "  ├──────────┼────────────────────┼──────────────────────────┤\n";
                std::cout << "  │ " << std::setw(8)  << std::left << temp.service
                            << " │ " << std::setw(18) << std::left << temp.nickname
                            << " │ " << std::setw(24) << std::left << temp.password << " │\n";
                std::cout << "  └──────────┴────────────────────┴──────────────────────────┘\n";
            }
        }
    }
};
#endif //TERMINALMANAGERPASSWORDS_FILE_H