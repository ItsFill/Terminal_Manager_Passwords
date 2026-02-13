cmake_minimum_required(VERSION 4.1)
project(TerminalManagerPasswords)

set(CMAKE_CXX_STANDARD 20)

add_executable(TerminalManagerPasswords main.cpp
        File/file.h
        Encryption/Encryption.h
        TUI/TUI.h
        Date_Type/Date_Type.h)
