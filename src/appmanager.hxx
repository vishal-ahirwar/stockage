#ifndef APP_MANAGER
#define APP_MANAGER
#include <stokage.hxx>

class AppManager
{
    int key;
    Stokage stokage;

public:
    AppManager();
    int run(int argc,char*argv[]);

private:
    void addNewEntry(std::string &entry);
    void deleteOldEntry(int id);
    void viewData();
    void deleteAll();
    void readInteger(std::string,int&);
    void readMultiLineString(std::string&);
    void askKey(std::string);
    void showHelp();
private:
    std::string getStockagePath() const;
};
#endif // APP Manager