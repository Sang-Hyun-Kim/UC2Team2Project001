#include "pch.h"
#include "ItemManager.h"

#include "HealthPotion.h"
#include "AttackBoostPotion.h"
#include "ManaPotion.h"
#include "DefenseBoostPotion.h"
#include "PoisonBottle.h"
#include "FireBottle.h"

ItemManager::ItemManager()
{
   items[nextKey++] = make_shared<HealthPotion>(nextKey);
   items[nextKey++] = make_shared<ManaPotion>(nextKey);
   items[nextKey++] = make_shared<AttackBoostPotion>(nextKey);
   items[nextKey++] = make_shared<DefenseBoostPotion>(nextKey);
   items[nextKey++] = make_shared<PoisonBottle>(nextKey);
   items[nextKey++] = make_shared<FireBottle>(nextKey);
}

ItemManager::~ItemManager()
{
   items.clear();
}

ItemManager& ItemManager::GetInstance()
{
    // 싱글턴 인스턴스
    static ItemManager instance;
    
    return instance;
}

void ItemManager::addItem(shared_ptr<Item> item)
{
    items[nextKey++] = item;
}

shared_ptr<Item> ItemManager::getItem(int key)
{
    auto it = items.find(key);
    if (it != items.end())
    {
        return it->second->clone();
    }
    return nullptr; // 해당 키에 아이템이 없으면 nullptr 반환
}

int ItemManager::getItemCount() const
{
    return static_cast<int>(items.size());
}

shared_ptr<Item> ItemManager::getRandomItem()
{
    if (items.empty()) {
        return nullptr; // 아이템이 없으면 nullptr 반환
    }

    random_device rd; //시드값 생성
    mt19937 gen(rd());//랜덤값 생성
    uniform_int_distribution<> dist(0, nextKey - 1);//범위 제한

    int randomIndex = dist(gen);
    return  items[randomIndex]->clone();
}
