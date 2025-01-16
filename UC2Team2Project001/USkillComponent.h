#pragma once

#include <unordered_map>
#include "EventManagerSystem.h"

class Skill;
class ActiveSkill;
class PassiveSkill;
class Character;

enum class SkillType
{
	ACTIVE,
	PASSIVE
};

class USkillComponent : public IEventManagerSystem
{
public:
	USkillComponent();

	USkillComponent(Character* _owner);

	void InitializeComponent();

private:
	// 액티브 스킬 리스트
	unordered_map<string, shared_ptr<Skill>> activeSkillList;

	// 패시브 스킬 리스트
	unordered_map<string, shared_ptr<Skill>> passiveSkillList;
public:
	// 스킬 리스트 선택
	unordered_map<string, shared_ptr<Skill>> ChooseSkillList(SkillType _skillType);

	unordered_map<string, shared_ptr<Skill>>& ChooseSkillListRef(SkillType _skillType);

	// 스킬 가져오기
	shared_ptr<Skill> GetSkill(SkillType _skillType, string _skillName);

	// 스킬 추가
	void AddSkill(std::shared_ptr<Skill> _skill);

	/*void AddSkill(shared_ptr<ActiveSkill> _activeSkill);

	void AddSkill(shared_ptr<PassiveSkill> _passiveSkill);*/

	// 스킬 삭제
	void RemoveSkill(SkillType _skillType, string _skillName);

	// 스킬 사용
	bool UseSkill(string _skillName, SkillType _skillType= SkillType::ACTIVE);

	bool UseSkillByType(const std::type_index& _type,SkillType _skillType = SkillType::ACTIVE);

	bool UseSkillByIndex(int _index, SkillType _skillType = SkillType::ACTIVE);

	// 매 턴 종료 시, 모든 스킬의 쿨타임을 1씩 감소
	void AllReduceCooldown();

	string GetActiveSkillNameByIndex(int _index) const;

	string GetPassiveSkillNameByIndex(int _index) const;

	vector<std::string> GetActiveSkillInfo() const;

	vector<std::string> GetPassiveSkillInfo() const;

	vector<std::string> GetActiveSkillInfoWithString(int _index) const;

	/* IEventManager System*/
public:
	virtual void OnEvent(std::shared_ptr<IEvent> _event) override;
	
	
	Character* ownerCharacter;
};