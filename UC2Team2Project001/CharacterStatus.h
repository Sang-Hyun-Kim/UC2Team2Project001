#pragma once

#include <string>
#include <iostream>
#include <memory>

#define INFINITEDURATION 99999

using namespace std;

class Character;

// 캐릭터 상태 인터페이스
class ICharacterState
{
public:
	ICharacterState(const string& _inStateName, int _inDuration) : stateName(_inStateName), duration(_inDuration)
	{
	}

	virtual ~ICharacterState()
	{
	}

	// 상태 효과 적용(데미지, 버프, 디버프 등)
	virtual void ApplyEffect(Character* _target) = 0;

	// 매 턴마다 지속 시간 감소
	virtual void TickDuration();


	// 상태가 만료되었는지 확인
	virtual bool IsExpired() const;

	// 상태가 제거되기 전에 호출 (복구 로직 등)
	virtual void EffectBeforeRemove()
	{
	};

	// 상태 이름 반환
	virtual const std::string& GetStateName() const;

	// 지속 시간 반환 및 설정
	virtual int GetDuration() const;
	virtual void SetDuration(int _newDuration);

	// 상태 스택 추가(디폴트 구현)
	virtual void ApplyStack(int _newStack);

protected:
	string stateName;	// 상태 이름
	int duration;		// 상태 지속 시간

public:
	int currentStack = 1; // 상태 스택
};


// 화상 상태
class BurnState : public ICharacterState
{
public:
	BurnState(int _inDuration, int _inDamagePerTurn) : ICharacterState("Burn", _inDuration), damagePerTurn(_inDamagePerTurn)
	{
	}

	virtual ~BurnState()
	{
	}

	void ApplyEffect(Character* _target) override;

private:
	int damagePerTurn;
};


// 방어력 수정 상태
class ModifyDefenseState : public ICharacterState
{
public:
	ModifyDefenseState(int _inDuration, float _increaseValue) : ICharacterState("IncreaseDefense", _inDuration), modifyValue(_increaseValue)
	{
	};

	virtual ~ModifyDefenseState();

	void ApplyEffect(Character* _target) override;

	virtual void EffectBeforeRemove() override;

public:
	float modifyValue;
	bool isApplied = false;
	Character* target = nullptr;
};


// 기절 상태
class StunState : public ICharacterState
{
public:
	StunState(int _inDuration) : ICharacterState("Stun", _inDuration)
	{
	};

	virtual ~StunState() = default;

	// 상태 효과 적용
	void ApplyEffect(Character* _target) override
	{
	};
};


// 중독 상태
class PoisonState : public ICharacterState
{
public:
	PoisonState(int _inDuration, int _inDamagePerTurn, int _amountStack) : ICharacterState("PoisonState", _inDuration), damagePerTurn(_inDamagePerTurn), amountStack(_amountStack)
	{
		currentStack = amountStack;
	}

	virtual ~PoisonState()
	{
	}

	virtual void ApplyStack(int _newStack) override;

	void ApplyEffect(Character* _target) override;

public:
	int damagePerTurn = 0;
	int amountStack = 0;
};

// 불굴 상태
class UnbreakableState : public ICharacterState
{
public:
	Character* target = nullptr;

	UnbreakableState(int _duration);

	virtual ~UnbreakableState();

	// 상태 효과 적용
	void ApplyEffect(Character* _target) override;

	// 버프 삭제 전 기능
	virtual void EffectBeforeRemove() override;
};

//스텟 수정 상태
class ModifyStatState : public ICharacterState
{
public:
	ModifyStatState(int _duration, StatType _statType, float _value) : ICharacterState("ModifyStat", _duration), statType(_statType), value(_value), isApplied(false), target(nullptr)
	{
	}

	virtual void ApplyEffect(Character* _target) override;

	virtual void EffectBeforeRemove() override;

private:
	StatType statType;
	float value;
	bool isApplied;
	Character* target;
};

// 신성화 상태
class SanctificationState : public ICharacterState
{
public:
	SanctificationState(int _duration, float _increasValue);

	virtual void ApplyEffect(Character* _target) override;

	virtual void EffectBeforeRemove() override;
private:
	float increasValue;
	bool isApplied;
	Character* target;
};

//저주 인장 상태
class CursedSealState : public ICharacterState
{
public:
	CursedSealState(int _duration, int _damage, int _interval) : ICharacterState("CursedSeal", _duration), damage(_damage), interval(_interval), turnCounter(0)
	{
	}

	virtual void ApplyEffect(Character* _target) override;

	virtual void TickDuration() override;

private:
	int damage;       // 적용되는 데미지 양
	int interval;     // 몇 턴마다 발동되는지
	int turnCounter;  // 현재 턴을 추적
};
