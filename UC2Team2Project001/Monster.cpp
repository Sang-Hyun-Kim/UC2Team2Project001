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

	displayName = characterName;

	// JSON에서 몬스터 기본 스탯 로드
	StatsData baseStats = StatsLoader::LoadFromJSON(characterName);
	
	statManager->Initialize(baseStats);
	combatManager->Initialize(baseStats);

	// 플레이어 레벨에 따라 스탯 조정
	AdjustStatsForLevel(baseStats, balanceLevel);

	// 처치 보상 생성
	CreateCharacterReward();

	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(BasicAttack), this);

}

void Monster::SetBlance(Character* _player)
{
	balanceLevel = (int)CharacterUtility::GetStat(_player, StatType::Level);
}

std::string Monster::DetermineMonsterName(int _playerLevel)
{
	// 플레이어 레벨에 따라 몬스터 이름 결정
	std::vector<std::string> possibleNames;

	if (_playerLevel <= 3) 
	{
		//possibleNames = { "Slime"};
		possibleNames = { "Slime", "Goblin" ,"RedSlime"};
	}
	else if (_playerLevel <= 5) 
	{
		//possibleNames = { "Slime"};
		possibleNames = { "Goblin", "Troll" };
	}
	else if (_playerLevel <= 9) 
	{
		//possibleNames = { "Slime"};
		possibleNames = { "Troll", "Orc" };
		//possibleNames = { "Slime"};
	}
	else 
	{
		possibleNames = { "Dragon" };
		isBoss = true; // 레벨 10 이상일 때 보스 설정
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

	float hp = std::round(baseStats.HP * levelMultiplier * (1.0f + variation(gen)));
	float mp = std::round(baseStats.MP * levelMultiplier * (1.0f + variation(gen)));
	float attackPower = std::round(baseStats.AttackPower * levelMultiplier * (1.0f + variation(gen)));
	float defense = std::round(baseStats.Defense * levelMultiplier * (1.0f + variation(gen)));
	float criticalChance = baseStats.CriticalChance * (1.0f + variation(gen));
	float evasionRate = baseStats.EvasionRate * (1.0f + variation(gen));

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

	characterReward.dropGold = reward.dropGold;

	characterReward.dropExperience = reward.dropExperience;

	// 아이템 드랍 확률: 30%
	if (rand() % 100 < 30) 
	{
		characterReward.dropItem = ItemManager::GetInstance().getRandomItem();
	}
	else 
	{
		characterReward.dropItem = nullptr;
	}
}
