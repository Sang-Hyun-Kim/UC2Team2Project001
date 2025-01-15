#pragma once

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
	shared_ptr<ICharacterState> state;
	IBuffEffect(shared_ptr<ICharacterState> _state);

	virtual void PreEffect()
	{
	};
	virtual void PostEffect() override;
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