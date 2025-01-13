#pragma once
#include "pch.h"

class Item;
class Character;

struct FItemData {
    shared_ptr<Item> item; // 아이템 객체
    int count = 0;         // 아이템 개수

    // 생성자
    FItemData(shared_ptr<Item> item = nullptr, int count = 0)
        : item(item), count(count) {}
};

class Inventory {
private:
    vector<FItemData> inven; // <인덱스, 아이템 데이터>
    int gold;                                         // 인벤토리 보유 골드
    Character* owner;                                 // 인벤토리 소유 캐릭터

public:
    // 생성자
    Inventory(Character* owner = nullptr);

    // 아이템 추가
    void addItem(shared_ptr<Item> item, int count = 1);

    // 아이템 삭제
    void removeItem(int index, int count = 1);

    // 아이템 사용
    void useItem(int index, Character* target = nullptr);
    
    // 아이템 수량 확인
    int getItemCount(int index) const;

    // 골드 getter
    int getGold() const;

    // 골드 추가/제거
    void addGold(int amount);

    void removeGold(int amount);

    // 인벤토리 정보 출력
    void displayInventory() const;

    // 인벤토리 개수 확인
    bool IsEmpty() const;
    // 소멸자
    ~Inventory() {}
};