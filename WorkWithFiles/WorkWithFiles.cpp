#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "DirectoryHandling.h"
#include "File.h"

using namespace std;
//save result in file 
int main()
{
    DirectoryHandling* dir = new DirectoryHandling("C:\\Users\\coklo\\Downloads");

    //std::cout << "files: " << std::endl;

    //std::cout << dir->countOfFile() << std::endl;

    //std::cout << "directory: " << std::endl;

    //std::cout << dir->countOfDirectory() << std::endl;
    File** all = dir->getAllFiles();
    dir->printArrayFiles(all);
    cout << "\n";
    //File** sortBySize = dir->sortBySize();
    //File** sortByDate1 = dir->sortByDate();
    //dir->printArrayFiles(sortBySize);
    //dir->printArrayFiles(sortByDate1);

   // cout << dir->getLastFile().getName() << endl;

    cout << "summa: " << endl;
    cout << dir->getSumOfFileSizes() << endl;

    cout << "summa with nested directory: " << endl;
    cout << dir->getSumOfFileSizesWithNestedDir() << endl;

    list<string> dubl = dir->getDublicate();
    for (string temp : dubl) {
        cout << temp << endl;
    }
}

