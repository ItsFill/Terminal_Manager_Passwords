#ifndef TERMINALMANAGERPASSWORDS_DATE_TYPE_H
#define TERMINALMANAGERPASSWORDS_DATE_TYPE_H

#include <string>
#include "../Encryption/Encryption.h"

class Entry {
    std::string service;
    std::string nickname;
    std::string password;
    Encryptor enc;

public:
    Entry(Encryptor other, std::string s, std::string n, std::string p) : service(s), password(p), nickname(n) {
        enc = other;
    }

    Entry(Encryptor other) : service(""), password(""), nickname("") {
        enc = other;
    }


    void set(std::string s, std::string n, std::string p) {
        service = s;
        nickname = n;
        password = p;
    }

    void set(std::string str, short type) {
        if (type == 1) {
            service = str;
        } else if (type == 2) {
            nickname = str;
        } else {
            password = str;
        }
    }

    std::string get_service() const { return service; }
    std::string get_nickname() const { return nickname; }
    std::string get_password() const { return password; }

    //LOCK AND UNLOCK IS SAME THING, IT'S FOR MORE COMFORT IN CODE

    void lock() {
        enc.encrypt(nickname);
        enc.encrypt(password);
    }

    void unlock() {
        enc.encrypt(nickname);
        enc.encrypt(password);
    }
};

#endif //TERMINALMANAGERPASSWORDS_DATE_TYPE_H
