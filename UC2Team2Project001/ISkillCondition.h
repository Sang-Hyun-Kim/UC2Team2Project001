#pragma once


class Skill;


class ISkillCondition
{
public:
	virtual ~ISkillCondition() = default;
	virtual bool Check(Skill* _checkSkill) = 0;
	virtual void CannotUseSkill() = 0;

	Character* _owner;
};

class ManaCondition : public ISkillCondition
{
public:
	bool Check(Skill* _checkSkill) override;
	void CannotUseSkill() override;
};

class CooldownCondition : public ISkillCondition
{
public:
	bool Check(Skill* _checkSkill) override;
	void CannotUseSkill() override;
};

class AliveCondition : public ISkillCondition
{
public:
	bool Check(Skill* _checkSkill) override;
	void CannotUseSkill() override;
};

class StunCondition : public ISkillCondition
{
public:
	bool Check(Skill* _checkSkill) override;
	void CannotUseSkill() override;
};