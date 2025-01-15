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

Monster::Monster()
{
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

void Monster::Initialize()
{
	GSystemContext->GetPlayer();
	//ToDo:
	/*SetBlance(GLobbySystem->player->GetName());*/

	// 입력받은 플레이어의 레벨이 10 이상인 경우 보스 몬스터 생성
	if (blanceLevel >= 10)
	{
		bIsBoss = true;
	}
	else
	{
		bIsBoss = false;
	}

	
	// 몬스터 스탯 설정
	SetMonsterStat(blanceLevel);

	// 몬스터 생성시 지니고 있을 골드와 아이템을 설정
	CreateCharacterReward();

	// 몬스터 스킬 설정


	//그냥 스킬을생성하고 추가하는거야.

	// 캐릭터 소멸자가 불리는 느낌?
	// 캐릭터가 소멸되니까 오류가 발생해
	//애를 주석치니까 일단은 캐릭터소멸자가 호출이 안됨

	//캐릭터가 소멸자가 호출을해야?
	//스킬을 만들었을분인데 왜 캐릭터가소멸하지?
	//이렇게하면 널포인터가  move 그래

	//charcter*
	//만든건다!
	//this 바라보는 쉐어드를만드는게
	//캐릭터자체를 또 새로만들어서 그걸 바라노는 쉐어드포인터 x

	//왜 캐릭터소멸자?
	//  this -> Monster* A123
	// 쉐어드포인터를 A123 ->
	// MOnster* BFasdf45587
	// 
	//복사생성자 캐릭터가 하나 더 생성된다? 

	//소멸자가 호출이 되는 과정 스텟매니저 

	//캐릭터를 생성하지 않아요.
	//this-> 바라보는 쉐어드포인터가 된다.
	// 
	//캐릭터를 새로만들어 <<쉐어드포인터
	//캐릭터를 새로만들었으니까 임시객체로 만든 얘가 필요없으니 지워야지<< 지우니까 소멸자가 호출되는건지


	//기존 착각 
	// main.cpp 에선 1참조가 있으니 저렇게 하면 2참조가 된다.

	//쉐어드포인터가 참조카운1인 새로운 쉐어드포인터




	//this

	// Monster가 이미 make_shared<Monster>()로 생성되었다는 전제 하에

	//shared_ptr<LifeStealAttack> newLifeStealAttack = make_shared<LifeStealAttack>(shared_from_this());



	//skillManager.get()->AddSkill(newLifeStealAttack);
}

void Monster::SetBlance(Character* Player)
{
	blanceLevel = (int)CharacterUtility::GetStat(Player, StatType::Level);
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
