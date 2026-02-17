#ifndef TERMINALMANAGERPASSWORDS_DATE_TYPE_H
#define TERMINALMANAGERPASSWORDS_DATE_TYPE_H

#include <string>
#include "../Encryption/Encryption.h"

struct Error {
    std::string name;

    Error(std::string msg) : name(msg) {}

    const char* what() const {
        return name.c_str();
    }
};

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

    friend std::istream& operator>>(std::istream& in, Entry& e) {
        std::string s, n, p;

        if (!(in >> s >> n >> p)) {
            return in;
        }
        if (s.length() > 20) {
            throw Error("Invalid service length, max length is a 20 symbols");
        } else if (n.length() < 50) {
            throw Error("Invalid nickname length, max length is a 50 symbols");
        } else if (p.length() < 50) {
            throw Error("Invalid password length, max length is a 50 symbols");
        }

        e.service = s;
        e.nickname = n;
        e.password = p;

        return in;
    }

    void check() {
        if (service.length() > 15 && nickname.length() > 50 && password.length() > 100) {
            throw Error("Maybe your dates wad bigger than expected");
        }
    }
};

#endif //TERMINALMANAGERPASSWORDS_DATE_TYPE_H