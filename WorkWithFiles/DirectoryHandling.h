#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include "File.h"

using namespace std;

class DirectoryHandling
{
private:
	string path;
	int countFile;
	int countAll;
	File** allFiles;
	int countOfFile();
	int countOfAll();

	int findMinIndexSize(File** files, int start, int count);
	int findMinIndexDate(File** files, int start, int count);

	void getSum(long& sum, const string& path);
	void searchDublicate(list<string>& dublicate, map<string, string>& allFiles, const string& path);

public:
	DirectoryHandling();
	DirectoryHandling(string title);

	int getCountFile();
	int countOfDirectory();

	int getSumOfFileSizes(); 
	long getSumOfFileSizesWithNestedDir();

	File** getAll();
	File** getAllFiles();
	File** sortBySize();
	File** sortByDate();

	File getLargestFile();
	File getLargestFileWithThreshold(int threshold);

	File getLastFile();

	list<string> getDublicate();

	void printArrayFiles(File** files);
};

