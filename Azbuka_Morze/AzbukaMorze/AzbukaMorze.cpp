﻿/* 22. Написать программу для кодирования данного текста с помощью азбуки Морзе.
Автор - Игнатьева Ю.О.*/

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <cctype>
#include <windows.h>
using namespace std;

//шифрование всех допустимых символов
map <char, string> AzbukaMorze = {
	{ 'а', "·-" },   { 'a', "·-" },
	{ 'б', "-···" }, { 'b', "-···" },
	{ 'в', "·--" },  { 'w', "·--" },
	{ 'г', "--·" },  { 'g', "--·" },
	{ 'д', "-··" },  { 'd', "-··" },
	{ 'е', "·" },    { 'ё', "·" },    { 'e', "·" },
	{ 'ж', "···-" }, { 'v', "···-" },
	{ 'з', "--··" }, { 'z', "--··" },
	{ 'и', "··" },   { 'i', "··" },
	{ 'й', "·---" }, { 'j', "·---" },
	{ 'к', "-·-" },  { 'k', "-·-" },
	{ 'л', "·-··" }, { 'l', "·-··" },
	{ 'м', "--" },   { 'm', "--" },
	{ 'н', "-·" },   { 'n', "-·" },
	{ 'о', "---" },  { 'o', "---" },
	{ 'п', "·--·" }, { 'p', "·--·" },
	{ 'р', "·-·" },  { 'r', "·-·" },
	{ 'с', "···" },  { 's', "···" },
	{ 'т', "-" },    { 't', "-" },
	{ 'у', "··-" },  { 'u', "··-" },
	{ 'ф', "··-·" }, { 'f', "··-·" },
	{ 'х', "····" }, { 'h', "····" },
	{ 'ц', "-·-·" }, { 'c', "-·-·" },
	{ 'ч', "---·" },
	{ 'ш', "----" },
	{ 'щ', "--·-" }, { 'q', "--·-" },
	{ 'ы', "-·--" }, { 'y', "-·--" },
	{ 'ъ', "-··-" }, { 'ь', "-··-" }, { 'x', "-··-" },
	{ 'э', "··-··" },
	{ 'ю', "··--" },
	{ 'я', "·-·-" },
	{ '1', "·----" },
	{ '2', "··---" },
	{ '3', "···--" },
	{ '4', "····-" },
	{ '5', "·····" },
	{ '6', "-····" },
	{ '7', "--···" },
	{ '8', "---··" },
	{ '9', "----·" },
	{ '0', "-----" },
	{ '.', "······" },
	{ ',', "·-·-·-" },
	{ ':', "---···" },
	{ ';', "-·-·-·" },
	{ '(', "-·--·-" },{ ')', "-·--·-" },
	{ '-', "-····-" },
	{ '/', "-··-·" },
	{ '?', "··--··" },
	{ '!', "--··--" },
	{ ' ', "   " }, //знак раздела
	{ '@', "·--·-·" },
};

bool CheckStr(string s)
{
	string valid_let = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyz1234567890.,:;()/?! @";
	int p, i=0, len = s.length();
	do {
		s[i] = (char)tolower(s[i]);
		p = valid_let.find(s[i]);
		i++;
	} while ((p >= 0)&&(i <= len));
	if (i == len+1)
		return true;
	else
		return false;
}
//кодирование принятой строки с помощью азбуки Морзе
string ConvertToAzbukaMorze(string s)
{
	string res_s = "";
	for (int i = 0; i < s.length(); i++){
		//если введена прописная буква, переводим в строчную
		s[i] = (char)tolower(s[i]);
		res_s = res_s + AzbukaMorze.find(s[i])->second + " ";
	}
	return res_s;
}

//ответ на вопрос (txt)
bool Question(const char *txt)
{
	char ans; //переменная, содержащая ответ на вопрос
	cout << txt << endl;
	do {
		cin >> ans;
		if ((ans != 'N') && (ans != 'n') && (ans != 'Y') && (ans != 'y'))
			cout << "Введеное значение неверно. Повторите ввод.\n";
	} while ((ans != 'N') && (ans != 'n') && (ans != 'Y') && (ans != 'y'));
	getchar();
	if ((ans == 'Y') || (ans == 'y'))
		return true; //если ответ положительный, то вернуть функции true
	else
		return false;
}

//главное меню
int Menu()
{
	cout << "---------------------------------------\n";
	cout << "                 МЕНЮ                  \n";
	cout << "---------------------------------------\n";
	cout << "1 - Загрузить текст из файла.\n";
	cout << "2 - Ввести текст в консоли.\n";
	cout << "---------------------------------------\n";
	int p;
	do {
		cin >> p;
		if ((p != 1) && (p != 2))
			cout << "Введеное значение неверно. Повторите ввод.\n";
	} while ((p != 1) && (p != 2));
	getchar();
	cout << "\n";
	return p;
}

//загрузка текста из файла
void FileText() 
{
	string str, res;
	cout << "Введите имя файла: \n";
	cin >> str;
	//открытие введенного пользователем файла
	ifstream file(str);
	if (!file)
		cout << "Не удается открыть файл.\n";
	else {
		if (Question("Хотите ли записать результат в файл? (y/n)")) 
		{
			//создание и открытие результирующего файла
			ofstream res_file("Result.txt");
			res_file << "Результат перевода:\n"; //запись строки в файл
			cout << "Результат перевода:\n";
			while (getline(file, str)) 
			{
				if (CheckStr(str))
				{
					res = ConvertToAzbukaMorze(str);
					cout << res << endl;
					res_file << res << endl;
				}
				else
				{
					cout << "Строка не переведена.\n";
					res_file << "Строка не переведена.\n";
				};
			}
			res_file << "Буквы отделяются одним пробелом, слова - тремя.\n" << endl;
			res_file.close(); //закрываем файл
			cout << "Результат сохранен в файле Result.txt\n";
		}
		else {
			cout << "Результат перевода:\n";
			while (getline(file, str)) 
			{
				if (CheckStr(str))
				{
					res = ConvertToAzbukaMorze(str);
					cout << res << endl;
				}
				else
					cout << "Строка не переведена.\n";
			}
			cout << "Буквы отделяются одним пробелом, слова - тремя.\n";
		}
		file.close(); //закрываем файл
	}
}

//ввод текста в консоли
void ConsoleText() 
{
	string str, res;
	cout << "Введите текст: \n";
	getline(cin, str);
	if (CheckStr(str))
	{
		res = ConvertToAzbukaMorze(str);
		cout << "Результат перевода:\n" << res << endl << "Буквы отделяются одним пробелом, слова - тремя.\n";
		if (Question("Хотите ли записать результат в файл? (y/n)"))
		{
			ofstream res_file("Result.txt");
			res_file << "Результат перевода:\n" << res << endl << "Буквы отделяются одним пробелом, слова - тремя.\n";
			res_file.close(); //закрываем файл
			cout << "Результат сохранен в файле Result.txt\n";
		}
	}
	else
		cout << "Строка не переведена.\n";
}

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n = Menu();
	switch (n) {
		case 1:
			FileText();
			break;
		case 2:
			ConsoleText();
			break;
	}
	system("Pause");

	return 0;
}

