#pragma once

#include <string>
#include <iostream>
#include <filesystem>

using namespace std;

class File
{
private:

	string name;
	string path;
	filesystem::file_time_type date;
	int size;
public:

	File();
	File(filesystem::directory_entry file);
	string getName();
	string getPath();
	filesystem::file_time_type getDate();
	int getSize();

	bool operator> (File f);
	bool operator< (File f);

	string toString();

};

