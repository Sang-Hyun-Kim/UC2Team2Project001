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
#include "LifeStealAttack.h"
#include "GameSystem.h"
#include "PlayerCharacter.h"
#include "BasicAttack.h"
#include "SkillManager.h"

Monster::Monster()
{
}

void Monster::SetMonsterStat(int _playerLevel)
{
	// 보스 몬스터라면 능력치 1.5배 범위에서 설정
	// 보스가 아닐경우 배수는 1
	float bossStat = 1.0f;
	// 보스 몬스터 이름 인덱스 = 0
	int randomIndex = 0;
	if (isBoss)
	{
		bossStat = 1.5f;
	}
	else
	{
		// 랜덤 엔진 및 실수형 분포 설정
		random_device rd;
		mt19937 gen(rd());
		// 보스 몬스터 인덱스 0을 제외한 범위로 난수 생성
		uniform_real_distribution<> dis(1.0, (unsigned int)monsterNames.size() - 1);

		// 실수형 랜덤 값 -> 정수로 변환
		// 일반 몬스터 이름 인덱스 랜덤 설정
		randomIndex = static_cast<int>(dis(gen));
	}

	// 몬스터 이름 설정
	characterName = monsterNames[randomIndex];
	displayName = characterName;

	statManager.get()->BeginPlay();
	StatsData LoadStatsData = StatsLoader::LoadFromJSON(characterName);

	// 전략 설정
	combatManager->SetAttackStrategy(StrategyFactory::CreateAttackStrategy(LoadStatsData.AttackStrategyData));
	combatManager->SetDefenseStrategy(StrategyFactory::CreateDefenseStrategy(LoadStatsData.DefenseStrategyData));

	// 체력 = 레벨 * (20 ~ 30)
	int randomHP = (rand() % (int)(20 * bossStat)) + (int)(30 * bossStat);
	float HP = (float)_playerLevel * randomHP;
	statManager->SetStat(StatType::MaxHP, HP);
	statManager->SetStat(StatType::HP, HP);

	// 공격력 = 레벨 * (5 ~ 10)
	int randomAttackPower = (rand() % (int)(5 * bossStat)) + (int)(10 * bossStat);
	float attackPower = (float)_playerLevel * randomAttackPower;
	statManager->SetStat(StatType::AttackPower, attackPower);

	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(BasicAttack), this);
}

void Monster::Initialize()
{
	shared_ptr<Player> player = GSystemContext->GetPlayer();

	blanceLevel = (int)player->statManager->GetStat(StatType::Level);

	ManagerRegister();

	// 입력받은 플레이어의 레벨이 10 이상인 경우 보스 몬스터 생성
	if (blanceLevel >= 10)
	{
		isBoss = true;
	}
	else
	{
		isBoss = false;
	}

	// 몬스터 스탯 설정
	SetMonsterStat(blanceLevel);

	// 몬스터 생성시 지니고 있을 골드와 아이템을 설정
	CreateCharacterReward();
}

void Monster::SetBlance(Character* _player)
{
	blanceLevel = (int)CharacterUtility::GetStat(_player, StatType::Level);
}

bool Monster::IsBoss() const
{
	return isBoss;
}

void Monster::CreateCharacterReward()
{
	// 골드는 10 ~ 15 범위로 랜덤 설정
	characterReward.dropGold = (rand() % 10) + 15;

	// 아이템은 30% 확률로 드랍
	// 0 ~ 99 범위로 랜덤 값 설정(총 100범위)
	int randomValue = rand() % 99;

	// 해당 랜덤 값이 30미만 인지 판별(0~29 => 총 30범위)
	bool canItemDrop = randomValue < 30;

	if (canItemDrop)
	{
		// 아이템 랜덤으로 지정
		characterReward.dropItem = ItemManager::GetInstance().getRandomItem();
	}
	else
	{
		// 아이템 없음 = nullptr
		characterReward.dropItem = nullptr;
	}
}
