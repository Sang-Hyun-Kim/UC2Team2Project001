#include "pch.h"
#include "GameSystem.h"
#include "ItemManager.h"

// 게임 시스템 코드가 돌아갈 main 함수

int main()
{
	GLobbySystem->CreatePlayer();
	GLobbySystem->PlayerMove();
	GBattleSystem->EnterSystem();
}
