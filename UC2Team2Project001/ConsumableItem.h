#pragma once
#include "Item.h"

class ConsumableItem : public Item {
public:
    ConsumableItem(const string& name, const string& description, int value);
};