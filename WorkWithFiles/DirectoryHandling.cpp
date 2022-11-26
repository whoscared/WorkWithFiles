#define _CRT_SECURE_NO_WARNINGS
#include "DirectoryHandling.h"
#include <tchar.h>
#include <filesystem>
#include <ctime>
#include "File.h"

//filesystem::file_time_type ftime = filesystem::last_write_time(file);
//cout << "time: " << ftime << endl;

int DirectoryHandling::countOfFile() {
	int counter = 0;
	
	for (const auto& file : filesystem::directory_iterator(title)) {
		if (!file.is_directory()) {
			counter++;
		}
	}
	return counter;
}

int DirectoryHandling::findMinIndexSize(File** files, int start, int count) {
	int minIndex = start;

	for (int i = start; i < count; i++) {
		minIndex = files[i]->getSize() < files[minIndex]->getSize() ? i : minIndex;
	}
	return minIndex;
}

DirectoryHandling::DirectoryHandling(string title) {
	this->title = title;
	this->countFile = countOfFile();
}

int DirectoryHandling::getCountFile() {
	return countFile;
}

int DirectoryHandling::countOfDirectory() {
	int counter = 0;

	for (const auto& file : filesystem::directory_iterator(title)) {
		if (file.is_directory()) {
			counter++;
		}
	}
	return counter;
}

File** DirectoryHandling::getAllFiles() {
	File** allFiles = new File * [countFile];
	int index = 0;

	for (const auto& file : filesystem::directory_iterator(title)) {
		if (!file.is_directory()) {
			File* temp = new File(file);
			allFiles[index] = temp;
			index++;
		}
	}
	return allFiles;
}


File** DirectoryHandling::sortBySize() {
	File** allFiles = getAllFiles();
	int start = 0;
	
	for (int i = 0; i < countFile; i++) {
		int minIndex = findMinIndexSize(allFiles, i, countFile);
		swap(allFiles[i], allFiles[minIndex]);
	}
	return allFiles;
}

void DirectoryHandling::printArrayFiles(File** files) {
	int count = countOfFile();

	//что позже = больше (еще хз )
	cout << files[0]->toString() << "  " << files[0]->getDate() << endl;
	cout << files[1]->toString() << "  " << files[1]->getDate() << endl;
	if (files[0]->getDate() > files[1]->getDate()) {
		cout << 0 << endl;
	}

	for (int i = 0; i < count; i++) {
		cout << files[i]->toString() << endl;
	}
}
