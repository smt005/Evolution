#pragma once

#include <string>

class UniqueId
{
public:
	UniqueId() {
		++_counter;
		_id = _counter;
	}

	inline long unsigned int getId() const {
		return _id;
	}

	inline std::string getIdAsString(const unsigned short int lenght = 0) const {
		return getIdAsStringStatic(_id, lenght);
	}

public:
	template <class ValueT>
	static std::string getIdAsStringStatic(const ValueT id, const unsigned short int lenght = 0) {
		std::string idStr = std::to_string(id);
		size_t lenghtId = idStr.length();

		if (lenghtId >= lenght) {
			return idStr;
		}

		size_t prefixLenght = lenght - lenghtId;
		std::string prefixStr;
		prefixStr.reserve(prefixLenght);
		char* prefixChar = prefixStr.data();
		size_t i = 0;
		for (i = 0; i < prefixLenght; ++i) {
			prefixChar[i] = '0';
		}
		prefixChar[i] = '\0';

		return prefixChar + idStr;
	}

private:
	long unsigned int _id;

private:
	static long unsigned int _counter;
};

class Name
{
public:
	Name() {
	}

	Name(const std::string& nameObject) {
		_nameObject = nameObject;
	}

	Name(const Name& name) {
		setName(name);
	}

	inline void setNameFromPtr() {
		long unsigned int intPtr = reinterpret_cast<long unsigned int>(this);
		_nameObject = std::to_string(intPtr);
	}

	inline void setName(const UniqueId& id, const unsigned short int lenght = 0) {
		_nameObject = id.getIdAsString(lenght);
	}

	template <class ValueT>
	inline void setName(const ValueT value, const unsigned short int lenght = 0) {
		_nameObject = UniqueId::getIdAsString(value, lenght);
	}

	inline void setName(const Name& name) {
		_nameObject = name._nameObject;
	}

	inline std::string getName() {
		return _nameObject;
	}

	inline const std::string& getName() const {
		return _nameObject;
	}

private:
	std::string _nameObject;
};


