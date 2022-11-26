#include <Windows.h>
#include <iostream>
#include <string>
#include <fileapi.h>


#pragma once

using namespace std;

//count of files
//count of directory
//summa file size (byte) 
  //with nested directiry
  //without nested directory
//search the most big file 
  //with threshold
//search the most new file
  //with temp date 
//search duplicate (size, title)


class DirectoryHandling
{
private:
	string title;
	//struct ffblk f;
	//WIN32_FIND_DATA findFileData;
	//HANDLE hFile;
	//LPCWSTR titleOfFile;
public:
	DirectoryHandling(string title);
	int countOfFile();
	int countOfDirectory();

};

