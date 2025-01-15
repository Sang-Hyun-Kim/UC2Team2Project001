#pragma once

#include <string>
#include <iostream>
#include <memory>


class Character;

/**
 * @brief 캐릭터에게 적용되는 '상태'를 나타내는 인터페이스
 *
 * - ApplyEffect(Character* Target): 상태 효과를 적용
 * - TickDuration(): 매 턴마다 1씩 지속 시간 감소
 * - IsExpired(): 남은 지속 시간이 0 이하라면 true
 */
class ICharacterState
{
public:
	ICharacterState(const std::string& inStateName, int inDuration) : StateName(inStateName), Duration(inDuration)
	{
	}

	virtual ~ICharacterState() = default;

	// 상태 효과 적용(데미지, 버프, 디버프 등)
	virtual void ApplyEffect(Character* Target) = 0;

	// 매 턴마다 1씩 줄여나가는 메서드
	virtual void TickDuration()
	{
		if (Duration > 0)
		{
			--Duration;
		}
	}

	// 남은 턴이 0 이하인지 확인
	virtual bool IsExpired() const
	{
		return Duration <= 0;
	}

	// 상태 이름 Get
	virtual const std::string& GetStateName() const
	{
		return StateName;
	}

	// 현재 상태의 남은 지속 턴(읽기/쓰기)
	virtual int GetDuration() const
	{
		return Duration;
	}

	virtual void SetDuration(int NewDuration)
	{
		Duration = NewDuration;
	}

protected:
	std::string StateName;
	int Duration;
};



/**
 * @brief 화상(Burn) 상태
 * - 매 턴마다 일정 데미지를 입힘
 */
class BurnState : public ICharacterState
{
public:
	BurnState(int inDuration, int inDamagePerTurn) : ICharacterState("Burn", inDuration), DamagePerTurn(inDamagePerTurn)
	{
	}

	virtual ~BurnState() = default;

	// 상태 효과 적용
	void ApplyEffect(Character* Target) override;

private:
	int DamagePerTurn;
};
