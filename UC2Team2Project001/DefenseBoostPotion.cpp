#include "pch.h"
#include "DefenseBoostPotion.h"
#include "UStatusComponent.h"
#include "CharacterStatus.h"
#include "Character.h"
#include "ConsoleLayout.h"

DefenseBoostPotion::DefenseBoostPotion(int _id) : Potion(_id, "방어력 부스트 물약", "방어력이 5 증가합니다.", 50)
{
}

bool DefenseBoostPotion::use(Character* _target)
{
	if (!_target->statusManager->GetState<ModifyStatState>())
	{
		shared_ptr<ModifyStatState> state = make_shared<ModifyStatState>(5, StatType::Defense, 5);
		_target->statusManager->AddState(state);
		state->ApplyEffect(_target);
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "방어력이 5상승 합니다.", true, ConsoleColor::LightBlue);
		return true;
	}
	
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "이미 스탯 증가 효과를 받는 중입니다.", true, ConsoleColor::Magenta);
	return false;
}

shared_ptr<Item> DefenseBoostPotion::clone() const
{
	return make_shared<DefenseBoostPotion>(*this);
}