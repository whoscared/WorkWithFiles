#include <iostream>
#include "DirectoryHandling.h"
#include "File.h"
#include "Utils.h"
#include "CreateReport.h"
#include <windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	int choose;
	bool menu = true;
	string path;
	string file;
	
	while (menu) {

		cout << "Введите путь или выберите default path\n" <<
			"1.Ввести путь 2.C:\\Users\\coklo\\Downloads" << endl;
		cin >> choose;

		if (choose == 1) {
			menu = false;

			while (!menu) {
				cout << "Путь: ";
				cin >> path;
				menu = checkPath(path);
				if (!menu) {
					cout << "Некорректный ввод! Попробуйте еще раз" << endl;
				}
			}
			menu = false;
			continue;
		}
		else if (choose == 2) {
			path = "C:\\Users\\coklo\\Downloads";
			menu = false;
			continue;
		}
	}

	while (!menu) {
		cout << "Введите название файла, в который будет сохранятся результаты и история работы: ";
		cin >> file;
		menu = checkFile(file);
		if (!menu) {
			cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		}
		
	}
	
	DirectoryHandling dirHand = DirectoryHandling(path);
	CreateReport report = CreateReport(file);

	while (menu) {
		cout << "1.Вывести все файлы \n" <<
			"2.Вывести все файлы и папки \n" <<
			"3.Количество файлов \n" <<
			"4.Количество папок\n" <<
			"5.Суммарный размер файлов в данной директории\n" <<
			"6.Суммарный размер файлов в данной директории и во вложенных директориях\n" <<
			"7.Файл с максимальным размером\n" <<
			"8.Файл с максимальным размером(с указанным порогом)\n" <<
			"9.Самый новый файл\n" << 
			"10.Дубликаты\n" << 
			"11.Выход\n" << endl;
		cin >> choose;

		switch (choose)
		{
		case 1:
		{
			cout << "\n";
			report.setString("Вывод всех файлов:");

			vector<File> all_files = dirHand.getAllFiles();
			vector<File>::iterator iter = all_files.begin();

			int index = 1;
			while (iter != all_files.end()) {
				cout << to_string(index) + " " << *iter;
				report.setString(iter->toString());
				iter++; index++;
			}

			report.setString("\n");
			cout << "\n";
			break;
		}
		case 2:
		{
			cout << "\n";
			report.setString("Вывод всех файлов и директорий:");

			vector<File> all = dirHand.getAll();
			vector<File>::iterator iter = all.begin();

			int index = 1;
			while (iter != all.end()) {
				cout << to_string(index) + " " << *iter;
				report.setString(iter->toString());
				iter++; index++;
			}

			report.setString("\n");
			cout << "\n";
			break;
		}
		case 3:
		{
			cout << "\n";
			cout << "Количество файлов: " + to_string(dirHand.getCountFile()) << endl;

			report.setString("Количество файлов: " + to_string(dirHand.getCountFile()));
			report.setString("\n");
			cout << "\n";
			break;
		}
		case 4:
		{
			cout << "\n";
			cout << "Количество директорий: " + to_string(dirHand.getCountOfDirectory()) << endl;

			report.setString("Количество директорий: " + to_string(dirHand.getCountOfDirectory()));
			report.setString("\n");
			cout << "\n";
			break;
		}
		case 5:
		{
			cout << "\n";
			cout << dirHand.getSumOfFileSizes() << " байт" << endl;

			report.setString("Сумма размеров всех файлов: " + to_string(dirHand.getSumOfFileSizes()) + " байт");
			report.setString("\n");
			cout << "\n";
			break;
		}
		case 6:
		{
			cout << "\n";
			cout << dirHand.getSumOfFileSizesWithNestedDir() << " байт" << endl;

			report.setString("Сумма размеров всех файлов в данной и во вложенных директориях: " + to_string(dirHand.getSumOfFileSizesWithNestedDir()) + " байт");
			report.setString("\n");
			cout << "\n";
			break;
		}
		case 7:
		{
			cout << "\n";
			cout << "Файл с максимальным размером:\n" << dirHand.getLargestFile() << endl;

			report.setString("Файл с максимальным размером:" + dirHand.getLargestFile().toString());
			report.setString("\n");
			cout << "\n";
			break;
		}
		case 8:
		{
			cout << "\n";
			cout << "Введите порог для максимального размера в байтах: ";
			int threshold;
			cin >> threshold;
			File temp = dirHand.getLargestFileWithThreshold(threshold);

			if (temp.getName() == "") {
				cout << "Файл не найден" << endl;
				report.setString("Файл с максимальным размером, учитывая порог = " + to_string(threshold) + " не найден");
			}
			else {
				cout << "Файл с максимальным размером, учитывая порог = " << to_string(threshold) << " :\n" << temp << endl;
				report.setString("Файл с максимальным размером, учитывая порог = " + to_string(threshold) + " " + temp.toString());
			}

			report.setString("\n");
			cout << "\n";
			break;
		}
		case 9:
		{
			cout << "\n";
			cout << "Последний созданный файл:\n" << dirHand.getLastFile();

			report.setString("Последний созданный файл: " + dirHand.getLastFile().toString());
			report.setString("\n");
			cout << "\n";
			break;
		}
		case 10:
		{
			cout << "\n";
			cout << "Дубликаты в данной и вложенных директориях:" << endl;
			report.setString("Дубликаты в данной и вложенных директориях:");
			 list<string> dublicate = dirHand.getDublicate();

			 for (string temp : dublicate) {
			     cout << temp << endl;
				 report.setString(temp);
			 }
			 report.setString("\n");
			 cout << "\n";
			break;
		}
		case 11:
		{
			menu = false;
			break;
		}
		default:
			cout << "\n";
			cout << "Данная опция отстуствует в меню." << endl;
			cout << "\n";
			break;
		}
	}
	report.closeReport();
}

