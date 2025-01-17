#include "pch.h"
#include "AttackBoostPotion.h"
#include "Character.h"
#include "StatComponent.h"
#include "CharacterStatus.h"
#include "UStatusComponent.h"
#include "ConsoleLayout.h"

AttackBoostPotion::AttackBoostPotion(int _id) : Potion(_id,"공격력 부스트 물약", "공격력이 5 증가 합니다.", 50) {}

bool AttackBoostPotion::use(Character* _target)
{
	if (!_target->statusManager->GetState<ModifyStatState>())
	{
		shared_ptr<ModifyStatState> state = make_shared<ModifyStatState>(5, StatType::AttackPower, 5);
		_target->statusManager->AddState(state);
		state->ApplyEffect(_target);
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "공격력이 5상승 합니다.", true, ConsoleColor::LightBlue);
		return true;
	}

	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "이미 스탯 증가 효과를 받는 중입니다.", true, ConsoleColor::Magenta);
	return false;
}

shared_ptr<Item> AttackBoostPotion::clone() const
{
	return make_shared<AttackBoostPotion>(*this);
}
