#include "pch.h"
#include "PoisonBottle.h"
#include "Character.h"
#include "UStatusComponent.h"
#include "CharacterStatus.h"
#include "CombatComponent.h"
#include "ConsoleLayout.h"

PoisonBottle::PoisonBottle(int _id) : ThrowableItem(_id, "독병", "적에게 독병을 던져 중독 상태를 2스택 적용합니다. 2턴 지속", 100)
{
}

bool PoisonBottle::use(Character* _owner)
{
	Character* target = _owner->combatManager->GetTarget();
	shared_ptr<PoisonState> state = make_shared<PoisonState>(2, 5, 2);
	target->statusManager->AddState(state);
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, target->GetName() + "에게 중독 상태가 적용 되었습니다.", true, ConsoleColor::LightBlue);
	return true;
}

shared_ptr<Item> PoisonBottle::clone() const
{
	return make_shared<PoisonBottle>(*this);
}
