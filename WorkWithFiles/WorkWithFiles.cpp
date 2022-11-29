#include <iostream>
#include "DirectoryHandling.h"
#include "File.h"
#include "Utils.h"
#include "CreateReport.h"

using namespace std;
//save result in file 
int main()
{
	setlocale(LC_ALL, "Russian");

	DirectoryHandling dirHand;

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
			}
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
	}
	
	dirHand = DirectoryHandling(path);
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
			"11.Выход" << endl;
		cin >> choose;

		switch (choose)
		{
		case 1:
		{
			File** allFiles = dirHand.getAllFiles();
			dirHand.printArrayFiles(allFiles);
			
			report.setString("Вывод всех файлов:");
			for (int i = 0; i < dirHand.getCountFile(); i++) {
				report.setString(allFiles[i]->toString());
			}
			report.setString("\n");

			break;
		}
		case 2:
		{
			File** all = dirHand.getAll();
			dirHand.printArrayFiles(all);

			report.setString("Вывод всех файлов и директорий:");
			for (int i = 0; i < dirHand.getCountFile(); i++) {
				report.setString(all[i]->toString());
			}
			report.setString("\n");

			break;
		}
		case 3:
		{
			cout << dirHand.getCountFile() << endl;

			report.setString("Количество файлов: " + to_string(dirHand.getCountFile()));
			report.setString("\n");

			break;
		}
		case 4:
		{
			cout << dirHand.countOfDirectory() << endl;

			report.setString("Количество директорий: " + to_string(dirHand.getCountFile()));
			report.setString("\n");

			break;
		}
		case 5:
		{
			cout << dirHand.getSumOfFileSizes() << " байт" << endl;

			report.setString("Сумма размеров всех файлов: " + to_string(dirHand.getSumOfFileSizes()) + " байт");
			report.setString("\n");

			break;
		}
		case 6:
		{
			cout << dirHand.getSumOfFileSizesWithNestedDir() << " байт" << endl;

			report.setString("Сумма размеров всех файлов в данной и во вложенных директориях: " + to_string(dirHand.getSumOfFileSizesWithNestedDir()) + " байт");
			report.setString("\n");

			break;
		}
		case 7:
		{
			cout << "Файл с максимальным размером:\n" << dirHand.getLargestFile().toString() << endl;

			report.setString("Файл с максимальным размером:" + dirHand.getLargestFile().toString());
			report.setString("\n");

			break;
		}
		case 8:
		{
			cout << "Введите порог для максимального размера в байтах: ";
			int threshold;
			cin >> threshold;
			cout << "Файл с максимальным размером, учитывая порог = " << to_string(threshold) << " :\n" << dirHand.getLargestFileWithThreshold(threshold).toString() << endl;

			report.setString("Файл с максимальным размером, учитывая порог = " + to_string(threshold) + dirHand.getLargestFileWithThreshold(threshold).toString());
			report.setString("\n");

			break;
		}
		case 9:
		{
			cout << "Последний созданный файл:\n" <<
				dirHand.getLastFile().toString() << " date: " << dirHand.getLastFile().getDate() << endl;

			report.setString("Последний созданный файл: " + dirHand.getLastFile().toString());
			report.setString("\n");

			break;
		}
		case 10:
		{
			cout << "Дубликаты в данной и вложенных директориях:" << endl;
			report.setString("Дубликаты в данной и вложенных директориях:");
			 list<string> dublicate = dirHand.getDublicate();

			 for (string temp : dublicate) {
			     cout << temp << endl;
				 report.setString(temp);
			 }
			 report.setString("\n");

			break;
		}
		case 11:
		{
			menu = false;
			break;
		}
		default:
			cout << "Данная опция отстуствует в меню." << endl;
			break;
		}
	}
	report.closeReport();
}

