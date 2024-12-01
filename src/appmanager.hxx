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
    void readInteger(int&);
    void readMultiLineString(std::string&);
    void askKey();
private:
    std::string getStockagePath() const;
};
#endif // APP Manager