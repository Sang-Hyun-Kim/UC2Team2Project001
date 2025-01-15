#pragma once

// 전방 선언: Character 클래스는 이후에 정의됩니다.
class Character;

// 공격 전략 인터페이스
class IAttackStrategy 
{
public:
	virtual ~IAttackStrategy() = default;

	// 공격 행동을 정의하는 순수 가상 함수
	virtual void Attack(Character* _self, Character* _target) = 0;
};

// 방어 전략 인터페이스
class IDefenseStrategy 
{
public:
	virtual ~IDefenseStrategy() = default;

	// 방어로 인해 받는 피해를 계산하는 순수 가상 함수
	virtual int CalculateDamageReceived(Character* _self, int _incomingDamage) = 0;
};

// 기본 공격 전략
class BasicAttackStrategy : public IAttackStrategy 
{
public:
	// 기본 공격 동작 구현
	virtual void Attack(Character* _self, Character* _target) override;
};

// 방어 전략: 데미지를 차단(Block)
class BlockDefenseStrategy : public IDefenseStrategy 
{
public:
	// 방어 시 받는 최종 피해 계산 구현
	virtual int CalculateDamageReceived(Character* _self, int _incomingDamage) override;
};

//// 방어 전략: 회피(Evade)
//class EvadeDefenseStrategy : public IDefenseStrategy 
//{
//public:
//	// 회피 시 받는 최종 피해 계산 구현
//	virtual int CalculateDamageReceived(Character* _self, int _incomingDamage) override;
//};
