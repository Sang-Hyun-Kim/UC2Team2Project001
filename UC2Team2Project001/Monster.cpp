#include "pch.h"
#include "Monster.h"
#include "StatComponent.h"
#include "IStrategy.h"
#include "ItemManager.h"
#include "Item.h"
#include "StatsLoader.h"
#include "StrategyFactory.h"

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
		uniform_real_distribution<> dis(1.0, MonsterNames.size() - 1);

		// 실수형 랜덤 값 -> 정수로 변환
		// 일반 몬스터 이름 인덱스 랜덤 설정
		randomIndex = static_cast<int>(dis(gen));
	}

	// 몬스터 이름 설정
	CharacterName = MonsterNames[randomIndex];

	StatManager.get()->BeginPlay();
	StatsData LoadStatsData = StatsLoader::LoadFromJSON(CharacterName);
	Initialize(LoadStatsData);

	// 체력 = 레벨 * (20 ~ 30)
	int RandomHP = (rand() % (int)(20 * BossStat)) + (int)(30 * BossStat);
	float HP = (float)PlayerLevel * RandomHP;
	StatManager->SetStat(StatType::MaxHP, HP);
	StatManager->SetStat(StatType::HP, HP);

	// 공격력 = 레벨 * (5 ~ 10)
	int RandomAttackPower = (rand() % (int)(5 * BossStat)) + (int)(10 * BossStat);
	float AttackPower = (float)PlayerLevel * RandomAttackPower;
	StatManager->SetStat(StatType::AttackPower, AttackPower);
}

bool Monster::IsBoss() const
{
	return bIsBoss;
}

void Monster::CreateCharacterReward()
{
	// 골드는 10 ~ 15 범위로 랜덤 설정
	CharacterReward.DropGold = (rand() % 10) + 15;

	// 아이템은 30% 확률로 드랍
	// 0 ~ 99 범위로 랜덤 값 설정(총 100범위)
	int RandomValue = rand() % 99;

	// 해당 랜덤 값이 30미만 인지 판별(0~29 => 총 30범위)
	bool CanItemDrop = RandomValue < 30;

	if (CanItemDrop)
	{
		// 아이템 랜덤으로 지정
		CharacterReward.DropItem = ItemManager::GetInstance().getRandomItem();
	}
	else
	{
		// 아이템 없음 = nullptr
		CharacterReward.DropItem = nullptr;
	}
}
