#ifndef TERMINALMANAGERPASSWORDS_FILE_H
#define TERMINALMANAGERPASSWORDS_FILE_H

#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>

#include "../Date_Type/Date_Type.h"
#include "../Encryption/Encryption.h"

struct Error_file_open {
    std::string name;
};

class File {
    std::string name;
    Encryptor enc;

    std::vector<std::string> smasher(std::string text) {
        std::vector<std::string> temp_vector;
        std::string temp_text;

        if (text.length() < 3) {
            temp_vector.push_back(text);
            return temp_vector;
        }

        for (unsigned int i = 0; i < text.length() - 3; i++) {
            temp_vector.push_back(text.substr(i, 3));
        }

        return temp_vector;
    }

public:
    File(Encryptor &other) {
        enc = other;
        name = "dates.txt";
    }


    void add(Entry &account) {
        std::ofstream file;

        file.open(name, std::ios::app | std::ios::binary);

        if (!file.is_open()) { throw Error_file_open("Error"); }

        account.lock();

        file << account.get_service() << "\t" << account.get_nickname() << "\t" << account.get_password() << "\n";

        file.close();
    }

    void add(const std::string &service, const std::string &nickname, const std::string &pass) {
        Entry temp(enc);
        temp.set(service, nickname, pass);

        add(temp);
    }


    std::vector<Entry> list() {
        std::ifstream file(name, std::ios::in | std::ios::binary);

        if (!file.is_open()) { throw Error_file_open("Error"); }
        std::string temp_a, temp_b, temp_c;
        std::vector<Entry> accounts;

        while (std::getline(file, temp_a, '\t')
               && std::getline(file, temp_b, '\t')
               && std::getline(file, temp_c, '\n')) {

            Entry temp(enc, temp_a, temp_b, temp_c);

            temp.unlock();

            accounts.push_back(temp);
        }

        file.close();

        return accounts;
    }


    void remove(const std::string target_service) {
        //OPEN BLOCK FILE TO READ

        Entry temp(enc);

        //MAKE TARGET SERVICE TO LOWER
        std::string temp_service = target_service;
        std::transform(temp_service.begin(), temp_service.end(), temp_service.begin(),
                       [](char c) { return std::tolower(c); });

        std::string temp_a, temp_b, temp_c;

        std::ifstream file_read;

        file_read.open(name, std::ios::in | std::ios::binary);
        if (!file_read.is_open()) { throw Error_file_open("Error"); }

        std::vector<Entry> accounts;


        while (std::getline(file_read, temp_a, '\t')
               && std::getline(file_read, temp_b, '\t')
               && std::getline(file_read, temp_c, '\n')) {

            temp.set(temp_a, temp_b, temp_c);

            temp.unlock();

            accounts.push_back(temp);
        }

        file_read.close();

        //DELETE BLOCK ACCOUNT WHICH WE NEEDN'T

        for (auto i = accounts.begin(); i != accounts.end();) {
            std::string check_name = i->get_service();
            std::transform(check_name.begin(), check_name.end(), check_name.begin(),
                           [](char c) { return std::tolower(c); });
            if (check_name == temp_service) {
                i = accounts.erase(i);
            } else {
                i->lock();
                ++i;
            }
        }

        //REWRITE BLOCK UPDATE IN US FILE

        std::ofstream file_write;

        file_write.open(name, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!file_write.is_open()) { throw Error_file_open("Error"); }

        for (auto i = accounts.begin(); i != accounts.end(); i++) {
            file_write << i->get_service() << "\t" << i->get_nickname() << "\t" << i->get_password() << "\n";
        }

        file_write.close();
    }


    void search(std::string target_service) {
        std::ifstream file;

        file.open(name, std::ios::in | std::ios::binary);

        if (!file.is_open()) { throw Error_file_open("Error"); }

        std::transform(target_service.begin(), target_service.end(), target_service.begin(),
                       [](char c) { return std::tolower(c); });

        std::vector<std::string> smashed_service = smasher(target_service);

        Entry temp(enc);

        std::string temp_a, temp_b, temp_c;

        while (std::getline(file, temp_a, '\t')
               && std::getline(file, temp_b, '\t')
               && std::getline(file, temp_c, '\n')) {
            std::string lower_service = temp_a;
            std::transform(lower_service.begin(), lower_service.end(), lower_service.begin(),
                           [](char c) { return std::tolower(c); });

            int counter = 0;
            for (const auto &i: smashed_service) {
                if (lower_service.find(i) != std::string::npos) {
                    counter++;
                }
            }

            double score = static_cast<double>(counter) / smashed_service.size();

            if (score > 0.5 || lower_service.find(target_service) != std::string::npos) {

                temp.set(temp_a, temp_b, temp_c);
                temp.unlock();

                std::cout << "\033[2J\033[H";
                std::cout << "  ┌──────────────────────────────────────────────────────────┐\n";
                std::cout << "  │   CRYPT-VAULT v1.0 | ACTION: SEARCH RESULTS              │\n";
                std::cout << "  ├──────────┬────────────────────┬──────────────────────────┤\n";
                std::cout << "  │   SERVICE│      USERNAME      │         PASSWORD         │\n";
                std::cout << "  ├──────────┼────────────────────┼──────────────────────────┤\n";
                std::cout << "  │ " << std::setw(8) << std::left << temp.get_service()
                        << " │ " << std::setw(18) << std::left << temp.get_nickname()
                        << " │ " << std::setw(24) << std::left << temp.get_password() << " │\n";
                std::cout << "  └──────────┴────────────────────┴──────────────────────────┘\n";
            }
        }
    }
};
#endif //TERMINALMANAGERPASSWORDS_FILE_H
