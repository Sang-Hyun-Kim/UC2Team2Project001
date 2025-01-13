#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "Character.h"

Inventory::Inventory(Character* owner)
	: owner(owner), gold(0){}

void Inventory::addItem(shared_ptr<Item> item, int count) {
    if (count <= 0) {
        cout << "0개 이하로 추가할 수 없습니다." << endl;
        return;
    }

    // 이미 존재하는 아이템인지 확인
    auto it =
        find_if(
        inven.begin(),
        inven.end(),
        [&item](const FItemData& data)
            {
            return data.item->getItemNumber() == item->getItemNumber();
            }
        );

    if (it != inven.end()) {
        // 아이템이 이미 존재하면 개수만 증가
        it->count += count;
    }
    else {
        // 신규 아이템 추가
        inven.push_back(FItemData(item, count));
    }
}

void Inventory::removeItem(int index, int count) {
    if (index >= 0 && index < inven.size()) {
        FItemData& data = inven[index];

        if (data.count <= count) {
            // 아이템의 수량이 요청된 값보다 작거나 같으면 삭제
            inven.erase(inven.begin() + index);
        }
        else {
            // 아이템 수량 감소
            data.count -= count;
        }
    }
    else {
        cout << "해당 인덱스에 아이템이 없습니다!" << endl;
    }
}

void Inventory::useItem(int index, Character* target)
{
    // 타겟이 없으면 owner를 기본값으로 설정
    if (!target) {
        target = owner;
    }
    
    if (index >= 0 && index < inven.size()) 
    {
        FItemData& itemData = inven[index];

        cout << itemData.item.get()->getName() <<"이 사용되었습니다!" << endl;

        // 아이템의 use 메서드 호출
        itemData.item->use(target);

        // 사용 후 아이템 수량 감소
        itemData.count -= 1;
        if (itemData.count <= 0) {
            inven.erase(inven.begin() + index);
        }
    }
    else {
        cout << "해당 인덱스에 아이템이 존재하지 않습니다!" << endl;
    }
}

int Inventory::getItemCount(int index) const {
    if (index >= 0 && index < inven.size()) {
        return inven[index].count;
    }
    return 0;  // 인덱스에 아이템이 없으면 0 반환
}

int Inventory::getGold() const {
    return gold;
}

void Inventory::addGold(int amount) {
    if (amount > 0) {
        gold += amount;
        cout << "추가된 골드 :  " << amount << " gold." << endl;
    }
    else {  
        cout << "0보다 작은 수는 추가할 수 없습니다."  << endl;
    }
}

void Inventory::removeGold(int amount) {
    if (amount > 0 && gold >= amount) {
        gold -= amount;
        cout << "빠져나간 골드 :  " << amount << " gold." << endl;
    }
    else {
        cout << "골드가 부족하거나 0보다 작은 값입니다." << endl;
    }
}

void Inventory::displayInventory() const {
    cout << "==== 인벤토리 아이템 정보 ====" << endl;

    if (inven.empty()) {
        cout << "- 인벤토리가 비어있습니다." << endl;
    } else {
        for (size_t i = 0; i < inven.size(); ++i) {
            cout << "===============" << endl;
            cout << "Index: " << i << endl;
            cout << "Item: ";
            inven[i].item->info(); // 아이템 정보 출력
            cout << " Count: " << inven[i].count << endl;
            cout << "===============" << endl;
        }
    }
    cout << "Gold: " << gold << endl;
    cout << "==== 인벤토리 끝 ====" << endl;
}

bool Inventory::IsEmpty() const
{
    return inven.size() <= 0;
}
