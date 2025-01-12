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
	ICharacterAttackEvent(const string& InCharacterName,int InDamage)
		: CharacterName(InCharacterName), Damage(InDamage) {}
};

// 캐릭터 방어 이벤트
class ICharacterDefenseEvent : public IEvent
{
public:
	string CharacterName;
	int IncomingDamage;
	int FinalDamage;
	ICharacterDefenseEvent(const string& InCharacterName, int InIncomingDamage, int InFinalDamage)
		: CharacterName(InCharacterName), IncomingDamage(InIncomingDamage), FinalDamage(InFinalDamage) {}
};

class ILevelUpEvent : public IEvent
{
public:
	string CharacterName;
	int Level;

	ILevelUpEvent(const std::string& name,int InLevel) : CharacterName(name) , Level(InLevel)
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
