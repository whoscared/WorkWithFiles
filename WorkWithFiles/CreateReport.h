#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class CreateReport
{
private:
	string title;
	ofstream fileout;
public: 
	CreateReport();
	CreateReport(string title);

	bool isOpen();

	bool setTitle(string title);
	bool setString(string s);
	void closeReport();
};

