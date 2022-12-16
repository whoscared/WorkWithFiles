#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "File.h"

using namespace std;

class DirectoryHandling
{
private:
	string path;
	int countFile;
	int countAll;
	File** allFiles;
	vector<File> v_allFiles;
	vector<File> v_all;

	void getSum(long& sum, const string path);
	void searchDublicate(list<string>& dublicate, map<string, string>& allFiles, const string& path);

public:
	//DirectoryHandling();
	DirectoryHandling(string title);

	int getCountFile();
	int getCountOfDirectory();

	long getSumOfFileSizes(); 
	long getSumOfFileSizesWithNestedDir();

	vector<File> getAll();
	vector<File> getAllFiles();

	File getLargestFile();
	File getLargestFileWithThreshold(int threshold);

	File getLastFile();

	list<string> getDublicate();

};

