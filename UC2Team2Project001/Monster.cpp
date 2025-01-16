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

//void Monster::SetMonsterStat(int _playerLevel)
//{
//	// 보스 몬스터라면 능력치 1.5배 범위에서 설정
//	// 보스가 아닐경우 배수는 1
//	float bossStat = 1.0f;
//	// 보스 몬스터 이름 인덱스 = 0
//	int randomIndex = 0;
//	if (isBoss)
//	{
//		bossStat = 1.5f;
//	}
//	else
//	{
//		// 랜덤 엔진 및 실수형 분포 설정
//		random_device rd;
//		mt19937 gen(rd());
//		// 보스 몬스터 인덱스 0을 제외한 범위로 난수 생성
//		uniform_real_distribution<> dis(1.0, (unsigned int)monsterNames.size() - 1);
//
//		// 실수형 랜덤 값 -> 정수로 변환
//		// 일반 몬스터 이름 인덱스 랜덤 설정
//		randomIndex = static_cast<int>(dis(gen));
//	}
//
//	// 몬스터 이름 설정
//	characterName = monsterNames[randomIndex];
//	displayName = characterName;
//
//	statManager.get()->BeginPlay();
//	StatsData LoadStatsData = StatsLoader::LoadFromJSON(characterName);
//
//	// 전략 설정
//	combatManager->SetAttackStrategy(StrategyFactory::CreateAttackStrategy(LoadStatsData.AttackStrategyData));
//	combatManager->SetDefenseStrategy(StrategyFactory::CreateDefenseStrategy(LoadStatsData.DefenseStrategyData));
//
//	// 체력 = 레벨 * (20 ~ 30)
//	int randomHP = (rand() % (int)(20 * bossStat)) + (int)(30 * bossStat);
//	float HP = (float)_playerLevel * randomHP;
//	statManager->SetStat(StatType::MaxHP, HP);
//	statManager->SetStat(StatType::HP, HP);
//
//	// 공격력 = 레벨 * (5 ~ 10)
//	int randomAttackPower = (rand() % (int)(5 * bossStat)) + (int)(10 * bossStat);
//	float attackPower = (float)_playerLevel * randomAttackPower;
//	statManager->SetStat(StatType::AttackPower, attackPower);
//
//	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(BasicAttack), this);
//}

void Monster::Initialize()
{
	ManagerRegister();

	// 플레이어 레벨 가져오기
	std::shared_ptr<Player> player = GSystemContext->GetPlayer();
	if (player) 
	{
		balanceLevel = static_cast<int>(player->statManager->GetStat(StatType::Level));
	}
	else
	{
		balanceLevel = 3;
	}

	

	// 몬스터 이름 설정
	characterName = DetermineMonsterName(balanceLevel);

	// JSON에서 몬스터 기본 스탯 로드
	StatsData baseStats = StatsLoader::LoadFromJSON(characterName);
	
	// 플레이어 레벨에 따라 스탯 조정
	AdjustStatsForLevel(baseStats, balanceLevel);

	// 처치 보상 생성
	CreateCharacterReward();

	SkillManager::GetInstance().CreateSkillFromType(typeid(BasicAttack), this);
}

void Monster::SetBlance(Character* _player)
{
	balanceLevel = (int)CharacterUtility::GetStat(Player, StatType::Level);
}

std::string Monster::DetermineMonsterName(int _playerLevel)
{
	// 플레이어 레벨에 따라 몬스터 이름 결정
	std::vector<std::string> possibleNames;

	if (_playerLevel <= 3) 
	{
		possibleNames = { "Slime", "Goblin" ,"RedSlime"};
	}
	else if (_playerLevel <= 5) 
	{
		possibleNames = { "Goblin", "Troll" };
	}
	else if (_playerLevel <= 9) 
	{
		possibleNames = { "Troll", "Orc" };
	}
	else 
	{
		possibleNames = { "Dragon" };
		bIsBoss = true; // 레벨 10 이상일 때 보스 설정
	}

	// 랜덤으로 이름 선택
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, possibleNames.size() - 1);

	return possibleNames[dis(gen)];
}

void Monster::AdjustStatsForLevel(const StatsData& baseStats, int playerLevel)
{
	// JSON에서 불러온 기본 스탯을 기준으로 플레이어 레벨에 따라 스탯 조정
	float levelMultiplier = 1.0f + (playerLevel * 0.1f);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> variation(-0.25, 0.25); // ±25% 변동

	float hp = baseStats.HP * levelMultiplier * (1.0f + variation(gen));
	float mp = baseStats.MP * levelMultiplier * (1.0f + variation(gen));
	float attackPower = baseStats.AttackPower * levelMultiplier * (1.0f + variation(gen));
	float defense = baseStats.Defense * levelMultiplier * (1.0f + variation(gen));
	float criticalChance = baseStats.CriticalChance * (1.0f + variation(gen));

	// 스탯 설정
	statManager->SetStat(StatType::HP, hp);
	statManager->SetStat(StatType::MaxHP, hp);
	statManager->SetStat(StatType::MP, mp);
	statManager->SetStat(StatType::MaxMP, mp);
	statManager->SetStat(StatType::AttackPower, attackPower);
	statManager->SetStat(StatType::Defense, defense);
	statManager->SetStat(StatType::CriticalChance, criticalChance);
}

bool Monster::IsBoss() const
{
	return isBoss;
}

void Monster::CreateCharacterReward()
{
	FCharacterReward reward = StatsLoader::LoadRewardFromJSON(characterName);

	characterReward.DropGold = reward.DropGold;

	characterReward.DropExperience = reward.DropExperience;

	// 아이템 드랍 확률: 30%
	if (rand() % 100 < 30) 
	{
		characterReward.DropItem = ItemManager::GetInstance().getRandomItem();
	}
	else 
	{
		characterReward.DropItem = nullptr;
	}
}
