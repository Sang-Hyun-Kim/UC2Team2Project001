#include "pch.h"
#include "Monster.h"
#include "StatComponent.h"
#include "IStrategy.h"
#include "ItemManager.h"
#include "Item.h"
#include "StatsLoader.h"
#include "StrategyFactory.h"
#include "USkillComponent.h"
#include "Skill.h"
#include "ISkillAction.h"
#include "ISkillEffect.h"
#include "CombatComponent.h"

Monster::Monster(int PlayerLevel)
{
	// 입력받은 플레이어의 레벨이 10 이상인 경우 보스 몬스터 생성
	if (PlayerLevel >= 10)
	{
		bIsBoss = true;
	}
	else
	{
		bIsBoss = false;
	}

	// 몬스터 스탯 설정
	SetMonsterStat(PlayerLevel);

	// 몬스터 생성시 지니고 있을 골드와 아이템을 설정
	CreateCharacterReward();

	// 몬스터 스킬 설정
	shared_ptr<ISkillAction> action = make_shared<AttackAction>();
	shared_ptr<ISkillEffect> effect = make_shared<ILifeStealEffect>(10);
	FSkillData skillData("기본 스킬", 10, 3, action, { effect }, combatManager->GetOwner(), combatManager->GetTarget());

	shared_ptr<ActiveSkill> basicAttack = make_shared<ActiveSkill>(skillData);
	effect->SetSkill(basicAttack);

	skillManager.get()->AddSkill(basicAttack);

}

void Monster::SetMonsterStat(int PlayerLevel)
{
	// 보스 몬스터라면 능력치 1.5배 범위에서 설정
	// 보스가 아닐경우 배수는 1
	float BossStat = 1.0f;
	// 보스 몬스터 이름 인덱스 = 0
	int randomIndex = 0;
	if (bIsBoss)
	{
		BossStat = 1.5f;
	}
	else
	{
		// 랜덤 엔진 및 실수형 분포 설정
		random_device rd;
		mt19937 gen(rd());
		// 보스 몬스터 인덱스 0을 제외한 범위로 난수 생성
		uniform_real_distribution<> dis(1.0, (unsigned int)MonsterNames.size() - 1);

		// 실수형 랜덤 값 -> 정수로 변환
		// 일반 몬스터 이름 인덱스 랜덤 설정
		randomIndex = static_cast<int>(dis(gen));
	}

	// 몬스터 이름 설정
	characterName = MonsterNames[randomIndex];

	statManager.get()->BeginPlay();
	StatsData LoadStatsData = StatsLoader::LoadFromJSON(characterName);
	Initialize(LoadStatsData);

	// 체력 = 레벨 * (20 ~ 30)
	int RandomHP = (rand() % (int)(20 * BossStat)) + (int)(30 * BossStat);
	float HP = (float)PlayerLevel * RandomHP;
	statManager->SetStat(StatType::MaxHP, HP);
	statManager->SetStat(StatType::HP, HP);

	// 공격력 = 레벨 * (5 ~ 10)
	int RandomAttackPower = (rand() % (int)(5 * BossStat)) + (int)(10 * BossStat);
	float AttackPower = (float)PlayerLevel * RandomAttackPower;
	statManager->SetStat(StatType::AttackPower, AttackPower);
}

bool Monster::IsBoss() const
{
	return bIsBoss;
}

void Monster::CreateCharacterReward()
{
	// 골드는 10 ~ 15 범위로 랜덤 설정
	characterReward.DropGold = (rand() % 10) + 15;

	// 아이템은 30% 확률로 드랍
	// 0 ~ 99 범위로 랜덤 값 설정(총 100범위)
	int RandomValue = rand() % 99;

	// 해당 랜덤 값이 30미만 인지 판별(0~29 => 총 30범위)
	bool CanItemDrop = RandomValue < 30;

	if (CanItemDrop)
	{
		// 아이템 랜덤으로 지정
		characterReward.DropItem = ItemManager::GetInstance().getRandomItem();
	}
	else
	{
		// 아이템 없음 = nullptr
		characterReward.DropItem = nullptr;
	}
}
