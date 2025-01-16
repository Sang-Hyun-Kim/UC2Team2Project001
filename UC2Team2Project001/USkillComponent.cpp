#include "pch.h"
#include "USkillComponent.h"
#include "Skill.h"
#include <unordered_set>
#include "ICharacterEventTypes.h"
#include "GlobalEventManager.h"

USkillComponent::USkillComponent()
{
}

USkillComponent::USkillComponent(Character* _Owner)
{
	OwnerCharacter = _Owner;
}

void USkillComponent::InitializeComponent()
{
	
}

unordered_map<string, shared_ptr<Skill>> USkillComponent::ChooseSkillList(SkillType _skillType)
{
	return _skillType == SkillType::ACTIVE ? activeSkillList : passiveSkillList;;
}

std::unordered_map<std::string, std::shared_ptr<Skill>>& USkillComponent::ChooseSkillListRef(SkillType _skillType)
{
	return _skillType == SkillType::ACTIVE ? activeSkillList : passiveSkillList;;
}

shared_ptr<Skill> USkillComponent::GetSkill(SkillType _skillType, string _skillName)
{
	auto skillList = ChooseSkillList(_skillType);

	for (int i = 0; i < skillList.size(); i++)
	{
		if (skillList.find(_skillName) != skillList.end())
		{
			return skillList[_skillName];
		}
	}

	return nullptr;
}

void USkillComponent::AddSkill(std::shared_ptr<Skill> skill)
{
	if (!skill)
	{
		std::cerr << "추가하려는 스킬이 유효하지 않습니다." << std::endl;
		return;
	}

	if (auto activeSkill = std::dynamic_pointer_cast<ActiveSkill>(skill))
	{
		activeSkillList[skill->GetSkillData().skillName] = activeSkill;
	}
	else if (auto passiveSkill = std::dynamic_pointer_cast<PassiveSkill>(skill))
	{
		passiveSkillList[skill->GetSkillData().skillName] = passiveSkill;
		passiveSkill->PassiveSkillRegisterTrigger();
	}
}

//void USkillComponent::AddSkill(shared_ptr<ActiveSkill> _activeSkill)
//{
//	activeSkillList[_activeSkill->GetSkillData().skillName] = _activeSkill;
//}
//
//void USkillComponent::AddSkill(shared_ptr<PassiveSkill> _passiveSkill)
//{
//	passiveSkillList[_passiveSkill->GetSkillData().skillName] = _passiveSkill;
//
//	_passiveSkill->PassiveSkillRegisterTrigger();
//}

void USkillComponent::RemoveSkill(SkillType _skillType, string _skillName)
{
	auto& skillList = ChooseSkillListRef(_skillType);

	if (skillList.find(_skillName) != skillList.end())
	{
		// 패시브라면 해제
		if (_skillType == SkillType::PASSIVE)
		{
			auto passiveSkill = std::dynamic_pointer_cast<PassiveSkill>(skillList[_skillName]);
			if (passiveSkill)
			{
				passiveSkill->PassiveSkillUnRegisterTrigger();
			}
		}

		skillList.erase(_skillName);
	}
}

bool USkillComponent::UseSkill(SkillType _skillType, string _skillName)
{
	auto skillList = ChooseSkillList(_skillType);

	if (skillList.count(_skillName))
	{
		return skillList[_skillName]->UseSkill();
	}

	cout << _skillName << "스킬이 없습니다" << endl;
	return false;
}

void USkillComponent::OnEvent(std::shared_ptr<IEvent> ev)
{
	for (auto& passive : passiveSkillList)
	{
		auto skillPtr = passive.second;
		auto passiveSkill = std::dynamic_pointer_cast<PassiveSkill>(skillPtr);

		if (!passiveSkill)
		{
			continue;
		}

		if (passiveSkill->handlers.find(std::type_index(typeid(*ev))) != passiveSkill->handlers.end())
		{
			passiveSkill->HandlePassiveEvent(ev);
		}
	}
}


std::string USkillComponent::GetActiveSkillNameByIndex(int index) const
{
	if (index < 0 || index >= static_cast<int>(activeSkillList.size()))
	{
		return {};
	}

	auto it = activeSkillList.begin();
	std::advance(it, index);
	return it->second->GetSkillData().skillName;
}

std::string USkillComponent::GetPassiveSkillNameByIndex(int index) const
{
	if (index < 0 || index >= static_cast<int>(passiveSkillList.size()))
	{
		throw std::out_of_range("Invalid index for passive skill.");
	}

	auto it = passiveSkillList.begin();
	std::advance(it, index);
	return it->second->GetSkillData().skillName;
}

std::vector<std::string> USkillComponent::GetActiveSkillInfo() const
{
	std::vector<std::string> skillInfos(activeSkillList.size(), "");

	if (activeSkillList.empty())
	{
		return {};
	};

	int index = 0;
	for (const auto& pair : activeSkillList)
	{
		const auto& skill = pair.second;
		if (skill)
		{
			skillInfos[index] = "[" + std::to_string(index) + "] 이름: " + skill->GetSkillData().skillName;
		}
		++index;
	}

	return skillInfos;
}

std::vector<std::string> USkillComponent::GetPassiveSkillInfo() const
{
	std::vector<std::string> skillInfos(passiveSkillList.size(), "");

	if (passiveSkillList.empty())
	{
		return {};
	};


	int index = 0;
	for (const auto& pair : passiveSkillList)
	{
		const auto& skill = pair.second;
		if (skill)
		{
			skillInfos[index] = "[" + std::to_string(index) + "] 이름: " + skill->GetSkillData().skillName;
		}
		++index;
	}


	return skillInfos;
}
