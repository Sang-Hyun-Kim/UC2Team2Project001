#pragma once

class Character;

class ISkillAction
{
public:
	virtual ~ISkillAction() = default;

	virtual void ExecuteAction(Character* _self, Character* _target) = 0;
};

class AttackAction : public ISkillAction
{
	virtual void ExecuteAction(Character* _self, Character* _target) override;
};

// 럭키스트라이크
// 불사자