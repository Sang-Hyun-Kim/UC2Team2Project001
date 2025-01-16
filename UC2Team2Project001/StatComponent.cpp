#include "pch.h"

#include "StatComponent.h"
#include "Character.h"
#include "GlobalEventManager.h"


#include <fstream>
#include "StatsLoader.h"
#include "ICharacterEventTypes.h"
#include "USkillComponent.h"

UStatsComponent::UStatsComponent(Character* InOwnedCharacter)
{
	OwnedCharacter = InOwnedCharacter;
}

void UStatsComponent::BeginPlay()
{
	if (!OwnedCharacter)
	{
		std::cerr << "Error: OwnedCharacter가 없습니다!" << std::endl;
		return;
	}
}

void UStatsComponent::Initialize(StatsData LoadStatsData)
{
	// 스탯 설정
	SetStat(StatType::HP, LoadStatsData.HP);
	SetStat(StatType::MaxHP, LoadStatsData.MaxHP);
	SetStat(StatType::MP, LoadStatsData.MP);
	SetStat(StatType::MaxMP, LoadStatsData.MaxMP);
	SetStat(StatType::AttackPower, LoadStatsData.AttackPower);
	SetStat(StatType::Defense, LoadStatsData.Defense);
	SetStat(StatType::CriticalChance, LoadStatsData.CriticalChance);
	SetStat(StatType::EvasionRate, LoadStatsData.EvasionRate);
	SetStat(StatType::Level, LoadStatsData.Level);
	SetStat(StatType::Experience, LoadStatsData.Experience);
	SetStat(StatType::MaxExperience, LoadStatsData.MaxExperience);
	PrintStatus();
}

UStatsComponent::~UStatsComponent()
{
}

void UStatsComponent::LoadFromJSON()
{
	// OwnerCharacter의 이름을 가져옴
	std::string characterName = OwnedCharacter->GetName();


	try
	{
		// StatsLoader를 통해 JSON에서 스탯 로드
		StatsData loadStatsData = StatsLoader::LoadFromJSON(characterName);

		Stats = {
		  {StatType::HP, loadStatsData.HP},
		  {StatType::MaxHP, loadStatsData.MaxHP},
		  {StatType::MP, loadStatsData.MP},
		  {StatType::MaxMP, loadStatsData.MaxMP},
		  {StatType::AttackPower, loadStatsData.AttackPower},
		  {StatType::Defense, loadStatsData.Defense},
		  {StatType::CriticalChance, loadStatsData.CriticalChance},
		  {StatType::EvasionRate, loadStatsData.EvasionRate},
		  {StatType::Level, loadStatsData.Level},
		  {StatType::Experience, loadStatsData.Experience},
		  {StatType::MaxExperience, loadStatsData.MaxExperience}
		};

		PrintStatus();
	}
	catch (const std::exception& e)
	{
		std::cerr << "캐릭터에 대한 통계를 로드하는 중 오류가 발생했습니다.'" << characterName << "': " << e.what() << std::endl;
	}
}

float UStatsComponent::GetStat(StatType type) const
{
	auto it = Stats.find(type);
	if (it != Stats.end())
		return it->second;
	return 0.0f;
}

void UStatsComponent::SetStat(StatType type, float value)
{
	Stats[type] = value;
}

void UStatsComponent::ModifyStat(StatType _type, float _delta)
{
	// 스탯 변경
	Stats[_type] += _delta;

	// HP, MP 경계값 처리
	if (_type == StatType::HP || _type == StatType::MP)
	{
		StatType maxStatType = (_type == StatType::HP) ? StatType::MaxHP : StatType::MaxMP;
		ClampStat(_type, 0.0f, GetStat(maxStatType));

		if (_type == StatType::HP && Stats[StatType::HP] == 0)
		{
			HandleCharacterDeath();
		}
	}
	else if (_type == StatType::Experience)
	{
		HandleExperienceGain();
	}
}

bool UStatsComponent::IsDead()
{
	return (Stats[StatType::HP] <= 0);
}

void UStatsComponent::PrintStatus()
{
	std::cout << "================ Character Status ================\n";
	std::cout << "Name: " << (OwnedCharacter ? OwnedCharacter->GetName(): "None") << "\n";
	std::cout << "Level: " << Stats[StatType::Level] << "\n";
	std::cout << "Experience: " << Stats[StatType::Experience]
		<< " / " << Stats[StatType::MaxExperience] << "\n";
	std::cout << "HP: " << Stats[StatType::HP]
		<< " / " << Stats[StatType::MaxHP] << "\n";
	std::cout << "MP: " << Stats[StatType::MP]
		<< " / " << Stats[StatType::MaxMP] << "\n";
	std::cout << "Attack Power: " << Stats[StatType::AttackPower] << "\n";
	std::cout << "Defense: " << Stats[StatType::Defense] << "\n";
	std::cout << "Critical Chance: " << (Stats[StatType::CriticalChance] * 100) << "%\n";
	std::cout << "Evasion Rate: " << (Stats[StatType::EvasionRate] * 100) << "%\n";
	std::cout << "==================================================\n";
	cout << endl;
}

void UStatsComponent::LevelUp()
{
	// 레벨 증가
	Stats[StatType::Level] += 1;

	// 체력/최대체력 증가
	Stats[StatType::MaxHP] += 20;
	// 체력은 새로 오른 최대체력으로 보충
	Stats[StatType::HP] = Stats[StatType::MaxHP];

	// MP/최대MP 증가
	Stats[StatType::MaxMP] += 10;
	Stats[StatType::MP] = Stats[StatType::MaxMP];

	// 공격력 증가
	Stats[StatType::AttackPower] += 5;

	// 방어력 증가
	Stats[StatType::Defense] += 2;

	// 다음 레벨에 필요한 경험치 증가(예: +20)
	Stats[StatType::MaxExperience] += 20;

	// 레벨업 시점에 메시지 출력 (UI 이벤트를 보낼 수도 있음)
	auto NewLevelUpEvent = make_shared<ICharacterLevelUpEvent>(OwnedCharacter->GetName(), (int)Stats[StatType::Level]);
	GlobalEventManager::Get().Notify(NewLevelUpEvent);
}


void UStatsComponent::ClampStat(StatType type, float _minValue, float _maxValue) 
{
	Stats[type] = std::clamp(Stats[type], _minValue, _maxValue);
}


void UStatsComponent::HandleCharacterDeath()
{
	// 불굴의 의지 스킬 확인
	if (OwnedCharacter->skillManager->GetSkill(SkillType::PASSIVE, "불굴의 의지"))
	{
		auto characterStatZeroEvent = std::make_shared<ICharacterStatZeroEvent>(OwnedCharacter->GetName());
		GlobalEventManager::Get().Notify(characterStatZeroEvent);
	}
	else
	{
		auto characterDeadEvent = std::make_shared<ICharacterDeadEvent>(OwnedCharacter->GetName(), OwnedCharacter->characterReward);
		GlobalEventManager::Get().Notify(characterDeadEvent);
	}
}

void UStatsComponent::HandleExperienceGain()
{
	float currentExp = Stats[StatType::Experience];
	float maxExp = Stats[StatType::MaxExperience];

	// 여러 레벨이 한 번에 오를 수 있도록 while 루프 사용
	while (currentExp >= maxExp)
	{
		float leftover = currentExp - maxExp;
		Stats[StatType::Experience] = leftover;
		LevelUp();

		// 레벨업 이후 maxExp 값이 변경될 수 있으므로 다시 확인
		currentExp = Stats[StatType::Experience];
		maxExp = Stats[StatType::MaxExperience];
	}
}