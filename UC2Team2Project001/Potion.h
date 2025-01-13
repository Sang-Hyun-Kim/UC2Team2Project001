#pragma once
#include "ConsumableItem.h"

class Potion: public ConsumableItem {
public:
    Potion();

    Potion(int itemNumber, const string& name, const string& description, int value);
};
