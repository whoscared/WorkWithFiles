#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "DirectoryHandling.h"


//save result in file 
int main()
{
    DirectoryHandling* dir = new DirectoryHandling("C:\\Users\\coklo\\Downloads");

    std::cout << "files: " << std::endl;

    std::cout << dir->countOfFile() << std::endl;

    std::cout << "directory: " << std::endl;

    std::cout << dir->countOfDirectory() << std::endl;
}

