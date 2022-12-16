#include "Utils.h"

using namespace std;

bool checkPath(string path) {
	if (path.empty()) {
		return false;
	}

	if (filesystem::is_directory(path)) {
		return true;
	}
	return false;
}

bool checkFile(string filetxt) {
	if (filetxt.empty()) {
		return false;
	}

	string ex = "/:*?<>|";

	for (int i = 0; i < filetxt.size(); i++) {

		if (ex.find(filetxt.substr(i, 1)) != string::npos) {
			return false;
		}
	}
	return true;
}