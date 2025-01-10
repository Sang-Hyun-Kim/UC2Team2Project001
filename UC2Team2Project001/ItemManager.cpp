#include "pch.h"
#include "ItemManager.h"

ItemManager::ItemManager(){}

ItemManager::~ItemManager()
{
   //items.clear();
}

//ItemManager* ItemManager::getInstance()
//{
//    if (!instance)
//    {
//        instance = new ItemManager();
//    }
//    return instance;
//}
//
//void ItemManager::addItem(shared_ptr<Item> item)
//{
//    items[nextKey++] = item;
//}
//
//shared_ptr<Item> ItemManager::getItem(int key)
//{
//    auto it = items.find(key);
//    if (it != items.end())
//    {
//        return it->second;
//    }
//    return nullptr; // 해당 키에 아이템이 없으면 nullptr 반환
//}
//
//int ItemManager::getItemCount() const
//{
//    return static_cast<int>(items.size());
//}
