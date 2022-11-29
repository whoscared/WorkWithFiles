#include "Utils.h"

using namespace std;

bool checkPath(string path) {
	string ex = "/:*?<>|";

	if (path.substr(1,1) != ":" || path.substr(2,1) != "\\") {
		return false;
	}
	if (path.find('"') != string::npos) {
		return false;
	}

	for (int i = 3; i < path.size(); i++) {

		if (ex.find(path.substr(i, 1)) != string::npos) {
			return false;
		}
	}
	return true;
}

bool checkFile(string filetxt) {
	string ex = "/:*?<>|";

	for (int i = 0; i < filetxt.size(); i++) {

		if (ex.find(filetxt.substr(i, 1)) != string::npos) {
			return false;
		}
	}
	return true;
}