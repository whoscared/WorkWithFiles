#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include "File.h"

#pragma once

using namespace std;

//count of files (done)
//count of directory (done)
//summa file size (byte) (done)
  //with nested directiry (done)
  //without nested directory (done)
//search the most big file (done)
  //with threshold !! (done)
//search the most new file (done)
  //with temp date 
//search duplicate (size, title) (done)


class DirectoryHandling
{
private:
	string path;
	int countFile;
	File** allFiles;
	int countOfFile();

	int findMinIndexSize(File** files, int start, int count);
	int findMinIndexDate(File** files, int start, int count);

	void getSum(long& sum, const string& path);
	void searchDublicate(list<string>& dublicate, map<string, string>& allFiles, const string& path);

public:
	DirectoryHandling(string title);

	int getCountFile();
	int countOfDirectory();

	int getSumOfFileSizes(); //to do number formatting
	long getSumOfFileSizesWithNestedDir(); //to do number formatting

	File** getAllFiles();
	File** sortBySize();
	File** sortByDate();

	File getLargestFile();
	File getLargestFileWithThreshold(int threshold);

	File getLastFile();

	list<string> getDublicate();

	void printArrayFiles(File** files);
};

