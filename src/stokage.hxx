#ifndef STOKAGE_HXX
#define STOKAGE_HXX
#include <string>
#include <fstream>
class Stokage
{
public:
    bool writeBinary(const std::string &input, const std::string &file_name, int key, const std::ios::openmode mode);
    void readBinary(std::string &decodedString, const std::string &file_name, int key);
};
#endif