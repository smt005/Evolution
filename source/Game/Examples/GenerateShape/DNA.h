#pragma once

#include <string>
#include <vector>
#include <memory>
#include "jsoncpp/include/json/json.h"
#include "Object/Identify.h"
#include "Common/DataClass.h"

namespace microbe
{

class DNA;

typedef unsigned short int Type;
typedef std::shared_ptr<DNA> DnaPtr;

class DNA : public DataClass<DNA>
{
public:
	struct ValueCell
	{
		Type type;
		float angle;
		float dist;
		float size;
	};

public:
	bool create(const string &_name) override;
	const std::vector<ValueCell>& getCells() const { return _cells; }

private:
	std::vector<ValueCell> _cells;

public:
	static std::vector<std::string> getListId();

private:
	static Json::Value& getData(const std::string& key);
	static Json::Value _dataBase;
};

};	// microbe

/* Пример:

{
  "000":			- идентификатор
  [					- массив ячеек
    {
      "t": 1,		- тип
      "a": 0.47,	- угол относительно родителя
      "d": 1.34		- дистанция
	  "s": 0.5		- размер
    },
    {
      ...
    }
  ],
  "001": [...]
}

*/