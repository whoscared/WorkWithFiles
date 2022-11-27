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

int DirectoryHandling::findMinIndexDate(File** files, int start, int count) {
	int minIndex = start;

	for (int i = start; i < count; i++) {
		minIndex = files[i]->getDate() < files[minIndex]->getDate() ? i : minIndex;
	}
	return minIndex;
}

void DirectoryHandling::getSum(long& sum, const string& path) {
	for (const auto& file : filesystem::directory_iterator(path)) {
		if (filesystem::is_directory(file)) {
			getSum(sum, file.path().string());
		}
		else {
			sum += file.file_size();
		}
	}
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


int DirectoryHandling::getSumOfFileSizes() {
	File** allFiles = getAllFiles();
	int sum = 0;

	for (int i = 0; i < countFile; i++) {
		sum += allFiles[i]->getSize();
	}

	return sum;
}

long DirectoryHandling::getSumOfFileSizesWithNestedDir() {
	long sum = 0;
	getSum(sum, title);
	return sum;
}

File** DirectoryHandling::getAllFiles() {
	File** allFiles = new File * [countFile]; // do fields
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


File** DirectoryHandling::sortByDate() {
	File** allFiles = getAllFiles();
	int start = 0;

	for (int i = 0; i < countFile; i++) {
		int minIndex = findMinIndexDate(allFiles, i, countFile);
		swap(allFiles[i], allFiles[minIndex]);
	}

	return allFiles;
}

File DirectoryHandling::getLargestFile() {
	File** sortFiles = sortBySize();
	if (countFile == 0) {
		throw new exception("Файлы отсутствуют!");
	}
	return *sortFiles[0];
}

File DirectoryHandling::getLargestFileWithThreshold(int threshold) {
	File** sortFiles = sortBySize();
	if (countFile == 0) {
		throw new exception("Файлы отсутствуют!");
	}
	for (int i = 0; i < countFile; i++) {
		if (sortFiles[i]->getSize() < threshold) {
			return *sortFiles[i];
		}
	}
	throw new exception("Подходящий файл не найден!");
}

File DirectoryHandling::getLastFile() {
	File** sortFiles = sortByDate();
	if (countFile == 0) {
		throw new exception("Файлы отсутствуют!");
	}
	return *sortFiles[countFile - 1];
}

void DirectoryHandling::printArrayFiles(File** files) {
	int count = countOfFile();

	//что позже = больше (еще хз )
	//cout << files[0]->toString() << "  " << files[0]->getDate() << endl;
	//cout << files[1]->toString() << "  " << files[1]->getDate() << endl;
	//if (files[0]->getDate() > files[1]->getDate()) {
	//	cout << 0 << endl;
	//}

	for (int i = 0; i < count; i++) {
		cout << files[i]->toString() << " " << files[i]->getDate() << endl;
	}
}
