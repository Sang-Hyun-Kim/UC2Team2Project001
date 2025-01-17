#include "pch.h"
#include "ISkillAction.h"
#include "Character.h"
#include "GlobalEventManager.h"
#include "ICharacterEventTypes.h"
#include "CombatComponent.h"
#include "Skill.h"
#include "UStatusComponent.h"
#include "StatComponent.h"
#include "IStrategy.h"
#include "ConsoleLayout.h"
#include <string>



void NormalAttackAction::ExecuteAction()
{
	Character* self = parentSkill->GetSkillData().owner;

	Character* target = parentSkill->GetTarget();

	if (CharacterUtility::IsDead(self))
	{
		// 디버그용 로그
		//std::cout << "Self 캐릭터가 죽어서 액션을 사용할 수 없습니다" << std::endl;
		return;
	}

	if (!target)
	{
		cout << "타겟이 없습니다." << endl;
		return;
	}

	if (!self->combatManager->GetAttackStrategy())
	{
		cout << "공격 전략이 설정되지 않았습니다." << endl;
		return;
	}

	float Damage = CharacterUtility::GetStat(self, StatType::AttackPower);
	
	self->combatManager->GetAttackStrategy()->Attack(self, target, Damage);
}


void AttackAction::ExecuteAction()
{
	Character* self = parentSkill->GetSkillData().owner;

	Character* target = parentSkill->GetTarget();

	if (CharacterUtility::IsDead(self))
	{
		return;
	}

	if (!target)
	{
		cout << "타겟이 없습니다." << endl;
		return;
	}

	if (!self->combatManager->GetAttackStrategy())
	{
		cout << "공격 전략이 설정되지 않았습니다." << endl;
		return;
	}

	// 공격 전략 실행
	self->combatManager->GetAttackStrategy()->Attack(self, target, attackDamage);
}

void PoisonIntensifierAction::ExecuteAction()
{
	Character* target = parentSkill->GetTarget();
	auto poisonState = target->statusManager->GetState<PoisonState>();
	if (poisonState)
	{
		poisonState->ApplyStack(poisonState->currentStack);
	}
}

void PoisonPogAction::ExecuteAction()
{
	Character* target = parentSkill->GetTarget();
	auto poisonState = target->statusManager->GetState<PoisonState>();
	if (poisonState)
	{
		poisonState->ApplyStack(2);
		poisonState->ApplyEffect(target);
	}
}

void PoisonTriggerAction::ExecuteAction()
{
	Character* target = parentSkill->GetTarget();
	auto poisonState = target->statusManager->GetState<PoisonState>();

	if (poisonState)
	{
		float TriggerPoisonDamage = poisonState->currentStack * poisonState->GetDuration();
		target->statManager->ModifyStat(StatType::HP, TriggerPoisonDamage);
		cout << "독을 격발하였습니다" << endl;
	}
}

void GlacialShardAction::ExecuteAction()
{
	Character* owner = parentSkill->GetSkillData().owner;
	Character* target = parentSkill->GetTarget();

	if (!owner || !target)
	{
		DEBUG_COUT("");
		std::cout << "대상 또는 소유자가 없습니다." << std::endl;
		return;
	}

	// 공격력의 200% 피해를 입힘
	float attackPower = CharacterUtility::GetStat(owner, StatType::AttackPower);
	int damage = static_cast<int>(attackPower * damageMultiplier);

	std::string skillPrint = owner->GetName() + "이(가) 빙하의 파편을 사용 " + to_string(damage) + " 피해! 방어력 20% 감소!";
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, skillPrint, true, ConsoleColor::Blue);

	target->combatManager->TakeDamage(damage);

	// 방어력을 20% 감소 (2턴 동안)
	float defenseReductionValue = CharacterUtility::GetStat(target, StatType::Defense) * defenseReduction;
	target->statusManager->AddState(std::make_shared<ModifyDefenseState>(defenseDuration, -defenseReductionValue));
	
}

void ChargeRageAction::ExecuteAction()
{
	Character* owner = parentSkill->GetSkillData().owner;

	if (!owner)
	{
		DEBUG_COUT("");
		std::cerr << "스킬 소유자가 유효하지 않습니다." << std::endl;
		return;
	}

	// 상태 추가: 다음 공격에 500% 피해 보너스
	auto rageState = std::make_shared<RageState>(rageMultiplier, 1); // 1턴 지속
	owner->statusManager->AddState(rageState);

	std::string skillPrint = owner->GetName() + "이(가) 분노 사용! 다음 공격에 500% 피해 보너스!";
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, skillPrint, true, ConsoleColor::Red);

}
