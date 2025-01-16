#include "pch.h"
#include "FireBottle.h"
#include "Character.h"
#include "UStatusComponent.h"
#include "CharacterStatus.h"
#include "CombatComponent.h"
#include "ConsoleLayout.h"

FireBottle::FireBottle(int _id) : ThrowableItem(_id, "화염병", "적에게 화염병을 던져 화상 상태를 적용합니다. 2턴 지속", 100)
{
}

bool FireBottle::use(Character* _owner)
{
	Character* target = _owner->combatManager->GetTarget();
	shared_ptr<BurnState> state = make_shared<BurnState>(2, 10);
	target->statusManager->AddState(state);
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, target->GetName() + "에게 화상 상태가 적용 되었습니다.", true, ConsoleColor::LightBlue);
	return true;
}

shared_ptr<Item> FireBottle::clone() const
{
	return make_shared<FireBottle>(*this);
}
