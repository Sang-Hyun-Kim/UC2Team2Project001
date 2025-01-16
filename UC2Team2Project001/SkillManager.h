#pragma once


#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <functional>

class Skill;
enum class SkillType;


using namespace std;

class SkillManager
{
public:
	SkillManager();
	~SkillManager();

	// 싱글턴 객체 반환
	static SkillManager& GetInstance();

	// 랜덤 스킬 반환 (캐릭터를 매개변수로 받음) - 중복 허용
	shared_ptr<Skill> GetRandomActiveSkill(Character* _owner);
	shared_ptr<Skill> GetRandomPassiveSkill(Character* _owner);

	// 캐릭터에 랜덤으로 스킬을 추가합니다 - 중복 허용
	void AddRandomSkillToCharacter(Character* _owner, SkillType _skillType);

	// 캐릭터에 랜덤으로 스킬을 추가합니다 - 중복 허용 X
	void AddUniqueSkillToCharacter(Character* _owner, SkillType _skillType);

	// 카운트 만큼 플레이어가 소유하지 않은 스킬들의 타입을 반환합니다.
	vector<type_index> GetUniqueRandomSkillTypes(Character* _owner, SkillType _skillType, int _count);

	// 지정해둔 타입으로 스킬을 생성합니다.
	shared_ptr<Skill> CreateSkillFromType(const type_index& _skillType, Character* _owner);

	void AddSelectSkillToCharacter(const type_index& _skillType, Character* _owner);

	// 팩토리 등록 메서드
	template <typename T>
	void RegisterSkill()
	{
		skillFactory[typeid(T)] = [](Character* _owner) -> shared_ptr<Skill> 
			{
			return make_shared<T>(_owner);
			};
	}

private:
	vector<type_index> activeSkillList;
	vector<type_index> passiveSkillList;

	unordered_map<type_index, function<shared_ptr<Skill>(Character*)>> skillFactory;
};