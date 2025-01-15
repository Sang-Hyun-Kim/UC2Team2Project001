#pragma once

class Character;

class Skill;

enum class StatType;

class ISkillEffect
{
public:
	Skill* skill;
public:
	virtual ~ISkillEffect() = default;

	void SetSkill(Skill* _skill)
	{
		skill = _skill;
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