#include "DirectoryHandling.h"
#include <filesystem>
#include <algorithm>
#include <numeric>
#include "File.h"

void DirectoryHandling::getSum(long& sum, const string path) {

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

DirectoryHandling::DirectoryHandling(string title) {
	this->path = title;
	int countF = 0;
	int countA = 0;
	for (const auto& file : filesystem::directory_iterator(path)) {
		if (!file.is_directory()) {
			v_allFiles.push_back(File(file));
			countF++;
		}
		v_all.push_back(File(file));
		countA++;
	}

	countFile = countF;
	countAll = countA;
}


int DirectoryHandling::getCountFile() {
	return countFile;
}

int DirectoryHandling::getCountOfDirectory() {
	return countAll - countFile;
}


long DirectoryHandling::getSumOfFileSizes() {
	long sum = 0;
	vector<File>::iterator iter = v_allFiles.begin();

	while (iter != v_allFiles.end()) {
		sum += iter->getSize();
		iter++;
	}

	return sum;
}

long DirectoryHandling::getSumOfFileSizesWithNestedDir() {
	long sum = 0;
	getSum(sum, path);
	return sum;
}


vector<File> DirectoryHandling::getAll() {
	return v_all;
}

vector<File> DirectoryHandling::getAllFiles() {
	return v_allFiles;
}


File DirectoryHandling::getLargestFile() {
	if (countFile == 0) {
		throw new exception("Файлы отсутствуют!");
	}
	auto max = max_element(v_allFiles.begin(), v_allFiles.end(), [](File const& file1, File const& file2) {
		return file1.getSize() < file2.getSize();
		});
	return *max;
}

File DirectoryHandling::getLargestFileWithThreshold(int threshold) {
	if (countFile == 0) {
		throw new exception("Файлы отсутствуют!");
	}

	sort(v_allFiles.begin(), v_allFiles.end(), [](File const& file1, File const& file2) {
		return file1.getSize() > file2.getSize();
		});

	auto find = find_if(v_allFiles.begin(), v_allFiles.end(), [&threshold](File const& file) {
		return file.getSize() < threshold;
		});

	if (find == v_allFiles.end()) {
		return File();
	}
	return *find;
}


File DirectoryHandling::getLastFile() {
	if (countFile == 0) {
		throw new exception("Файлы отсутствуют!");
	}

	auto last = max_element(v_allFiles.begin(), v_allFiles.end(), [](File const& file1, File const& file2) {
		return file1.getDate() < file2.getDate();
		});

	return *last;
}


list<string> DirectoryHandling::getDublicate() {
	list<string> dublicate;
	map<string, string> allFiles;

	searchDublicate(dublicate, allFiles, path);

	return dublicate;
}


