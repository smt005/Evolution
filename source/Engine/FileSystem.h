
#pragma once

#include <string>

class FileSystem
{
public:
	static bool readTextFile(const std::string& fileName, char*& data, int lenght);
	static std::string readTextFile(const std::string& fileName);

	static bool writeTextFile(const std::string& fileName, char* data);
	static bool writeTextFile(const std::string& fileName, const std::string& text);
};