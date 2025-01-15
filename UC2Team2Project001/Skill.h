#pragma once

#include "ISkillAction.h"
#include "ISkillEffect.h"

using namespace std;

class Character;
class ICharacterState;

struct FSkillData
{
	string skillName ="";
	int mpCost =0;
	int maxCooldown =99;
	int currentCooldown =0;
	shared_ptr<ISkillAction> action;
	vector<shared_ptr<ISkillEffect>> effects;
	shared_ptr<Character> owner;
	vector<shared_ptr<ICharacterState>> state;

	FSkillData() = default;

	FSkillData(const string& skillName, int mpCost, int maxCooldown)
		: skillName(skillName), mpCost(mpCost), maxCooldown(maxCooldown)
	{
	}

	FSkillData(const string& skillName, int mpCost, int maxCooldown, int currentCooldown)
		: skillName(skillName), mpCost(mpCost), maxCooldown(maxCooldown), currentCooldown(currentCooldown)
	{
	}

	FSkillData(const string& skillName, int mpCost, int maxCooldown, int currentCooldown, const shared_ptr<ISkillAction>& action, const vector<shared_ptr<ISkillEffect>>& effects, const shared_ptr<Character>& owner, const shared_ptr<Character>& target)
		: skillName(skillName), mpCost(mpCost), maxCooldown(maxCooldown), currentCooldown(currentCooldown), action(action), effects(effects), owner(owner)
	{
	}
};

class Skill
{
protected:
	FSkillData skillData;

public:

	Skill()
	{
	};

	Skill(shared_ptr<Character> _owner) 
	{
		skillData.owner = _owner;
	};

	template<typename T>
	void SkillInit()
	{
		skillData.action.get()->SetSkill(shared_ptr<T>(this));
		for (auto effect : skillData.effects)
		{
			effect.get()->SetSkill(shared_ptr<T>(this));
		}
	}

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

	virtual shared_ptr<Character> GetTarget();

	virtual void SetOwner(shared_ptr<Character> _owner)
	{
		skillData.owner = _owner;
	}

};

class ActiveSkill : public Skill
{
public:
	ActiveSkill()
	{
	};

	ActiveSkill(shared_ptr<Character> _owner) : Skill(_owner)
	{
	};

	ActiveSkill(shared_ptr<Character> _owner, const string& skillName, int mpCost, int maxCooldown) : Skill(_owner)
	{
		skillData = FSkillData(skillName, mpCost, maxCooldown);
	};

	virtual void UseSkill() override;
};

class PassiveSkill : public Skill
{
public:
	PassiveSkill()
	{
	};

	PassiveSkill(shared_ptr<Character> _owner) : Skill(_owner)
	{
	};

	PassiveSkill(shared_ptr<Character> _owner, const string& skillName, int mpCost, int maxCooldown) : Skill(_owner)
	{
		skillData = FSkillData(skillName, mpCost, maxCooldown);
	};

	virtual void UseSkill() override;
};