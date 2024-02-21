//"$(ProjectDir)test.bat" "$(TargetPath)"
#include <iostream>
#include <fstream>
#include <string>

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);

		if (foundPos < subject.length())
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			pos = subject.length();
		}
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

//принимат строки вместо char
bool ReplaceStringProgramm(char* inFile, char* outFile, const char* searchString, const char* replacementString)
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	inputFile.open(inFile);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open inFile\n";
		return false;
	}
	outputFile.open(outFile);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open outFile\n";
		return false;
	}
	const std::string search = searchString;
	const std::string replace = replacementString;

	CopyStreamWithReplacement(inputFile, outputFile, search, replace);

	if (!outputFile.flush())
	{
		std::cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	if (ReplaceStringProgramm(argv[1], argv[2], argv[3], argv[4]))
		return 0;
	else
		return 1;
}