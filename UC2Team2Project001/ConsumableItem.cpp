#include "pch.h"
#include "ConsumableItem.h"

ConsumableItem::ConsumableItem(){}

ConsumableItem::ConsumableItem(int itemNumber,const string& name, const string& description, int value)
: Item(itemNumber, name, description, value) {}
