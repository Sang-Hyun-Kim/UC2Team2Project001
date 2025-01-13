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
#include <unordered_map>
#include "ICommand.h"
#include "Inventory.h"

// 게임 시스템 코드가 돌아갈 main 함수

using namespace std;

int main()
{
	// 랜덤 함수 시드 설정
	//srand(time(NULL));

	// GlobalEventManager 싱글톤 인스턴스 가져오기 //지우지마세요
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	// UI 시스템 생성  //지우지 마세요
	auto UISystem = std::make_shared<UIEventManagerSystem>();
	eventManager.Subscribe(UISystem);

	//			break;
	//	}

	//	//명령 안내
	//	cout << "\n 액션을 선택하세요.\n";
	//	cout << "[1] 공격 \n";
	//	cout << "[2] 아이템사용 \n";
	//	cout << "Input : ";

	//	int input;

	//	cin >> input;

	//	if (!cin || input == 0)
	//	{
	//		cout << "배틀을 종료합니다";
	//	}

	//	auto it = commandMap.find(input);
	//	if (it != commandMap.end())
	//	{
	//		it->second->Excute();
	//	}
	//	else
	//	{
	//		cout << "[System] 유효하지 않은 입력 액션입니다";
	//	}

#pragma region 캐릭터 테스트 예시 코드

	ItemManager::GetInstance().init();

	Character* player = new Character("Player");
	Monster* monster = new Monster(1);

	Inventory inv(player);

	inv.addItem(ItemManager::GetInstance().getRandomItem());
	inv.addItem(ItemManager::GetInstance().getRandomItem());
	inv.addItem(ItemManager::GetInstance().getRandomItem());
	inv.addItem(ItemManager::GetInstance().getRandomItem());
	inv.addGold(50);

	inv.displayInventory();

	inv.useItem(0);
	inv.useItem(0);
	inv.useItem(0);
	inv.removeGold(10);
	inv.displayInventory();
	
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


//현재 디렉토리 출력
	//std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;