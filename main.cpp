#include <iostream>
#include <string>

#include "TUI/TUI.h"
#include "File/File.h"
#include "Encryption/Encryption.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    //MAKE COUT AND CIN FASTER
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    //FOR SYMBOLS AND BEAUTY DESIGN
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    //GET READY US APP
    TUI ui;
    File db;
    std::string masterPass;

    //START APP
    ui.first();
    std::cin >> masterPass;


    Encryptor enc(masterPass);

    bool isRunning = true;
    while (isRunning) {
        ui.commands();

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    ui.add();
                    std::string res, user, pass;
                    std::cin >> res >> user >> pass;
                    db.add(enc, res, user, pass);
                    break;
                }
                case 2: {
                    ui.search();
                    std::string target;
                    std::cin >> target;
                    db.search(enc, target);

                    std::cout << "\n  Press Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }
                case 3: {
                    ui.remove();
                    std::string target;
                    std::cin >> target;
                    db.remove(enc, target);
                    break;
                }
                case 4: {
                    ui.list();
                    db.list(enc);
                    std::cout << "\n  Press Enter to return to menu...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }
                case 0:
                    isRunning = false;
                    break;
                default:
                    break;
            }
        } catch (const Error_with_open& e) {
            std::cerr << "  [ERROR] Could not open database file! \n";
            std::cin.get();
        }
    }

    //END APP
    std::cout << "  Vault secured. Goodbye!\n";
    return 0;
}