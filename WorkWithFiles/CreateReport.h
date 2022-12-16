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
	CreateReport(string title);

	void setString(string s);
	void closeReport();
};

