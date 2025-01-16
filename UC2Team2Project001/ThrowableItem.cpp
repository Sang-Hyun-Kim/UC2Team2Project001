#include "pch.h"
#include "ThrowableItem.h"

ThrowableItem::ThrowableItem()
{
}

ThrowableItem::ThrowableItem(int _itemNumber, const string& _name, const string& _description, int _value)
	: Item(_itemNumber, _name, _description, _value)
{
}
