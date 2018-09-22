
#pragma once

#include <string>

class FileSystem
{
public:
	static bool readTextFile(const std::string& fileName);
	static bool writeTextFile(const std::string& fileName, const std::string& text);
};
