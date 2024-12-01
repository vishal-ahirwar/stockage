
// Auto Genrated C++ file by ccli CLI
// Copyright 2023 Vishal Ahirwar //replace it with your copyright notice!
#include <iostream>
#include <stokage.hxx>
#include <filesystem>
#define FILE_NAME "data.xork"
int main(int argc, char *argv[])
{
    // Test
    Stokage stokage;
    namespace fs = std::filesystem;
    if (fs::exists(FILE_NAME))
    {
        std::cout << "Enter Decryption key : ";
        int key{};
        std::cin >> key;
        std::string out;
        stokage.readBinary(out,FILE_NAME, key);
        std::cout << out << "\n";
    }
    else
    {
        std::cout << "Enter Encryption key : ";
        int key{};
        std::cin >> key;
        std::cout << "Enter your msg : ";
        std::cin.clear();
        std::cin.ignore();
        std::string msg{};
        std::getline(std::cin, msg);
        stokage.writeBinary(msg, FILE_NAME, key);
    }

    return 0;
};
