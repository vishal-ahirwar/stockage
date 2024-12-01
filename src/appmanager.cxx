#include <appmanager.hxx>
#include <filesystem>
#include <iostream>
#include <iomanip>

AppManager::AppManager() : key{0}
{
    std::cout << "Welcome this is Stockage Menu:\n";
    std::cout<< "1." << " Add new entry to stockage\n";
    std::cout<< "2." << " Delete old entry\n";
    std::cout<< "3." << " View your whole data\n";
    std::cout<< "4." << " Delete all of your stockage data\n";
}
int AppManager::run(int argc, char **argv)
{
    std::cout << ": ";
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
        std::cout << "ID:>";
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
    stokage.writeBinary(entry, getStockagePath(), key, std::ios::app | std::ios::out);
}
void AppManager::deleteOldEntry(int id)
{
    std::cout << "Not Available!\n";
    // askKey();
    // // TODO
}
void AppManager::viewData()
{
    std::string entries{};
    stokage.readBinary(entries, getStockagePath(), key);
    std::cout << entries << "\n";
};

void AppManager::deleteAll()
{
    std::cout << "You can't delete the aura from stockage, file is saved here " << getStockagePath() << " delete it manualy!\n";
};

void AppManager::readMultiLineString(std::string &new_entry)
{
    std::cout << "type {stop} to stop:>\n";
    std::cin.ignore();
    std::cin.clear();
    while (true)
    {
        std::string line{};
        std::getline(std::cin, line);
        if (line == "{stop}")
            break;
        new_entry += line;
    };
}
void AppManager::askKey()
{
    int flag{};
    do
    {
        std::cout << "Key: ";
        readInteger(key);
        std::cout << "Warning: Double check it please even if one digit is incorrect whole aura data will get corrupt\nAre you sure key is correct?0(n)/1(y)\n";
        std::cout << ": ";
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
            std::cout << "Invalid input. Please enter an integer: ";
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
