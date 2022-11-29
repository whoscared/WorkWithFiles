#include "CreateReport.h"

CreateReport::CreateReport() {

}

CreateReport::CreateReport(string title) {
	this->title = title;
	fileout.open(title + ".txt");
}


bool CreateReport::isOpen() {
	if (fileout.is_open()) {
		return true;
	}
	else {
		return false;
	}
}


bool CreateReport::setTitle(string title) {
	fileout.open(title + ".txt");

	if (isOpen()) {
		this->title = title;
		return true;
	}
	else {
		fileout.close();
		return false;
	}
}

bool CreateReport::setString(string s) {

	if (isOpen()) {
		fileout << s << endl;
		return true;
	}
	else {
		return false;
	}
}

void CreateReport::closeReport() {
	fileout.close();
}