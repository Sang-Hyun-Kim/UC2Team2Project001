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

	// 싱글톤 객체 획득 (140×50)
	
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

	auto& layout = ConsoleLayout::GetInstance();

	// 4등분 라인
	layout.DrawFourSplit();

	// 좌상에 한 줄 추가
	layout.AppendLine(ConsoleRegionType::LeftTop, "[좌상] Hello World");
	// 좌하에 한 줄 추가
	layout.AppendLine(ConsoleRegionType::LeftBottom, "[좌하] 전투 로그 시작");
	// 우상에 한 줄 추가
	layout.AppendLine(ConsoleRegionType::RightTop, "[우상] 몬스터 정보");
	// 우하에 한 줄 추가
	layout.AppendLine(ConsoleRegionType::RightBottom, "[우하] 시스템 메세지");

	std::cin.get();

	// 좌상 0번 줄 수정
	layout.UpdateLine(ConsoleRegionType::LeftTop, 0, "[좌상] 업데이트된 텍스트");
	// 우상 0번 줄 삭제
	layout.RemoveLine(ConsoleRegionType::RightTop, 0);



	std::cin.get();

	// 우하단 ClearAll
	layout.SelectClear(ConsoleRegionType::RightBottom);

	// 1) 기본 AppendLine (흰색, 검정)
	layout.AppendLine(ConsoleRegionType::LeftTop, "기본색 텍스트(색상 안 지정)");

	// 2) 색상 지정 AppendLine (연두색 LightGreen=10, 배경=Black=0)
	layout.AppendLine(ConsoleRegionType::LeftTop, "이 라인은 녹색!",
		true,
		ConsoleColor::LightGreen,
		ConsoleColor::Black);

	// 3) 또 다른 라인(빨강, 검정)
	layout.AppendLine(ConsoleRegionType::RightTop, "이 라인은 빨강!",
		true,
		ConsoleColor::LightRed,
		ConsoleColor::Black);

	// 4) 다시 기본색
	layout.AppendLine(ConsoleRegionType::RightBottom, "다시 기본색(매개변수 생략)");



	std::cin.get();
	return 0;


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
