#include <windows.h>
#include <iostream>
#include "./File/File.h"
#include "./Encryption/Encryption.h"
#include "./TUI/TUI.h"


int main() {

    //On support of UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    //On processing of ANSI-Sequences

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    File file;
    TUI tui;

    return 0;
}