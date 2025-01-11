#include "pch.h"
#include "GameSystem.h"

// 게임 시스템 코드가 돌아갈 main 함수

int main()
{
	// 랜덤 함수 시드 설정
	srand(time(NULL));

	GLobbySystem->CreatePlayer();
	GLobbySystem->PlayerMove();
	GBattleSystem->EnterSystem();
}
