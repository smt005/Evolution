
#pragma once

#include <string>

class FileSystem
{
public:
	static bool readTextFile(const std::string& fileName, char*& data, int lenght);
	static bool writeTextFile(const std::string& fileName, char* data);
};
