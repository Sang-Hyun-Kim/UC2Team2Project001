#pragma once
#include <typeindex>

class Character;

class Skill;

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
	StatType type;
	float modifyValue;

	IBuffEffect(StatType _type, float _modifyValue) : type(_type), modifyValue(_modifyValue)
	{
	};

	virtual void PreEffect()
	{
	};
	virtual void PostEffect() override;
};


// 중독 효과
class IPoisonEffect : public ISkillEffect
{
public:
	IPoisonEffect(int amountStack=0);

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
	}

	virtual void PostEffect() override;

private:
	std::type_index stateType; // 제거할 상태의 타입
};