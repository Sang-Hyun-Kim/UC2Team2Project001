#pragma once
#include "Item.h"

class ThrowableItem : public Item {
public:
    ThrowableItem();

    ThrowableItem(int _itemNumber, const string& _name, const string& _description, int _value);
};
