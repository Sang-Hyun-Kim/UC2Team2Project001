#include "pch.h"
#include "Potion.h"

Potion::Potion(const string& name, const string& description, int value)
	: ConsumableItem(name, description, value) {}
