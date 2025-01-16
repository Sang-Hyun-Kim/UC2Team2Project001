#pragma once
#include "Item.h"

class ConsumableItem : public Item {
public:
    ConsumableItem();

    ConsumableItem(int _itemNumber,const string& _name, const string& _description, int _value);
};
