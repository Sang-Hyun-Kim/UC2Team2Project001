#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include "CharacterTypes.h"
#include "StatType.h"

struct StatsData;

class UStatusComponent;
class UStatsComponent;
class USkillComponent;
class UCombatComponent;

using namespace std;

class Character
{
public:
	// 생성자 및 소멸자
	Character();
	Character(const string& _name);
	virtual ~Character() {}

public:
	// 캐릭터 초기화 (스텟, 컴포넌트 등)
	virtual void Initialize();

	// 캐릭터 사망 보상 생성
	virtual void CreateCharacterReward() {}

	// 아이템 사용
	virtual void UseItem(const string& _itemName);

	// 컴포넌트 등록
	virtual void ManagerRegister();

	void PrintCharacterInfo(int type = 0);

public:
	// 캐릭터 이름 반환
	const string& GetName()
	{
		return displayName;
	}

public:
	//스텟 컴포넌트
	shared_ptr<UStatsComponent> statManager;

	// 전투 매니저
	shared_ptr<UCombatComponent> combatManager;

	// 스킬 매니저
	shared_ptr<USkillComponent> skillManager;

	// 상태 매니저
	shared_ptr<UStatusComponent> statusManager;

public:
	// 캐릭터 사망 보상
	FCharacterReward characterReward;

	bool bIsPlayer = false;

protected:
	// 캐릭터 이름(json에서 찾을 이름)
	string characterName = "Player";

	// 화면에 표시 될 이름
	string displayName;
};


