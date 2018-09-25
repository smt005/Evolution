
#include "../../FileSystem.h"

bool FileSystem::readTextFile(const std::string& fileName, char*& data, int lenght)
{
	FILE* file;

	if (fopen_s(&file, fileName.c_str(), "r") == NULL)
	{
		fseek(file, 0, SEEK_END);
		lenght = ftell(file);
		rewind(file);

		if (lenght == 0) {
			fclose(file);
			return false;
		}

		data = (char *)malloc(sizeof(char)* (lenght + 1));
		lenght = fread(data, sizeof(char), lenght, file);
		data[lenght] = '\0';

		fclose(file);

		return true;
	}

	return false;
}

std::string FileSystem::readTextFile(const std::string& fileName)
{
	char* data = nullptr;
	int lenght = 0;

	if (readTextFile(fileName, data, lenght) && data && lenght > 0) {
		return std::string(data);
	}

	return std::string();
}

bool FileSystem::writeTextFile(const std::string& fileName, char* data)
{
	FILE* file;

	if (fopen_s(&file, fileName.c_str(), "w") != NULL) {
		return false;
	}

	fputs(data, file);
	fclose(file);
	return true;
}

bool FileSystem::writeTextFile(const std::string& fileName, const std::string& text)
{
	return writeTextFile(fileName, text.c_str());
}