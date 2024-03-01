#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>


using namespace std;

struct Date
{
	int year, month, day;
};

bool SameWeekDayProgramm(std::string& inFile);
string ReadLine(std::ifstream& inputFile);
bool CheckLineIsDate(string& line);
bool isValidDate(Date& date);
bool CheckLeapYear(int year);
bool IsNumber(const std::string& num);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RU");

	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: Usage: SameWeekDay.exe <inputFile>\n";
		return 1;
	}

	std::string pathFile = argv[1];

	if (SameWeekDayProgramm(pathFile))
		return 0;
	else
		return 1;
}

bool SameWeekDayProgramm(std::string& inFile)
{
	std::ifstream inputFile;

	inputFile.open(inFile);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open inFile\n";
		return false;
	}

	string line = ReadLine(inputFile);
	if (CheckLineIsDate(line))
	{
		return true;
	}

	//date.year = stoi(a);
	//date.month = stoi(b);
	//date.day = stoi(c);
	//Date firstDate = ReadLine(inputFile);
	//Date secondDate = ReadLine(inputFile);

	return true;
}

string ReadLine(std::ifstream& inputFile)
{
	string line;
	getline(inputFile, line);
	return line;
}

bool CheckLineIsDate(string& line)
{
	istringstream abc(line);
	string a, b, c;
	abc >> a >> b >> c;

	if (IsNumber(a) && IsNumber(b) && IsNumber(c))
	{
		Date date = { stoi(a), stoi(b), stoi(c) };
		return isValidDate(date);
	}
	else
	{
		return false;
	}
}

bool isValidDate(Date& date)
{
	bool leapYear = false;
	Date minDate = { 1900, 1, 1 };
	Date maxDate = { 9999, 12, 31 };
	int longMonths[]{ 1, 3, 5, 7, 8, 10, 12 };
	int shortMonths[]{ 4, 6, 9, 11 };

	if (maxDate.year < date.year < minDate.year)
	{
		return false;
	}
	leapYear = CheckLeapYear(date.year);
	if (maxDate.month < date.month < minDate.month)
	{
		return false;
	}
	return true;
}

bool CheckLeapYear(int year)
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

bool IsNumber(const std::string& num)
{
	for (unsigned i = 0; i < num.length(); ++i)
	{
		if (!std::isdigit(num[i]))
		{
			return false;
		}
	}
	return true;
}