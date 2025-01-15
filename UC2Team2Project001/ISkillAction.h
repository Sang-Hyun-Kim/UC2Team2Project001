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