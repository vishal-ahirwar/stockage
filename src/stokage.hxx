#ifndef STOKAGE_HXX
#define STOKAGE_HXX
#include<string>
class Stokage
{
    public:
    void writeBinary(const std::string&input,const std::string&file_name);
    void readBinary(std::string&decodedString,const std::string&file_name);
};
#endif