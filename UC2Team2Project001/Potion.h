#pragma once

#include "ConsumableItem.h"
class Potion : public ConsumableItem {
public:
    Potion(const string& name, const string& description, int value);
};

