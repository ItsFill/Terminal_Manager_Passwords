#ifndef TERMINALMANAGERPASSWORDS_GUI_H
#define TERMINALMANAGERPASSWORDS_GUI_H

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
        std::cout << "\033[2J\033[H";
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
        std::cout << "  >  ";
    }

    void add() {
        std::cout << "\033[2J\033[H";
        std::cout << "  ┌──────────────────────────────────────────────────────────┐\n";
        std::cout << "  │   CRYPT-VAULT v1.0 | ACTION: ADD NEW ENTRY               │\n";
        std::cout << "  ├──────────────────────────────────────────────────────────┤\n";
        std::cout << "  │   Template:                                              │\n";
        std::cout << "  │      - Resource Username Password                        │\n";
        std::cout << "  └──────────────────────────────────────────────────────────┘\n";
        std::cout << "  >  ";
    }
    void search() {
        std::cout << "\033[2J\033[H";
        std::cout << "  ┌──────────────────────────────────────────────────────────┐\n";
        std::cout << "  │   CRYPT-VAULT v1.0 | ACTION: DATABASE SEARCH             │\n";
        std::cout << "  ├──────────────────────────────────────────────────────────┤\n";
        std::cout << "  │                                                          │\n";
        std::cout << "  │                    ENTER RESOURCE                        │\n";
        std::cout << "  │                                                          │\n";
        std::cout << "  └──────────────────────────────────────────────────────────┘\n";
        std::cout << "  >  ";
    }
    void remove() {
        std::cout << "\033[2J\033[H";
        std::cout << "  ┌──────────────────────────────────────────────────────────┐\n";
        std::cout << "  │   CRYPT-VAULT v1.0 | ACTION: PERMANENT REMOVAL           │\n";
        std::cout << "  ├──────────────────────────────────────────────────────────┤\n";
        std::cout << "  │   WARNING: Data removal cannot be undone.                │\n";
        std::cout << "  │                                                          │\n";
        std::cout << "  │                    ENTER RESOURCE                        │\n";
        std::cout << "  │                                                          │\n";
        std::cout << "  └──────────────────────────────────────────────────────────┘\n";
        std::cout << "  >  ";
    }
    void list() {
        std::cout << "\033[2J\033[H";
        std::cout << "  ┌──────────────────────────────────────────────────────────┐\n";
        std::cout << "  │   CRYPT-VAULT v1.0 | ACTION: ALL ENTRIES                 │\n";
        std::cout << "  ├──────────┬────────────────────┬──────────────────────────┤\n";
        std::cout << "  │   RES    │      USERNAME      │         PASSWORD         │\n";
        std::cout << "  ├──────────┼────────────────────┼──────────────────────────┤\n";
    }
};

#endif //TERMINALMANAGERPASSWORDS_GUI_H
