#pragma once

#include "pch.h"

class Character;
//아이템 기본 클래스
class Item {
protected:
    string name;        // 아이템명
    string description; // 아이템 설명
    int value;              // 아이템 가치

public:
    //생성자
    Item(const string& name, const string& description, int value);

    virtual void use(Character& Target) = 0; // 순수 가상 함수
    void info() const;
    
    virtual ~Item() {}
};
    