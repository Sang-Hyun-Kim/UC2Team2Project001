#include "pch.h"
#include "ConsumableItem.h"

ConsumableItem::ConsumableItem(const string& name, const string& description, int value)
	: Item(name, description, value) {}
