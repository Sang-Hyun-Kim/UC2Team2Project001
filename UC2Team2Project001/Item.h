#pragma once

#include "pch.h"

class Character;

//아이템 기본 클래스
class Item {
protected:
    int itemNumber;
    string name;        // 아이템명
    string description; // 아이템 설명
    int value;              // 아이템 가치

public:
    //생성자
    Item();
    Item(int itemNumber,const string& name, const string& description, int value);

    int getItemNumber() const { return itemNumber; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    int getValue() const { return value; }

    virtual void use(Character& Target) = 0; // 순수 가상 함수

    //프로토 타입 패턴을 위한 clone 함수
    virtual shared_ptr<Item> clone() const = 0;
    void info() const;
    
    virtual ~Item() {}
};
    