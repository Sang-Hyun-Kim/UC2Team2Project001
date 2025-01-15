
#include "pch.h"
#include "Item.h"

Item::Item(){}

Item::Item(int itemNumber, const string& name, const string& description, int value)
: itemNumber(itemNumber),name(name), description(description), value(value) {}

string Item::getInfoTextForShop()
{
    string prompt = "아이템명: " + name + " 가격: " + to_string(value) + "골드 " + " 설명: " + description;

    return prompt;
}

void Item::info() const
{
    cout << "아이템명: " << name << endl
          << "설명: " << description << endl
          << "가치: " << value << " 골드" << endl;
}
