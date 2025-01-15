#pragma once

class Character;

class Skill;

class ISkillAction
{
public:
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
	virtual void ExecuteAction() override;

	~AttackAction() = default;
};

// 럭키스트라이크
// 불사자