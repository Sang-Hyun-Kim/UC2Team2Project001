#pragma once
#include "ConsumableItem.h"

class Potion: public ConsumableItem {
public:
    Potion();

    Potion(int _itemNumber, const string& _name, const string& _description, int _value);
};
