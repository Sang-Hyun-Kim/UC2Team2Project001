#pragma once

#include "IEventTypes.h"
#include <string>
#include "CharacterTypes.h"

using namespace std;


// ======================= 캐릭터 관련 이벤트 =======================
// 캐릭터가 데미지를 받는 이벤트

class ICharacterDamagedEvent : public IEvent
{
public:
	string characterName; // 캐릭터 이름
	int damage;           // 받은 데미지
	int hp;               // 남은 HP

	ICharacterDamagedEvent(const string& _name, int _dmg, int _hp) : characterName(_name), damage(_dmg), hp(_hp)
	{
	}
};

// 캐릭터가 사망하는 이벤트
class ICharacterDeadEvent : public IEvent
{
public:
	string characterName;     // 캐릭터 이름
	FCharacterReward reward;  // 사망 시 보상

	ICharacterDeadEvent(const string& _name, FCharacterReward _reward) : characterName(_name), reward(_reward)
	{
	}
};

// 캐릭터가 공격하는 이벤트
class ICharacterAttackEvent : public IEvent
{
public:
	string characterName; // 캐릭터 이름
	int damage;           // 공격 데미지
	ICharacterAttackEvent(const string& _name, int _dmg) : characterName(_name), damage(_dmg)
	{
	}
};

// 캐릭터가 방어하는 이벤트
class ICharacterDefenseEvent : public IEvent
{
public:
	string characterName;   // 캐릭터 이름
	int incomingDamage;     // 들어오는 데미지
	int defenseValue;       // 방어 값
	ICharacterDefenseEvent(const string& _name, int _incomingDamage, int _defenseValue) : characterName(_name), incomingDamage(_incomingDamage), defenseValue(_defenseValue)
	{
	}
};

// 캐릭터가 레벨업하는 이벤트
class ICharacterLevelUpEvent : public IEvent
{
public:
	string characterName; // 캐릭터 이름
	int level;            // 레벨

	ICharacterLevelUpEvent(const string& _name, int _level) : characterName(_name), level(_level)
	{
	}
};

class ICharacterCreateEvent : public IEvent
{
public:
	string name;
	ICharacterCreateEvent(const string& _name) : name(_name) 
	{
	}
};

// 캐릭터 스탯이 0이 되는 이벤트
class ICharacterStatZeroEvent : public IEvent
{
public:
	string characterName;
	ICharacterStatZeroEvent(const string& _name) : characterName(_name)
	{
	}
};

class IPlayerAddSkillEvent : public IEvent
{
public:
	string skillName;
	string ownerName;
	bool bIsPlayer;
	IPlayerAddSkillEvent(const string& _skillName, const string& _ownerName, bool _bIsPlayer) : skillName(_skillName), ownerName(_ownerName), bIsPlayer(_bIsPlayer)
	{
	}
};