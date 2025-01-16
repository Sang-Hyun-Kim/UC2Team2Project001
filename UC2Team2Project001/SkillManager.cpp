#include "pch.h"
#include "SkillManager.h"
#include "PoisonedBlade.h"
#include "Plague.h"
#include "PoisonFog.h"
#include "PoisonInfusion.h"
#include "PoisonTrigger.h"
#include "BashAttack.h"
#include "MentalDiscipline.h"
#include "ShieldAttack.h"
#include "OnePointAttack.h"
#include "Unbreakable.h"
#include "Patience.h"
#include "USkillComponent.h"
#include "Character.h"
#include <unordered_set>
#include "Sanctification.h"
#include "LuckyGuy.h"
#include "CursedSeal.h"
#include "BasicAttack.h" 
#include "ConsoleColorManager.h"

SkillManager::SkillManager()
{
	// 액티브 스킬 등록
	RegisterSkill<BasicAttack>();
	RegisterSkill<PoisonedBlade>();
	RegisterSkill<PoisonFog>();
	RegisterSkill<PoisonInfusion>();
	RegisterSkill<PoisonTrigger>();
	RegisterSkill<Sanctification>();


	activeSkillList.push_back(typeid(BasicAttack));
	activeSkillList.push_back(typeid(PoisonedBlade));
	activeSkillList.push_back(typeid(PoisonFog));
	activeSkillList.push_back(typeid(PoisonInfusion));
	activeSkillList.push_back(typeid(PoisonTrigger));
	activeSkillList.push_back(typeid(Sanctification));

	//명관님꺼 넣어주세요.
	RegisterSkill<BashAttack>();
	RegisterSkill<MentalDiscipline>();
	RegisterSkill<ShieldAttack>();
	RegisterSkill<OnePointAttack>();

	activeSkillList.push_back(typeid(BashAttack));
	activeSkillList.push_back(typeid(MentalDiscipline));
	activeSkillList.push_back(typeid(ShieldAttack));
	activeSkillList.push_back(typeid(OnePointAttack));

	// 패시브 스킬 등록
	RegisterSkill<Plague>();

	RegisterSkill<Unbreakable>();
	RegisterSkill<Patience>();

	passiveSkillList.push_back(typeid(Plague));
	passiveSkillList.push_back(typeid(Unbreakable));
	passiveSkillList.push_back(typeid(Patience));

	RegisterSkill<LuckyGuy>();
	RegisterSkill<CursedSeal>();
	

	passiveSkillList.push_back(typeid(Plague));
	passiveSkillList.push_back(typeid(LuckyGuy));
	passiveSkillList.push_back(typeid(CursedSeal));
}

SkillManager::~SkillManager()
{
	activeSkillList.clear();
	passiveSkillList.clear();
}

SkillManager& SkillManager::GetInstance()
{
	static SkillManager instance;
	return instance;
}

shared_ptr<Skill> SkillManager::GetRandomActiveSkill(Character* _owner)
{
	if (activeSkillList.empty())
	{
		return nullptr;
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, activeSkillList.size() - 1);

	int randomIndex = dist(gen);
	type_index skillType = activeSkillList[randomIndex];

	if (skillFactory.find(skillType) != skillFactory.end())
	{
		return skillFactory[skillType](_owner);
	}

	return nullptr;
}

shared_ptr<Skill> SkillManager::GetRandomPassiveSkill(Character* _owner)
{
	if (passiveSkillList.empty())
	{
		return nullptr;
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, passiveSkillList.size() - 1);

	int randomIndex = dist(gen);
	type_index skillType = passiveSkillList[randomIndex];

	if (skillFactory.find(skillType) != skillFactory.end())
	{
		return skillFactory[skillType](_owner);
	}

	return nullptr;
}


void SkillManager::AddRandomSkillToCharacter(Character* _owner, SkillType _skillType)
{
	if (!_owner)
	{
		cerr << "소유자가 유효하지 않습니다: nullptr" << endl;
		return;
	}

	shared_ptr<Skill> newSkill;

	if (_skillType == SkillType::ACTIVE)
	{
		newSkill = GetRandomActiveSkill(_owner);
	}
	else if (_skillType == SkillType::PASSIVE)
	{
		newSkill = GetRandomPassiveSkill(_owner);
	}

	if (!newSkill)
	{
		cerr << "소유자를 위한 스킬 생성에 실패했습니다." << endl;
		return;
	}

	_owner->skillManager->AddSkill(newSkill);
	cout << "스킬 " << newSkill->GetSkillData().skillName << "이(가) " << _owner->GetName() << "에게 추가되었습니다." << endl;
}

void SkillManager::AddUniqueSkillToCharacter(Character* _owner, SkillType _skillType)
{
	if (!_owner)
	{
		cerr << "소유자가 유효하지 않습니다: nullptr" << endl;
		return;
	}

	auto uniqueSkillTypes = GetUniqueRandomSkillTypes(_owner, _skillType, 1);
	if (uniqueSkillTypes.empty())
	{
		cerr << "플레이어가 추가할 수 있는 새로운 스킬이 없습니다." << endl;
		return;
	}

	auto newSkill = CreateSkillFromType(uniqueSkillTypes[0], _owner);
	if (!newSkill)
	{
		cerr << "스킬 생성에 실패했습니다." << endl;
		return;
	}

	_owner->skillManager->AddSkill(newSkill);
	cout << "스킬 " << newSkill->GetSkillData().skillName << "이(가) " << _owner->GetName() << "에게 추가되었습니다." << endl;
}

vector<type_index> SkillManager::GetUniqueRandomSkillTypes(Character* _owner, SkillType _skillType, int _count)
{
	if (!_owner)
	{
		cerr << "소유자가 유효하지 않습니다: nullptr" << endl;
		return {};
	}

	auto& skillListRef = _owner->skillManager->ChooseSkillListRef(_skillType);
	unordered_set<string> ownedSkills;
	for (const auto& [skillName, skillInstance] : skillListRef)
	{
		ownedSkills.insert(skillName);
	}

	const auto& availableSkills = (_skillType == SkillType::ACTIVE) ? activeSkillList : passiveSkillList;
	vector<type_index> filteredSkills;
	for (const auto& skillType : availableSkills)
	{
		auto tempSkill = skillFactory[skillType](_owner);
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

	return vector<type_index>(filteredSkills.begin(), filteredSkills.begin() + min(_count, (int)filteredSkills.size()));
}

shared_ptr<Skill> SkillManager::CreateSkillFromType(const type_index& _skillType, Character* _owner)
{
	if (skillFactory.find(_skillType) == skillFactory.end())
	{
		cerr << "등록되지 않은 스킬 타입입니다: " << _skillType.name() << endl;
		return nullptr;
	}

	if (!_owner)
	{
		cerr << "소유자가 유효하지 않습니다: nullptr" << endl;
		return nullptr;
	}

	return skillFactory[_skillType](_owner);
}

void SkillManager::AddSelectSkillToCharacter(const type_index& _skillType, Character* _owner)
{
	auto newSkill = CreateSkillFromType(_skillType, _owner);

	if (!newSkill)
	{
		ConsoleColorManager::GetInstance().SetColor(ConsoleColor::Green, ConsoleColor::Black);
		cerr << "스킬 생성에 실패했습니다. 스킬이 유효하지 않습니다." << endl;
	}

	ConsoleColorManager::GetInstance().SetColor(ConsoleColor::Green, ConsoleColor::Black);
	std::cout << newSkill->GetSkillData().skillName <<"스킬을 획득했습니다" << endl;
	_owner->skillManager->AddSkill(newSkill);
}
