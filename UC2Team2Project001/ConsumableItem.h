#pragma once
#include "Item.h"

class ConsumableItem : public Item {
public:
    ConsumableItem();

    ConsumableItem(int itemNumber,const string& name, const string& description, int value);
};
