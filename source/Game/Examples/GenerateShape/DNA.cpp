
#include "Common/Help.h"
#include "DNA.h"

using namespace microbe;

bool DNA::create(const string &name)
{
	_name = name;
	const Json::Value& data = getData(_name);

	if (data.empty() || !data.isArray()) {
		return false;
	}

	for (Json::ValueConstIterator it = data.begin(); it != data.end(); ++it)
	{
		if (!it->isObject()) continue;

		const Json::Value& valueJson = *it;
		ValueCell cell;

		cell.type	= valueJson["t"].asInt();
		cell.angle	= valueJson["a"].asFloat();
		cell.dist	= valueJson["d"].asFloat();
		cell.size	= valueJson["s"].asFloat();

		_cells.push_back(cell);
	}

	return true; 
}

//	static

#define DNA_FILE_NAME "Data/MicrobesDNA.json"

Json::Value DNA::_dataBase;

std::vector<std::string> DNA::getListId()
{
	if (_dataBase.empty()) {
		help::loadJson(DNA_FILE_NAME, _dataBase);
	}

	std::vector<std::string> listId;

	if (!_dataBase.empty() || _dataBase.isObject()) {
		for (auto const& key : _dataBase.getMemberNames()) {
				listId.push_back(key);
		}
	}

	return listId;
}

Json::Value& DNA::getData(const std::string& key)
{
	if (_dataBase.empty()) {
		help::loadJson(DNA_FILE_NAME, _dataBase);
	}

	return _dataBase[key];
}
