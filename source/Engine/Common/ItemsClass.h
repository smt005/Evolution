#pragma once

#include <memory>
#include <vector>

template <class ItemT>
#define ItemTPtrT shared_ptr<ItemT>

class ItemsClass
{
public:
	virtual glm::mat4x4 getMatrix() = 0;
	virtual ModelPtr getModel() = 0;

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
		for (auto& item : _items) {
			item->update();
		}
	}
	inline static std::vector<ItemTPtrT>& getItems() {
		return _items;
	}

private:
	static std::vector<ItemTPtrT> _items;
};

template <class ItemT>
std::vector<ItemTPtrT> ItemsClass<ItemT>::_items;
