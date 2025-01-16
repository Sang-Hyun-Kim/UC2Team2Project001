#include "pch.h"
#include "ConsoleLayout.h"



#pragma region 더미 코드
//class RightBottomInputRegion
//{
//private:
//	int startX;
//	int startY;
//	int width;
//	int height;
//	HANDLE hConsole;
//
//public:
//	RightBottomInputRegion(int x, int y, int w, int h)
//		: startX(x), startY(y), width(w), height(h)
//	{
//		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	}
//
//	// (1) ClearScreen: 이 영역만 공백으로 지우기
//	void ClearScreen() const
//	{
//		for (int row = 0; row < height; ++row)
//		{
//			SetCursorPosition(0, row);
//			std::cout << std::string(width, ' ');
//		}
//	}
//
//	// (2) 항상 첫 라인( y=0 )에서 입력을 받는다
//	std::string GetUserInput(const std::string& prompt = "Input> ")
//	{
//		// (a) 이 영역을 싹 지우고
//		ClearScreen();
//
//		// (b) 커서를 (0,0)에 두고, 안내 문구 출력
//		SetCursorPosition(0, 0);
//		std::cout << prompt;
//
//		// (c) cin >> 로 입력 받기
//		std::string userCommand;
//		std::cin >> userCommand;
//
//		return userCommand;
//	}
//
//private:
//	// 이 클래스 내부에서만 쓰는 "영역 내 커서 이동" (startX, startY 기준)
//	void SetCursorPosition(int x, int y) const
//	{
//		COORD pos;
//		pos.X = static_cast<SHORT>(startX + x);
//		pos.Y = static_cast<SHORT>(startY + y);
//		SetConsoleCursorPosition(hConsole, pos);
//	}
//};

#pragma endregion
