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
	//virtual ModelPtr getModel() = 0;

	inline static void clear() {
		_items.clear();
	}
	inline static ItemTPtrT addItem()
	{
		ItemT* item = new ItemT();
		ItemTPtrT itemPtr = ItemTPtrT(item);
		_items.push_back(itemPtr);

		return itemPtr;
	}
	inline static void updateItems() {
		if (_function) {
			_function();
		}

		for (auto& item : _items) {
			item->update();
		}
	}
	inline static std::vector<ItemTPtrT>& getItems() {
		return _items;
	}
	inline static void setFunction(std::function<void(void)> function) {
		_function = function;
	}

private:
	static std::vector<ItemTPtrT> _items;
	static std::function<void(void)> _function;
};

template <class ItemT>
std::vector<ItemTPtrT> ItemsClass<ItemT>::_items;

template <class ItemT>
std::function<void(void)> ItemsClass<ItemT>::_function = 0;