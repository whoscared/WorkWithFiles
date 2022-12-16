#include "File.h"

File::File() {}

File::File(filesystem::directory_entry file) {
	name = file.path().filename().string();
	path = file.path().string();
	date = filesystem::last_write_time(file);
	size = file.file_size();
}


string File::getName() const {
	return name;
}

string File::getPath() const  {
	return path;
}

filesystem::file_time_type File::getDate() const  {
	return date;
}

int File::getSize() const {
	return size;
}


string File::toString() const  {
	return "name: " + name + " size: " + to_string(size);
}

ostream& operator<<(ostream& out, File const& file)
{
	out << "name: " + file.getName() + " size: " + to_string(file.getSize()) + " date: " << file.getDate() << endl;
	return out;
}
