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
			break;
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
bool ReplaceStringProgramm(std::string& inFile, std::string& outFile, const std::string& searchString, const std::string& replacementString)
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

	const std::string search = argv[3];
	const std::string replace = argv[4];

	if (ReplaceStringProgramm(argv[1], argv[2], search, replace))
		return 0;
	else
		return 1;
}