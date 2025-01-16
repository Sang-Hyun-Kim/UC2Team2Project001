#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "Character.h"

Inventory::Inventory(Character* _owner)
	: owner(_owner), gold(0){}

shared_ptr<Item> Inventory::GetItemWithIndex(int _index)
{
    return inven[_index].item;
}

void Inventory::addItem(shared_ptr<Item> _item, int _count) {
    if (_count <= 0) {
        cout << "0개 이하로 추가할 수 없습니다." << endl;
        return;
    }

    // 이미 존재하는 아이템인지 확인
    auto it =
        find_if(
        inven.begin(),
        inven.end(),
        [&_item](const FItemData& data)
            {
            return data.item->getItemNumber() == _item->getItemNumber();
            }
        );

    if (it != inven.end()) {
        // 아이템이 이미 존재하면 개수만 증가
        it->count += _count;
    }
    else {
        // 신규 아이템 추가
        inven.push_back(FItemData(_item, _count));
    }
}

void Inventory::removeItem(int _index, int _count) {
    //입력시 인덱스가 + 1된걸 선택함으로 - 1해준다
    //index--;
    if (_index >= 0 && _index < inven.size()) {
        FItemData& data = inven[_index];

        if (data.count <= _count) {
            // 아이템의 수량이 요청된 값보다 작거나 같으면 삭제
            inven.erase(inven.begin() + _index);
        }
        else {
            // 아이템 수량 감소
            data.count -= _count;
        }
    }
    else {
        cout << "해당 인덱스에 아이템이 없습니다!" << endl;
    }
}

void Inventory::useItem(int _index, Character* _target)
{
    // 타겟이 없으면 owner를 기본값으로 설정
    if (!_target) {
        _target = owner;
    }
    //입력시 인덱스가 + 1된걸 선택함으로 - 1해준다
    //index--;
    if (_index >= 0 && _index < inven.size()) 
    {
        FItemData& itemData = inven[_index];

        cout << itemData.item.get()->getName() <<"이 사용되었습니다!" << endl;

        // 아이템의 use 메서드 호출
        itemData.item->use(_target);

        // 사용 후 아이템 수량 감소
        itemData.count -= 1;
        if (itemData.count <= 0) {
            inven.erase(inven.begin() + _index);
        }
    }
    else {
        cout << "해당 인덱스에 아이템이 존재하지 않습니다!" << endl;
    }
}

int Inventory::getItemCount(int _index) const {
    //입력시 인덱스가 + 1된걸 선택함으로 - 1해준다
    //index--;
    if (_index >= 0 && _index < inven.size()) {
        return inven[_index].count;
    }
    return 0;  // 인덱스에 아이템이 없으면 0 반환
}

int Inventory::getGold() const {
    return gold;
}

void Inventory::addGold(int _amount) {
    if (_amount > 0) {
        gold += _amount;
        //cout << "추가된 골드 :  " << amount << " gold." << endl;
    }
    else {  
        //cout << "0보다 작은 수는 추가할 수 없습니다."  << endl;
    }
}

void Inventory::removeGold(int _amount) {
    if (_amount > 0 && gold >= _amount) {
        gold -= _amount;
        //cout << "빠져나간 골드 :  " << amount << " gold." << endl;
    }
    else {
        //cout << "골드가 부족하거나 0보다 작은 값입니다." << endl;
    }
}

void Inventory::displayInventory(int _intype) const {
    cout << "==== 인벤토리 아이템 정보 ====" << endl;

    if (inven.empty()) {
        cout << "- 인벤토리가 비어있습니다." << endl;
    }
    else {
        for (size_t i = 0; i < inven.size(); ++i) {
            ostringstream itemInfo;
            itemInfo << i + 1 << "." << inven[i].item->getName() << "x" << inven[i].count << " ";

            switch (_intype) {
            case 0: // 이름, 설명, 개수, 가치 출력
                itemInfo << inven[i].item->getValue() << " Gold  [" << inven[i].item->getDescription() << "]";
                break;

            case 1: // 이름, 설명, 개수 출력
                itemInfo << " [Count: " << inven[i].count << "]";
                break;

            case 2: // 이름, 설명만 출력
            default:
                break;
            }
            std::cout << itemInfo.str() << std::endl;
        }
    }
    cout << "Gold: " << gold << endl;
    cout << "==== 인벤토리 끝 ====" << endl;
}

vector<string> Inventory::GetInventoryInfoWithString(int _type) const
{
    vector<string> inventoryInfos(inven.size(), "");

    if (_type == 0) //배틀, 인벤토리 열기
    {
        for (size_t i = 0; i < inven.size(); ++i)
        {
            inventoryInfos[i] = to_string(i + 1) + ". " + inven[i].item->getName() + " x" + to_string(inven[i].count) + " : " + inven[i].item->getDescription();
        }
    }
    else //상점
    {
        for (size_t i = 0; i < inven.size(); ++i)
        {
            auto item = inven[i].item;
            

            inventoryInfos[i] = to_string(i + 1) + ". " + item->getInfoTextForShop();
        }
    }

    return inventoryInfos;
}

int Inventory::getInventorySize() const
{
    return inven.size();
}

int Inventory::GetItemVelue(int _index) const
{
    return inven[_index].item->getValue();
}

bool Inventory::IsEmpty() const
{
    return inven.size() <= 0;
}
