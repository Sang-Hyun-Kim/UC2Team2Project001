#include "pch.h"
#include "GameSystem.h"
#include "GlobalEventManager.h"
#include "IEventTypes.h"
#include "Character.h"
#include "IStrategy.h"
#include <filesystem>
#include "UIEventManagerSystem.h"
#include "Monster.h"
#include "StatComponent.h"
#include "ItemManager.h"
#include "Item.h"

// 게임 시스템 코드가 돌아갈 main 함수

int main()
{
	// 랜덤 함수 시드 설정
	srand(time(NULL));

	// GlobalEventManager 싱글톤 인스턴스 가져오기
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	// UI 시스템 생성
	auto UISystem = std::make_shared<UIEventManagerSystem>();
	eventManager.Subscribe(UISystem);


	//std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

#pragma region 캐릭터 테스트 예시 코드

	ItemManager::GetInstance().init();

	Character* player = new Character("Player");
	Monster* monster = new Monster(1);
	
	// 공격 전략 설정
	player->SetAttackStrategy(std::make_shared<BasicAttackStrategy>());
	// 방어 전략 설정
	player->SetDefenseStrategy(make_shared<BlockDefenseStrategy>());
	while (!monster->StatManager->IsDead())
	{
		player->Attack(monster);
		monster->Attack(player);
	}

	cout << player->GetName() << "가 " << monster->CharacterReward.DropGold << "골드를 획득했습니다.\n";
	
	// 아이템이 있을 경우
	if (monster->CharacterReward.DropItem != nullptr)
	{
		// 현재 아이템 이름이 설정되어 있지 않아서 빈칸으로 출력됨
		cout << player->GetName() << "가 " << monster->CharacterReward.DropItem.get()->GetName() << "을(를) 획득했습니다.";
	}

	delete player;
	delete monster;

#pragma endregion
	

	/*GLobbySystem->CreatePlayer();
	GLobbySystem->PlayerMove();
	GBattleSystem->EnterSystem();*/
}
