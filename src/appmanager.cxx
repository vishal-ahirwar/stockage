#include <appmanager.hxx>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <colors.hpp>

AppManager::AppManager() : key{0}
{
    showHelp();
}
int AppManager::run(int argc, char **argv)
{
    int input{};
    readInteger("Command No.",input);
    if(input<0)return 0;
    while (true)
    {
        switch (input)
        {
        case 1:
        {
            askKey("Add New Entry key");
            std::string new_entry{};
            readMultiLineString(new_entry);
            addNewEntry(new_entry);
            break;
        }
        case 2:
        {
            askKey("Delete Data Key");
            int id;
            readInteger("Delete Data<ID>",id);
            deleteOldEntry(id);
            break;
        }

        case 3:
            askKey("View Data Key");
            viewData();
            break;
        case 4:
            deleteAll();
            break;
        case 5:
            showHelp();
            break;
        default:
            std::cout << RED << "Invalid Input!\n"
                      << WHITE;
            break;
        };
        readInteger("Command No.",input);
        if (input < 0)
            break;
    }

    return 0;
}
void AppManager::addNewEntry(std::string &entry)
{
    std::string sep{"<:>" + entry};
    std::istringstream ss(sep);
    std::string valid_string{};
    std::string temp_string{};
    while(std::getline(ss,temp_string,';'))
    {
        valid_string+=temp_string;
    };
    valid_string+=';';
    stokage.writeBinary(valid_string, getStockagePath(), key, std::ios::app | std::ios::out);
}
void AppManager::deleteOldEntry(int id)
{
    std::cout << RED << "Not Available!\n"
              << WHITE;
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
        if (auto pos = str.find("<:>"); pos != std::string::npos)
            std::cout << GREEN << str.substr(pos + 3) << "\n";
    };
    std::cout << WHITE;
};

void AppManager::deleteAll()
{
    std::cout << BLUE << "You can't delete the aura from stockage, file is saved here " << RED << getStockagePath() << BLUE << " delete it manualy!\n"
              << WHITE;
};

void AppManager::readMultiLineString(std::string &new_entry)
{
    std::cout << GREEN << "type ; to stop:>\n"
              << WHITE;
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
void AppManager::askKey(std::string why_str)
{
    int flag{};
    do
    {
        readInteger("<"+why_str+">:",key);
        std::cout << YELLOW << "Warning: Double check it please even if one digit is incorrect whole aura data will get corrupt\nAre you sure key is correct?\n"
                  << WHITE;

        readInteger("0(n)/1(y)",flag);
    } while (flag != 1);
}
void AppManager::showHelp()
{
    std::cout << YELLOW;
    std::cout << "Welcome this is Stockage Menu:\n";
    std::cout << "1." << " Add new entry to stockage\n";
    std::cout << "2." << " Delete old entry\n";
    std::cout << "3." << " View your whole data\n";
    std::cout << "4." << " Delete all of your stockage data\n";
    std::cout << "5." << " Show help\n";
    std::cout << "?." << "Any Negative number to quit\n" << WHITE;
}
void AppManager::readInteger(std::string why_str,int &input)
{
    while (true)
    {
        std::cout<<why_str<<": ";
        std::cin >> input;

        // Check if the input is valid
        if (std::cin.fail())
        {
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << RED << "Invalid input. Please enter an integer\n:" << WHITE;
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
