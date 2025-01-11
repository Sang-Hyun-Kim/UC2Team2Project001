#pragma once
#include "ConsumableItem.h"

class Potion: public ConsumableItem {
public:
    Potion()
    {

    }

    Potion(const string& name, const string& description, int value);
};
