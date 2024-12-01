#include <stokage.hxx>
#include <fstream>
#include <iostream>
#include <bitset>

void Stokage::writeBinary(const std::string &input, const std::string &fileName, int key)
{
    // Open file in binary mode
    std::ofstream outFile(fileName, std::ios::binary);

    if (!outFile)
    {
        std::cerr << "Error opening file for writing!\n";
        return;
    }

    for (char c : input)
    {
        // Convert each character to an 8-bit binary string
        std::bitset<32> binaryChar(c ^ key);
        outFile << binaryChar;
    }

    outFile.close();
    std::cout << "Binary representation written to file: " << fileName << "\n";
};
void Stokage::readBinary(std::string &dekeydString, const std::string &fileName, int key)
{
    std::ifstream inFile(fileName, std::ios::binary);

    if (!inFile)
    {
        std::cerr << "Error opening file for reading!\n";
        return;
    }

    std::string binaryStr;
    while (std::getline(inFile, binaryStr))
    {
        for (size_t i = 0; i < binaryStr.size(); i += 32)
        {
            std::bitset<32> binaryChar(binaryStr.substr(i, 32));
            dekeydString += static_cast<char>(binaryChar.to_ulong() ^ key);
        }
    }

    inFile.close();
}
