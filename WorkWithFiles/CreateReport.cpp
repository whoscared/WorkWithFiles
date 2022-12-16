#include "CreateReport.h"

CreateReport::CreateReport(string title) {
	this->title = title;
	fileout.open(title + ".txt");
}


void CreateReport::setString(string s) {
	fileout << s << endl;
}

void CreateReport::closeReport() {
	fileout.close();
}