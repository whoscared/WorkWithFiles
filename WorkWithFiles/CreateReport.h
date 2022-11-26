#include <fstream>
#include <iostream>
#include <string>

using namespace std;
#pragma once
class CreateReport
{
private:
	string title;
	ofstream fileout;

public: 
	CreateReport();
	CreateReport(string title);
	//add string in report file
	bool isOpen();
	bool setTitle(string title);
	bool setString(string s);
	void closeReport();
};

