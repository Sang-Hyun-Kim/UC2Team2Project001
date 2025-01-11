
#include "pch.h"
#include "Item.h"

Item::Item(const string& name, const string& description, int value)
: name(name), description(description), value(value) {}

void Item::info() const
{
    cout << "아이템명: " << name << endl
          << "설명: " << description << endl
          << "가치: " << value << " 골드" << endl;
}
