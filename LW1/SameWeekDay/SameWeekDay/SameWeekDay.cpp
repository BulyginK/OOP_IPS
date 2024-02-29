#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool checkYear(int year)
{
	if (year % 400 == 0)
	{
		return true;
	}
	else if (year % 100 == 0)
	{
		return false;
	}
	else if (year % 4 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RU");

	if (argc != 2)
	{
		cout << "Invalid argument count\n";
		return EXIT_SUCCESS;
	}

	ifstream inputFile;
	inputFile.exceptions(ifstream::badbit | ifstream::failbit);

	try
	{
		cout << "Попытка открыть файл\n";
		inputFile.open(argv[1]);
		cout << "Файл успешно открыт\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}
}