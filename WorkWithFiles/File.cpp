#include "File.h"

File::File() {}

File::File(filesystem::directory_entry file) {
	name = file.path().filename().string();
	path = file.path().string();
	date = filesystem::last_write_time(file);
	size = file.file_size();
}


string File::getName() {
	return name;
}

string File::getPath() {
	return path;
}

filesystem::file_time_type File::getDate() {
	return date;
}

int File::getSize() {
	return size;
}


string File::toString() {
	return "name: " + name + " size: " + to_string(size);
}
