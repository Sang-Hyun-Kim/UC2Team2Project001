#pragma once

#include "ISkillAction.h"
#include "ISkillEffect.h"

using namespace std;

class Character;

struct FSkillData
{
	string skillName;
	int mpCost;
	int cooldown;
	shared_ptr<ISkillAction> action;
	vector<shared_ptr<ISkillEffect>> effects;
	shared_ptr<Character> owner;
	shared_ptr<Character> target;

	FSkillData() = default;

	FSkillData(const string& _skillName, int _mpCost, int _cooldown, const shared_ptr<ISkillAction>& _action, const vector<shared_ptr<ISkillEffect>>& _effects, const shared_ptr<Character>& _owner, const shared_ptr<Character>& _target)
		: skillName(_skillName), mpCost(_mpCost), cooldown(_cooldown), action(_action), effects(_effects), owner(_owner), target(_target)
	{
	}
};

class Skill
{
protected:
	FSkillData skillData;

public:

	bool IsCoolDown()
	{
		return true;
	}

	virtual void UseSkill() = 0;

	virtual FSkillData GetSkillData()
	{
		return skillData;
	}

	//virtual vector<Character> GetSearchFindTarget();

	virtual shared_ptr<Character> GetTarget()
	{
		return skillData.target;
	}

	virtual void SetOwner(shared_ptr<Character> _owner)
	{
		skillData.owner = _owner;
	}

	virtual void SetTarget(shared_ptr<Character> _newTarget)
	{
		skillData.target = _newTarget;
	};
};

class ActiveSkill : public Skill
{
public:
	ActiveSkill(FSkillData _skillData)
	{
		skillData = _skillData;
	};
	virtual void UseSkill() override;
};

class PassiveSkill : public Skill
{
	virtual void UseSkill() override;
};