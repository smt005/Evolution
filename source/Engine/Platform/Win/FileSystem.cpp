
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
