#pragma once

#include <memory>
#include <vector>
#include <functional>

template <class ItemT>
#define ItemTPtrT shared_ptr<ItemT>

class ItemsClass
{
public:
	virtual glm::mat4x4 getMatrix() = 0;
	virtual void update() {}

	inline static void clear() {
		delete _items;
		_items = nullptr;
	}
	inline static ItemTPtrT addItem()
	{
		ItemT* item = new ItemT();
		ItemTPtrT itemPtr = ItemTPtrT(item);
		getItems().push_back(itemPtr);

		return itemPtr;
	}
	inline static void updateItems() {
		if (_function) {
			_function();
		}

		for (auto& item : getItems()) {
			item->update();
		}

		remove();
	}
	inline static void setFunction(std::function<void(void)> function) {
		_function = function;
	}
	inline static std::vector<ItemTPtrT>& getItems() {
		if (!_items) {
			_items = new std::vector<ItemTPtrT>();
		}
		return *_items;
	}
	// TODO:
	void static remove() {
		std::vector<ItemTPtrT>* newItems = new std::vector<ItemTPtrT>();
		for (auto& item : getItems()) {
			if (item->_live && *item->_live > 0.0f) {
				newItems->push_back(item);
			}
		}
		delete _items;
		_items = newItems;
	}

private:
	static std::vector<ItemTPtrT>* _items;
	static std::function<void(void)> _function;
};

template <class ItemT>
std::vector<ItemTPtrT>* ItemsClass<ItemT>::_items = nullptr;

template <class ItemT>
std::function<void(void)> ItemsClass<ItemT>::_function = 0;