#include "pch.h"
#include "SkillManager.h"
#include "PoisonedBlade.h"
#include "Plague.h"
#include "PoisonFog.h"
#include "PoisonInfusion.h"
#include "PoisonTrigger.h"
#include "USkillComponent.h"
#include "Character.h"
#include <unordered_set>
#include "Sanctification.h"
#include "LuckyGuy.h"
#include "CursedSeal.h"

SkillManager::SkillManager()
{
	// 액티브 스킬 등록
	RegisterSkill<PoisonedBlade>();
	RegisterSkill<PoisonFog>();
	RegisterSkill<PoisonInfusion>();
	RegisterSkill<PoisonTrigger>();
	RegisterSkill<Sanctification>();


	ActiveSkillList.push_back(typeid(PoisonedBlade));
	ActiveSkillList.push_back(typeid(PoisonFog));
	ActiveSkillList.push_back(typeid(PoisonInfusion));
	ActiveSkillList.push_back(typeid(PoisonTrigger));
	ActiveSkillList.push_back(typeid(Sanctification));

	


	// 패시브 스킬 등록
	RegisterSkill<Plague>();
	RegisterSkill<LuckyGuy>();
	RegisterSkill<CursedSeal>();
	

	PassiveSkillList.push_back(typeid(Plague));
	PassiveSkillList.push_back(typeid(LuckyGuy));
	PassiveSkillList.push_back(typeid(CursedSeal));
}

SkillManager::~SkillManager()
{
	ActiveSkillList.clear();
	PassiveSkillList.clear();
}

SkillManager& SkillManager::GetInstance()
{
	static SkillManager instance;
	return instance;
}

shared_ptr<Skill> SkillManager::GetRandomActiveSkill(Character* owner)
{
	if (ActiveSkillList.empty())
	{
		return nullptr;
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, ActiveSkillList.size() - 1);

	int randomIndex = dist(gen);
	type_index skillType = ActiveSkillList[randomIndex];

	if (SkillFactory.find(skillType) != SkillFactory.end())
	{
		return SkillFactory[skillType](owner);
	}

	return nullptr;
}

shared_ptr<Skill> SkillManager::GetRandomPassiveSkill(Character* owner)
{
	if (PassiveSkillList.empty())
	{
		return nullptr;
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, PassiveSkillList.size() - 1);

	int randomIndex = dist(gen);
	type_index skillType = PassiveSkillList[randomIndex];

	if (SkillFactory.find(skillType) != SkillFactory.end())
	{
		return SkillFactory[skillType](owner);
	}

	return nullptr;
}


void SkillManager::AddRandomSkillToCharacter(Character* owner, SkillType skillType)
{
	if (!owner)
	{
		cerr << "소유자가 유효하지 않습니다: nullptr" << endl;
		return;
	}

	shared_ptr<Skill> newSkill;

	if (skillType == SkillType::ACTIVE)
	{
		newSkill = GetRandomActiveSkill(owner);
	}
	else if (skillType == SkillType::PASSIVE)
	{
		newSkill = GetRandomPassiveSkill(owner);
	}

	if (!newSkill)
	{
		cerr << "소유자를 위한 스킬 생성에 실패했습니다." << endl;
		return;
	}

	owner->skillManager->AddSkill(newSkill);
	cout << "스킬 " << newSkill->GetSkillData().skillName << "이(가) " << owner->GetName() << "에게 추가되었습니다." << endl;
}

void SkillManager::AddUniqueSkillToCharacter(Character* owner, SkillType skillType)
{
	if (!owner)
	{
		cerr << "소유자가 유효하지 않습니다: nullptr" << endl;
		return;
	}

	auto uniqueSkillTypes = GetUniqueRandomSkillTypes(owner, skillType, 1);
	if (uniqueSkillTypes.empty())
	{
		cerr << "플레이어가 추가할 수 있는 새로운 스킬이 없습니다." << endl;
		return;
	}

	auto newSkill = CreateSkillFromType(uniqueSkillTypes[0], owner);
	if (!newSkill)
	{
		cerr << "스킬 생성에 실패했습니다." << endl;
		return;
	}

	owner->skillManager->AddSkill(newSkill);
	cout << "스킬 " << newSkill->GetSkillData().skillName << "이(가) " << owner->GetName() << "에게 추가되었습니다." << endl;
}

vector<type_index> SkillManager::GetUniqueRandomSkillTypes(Character* owner, SkillType skillType, int count)
{
	if (!owner)
	{
		cerr << "소유자가 유효하지 않습니다: nullptr" << endl;
		return {};
	}

	auto& skillListRef = owner->skillManager->ChooseSkillListRef(skillType);
	unordered_set<string> ownedSkills;
	for (const auto& [skillName, skillInstance] : skillListRef)
	{
		ownedSkills.insert(skillName);
	}

	const auto& availableSkills = (skillType == SkillType::ACTIVE) ? ActiveSkillList : PassiveSkillList;
	vector<type_index> filteredSkills;
	for (const auto& skillType : availableSkills)
	{
		auto tempSkill = SkillFactory[skillType](owner);
		if (tempSkill && ownedSkills.find(tempSkill->GetSkillData().skillName) == ownedSkills.end())
		{
			filteredSkills.push_back(skillType);
		}
	}

	if (filteredSkills.empty())
	{
		cerr << "소유자가 중복되지 않은 새로운 스킬을 얻을 수 없습니다." << endl;
		return {};
	}

	random_device rd;
	mt19937 gen(rd());
	shuffle(filteredSkills.begin(), filteredSkills.end(), gen);

	return vector<type_index>(filteredSkills.begin(), filteredSkills.begin() + min(count, (int)filteredSkills.size()));
}

shared_ptr<Skill> SkillManager::CreateSkillFromType(const type_index& skillType, Character* owner)
{
	if (SkillFactory.find(skillType) == SkillFactory.end())
	{
		cerr << "등록되지 않은 스킬 타입입니다: " << skillType.name() << endl;
		return nullptr;
	}

	if (!owner)
	{
		cerr << "소유자가 유효하지 않습니다: nullptr" << endl;
		return nullptr;
	}

	return SkillFactory[skillType](owner);
}

void SkillManager::AddSelectSkillToCharacter(const type_index& skillType, Character* owner)
{
	auto newSkill = CreateSkillFromType(skillType, owner);

	if (!newSkill)
	{
		cerr << "스킬 생성에 실패했습니다. 스킬이 유효하지 않습니다." << endl;
	}

	owner->skillManager->AddSkill(newSkill);
}

