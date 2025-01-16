#include "pch.h"
#include "GlobalEventManager.h"
#include "SystemContext.h"
#include "UIEventManagerSystem.h"
#include <memory>

#include "PlayerCharacter.h"
#include "Monster.h"
#include "CombatComponent.h"
#include "UTurnEventManager.h"
#include "SkillManager.h"
#include "Sanctification.h"
#include "USkillComponent.h"
#include "BasicAttack.h"
#include "PoisonedBlade.h"
#include "PoisonFog.h"

#include "ConsoleLayout.h"




// 실행 모드를 설정합니다.
// GAME_MODE = 1 : 메인 게임 루프 실행
// GAME_MODE = 0 : 디버그 테스트 실행
#define GAME_MODE 1
// 게임 시스템 코드가 돌아갈 main 함수



// 원하는 콘솔 (x, y) 위치에 text를 출력
void PrintAtCoordinates(int x, int y, const std::string& text)
{
	// 1) 콘솔 핸들 획득
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 2) 콘솔 커서 위치 설정
	COORD coord;
	coord.X = static_cast<SHORT>(x);
	coord.Y = static_cast<SHORT>(y);
	SetConsoleCursorPosition(hConsole, coord);

	// 3) std::cout으로 text 출력
	std::cout << text;
}

int main()
{
	// 랜덤 함수 시드 설정
	srand((unsigned int)time(NULL));

	// 싱글톤 객체 획득 (180×50)
	auto& layout = ConsoleLayout::GetInstance();

#if GAME_MODE == 1

	//GlobalEventManager 싱글톤 인스턴스 가져오기 
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	// UI 시스템 생성  //지우지 마세요
	auto UISystem = std::make_shared<UIEventManagerSystem>();

	eventManager.Subscribe(GSystemContext);
	eventManager.Subscribe(UISystem);


	while (true)
	{
		GSystemContext->Update(); // Update()로 변경해야함
	}


#elif GAME_MODE == 0

	//GlobalEventManager 싱글톤 인스턴스 가져오기 
	GlobalEventManager& eventManager = GlobalEventManager::Get();

	// UI 시스템 생성  //지우지 마세요
	auto UISystem = std::make_shared<UIEventManagerSystem>();

	eventManager.Subscribe(GSystemContext);
	eventManager.Subscribe(UISystem);


	auto TurnEventManager = std::make_shared<UTurnEventManager>();
	eventManager.Subscribe(TurnEventManager);

	shared_ptr<Player> player = make_shared<Player>("Player");
	player->Initialize();

	shared_ptr<Monster> monster = make_shared<Monster>();
	monster->Initialize();

	//타겟 설정합니다
	monster->combatManager->SetTarget(player.get());
	player->combatManager->SetTarget(monster.get());

	std::vector<Character*> battleCharacters;
	battleCharacters.push_back(player.get());
	battleCharacters.push_back(monster.get());


	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(BasicAttack), player.get());
	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(Sanctification), player.get());
	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(PoisonedBlade), player.get());
	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(PoisonFog), player.get());


	SkillManager::GetInstance().AddSelectSkillToCharacter(typeid(BasicAttack), monster.get());



	TurnEventManager->BeginTurn();


	//player->combatManager->Attack();
	//monster->combatManager->Attack();

	//player->skillManager->UseSkill(SkillType::ACTIVE, "신성화");
	//player->skillManager->UseSkill(SkillType::ACTIVE, "기본 공격");
	player->skillManager->UseSkill(SkillType::ACTIVE, "독이 묻은 칼");
	player->skillManager->UseSkill(SkillType::ACTIVE, "독 안개");

	monster->skillManager->UseSkill(SkillType::ACTIVE, "기본 공격");


	TurnEventManager->EndTurn(battleCharacters);

	CharacterUtility::PrintStatus(player.get());
	CharacterUtility::PrintStatus(monster.get());

#endif // !DEBUG_TEST

}
