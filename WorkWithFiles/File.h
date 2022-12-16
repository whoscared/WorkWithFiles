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

	string getName() const;
	string getPath() const;
	filesystem::file_time_type getDate() const;
	int getSize() const;

	string toString() const;
};

ostream& operator<<(ostream& out, File const& file);

