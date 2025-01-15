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

SkillManager::SkillManager()
{
	// 액티브 스킬 등록
	RegisterSkill<PoisonedBlade>();
	RegisterSkill<PoisonFog>();
	RegisterSkill<PoisonInfusion>();
	RegisterSkill<PoisonTrigger>();

	ActiveSkillList.push_back(typeid(PoisonedBlade));
	ActiveSkillList.push_back(typeid(PoisonFog));
	ActiveSkillList.push_back(typeid(PoisonInfusion));
	ActiveSkillList.push_back(typeid(PoisonTrigger));

	//명관님꺼 넣어주세요.


	// 패시브 스킬 등록
	RegisterSkill<Plague>();

	PassiveSkillList.push_back(typeid(Plague));
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

Skill* SkillManager::GetRandomActiveSkill(Character* owner)
{
	if (ActiveSkillList.empty())
	{
		return nullptr;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, ActiveSkillList.size() - 1);

	int randomIndex = dist(gen);
	std::type_index skillType = ActiveSkillList[randomIndex];

	if (SkillFactory.find(skillType) != SkillFactory.end())
	{
		return SkillFactory[skillType](owner);
	}

	return nullptr;
}

Skill* SkillManager::GetRandomPassiveSkill(Character* owner)
{
	if (PassiveSkillList.empty())
	{
		return nullptr;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, PassiveSkillList.size() - 1);

	int randomIndex = dist(gen);
	std::type_index skillType = PassiveSkillList[randomIndex];

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
		std::cerr << "소유자가 유효하지 않습니다: nullptr" << std::endl;
		return;
	}

	Skill* newSkill = nullptr;

	// 활성 스킬 또는 패시브 스킬을 랜덤으로 생성
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
		std::cerr << "소유자를 위한 스킬 생성에 실패했습니다." << std::endl;
		return;
	}

	// 활성 스킬인지 패시브 스킬인지 확인 후 추가
	if (auto activeSkill = dynamic_cast<ActiveSkill*>(newSkill))
	{
		owner->skillManager->AddSkill(std::shared_ptr<ActiveSkill>(activeSkill));
		std::cout << "활성 스킬 " << newSkill->GetSkillData().skillName << "이(가) " << owner->GetName() << "에게 추가되었습니다." << std::endl;
	}
	else if (auto passiveSkill = dynamic_cast<PassiveSkill*>(newSkill))
	{
		owner->skillManager->AddSkill(std::shared_ptr<PassiveSkill>(passiveSkill));
		std::cout << "패시브 스킬 " << newSkill->GetSkillData().skillName << "이(가) " << owner->GetName() << "에게 추가되었습니다." << std::endl;
	}
	else
	{
		std::cerr << "알 수 없는 스킬 유형: " << newSkill->GetSkillData().skillName << std::endl;
		delete newSkill; // 필요하다면 메모리 해제
		return;
	}
}

void SkillManager::AddUniqueSkillToCharacter(Character* owner, SkillType skillType)
{
	if (!owner)
	{
		std::cerr << "소유자가 유효하지 않습니다: nullptr" << std::endl;
		return;
	}

	// 중복되지 않은 스킬 하나 선택
	auto uniqueSkillTypes = GetUniqueRandomSkillTypes(owner, skillType, 1);
	if (uniqueSkillTypes.empty())
	{
		std::cerr << "플레이어가 추가할 수 있는 새로운 스킬이 없습니다." << std::endl;
		return;
	}

	// 선택된 스킬 생성
	Skill* newSkill = CreateSkillFromType(uniqueSkillTypes[0], owner);
	if (!newSkill)
	{
		std::cerr << "스킬 생성에 실패했습니다." << std::endl;
		return;
	}

	// 활성 스킬인지 패시브 스킬인지 확인 후 추가
	if (auto activeSkill = dynamic_cast<ActiveSkill*>(newSkill))
	{
		owner->skillManager->AddSkill(std::shared_ptr<ActiveSkill>(activeSkill));
		std::cout << "활성 스킬 " << newSkill->GetSkillData().skillName << "이(가) " << owner->GetName() << "에게 추가되었습니다." << std::endl;
	}
	else if (auto passiveSkill = dynamic_cast<PassiveSkill*>(newSkill))
	{
		owner->skillManager->AddSkill(std::shared_ptr<PassiveSkill>(passiveSkill));
		std::cout << "패시브 스킬 " << newSkill->GetSkillData().skillName << "이(가) " << owner->GetName() << "에게 추가되었습니다." << std::endl;
	}
}

std::vector<std::type_index> SkillManager::GetUniqueRandomSkillTypes(Character* owner, SkillType skillType, int count)
{
	if (!owner)
	{
		std::cerr << "소유자가 유효하지 않습니다: nullptr" << std::endl;
		return {};
	}

	// 소유한 스킬 확인
	unordered_map<string, shared_ptr<Skill>>& skillListRef = owner->skillManager->ChooseSkillListRef(skillType);
	std::unordered_set<std::string> ownedSkills;
	for (const auto& [skillName, skillInstance] : skillListRef)
	{
		ownedSkills.insert(skillName);
	}

	// 선택 가능한 스킬 필터링
	const auto& availableSkills = (skillType == SkillType::ACTIVE) ? ActiveSkillList : PassiveSkillList;
	std::vector<std::type_index> filteredSkills;
	for (const auto& skillType : availableSkills)
	{
		auto tempSkill = SkillFactory[skillType](owner);
		if (tempSkill && ownedSkills.find(tempSkill->GetSkillData().skillName) == ownedSkills.end())
		{
			filteredSkills.push_back(skillType);
		}
		delete tempSkill; // 임시로 생성된 스킬 제거
	}

	// 반환할 스킬이 부족한 경우 가능한 만큼만 반환
	if (filteredSkills.empty())
	{
		cerr << "소유자가 중복되지 않은 새로운 스킬을 얻을 수 없습니다." << std::endl;
		return {};
	}

	// 랜덤으로 스킬 선택
	random_device rd;
	mt19937 gen(rd());
	shuffle(filteredSkills.begin(), filteredSkills.end(), gen);

	// 요청된 크기만큼 반환
	if (count > filteredSkills.size())
	{
		count = filteredSkills.size();
	}

	return vector<type_index>(filteredSkills.begin(), filteredSkills.begin() + count);
}

Skill* SkillManager::CreateSkillFromType(const std::type_index& skillType, Character* owner)
{
	if (SkillFactory.find(skillType) == SkillFactory.end())
	{
		std::cerr << "등록되지 않은 스킬 타입입니다: " << skillType.name() << std::endl;
		return nullptr;
	}

	if (!owner)
	{
		std::cerr << "소유자가 유효하지 않습니다: nullptr" << std::endl;
		return nullptr;
	}

	// 팩토리를 사용해 스킬 생성
	Skill* newSkill = SkillFactory[skillType](owner);
	if (!newSkill)
	{
		std::cerr << "스킬 생성에 실패했습니다: " << skillType.name() << std::endl;
	}
	return newSkill;
}
