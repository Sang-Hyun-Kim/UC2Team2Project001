#pragma once

class Character;

class Skill;

class ISkillAction
{
public:
	ISkillAction()
	{

	}

	virtual ~ISkillAction() = default;

	virtual void ExecuteAction() = 0;

	void SetSkill(Skill* _skill)
	{
		parentSkill = _skill;
	}

public:
	Skill* parentSkill;
};

class NormalAttackAction : public ISkillAction
{
public:
	NormalAttackAction()
	{
	};

	~NormalAttackAction() = default;

	virtual void ExecuteAction() override;
};


class AttackAction : public ISkillAction
{
public:
	AttackAction()
	{
	}

	AttackAction(float _attackDamage)
	{
		attackDamage = _attackDamage;
	}

	~AttackAction() = default;

	virtual void ExecuteAction() override;

	float attackDamage = 0;
};


//중독 상태를 가져와서 스택을2배로 만듭니다.
class PoisonIntensifierAction : public ISkillAction
{
public:
	PoisonIntensifierAction()
	{

	}

	~PoisonIntensifierAction() = default;

	virtual void ExecuteAction() override;
};


//중독 상태 2스텍을 쌓고 중독 카운트만큼 데미지를 입힌다
class PoisonPogAction : public ISkillAction
{
public:
	PoisonPogAction()
	{

	}

	~PoisonPogAction() = default;

	virtual void ExecuteAction() override;
};

//쌓은 중독 카운트를 모두 소비하여 폭발시킵니다.
class PoisonTriggerAction : public ISkillAction
{
public:
	PoisonTriggerAction()
	{

	}

	~PoisonTriggerAction() = default;

	virtual void ExecuteAction() override;
};


// 빙하의 파편 동작 정의
class GlacialShardAction : public ISkillAction
{
public:
	GlacialShardAction(float _damageMultiplier, float _defenseReduction, int _defenseDuration) : damageMultiplier(_damageMultiplier), defenseReduction(_defenseReduction), defenseDuration(_defenseDuration)
	{
	}

	virtual void ExecuteAction() override;

private:
	float damageMultiplier;  // 공격력 배율
	float defenseReduction;  // 방어력 감소 비율
	int defenseDuration;     // 방어력 감소 지속 시간
};

// 분노모으기 동작 정의
class ChargeRageAction : public ISkillAction
{
public:
	ChargeRageAction(float _rageMultiplier) : rageMultiplier(_rageMultiplier) {}

	virtual void ExecuteAction() override;

private:
	float rageMultiplier; // 다음 공격에 추가될 피해 배율
};