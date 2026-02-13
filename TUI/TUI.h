#ifndef TERMINALMANAGERPASSWORDS_GUI_H
#define TERMINALMANAGERPASSWORDS_GUI_H

#include <windows.h>
#include <iostream>

class TUI {
public:
    void first() {
        std::cout << "\033[2J\033[H";

        std::cout << "  ┌──────────────────────────────────────────────────────────┐\n";
        std::cout << "  │                                                          │\n";
        std::cout << "  │     CRYPT-VAULT v1.0                                     │\n";
        std::cout << "  │                                                          │\n";
        std::cout << "  └──────────────────────────────────────────────────────────┘\n";
        std::cout << "  Please enter your Master Password to unlock:  ";
        std::cout << "  >  ";
    }
    void commands() {
        std::cout << "  ┌──────────────────────────────────────────────────────────┐\n";
        std::cout << "  │   CRYPT-VAULT v1.0 | Status: SECURED                     │\n";
        std::cout << "  ├──────────────────────────────────────────────────────────┤\n";
        std::cout << "  │                                                          │\n";
        std::cout << "  │   1. ADD                                                 │\n";
        std::cout << "  │   2. SEARCH                                              │\n";
        std::cout << "  │   3. REMOVE                                              │\n";
        std::cout << "  │   4. LIST                                                │\n";
        std::cout << "  │   0. EXIT                                                │\n";
        std::cout << "  │                                                          │\n";
        std::cout << "  └──────────────────────────────────────────────────────────┘\n";
        std::cout << "  Selection > ";
    }
};

#endif //TERMINALMANAGERPASSWORDS_GUI_H
