#pragma once

#include <unordered_map>

class Skill;
class ActiveSkill;
class PassiveSkill;

enum class SkillType
{
	ACTIVE,
	PASSIVE
};

class USkillComponent
{
private:
	// 액티브 스킬 리스트
	unordered_map<string, shared_ptr<Skill>> activeSkillList;
	// 패시브 스킬 리스트
	unordered_map<string, shared_ptr<Skill>> passiveSkillList;
public:
	// 스킬 리스트 선택
	unordered_map<string, shared_ptr<Skill>> ChooseSkillList(SkillType _skillType);

	// 스킬 가져오기
	shared_ptr<Skill> GetSkill(SkillType _skillType, string _skillName);

	// 스킬 추가
	void AddSkill(shared_ptr<ActiveSkill> _activeSkill);
	void AddSkill(shared_ptr<PassiveSkill> _passiveSkill);

	// 스킬 삭제
	void RemoveSkill(SkillType _skillType, string _skillName);

	// 스킬 사용
	bool UseSkill(SkillType _skillType, string _skillName);

	// 스킬 재사용 대기시간 설정
	void SetSkillCooldown(SkillType _skillType, string _skillName, int cooldown);
};

