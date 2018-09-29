
#pragma once

#include <string>
#include "jsoncpp/include/json/json.h"

namespace help
{
	bool loadJson(const std::string& fileName, Json::Value& value);
}; // help