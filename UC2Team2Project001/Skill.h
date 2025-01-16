#pragma once

#include "ISkillAction.h"
#include "ISkillEffect.h"
#include <functional>
#include <set>

using namespace std;

class Character;
class ICharacterState;
class ISkillCondition;
class IEvent;

struct FSkillData
{
public:
	string skillName = ""; //스킬이름
	string skillDescription = ""; // 스킬 내용
	int mpCost = 0; //스킬에 사용되는 코스트
	int maxCooldown = 99; //스킬 쿨다운
	int currentCooldown = 0; //현재 스킬쿨다운

	shared_ptr<ISkillAction> action; //액션
	vector<shared_ptr<ISkillEffect>> effects; //효과가 여러개일수도있으니

	Character* owner = nullptr;

	vector<shared_ptr<ISkillCondition>> conditions; // 스킬 조건 리스트

public:
	FSkillData() = default;

	FSkillData(const string& _skillName, int _mpCost, int _maxCooldown);

	FSkillData(Character* _owner, const string& _skillName, const string& _skillDescription,int _mpCost, int _maxCooldown)
		: owner(_owner), skillName(_skillName), skillDescription(_skillDescription), mpCost(_mpCost), maxCooldown(_maxCooldown)
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

	virtual bool CanUseSkill();

	~Skill() = default;

	void SkillInit(Skill* _ownerSkill);

	virtual bool UseSkill();

	virtual FSkillData GetSkillData()
	{
		return skillData;
	}

	virtual Character* GetTarget();

	// 매 턴마다 재사용 대기시간 감소
	virtual void ReduceCooldown()
	{
		if (skillData.currentCooldown > 0)
		{
			skillData.currentCooldown--;
		}
	}
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

	ActiveSkill(Character* _owner, const string& _skillName, int _mpCost, int _maxCooldown) : Skill(_owner)
	{
		skillData.skillName = _skillName;
		skillData.mpCost = _mpCost;
		skillData.maxCooldown = _maxCooldown;
	};

	~ActiveSkill() = default;
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

	PassiveSkill(Character* _owner, const string& _skillName, int _mpCost, int _maxCooldown) : Skill(_owner)
	{
		skillData.skillName = _skillName;
		skillData.mpCost = _mpCost;
		skillData.maxCooldown = _maxCooldown;
	};

	~PassiveSkill() = default;

	virtual void PassiveSkillRegisterTrigger();

	virtual void PassiveSkillUnRegisterTrigger();


	// 실제로 이벤트를 처리하는(혹은 스킬을 발동하는) 함수
	virtual void HandlePassiveEvent(std::shared_ptr<IEvent> _event);

public:
	// '어떤 이벤트 타입'들을 처리할지 저장
	std::set<std::type_index> handlers;
};