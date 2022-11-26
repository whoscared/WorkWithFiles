#define _CRT_SECURE_NO_WARNINGS
#include "DirectoryHandling.h"
#include <tchar.h>
#include <filesystem>
#include <ctime>
#include "File.h"


DirectoryHandling::DirectoryHandling(string title) {
	this->title = title;

}

int DirectoryHandling::countOfFile() {
	int counter = 0;
	for (const auto& file : filesystem::directory_iterator(title)) {
		if (!file.is_directory()) {
			cout << file.path().string() << " size: " << file.file_size() << endl;
			filesystem::file_time_type ftime = filesystem::last_write_time(file);
			cout << "time: " << ftime << endl;
			counter++;
			File* tempfile1 = new File(file);
		}
	}
	cout << "\n";


	return counter;
}

int DirectoryHandling::countOfDirectory() {
	int counter = 0;
	for (const auto& file : filesystem::directory_iterator(title)) {
		if (file.is_directory()) {
			counter++;
			cout << file.path().string() << endl;
			counter++;
		}
	}
	return counter;
}

