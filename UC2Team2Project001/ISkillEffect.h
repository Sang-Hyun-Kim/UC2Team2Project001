#pragma once
#include <typeindex>

class Character;
class Skill;
class ICharacterState;

class ICharacterState;


enum class StatType;

class ISkillEffect
{
public:
	Skill* parentSkill;

	vector<shared_ptr<ICharacterState>> states; //상태
public:
	virtual ~ISkillEffect() = default;

	void SetSkill(Skill* _skill)
	{
		parentSkill = _skill;
	}

	virtual void PreEffect() = 0;

	virtual void PostEffect() = 0;
};

// 흡혈 효과
class ILifeStealEffect : public ISkillEffect
{
public:
	float lifeAmount;

	ILifeStealEffect(float _lifeAmount) : lifeAmount(_lifeAmount)
	{
	};

	virtual void PreEffect()
	{
	};
	virtual void PostEffect() override;
};



// 버프 및 디버프 효과
class IBuffEffect : public ISkillEffect
{
public:
	shared_ptr<ICharacterState> state;
	IBuffEffect(shared_ptr<ICharacterState> _state, bool _isSelf);

	virtual void PreEffect()
	{
	};
	virtual void PostEffect() override;

	bool isSelf;
};

// 방어력 기반 피해 효과
class IDefenseBasedDamageEffect : public ISkillEffect
{
public:
	virtual void PreEffect()
	{
	};
	virtual void PostEffect() override;
};

// 일점 돌파 추가 효과
class IOnePointAttackEffect : public ISkillEffect
{
public:
	virtual void PreEffect()
	{
	};
	virtual void PostEffect() override;
};

// 기절 효과
class IStunEffect : public ISkillEffect
{
public:
	shared_ptr<ICharacterState> stunState;

	IStunEffect(int _duration);

	virtual void PreEffect()
	{
	};
	virtual void PostEffect() override;
};


// 중독 효과
class IPoisonEffect : public ISkillEffect
{
public:
	IPoisonEffect(int amountStack = 0);

	virtual void PreEffect()
	{
	};

	virtual void PostEffect() override;


};


// 상태를 제거합니다.
class IRemoveStateEffect : public ISkillEffect
{
public:
	// 생성자에서 제거할 상태의 타입 정보 받기
	IRemoveStateEffect(std::type_index _stateType) : stateType(_stateType)
	{

	}

	virtual void PreEffect() override
	{
	};

	virtual void PostEffect() override;

private:
	std::type_index stateType; // 제거할 상태의 타입
};

// 체력 회복 효과
class IHealingEffect : public ISkillEffect
{
public:
	float healAmount;
	IHealingEffect(float _healAmount);
	
	virtual void PreEffect() override;

	virtual void PostEffect()
	{
	};
};

// 불굴 상태
class IUnbreakableEffect : public ISkillEffect
{
public:
	IUnbreakableEffect();

	virtual void PreEffect() override
	{
	};

	virtual void PostEffect() override;
};

class LuckyRewardEffect : public ISkillEffect
{
public:
	LuckyRewardEffect(int _goldAmount) : goldAmount(_goldAmount)
	{
	}

	virtual void PreEffect() override
	{
	}

	virtual void PostEffect() override;
private:
	int goldAmount = 100; // 획득할 골드 양
};
