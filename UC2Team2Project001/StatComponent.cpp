#include "pch.h"

#include "StatComponent.h"
#include "Character.h"
#include "GlobalEventManager.h"


#include <fstream>
#include "StatsLoader.h"
#include "ICharacterEventTypes.h"
#include "USkillComponent.h"

#include "ConsoleLayout.h"

UStatsComponent::UStatsComponent(Character* _inOwnedCharacter)
{
	ownedCharacter = _inOwnedCharacter;
}

void UStatsComponent::BeginPlay()
{
	if (!ownedCharacter)
	{
		std::cerr << "Error: OwnedCharacter가 없습니다!" << std::endl;
		return;
	}
}

void UStatsComponent::Initialize(StatsData _loadStatsData)
{
	// 스탯 설정
	SetStat(StatType::HP, _loadStatsData.HP);
	SetStat(StatType::MaxHP, _loadStatsData.MaxHP);
	SetStat(StatType::MP, _loadStatsData.MP);
	SetStat(StatType::MaxMP, _loadStatsData.MaxMP);
	SetStat(StatType::AttackPower, _loadStatsData.AttackPower);
	SetStat(StatType::Defense, _loadStatsData.Defense);
	SetStat(StatType::CriticalChance, _loadStatsData.CriticalChance);
	SetStat(StatType::EvasionRate, _loadStatsData.EvasionRate);
	SetStat(StatType::Level, _loadStatsData.Level);
	SetStat(StatType::Experience, _loadStatsData.Experience);
	SetStat(StatType::MaxExperience, _loadStatsData.MaxExperience);
	//PrintStatus();
}

UStatsComponent::~UStatsComponent()
{
}

void UStatsComponent::LoadFromJSON()
{
	// OwnerCharacter의 이름을 가져옴
	std::string characterName = ownedCharacter->GetName();


	try
	{
		// StatsLoader를 통해 JSON에서 스탯 로드
		StatsData loadStatsData = StatsLoader::LoadFromJSON(characterName);

		stats = {
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
	catch (const std::exception& _exception)
	{
		std::cerr << "캐릭터에 대한 통계를 로드하는 중 오류가 발생했습니다.'" << characterName << "': " << _exception.what() << std::endl;
	}
}

float UStatsComponent::GetStat(StatType _type) const
{
	auto it = stats.find(_type);
	if (it != stats.end())
		return it->second;
	return 0.0f;
}

void UStatsComponent::SetStat(StatType _type, float _value)
{
	stats[_type] = _value;
}

void UStatsComponent::ModifyStat(StatType _type, float _delta)
{
	// 스탯 변경
	stats[_type] += _delta;

	if (stats[_type] < 0)
	{
		stats[_type] = 0;
	}

	// HP, MP 경계값 처리
	if (_type == StatType::HP || _type == StatType::MP)
	{
		StatType maxStatType = (_type == StatType::HP) ? StatType::MaxHP : StatType::MaxMP;
		ClampStat(_type, 0.0f, GetStat(maxStatType));

		if (_type == StatType::HP && stats[StatType::HP] == 0)
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
	return (stats[StatType::HP] <= 0);
}

std::string UStatsComponent::FormatFloat(float value, int precision) {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(precision) << value;
	return oss.str();
}

void UStatsComponent::PrintStatus(int type)
{

	ConsoleRegionType _consoleRegion;

	if (type == 0)
	{
		_consoleRegion = ConsoleRegionType::LeftTop;
	}
	else if (type == 1)
	{
		_consoleRegion = ConsoleRegionType::RightTop;
	}
	else if (type == 2)
	{
		_consoleRegion = ConsoleRegionType::LeftBottom;
	}
	else if (type == 3)
	{
		_consoleRegion = ConsoleRegionType::RightBottom;
	}

	auto& layout = ConsoleLayout::GetInstance();

	vector<string> statusLines;
	std::ostringstream oss;
	oss.precision(1); // 소수점 이하 1자리

	layout.AppendLine(_consoleRegion, "=================== 캐릭터 정보 ===================");
	layout.AppendLine(_consoleRegion, "이름    : " + (ownedCharacter ? ownedCharacter->GetName() : "None"));
	layout.AppendLine(_consoleRegion, "레벨    : " + std::to_string(int(stats[StatType::Level])));
	layout.AppendLine(_consoleRegion, "경험치  : " + FormatFloat(stats[StatType::Experience]) + " / " + FormatFloat(stats[StatType::MaxExperience]));

	//layout.AppendLine(ConsoleRegionType::LeftTop, "================ 캐릭터 스테이터스 ================");

	layout.AppendLine(_consoleRegion, "HP      : " + std::to_string(int(stats[StatType::HP])) + " / " + std::to_string(int(stats[StatType::MaxHP])));
	layout.AppendLine(_consoleRegion, "MP      : " + std::to_string(int(stats[StatType::MP])) + " / " + std::to_string(int(stats[StatType::MaxMP])));
	
	layout.AppendLine(_consoleRegion, "공격력  : " + FormatFloat(stats[StatType::AttackPower]));
	layout.AppendLine(_consoleRegion, "방어력  : " + FormatFloat(stats[StatType::Defense]));
	layout.AppendLine(_consoleRegion, "치명타율: " + FormatFloat(stats[StatType::CriticalChance] * 100) + "%");
	layout.AppendLine(_consoleRegion, "회피율  : " + FormatFloat(stats[StatType::EvasionRate]) + "%");
	layout.AppendLine(_consoleRegion, "==================================================");
}

void UStatsComponent::LevelUp()
{
	// 레벨 증가
	stats[StatType::Level] += 1;

	// 체력/최대체력 증가
	stats[StatType::MaxHP] += 20;
	// 체력은 새로 오른 최대체력으로 보충
	stats[StatType::HP] = stats[StatType::MaxHP];

	// MP/최대MP 증가
	stats[StatType::MaxMP] += 10;
	stats[StatType::MP] = stats[StatType::MaxMP];

	// 공격력 증가
	stats[StatType::AttackPower] += 5;

	// 방어력 증가
	stats[StatType::Defense] += 2;

	// 다음 레벨에 필요한 경험치 증가(예: +20)
	stats[StatType::MaxExperience] += 20;

	// 레벨업 시점에 메시지 출력 (UI 이벤트를 보낼 수도 있음)
	auto NewLevelUpEvent = make_shared<ICharacterLevelUpEvent>(ownedCharacter->GetName(), (int)stats[StatType::Level]);
	GlobalEventManager::Get().Notify(NewLevelUpEvent);
}

void UStatsComponent::ClampStat(StatType type, float _minValue, float _maxValue) 
{
	stats[type] = std::clamp(stats[type], _minValue, _maxValue);
}


void UStatsComponent::HandleCharacterDeath()
{
	// 불굴의 의지 스킬 확인
	if (ownedCharacter->skillManager->GetSkill(SkillType::PASSIVE, "불굴의 의지"))
	{
		auto characterStatZeroEvent = std::make_shared<ICharacterStatZeroEvent>(ownedCharacter->GetName());
		GlobalEventManager::Get().Notify(characterStatZeroEvent);
	}
	else
	{
		auto characterDeadEvent = std::make_shared<ICharacterDeadEvent>(ownedCharacter->GetName(), ownedCharacter->characterReward);
		GlobalEventManager::Get().Notify(characterDeadEvent);
	}
}

void UStatsComponent::HandleExperienceGain()
{
	float currentExp = stats[StatType::Experience];
	float maxExp = stats[StatType::MaxExperience];

	// 여러 레벨이 한 번에 오를 수 있도록 while 루프 사용
	while (currentExp >= maxExp)
	{
		float leftover = currentExp - maxExp;
		stats[StatType::Experience] = leftover;
		LevelUp();

		// 레벨업 이후 maxExp 값이 변경될 수 있으므로 다시 확인
		currentExp = stats[StatType::Experience];
		maxExp = stats[StatType::MaxExperience];
	}
}