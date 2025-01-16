#pragma once

#include "IEventTypes.h"
#include <string>

using namespace std;


// ======================= 아이템 관련 이벤트 =======================
// 
// 아이템 구매 이벤트
class IItemPurchasedEvent : public IEvent
{
public:
	string buyerName; // 구매자 이름
	string itemName;  // 아이템 이름
	int cost;         // 가격

	IItemPurchasedEvent(const string& _buyer, const string& _item, int _cost): buyerName(_buyer), itemName(_item), cost(_cost) 
	{
	}
};

// 아이템 판매 이벤트
class IItemSoldEvent : public IEvent
{
public:
	string sellerName; // 판매자 이름
	string itemName;   // 아이템 이름
	int cost;          // 가격

	IItemSoldEvent(const string& _seller, const string& _item, int _cost)	: sellerName(_seller), itemName(_item), cost(_cost) 
	{
	}
};

#pragma region 더미코드
// 플레이어가 아이템을 획득하는 이벤트
class IPlayerGetItemEvent : public IEvent
{
public:
	IPlayerGetItemEvent()
	{
	}
};
#pragma endregion 더미코드
