#include <iostream>
#include <string>

#include "TUI/TUI.h"
#include "File/File.h"
#include "Date_Type/Date_Type.h"
#include "Encryption/Encryption.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    //MAKE COUT AND CIN FASTER

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
    std::string masterPass;

    //START APP
    ui.first();
    std::cin >> masterPass;

    Encryptor enc(masterPass);

    Entry de(enc);
    File db(enc);

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
                    std::cin >>de;
                    db.add(de);
                    break;
                }
                case 2: {
                    ui.search();
                    std::string target;
                    std::cin >> target;
                    db.search(target);

                    std::cout << "\n  Press Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }
                case 3: {
                    ui.remove();
                    std::string target;
                    std::cin >> target;
                    db.remove(target);
                    break;
                }
                case 4: {
                    ui.list(enc, db);
                    db.list();
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
        } catch (const Error_file_open &e) {
            std::cerr << "  [ERROR] Could not open database file! \n";
            std::cin.get();
        } catch (const Error &e) {
            std::cerr << "  [ERROR] " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "  Press Enter to try again...";
            std::cin.get();
        }
    }

    //END APP
    std::cout << "  Vault secured. Goodbye!\n";
    return 0;
}
