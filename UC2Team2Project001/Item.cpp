
#include "pch.h"
#include "Item.h"

Item::Item(){}

Item::Item(int itemNumber, const string& name, const string& description, int value)
: itemNumber(itemNumber),name(name), description(description), value(value) {}

string Item::getInfoText(int type)
{
    switch (type)
    {
    case 0: // shop 이름, 설명, 가치
        return name + " " + description + " - " + to_string(value) + "Gold";
    case 1: // battle 이름, 설명
        return name + " " + description;
    default:
        break;
    }

    return "Item->getInfoText에 잘못된 매개변수가 들어갔습니다.";
}

void Item::info() const
{
    cout << "아이템명: " << name << endl
          << "설명: " << description << endl
          << "가치: " << value << " 골드" << endl;
}
