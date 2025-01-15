#include "pch.h"
#include "LifeStealAttack.h"

//LifeStealAttack::LifeStealAttack()
//{
//	shared_ptr<ISkillAction> action = make_shared<AttackAction>();
//	shared_ptr<ISkillEffect> effect = make_shared<ILifeStealEffect>(10);
//	FSkillData skillData("기본 스킬", 10, 3, action, { effect }, combatManager->GetOwner(), combatManager->GetTarget());
//}

LifeStealAttack::LifeStealAttack(Character* _owner) : ActiveSkill(_owner)
{
	//skillData= FSkillData(_owner,"흡혈 공격", 10, 3);
	//
	//skillData.action = make_shared<AttackAction>();

	//shared_ptr<ISkillEffect> lifeEffect = make_shared<ILifeStealEffect>(10);
	//skillData.effects.push_back(lifeEffect);


	//SkillInit<Skill>(); //여기 다음에 갑자기 캐릭터소멸자 호출? //왜 ?
}
