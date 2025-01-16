#include "pch.h"
#include "USkillComponent.h"
#include "Skill.h"
#include <unordered_set>
#include "ICharacterEventTypes.h"
#include "GlobalEventManager.h"

USkillComponent::USkillComponent()
{
}

USkillComponent::USkillComponent(Character* _owner)
{
	ownerCharacter = _owner;
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

void USkillComponent::AddSkill(std::shared_ptr<Skill> _skill)
{
	if (!_skill)
	{
		std::cerr << "추가하려는 스킬이 유효하지 않습니다." << std::endl;
		return;
	}

	if (auto activeSkill = std::dynamic_pointer_cast<ActiveSkill>(_skill))
	{
		activeSkillList[_skill->GetSkillData().skillName] = activeSkill;
	}
	else if (auto passiveSkill = std::dynamic_pointer_cast<PassiveSkill>(_skill))
	{
		passiveSkillList[_skill->GetSkillData().skillName] = passiveSkill;
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

bool USkillComponent::UseSkill(string _skillName, SkillType _skillType/*= SkillType::ACTIVE*/)
{
	auto skillList = ChooseSkillList(_skillType);

	if (skillList.count(_skillName))
	{
		return skillList[_skillName]->UseSkill();
	}

	cout << _skillName << "스킬이 없습니다" << endl;
	return false;
}

bool USkillComponent::UseSkillByType(const std::type_index& _type, SkillType _skillType /*= SkillType::ACTIVE*/)
{
	auto& skillList = ChooseSkillListRef(_skillType);

	for (const auto& [name, skill] : skillList)
	{
		// std::type_index를 사용해 비교
		if (std::type_index(typeid(*skill)) == _type)
		{
			if (skill)
			{
				return skill->UseSkill();
			}

			DEBUG_COUT("");
			std::cerr << "타입에 해당하는 유효한 스킬을 찾을 수 없습니다: " << _type.name() << std::endl;
			return false;
		}
	}

	DEBUG_COUT("");
	std::cerr << "타입에 해당하는 스킬을 찾을 수 없습니다: " << _type.name() << std::endl;
	return false;
}

bool USkillComponent::UseSkillByIndex(int _index,SkillType _skillType)
{
	auto& skillList = ChooseSkillListRef(_skillType);

	if (_index < 0 || _index >= static_cast<int>(skillList.size()))
	{
		std::cerr << "잘못된 인덱스입니다. 범위를 초과했습니다: " << _index << std::endl;
		return false;
	}

	// 인덱스를 기반으로 스킬 검색
	auto it = skillList.begin();
	std::advance(it, _index);

	if (it->second)
	{
		return it->second->UseSkill();
	}

	std::cerr << "해당 인덱스에 유효한 스킬이 없습니다: " << _index << std::endl;
	return false;
}

void USkillComponent::AllReduceCooldown()
{
	for (auto& skill : activeSkillList)
	{
		int currentCooldown = skill.second->GetSkillData().currentCooldown;
		if (currentCooldown > 0)
		{
			skill.second->ReduceCooldown();
		}
	}
}

void USkillComponent::OnEvent(std::shared_ptr<IEvent> _event)
{
	for (auto& passive : passiveSkillList)
	{
		auto skillPtr = passive.second;
		auto passiveSkill = std::dynamic_pointer_cast<PassiveSkill>(skillPtr);

		if (!passiveSkill)
		{
			continue;
		}

		if (passiveSkill->handlers.find(std::type_index(typeid(*_event))) != passiveSkill->handlers.end())
		{
			passiveSkill->HandlePassiveEvent(_event);
		}
	}
}


std::string USkillComponent::GetActiveSkillNameByIndex(int _index) const
{
	if (_index < 0 || _index >= static_cast<int>(activeSkillList.size()))
	{
		return "";
	}

	auto it = activeSkillList.begin();
	std::advance(it, _index);
	return it->second->GetSkillData().skillName;
}

std::string USkillComponent::GetPassiveSkillNameByIndex(int _index) const
{
	if (_index < 0 || _index >= static_cast<int>(passiveSkillList.size()))
	{
		throw std::out_of_range("Invalid index for passive skill.");
	}

	auto it = passiveSkillList.begin();
	std::advance(it, _index);
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


vector<string> USkillComponent::GetActiveSkillInfoWithString(int _type) const
{
	vector<string> skillListInfo;
	if (_type == 0) //배틀, 인벤토리 열기
	{
		int i = 1;
		for (auto activeSkill : activeSkillList)
		{
			string index = to_string(i++);
			string name = activeSkill.first;
			string mp = to_string(activeSkill.second->GetSkillData().mpCost);
			int cooldown = activeSkill.second->GetSkillData().currentCooldown;
			string cooldownString = cooldown == 0 ? "" : (" CoolDown: " + to_string(cooldown));
			string result = index + ". " + name + " " + " MP: " + mp + cooldownString;
			
			skillListInfo.push_back(result) ;
		}
	}
	else //상점
	{
		// 상점에서 스킬을 팔기 위한 정보 함수를 불러와주세요
	}
	return skillListInfo;
}
