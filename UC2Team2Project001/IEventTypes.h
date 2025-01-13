#pragma once

#include <string>
#include <memory>
#include "CharacterTypes.h"

using namespace std;

// 모든 이벤트의 공통 부모
class IEvent
{
public:
	virtual ~IEvent() = default;
};

// 캐릭터가 데미지를 받는 이벤트
class ICharacterDamagedEvent : public IEvent
{
public:
	string CharacterName;
	int Damage;
	int HP;

	ICharacterDamagedEvent(const std::string& name, int dmg, int InHP) : CharacterName(name), Damage(dmg), HP(InHP)
	{
	}
};

// 캐릭터가 죽는 이벤트
class ICharacterDeadEvent : public IEvent
{
public:
	string CharacterName;
	FCharacterReward Reward;

	ICharacterDeadEvent(const std::string& name, FCharacterReward InReward) : CharacterName(name), Reward(InReward)
	{
	}
};

// 캐릭터 공격 이벤트
class ICharacterAttackEvent : public IEvent
{
public:
	string CharacterName;
	int Damage;
	ICharacterAttackEvent(const string& InCharacterName, int InDamage)
		: CharacterName(InCharacterName), Damage(InDamage) {
	}
};

// 캐릭터 방어 이벤트
class ICharacterDefenseEvent : public IEvent
{
public:
	string CharacterName;
	int IncomingDamage;
	int DefenseValue;

	ICharacterDefenseEvent(const string& InCharacterName, int InIncomingDamage, int InDefenseValue)
		: CharacterName(InCharacterName), IncomingDamage(InIncomingDamage), DefenseValue(InDefenseValue) 
	{
	}
};

class ILevelUpEvent : public IEvent
{
public:
	string CharacterName;
	int Level;

	ILevelUpEvent(const std::string& name, int InLevel) : CharacterName(name), Level(InLevel)
	{
	}
};


class IEnterEvent : public IEvent
{
	string PaseName;

};


//예시 코드
// 아이템 구매 이벤트
class IItemPurchasedEvent : public IEvent
{
public:
	std::string BuyerName;
	std::string ItemName;
	int Cost;

	IItemPurchasedEvent(const std::string& buyer, const std::string& item, int c) : BuyerName(buyer), ItemName(item), Cost(c)
	{
	}
};

class IItemSoldEvent : public IEvent
{
public:
	std::string SellerName;
	std::string ItemName;
	int Cost;

	IItemSoldEvent(const std::string& seller, const std::string& item, int c) : SellerName(seller), ItemName(item), Cost(c)
	{
	}
};

class IMoveEvent : public IEvent
{
public:
	std::string to;
	std::string from;

	IMoveEvent(const std::string& to, const std::string& from) :to(to), from(from) {}
};

class IDisplayMenuEvent : public IEvent
{
public:
	std::string title;
	std::vector<string> options;

	IDisplayMenuEvent() {}
	IDisplayMenuEvent(const std::string& title, const std::vector<string>& options) :title(title), options(options) {}
};

class IWrongInputEvent : public IEvent
{
public:
	IWrongInputEvent() {}
};

// 게임 종료 이벤트
class IGameExitEvent : public IEvent
{
public:
	IGameExitEvent() {}
};
// 게임 종료 이벤트
class IGameStartEvent : public IEvent
{
public:
	IGameStartEvent() {}
};

// 전투 중 공격 이벤트
class IBattleAttackEvent : public IEvent
{
public:
	IBattleAttackEvent() {}
};

// 전투 중 스탯 확인 이벤트
class IBattleStatCheckEvent : public IEvent
{
public:
	IBattleStatCheckEvent() {}
};

// 전투 중 아이템 사용 이벤트
class IBattleUseItemEvent : public IEvent
{
public:
	IBattleUseItemEvent() {}
};