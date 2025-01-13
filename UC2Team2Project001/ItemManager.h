#pragma once
#include <unordered_map>
#include <memory>

class Item;

class ItemManager
{
private:
    // 아이템을 저장할 맵
    unordered_map<int, shared_ptr<Item>> items;

    // 다음에 저장될 키 
    int nextKey = 0;

    //생성자
    ItemManager();
    // 복사 생성자와 대입 연산자 삭제 (복사 방지)
    ItemManager(const ItemManager&) = delete;
    ItemManager& operator=(const ItemManager&) = delete;
    ItemManager(ItemManager&&) = delete;
    ItemManager& operator=(ItemManager&&) = delete;

public:
    // 소멸자
    ~ItemManager();
    
   // 싱글턴 객체 반환 메서드
   static ItemManager& GetInstance();
 
   // 아이템 추가 메서드
    void addItem(shared_ptr<Item> item);

   // 아이템 가져오기 메서드
    shared_ptr<Item> getItem(int key);

   //아이템 개수 출력
   int getItemCount() const;

   //랜덤 아이템 반환 매서드
   shared_ptr<Item> getRandomItem();
};

    