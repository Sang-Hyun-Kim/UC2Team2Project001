#pragma once

class Character;

class Skill;

class ISkillAction
{
public:
	virtual ~ISkillAction() = default;

	virtual void ExecuteAction() = 0;

	void SetSkill(shared_ptr<Skill> _skill)
	{
		parentSkill = _skill;
	}

protected:
	shared_ptr<Skill> parentSkill;
};

class AttackAction : public ISkillAction
{
	virtual void ExecuteAction() override;
};

// 럭키스트라이크
// 불사자