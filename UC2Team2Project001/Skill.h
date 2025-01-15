#pragma once

#include "ISkillAction.h"
#include "ISkillEffect.h"

using namespace std;

class Character;
class ICharacterState;

struct FSkillData
{
	string skillName =""; //스킬이름
	int mpCost =0; //스킬에 사용되는 코스트
	int maxCooldown =99; //스킬 쿨다운
	int currentCooldown =0; //현재 스킬쿨다운

	shared_ptr<ISkillAction> action; //액션
	vector<shared_ptr<ISkillEffect>> effects; //효과가 여러개일수도있으니
	
	Character* owner;//이 스킬을 소유한 캐릭터오너 //ToDO: 원시 or 위크드
	vector<shared_ptr<ICharacterState>> state; //상태

	FSkillData() = default;

	FSkillData(const string& skillName, int mpCost, int maxCooldown)
		: skillName(skillName), mpCost(mpCost), maxCooldown(maxCooldown)
	{
	}
	FSkillData(Character* _owner,const string& skillName, int mpCost, int maxCooldown)
		: owner(_owner), skillName(skillName), mpCost(mpCost), maxCooldown(maxCooldown)
	{
	}

	FSkillData(const string& skillName, int mpCost, int maxCooldown, int currentCooldown)
		: skillName(skillName), mpCost(mpCost), maxCooldown(maxCooldown), currentCooldown(currentCooldown)
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

	Skill(Character* _owner) 
	{
		skillData.owner = _owner;
	};

	~Skill() = default;

	template<typename T>
	void SkillInit()
	{
		skillData.action.get()->SetSkill(this);
		for (auto effect : skillData.effects)
		{
			effect.get()->SetSkill(this);
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

	virtual Character* GetTarget();

};

class ActiveSkill : public Skill
{
public:
	ActiveSkill()
	{
	};

	ActiveSkill(Character* _owner) : Skill(_owner)
	{
	};

	ActiveSkill(Character* _owner, const string& skillName, int mpCost, int maxCooldown) : Skill(_owner)
	{
		skillData.skillName = skillName;
		skillData.mpCost = mpCost;
		skillData.maxCooldown = maxCooldown;
	};

	~ActiveSkill() = default;

	virtual void UseSkill() override;
};

class PassiveSkill : public Skill
{
public:
	PassiveSkill()
	{
	};

	PassiveSkill(Character* _owner) : Skill(_owner)
	{
	};

	PassiveSkill(Character* _owner, const string& skillName, int mpCost, int maxCooldown) : Skill(_owner)
	{
		skillData.skillName = skillName;
		skillData.mpCost = mpCost;
		skillData.maxCooldown = maxCooldown;
	};

	~PassiveSkill() = default;

	virtual void UseSkill() override;
};