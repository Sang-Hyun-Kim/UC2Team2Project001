#include "pch.h"
#include "ManaMastery.h"
#include "ICombatEventTypes.h"
#include "StatComponent.h"
#include "ConsoleColorManager.h"
#include "ICharacterEventTypes.h"

#include "Character.h"
#include "ConsoleLayout.h"

ManaMastery::ManaMastery(Character* _owner) : PassiveSkill(_owner)
{
	// 스킬 기본 정보 설정
	skillData = FSkillData(
		_owner,
		"마나의 지배자",
		"피해를 입을 때 피해량의 10%만큼 마나를 회복합니다.",
		0,
		0
	);

	// 이벤트 핸들러 등록
	handlers.insert(typeid(ICharacterDamagedEvent));

	SkillInit(this);
}

void ManaMastery::HandlePassiveEvent(std::shared_ptr<IEvent> _event)
{
	// 받은 이벤트가 캐릭터 피해 이벤트인지 확인
	shared_ptr<ICharacterDamagedEvent> damagedEvent = std::dynamic_pointer_cast<ICharacterDamagedEvent>(_event);

	if (!damagedEvent || damagedEvent->characterName != skillData.owner->GetName())
		return;

	// 피해량의 10%만큼 마나 회복
	float damageTaken = damagedEvent->damage;
	int manaRecovery = std::round(damageTaken * 0.1f);
	

	CharacterUtility::ModifyStat(skillData.owner, StatType::MP, manaRecovery);

	// 출력 메시지
	std::string skillMessage = skillData.owner->GetName() + "이(가) [마나의 지배자]로 " + std::to_string(manaRecovery) + " MP를 회복했습니다!";
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, skillMessage, true, ConsoleColor::Blue);

}
