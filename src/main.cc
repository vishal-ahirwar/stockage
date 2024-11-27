
//Auto Genrated C++ file by ccli CLI
//Copyright 2023 Vishal Ahirwar //replace it with your copyright notice!
#include<iostream>
#include<stokage.hxx>
#define FILE_NAME "test.bin"
int main(int argc,char*argv[])
{
    //Test
    Stokage stokage;
    stokage.writeBinary("UserName:Vishal Ahirwar\nPassword:Juz9uapsvpQ&\nAddress:Bhopal\nAge:19\nBS in electronics system\n",FILE_NAME);
    std::string out;
    stokage.readBinary(out,"test.bin");
    std::cout<<out<<"\n";
    return 0;
};

