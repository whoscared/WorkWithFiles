#include "DirectoryHandling.h"
#include <filesystem>
#include "File.h"

int DirectoryHandling::countOfFile() {
	int counter = 0;
	
	for (const auto& file : filesystem::directory_iterator(path)) {
		if (!file.is_directory()) {
			counter++;
		}
	}
	return counter;
}

int DirectoryHandling::countOfAll() {
	int counter = 0;

	for (const auto& file : filesystem::directory_iterator(path)) {
		counter++;
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

void DirectoryHandling::searchDublicate(list<string>& dublicate, map<string, string>& allFiles, const string& path) {

	for (const auto& file : filesystem::directory_iterator(path)) {

		if (filesystem::is_directory(file)) {
			searchDublicate(dublicate, allFiles, file.path().string());
		}
		else {

			auto temp = allFiles.find(file.path().filename().string() + " " + to_string(file.file_size()));

			if (temp != allFiles.end()) {
				dublicate.push_back(temp->first + " " + temp->second);
				dublicate.push_back(temp->first + " " + file.path().string());
			}
			else {
				allFiles.emplace(file.path().filename().string() + " " + to_string(file.file_size()), file.path().string());
			}
		}
	}
}


DirectoryHandling::DirectoryHandling() {
	this->path = "C:\\Users\\coklo\\Downloads";
	countFile = countOfFile();
	countAll = countOfAll();
	allFiles = getAllFiles();
}

DirectoryHandling::DirectoryHandling(string title) {
	this->path = title;
	countFile = countOfFile();
	countAll = countOfAll();
	allFiles = getAllFiles();
}


int DirectoryHandling::getCountFile() {
	return countFile;
}

int DirectoryHandling::countOfDirectory() {
	int counter = 0;

	for (const auto& file : filesystem::directory_iterator(path)) {
		if (file.is_directory()) {
			counter++;
		}
	}
	return counter;
}


int DirectoryHandling::getSumOfFileSizes() {
	int sum = 0;

	for (int i = 0; i < countFile; i++) {
		sum += allFiles[i]->getSize();
	}

	return sum;
}

long DirectoryHandling::getSumOfFileSizesWithNestedDir() {
	long sum = 0;
	getSum(sum, path);
	return sum;
}


File** DirectoryHandling::getAll() {
	File** allFiles = new File * [countAll];
	int index = 0;

	for (const auto& file : filesystem::directory_iterator(path)) {
		File* temp = new File(file);
		allFiles[index] = temp;
		index++;
	}
	return allFiles;
}

File** DirectoryHandling::getAllFiles() {
	File** allFiles = new File * [countFile]; 
	int index = 0;

	for (const auto& file : filesystem::directory_iterator(path)) {
		if (!file.is_directory()) {
			File* temp = new File(file);
			allFiles[index] = temp;
			index++;
		}
	}
	return allFiles;
}

File** DirectoryHandling::sortBySize() {
	File** sortArraySize = getAllFiles();
	int start = 0;
	
	for (int i = 0; i < countFile; i++) {
		int minIndex = findMinIndexSize(sortArraySize, i, countFile);
		swap(sortArraySize[i], sortArraySize[minIndex]);
	}
	return sortArraySize;
}

File** DirectoryHandling::sortByDate() {
	File** sortArrayDate = getAllFiles();
	int start = 0;

	for (int i = 0; i < countFile; i++) {
		int minIndex = findMinIndexDate(sortArrayDate, i, countFile);
		swap(sortArrayDate[i], sortArrayDate[minIndex]);
	}

	return sortArrayDate;
}


File DirectoryHandling::getLargestFile() {
	File** sortFiles = sortBySize();
	if (countFile == 0) {
		throw new exception("Файлы отсутствуют!");
	}
	return *sortFiles[countFile - 1];
}

File DirectoryHandling::getLargestFileWithThreshold(int threshold) {
	File** sortFiles = sortBySize();
	if (countFile == 0) {
		throw new exception("Файлы отсутствуют!");
	}
	for (int i = countFile - 1; i >= 0; i--) {
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


list<string> DirectoryHandling::getDublicate() {
	list<string> dublicate;
	map<string, string> allFiles;

	searchDublicate(dublicate, allFiles, path);

	return dublicate;
}


void DirectoryHandling::printArrayFiles(File** files) {
	int count = countOfFile();

	for (int i = 0; i < count; i++) {
		cout << files[i]->toString() << " date: " << files[i]->getDate() << endl;
	}
}
