
#include "Help.h"
#include "../../Engine.h"
#include "../../FileManager.h"

bool help::loadJson(const std::string& fileName, Json::Value& value)
{
	std::string mystring = FileManager::readTextFile(fileName);

	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	std::string err;
	if (reader->parse(mystring.c_str(), mystring.c_str() + mystring.length(), &value, &err)) {
		return true;
	}

	Core::Engine::log("LOG: help::loadJson FAIL file: " + fileName);
	return false;
}
