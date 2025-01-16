#pragma once


class Skill;


class ISkillCondition
{
public:
	virtual ~ISkillCondition() = default;
	virtual bool Check(Skill* _checkSkill) = 0;
};

class ManaCondition : public ISkillCondition
{
public:
	bool Check(Skill* _checkSkill) override;
};

class CooldownCondition : public ISkillCondition
{
public:
	bool Check(Skill* _checkSkill) override;
};

class AliveCondition : public ISkillCondition
{
public:
	bool Check(Skill* _checkSkill) override;
};

class StunCondition : public ISkillCondition
{
public:
	bool Check(Skill* _checkSkill) override;
};