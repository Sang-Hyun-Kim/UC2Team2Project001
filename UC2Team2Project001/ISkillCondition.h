#pragma once


class Skill;


class ISkillCondition
{
public:
	virtual ~ISkillCondition() = default;
	virtual bool Check(Skill* chekckSkill) = 0;
};

class ManaCondition : public ISkillCondition
{
public:
	bool Check(Skill* chekckSkill) override;
};

class CooldownCondition : public ISkillCondition
{
public:
	bool Check(Skill* chekckSkill) override;
};

class AliveCondition : public ISkillCondition
{
public:
	bool Check(Skill* chekckSkill) override;
};