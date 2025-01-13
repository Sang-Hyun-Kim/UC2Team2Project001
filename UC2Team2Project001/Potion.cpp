#include "pch.h"
#include "Potion.h"

Potion::Potion(){}

Potion::Potion(int itemNumber, const string& name, const string& description, int value)
: ConsumableItem(itemNumber, name, description, value) {}
