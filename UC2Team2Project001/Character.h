#pragma once

#include <iostream>
#include <memory>
#include <algorithm>



// Forward declarations
class IAttackStrategy;
class IDefenseStrategy;

class UStatsComponent;

using namespace std;


// 캐릭터(공통 베이스 클래스)
class Character 
{

public:
	//생성자 및 소멸자
	Character();

	Character(const string& InName);

	virtual ~Character() {}

	// 공격 및 피해 처리
	virtual void Attack(Character* Target);
	virtual void TakeDamage(int IncomingDamage);

	// 전략 설정
	void SetAttackStrategy(std::shared_ptr<IAttackStrategy> NewAttackStrategy);
	void SetDefenseStrategy(std::shared_ptr<IDefenseStrategy> NewDefenseStrategy);

public:
	// 캐릭터 이름 반환
	const string& GetName() { return CharacterName; }

public:
	// 스탯 컴포넌트
	shared_ptr<UStatsComponent> StatManager;

protected:
	string CharacterName;

	// 공격/방어 전략
	std::shared_ptr<IAttackStrategy> AttackStrategy;
	std::shared_ptr<IDefenseStrategy> DefenseStrategy;
};

