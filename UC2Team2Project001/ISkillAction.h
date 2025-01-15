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

class AttackAction : public ISkillAction
{
public:
    AttackAction()
    {
    };

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
