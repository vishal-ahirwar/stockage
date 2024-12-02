#include <appmanager.hxx>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <string.h>
#include<colors.hpp>
AppManager::AppManager() : key{0}
{
    std::cout<<YELLOW;
    std::cout << "Welcome this is Stockage Menu:\n";
    std::cout << "1." << " Add new entry to stockage\n";
    std::cout << "2." << " Delete old entry\n";
    std::cout << "3." << " View your whole data\n";
    std::cout << "4." << " Delete all of your stockage data\n"<<WHITE;
}
int AppManager::run(int argc, char **argv)
{
    std::cout <<GREEN<<": ";
    int input{};
    readInteger(input);
    switch (input)
    {
    case 1:
    {
        askKey();
        std::string new_entry{};
        readMultiLineString(new_entry);
        addNewEntry(new_entry);
        break;
    }
    case 2:
    {
        askKey();
        std::cout <<GREEN<<"ID:>";
        int id;
        readInteger(id);
        deleteOldEntry(id);
        break;
    }

    case 3:
        askKey();
        viewData();
        break;
    case 4:
        deleteAll();
        break;
    default:
        break;
    }
    return 0;
}
void AppManager::addNewEntry(std::string &entry)
{
    entry += ";";
    std::string sep{";" + entry};
    stokage.writeBinary(sep, getStockagePath(), key, std::ios::app | std::ios::out);
}
void AppManager::deleteOldEntry(int id)
{
    std::cout <<RED<< "Not Available!\n"<<WHITE;
    // askKey();
    // // TODO
}
void AppManager::viewData()
{
    std::string entries{};
    stokage.readBinary(entries, getStockagePath(), key);
    std::istringstream ss(entries);
    std::string str{};
    while (std::getline(ss, str, ';'))
    {
        if(isprint(str[0]))
        std::cout <<GREEN<< str << "\n";
    };
    std::cout<<WHITE;
};

void AppManager::deleteAll()
{
    std::cout <<BLUE<< "You can't delete the aura from stockage, file is saved here " <<RED<< getStockagePath() <<BLUE<< " delete it manualy!\n"<<WHITE;
};

void AppManager::readMultiLineString(std::string &new_entry)
{
    std::cout <<GREEN<< "type ; to stop:>\n"<<WHITE;
    std::cin.ignore();
    std::cin.clear();
    while (true)
    {
        std::string line{};
        std::getline(std::cin, line);
        if (line == ";")
            break;
        new_entry += line;
    };
}
void AppManager::askKey()
{
    int flag{};
    do
    {
        std::cout <<BLUE<<"Key: ";
        readInteger(key);
        std::cout <<YELLOW<< "Warning: Double check it please even if one digit is incorrect whole aura data will get corrupt\nAre you sure key is correct?0(n)/1(y)\n"<<WHITE;
        std::cout << GREEN<<": ";
        readInteger(flag);
    } while (flag != 1);
}
void AppManager::readInteger(int &input)
{
    while (true)
    {
        std::cin >> input;

        // Check if the input is valid
        if (std::cin.fail())
        {
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout <<RED<< "Invalid input. Please enter an integer: "<<WHITE;
        }
        else
        {
            break; // Input is valid, exit the loop
        }
    }
};

std::string AppManager::getStockagePath() const
{
#ifdef WIN32
#define USER_NAME "USERPROFILE"
#else
#define USER_NAME "USER"
#endif

    std::string user_name{getenv(USER_NAME)};

#ifdef WIN32
    std::string path{user_name + "\\stockage"};
#else
    std::string path{"/home/" + user_name + "/stockage"};
#endif

    namespace fs = std::filesystem;

    if (!fs::exists(path))
    {
        fs::create_directory(path);
    };
#ifdef WIN32
    return path + "\\data.aura";
#else
    return path + "/data.aura";
#endif
};
