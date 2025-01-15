#pragma once
// 캐릭터(공통 베이스 클래스)

#include <iostream>
#include <memory>
#include <algorithm>
#include "CharacterTypes.h"
#include "StatType.h"

class USkillComponent;
class CombatComponent;

struct StatsData;

class IAttackStrategy;
class IDefenseStrategy;

class Item;
class UStatusComponent;

class UStatsComponent;

using namespace std;

class Character
{

public:
	//생성자 및 소멸자
	Character();

	Character(const string& _name);

public:
	void Initialize(const StatsData& _stats);

	virtual ~Character() {}

	virtual void CreateCharacterReward() {}

	virtual void UseItem(const string& _itemName);

	// 매니저 등록
	void ManagerRegister();

public:

	// 캐릭터 이름 반환
	const string& GetName() { return characterName; }

public:

	//스텟 컴포넌트
	shared_ptr<UStatsComponent> statManager;

	// 컴뱃 매니저
	shared_ptr<CombatComponent> combatManager;

	// 스킬 매니저
	shared_ptr<USkillComponent> skillManager;

	shared_ptr<UStatusComponent> StatusComponent;

protected:
	// 공격/방어 전략
	shared_ptr<IAttackStrategy> AttackStrategy;
	shared_ptr<IDefenseStrategy> DefenseStrategy;

public:

	// 캐릭터 사망 보상
	FCharacterReward characterReward;

protected:
	string characterName;
};


