//#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>
//#include <iostream>

//// 콘솔에서 사용할 색상을 관리하기 위한 열거형입니다.
//// 필요에 따라 색상 값을 추가하거나 수정할 수 있습니다.
//enum class ConsoleColor : WORD
//{
//	Black = 0,
//	Blue = 1,
//	Green = 2,
//	Cyan = 3,
//	Red = 4,
//	Magenta = 5,
//	Brown = 6,
//	LightGray = 7,
//	DarkGray = 8,
//	LightBlue = 9,
//	LightGreen = 10,
//	LightCyan = 11,
//	LightRed = 12,
//	LightMagenta = 13,
//	Yellow = 14,
//	White = 15
//};
//
//class ConsoleColorManager
//{
//public:
//	// 싱글톤 인스턴스를 반환합니다.
//	static ConsoleColorManager& GetInstance()
//	{
//		static ConsoleColorManager instance;
//		return instance;
//	}
//
//	// 콘솔 텍스트 및 배경 색상을 설정하는 함수입니다.
//	// foreground : 텍스트(글자) 색상
//	// background : 배경 색상
//	void SetColor(ConsoleColor foreground, ConsoleColor background)
//	{
//		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//		if (hConsole == INVALID_HANDLE_VALUE)
//		{
//			std::cerr << "[ConsoleColorManager] 콘솔 핸들을 가져오지 못했습니다.\n";
//			return;
//		}
//
//		// WinAPI의 SetConsoleTextAttribute:
//		// 배경색은 상위 4비트, 전경색은 하위 4비트를 사용합니다.
//		// 예) (background << 4) | foreground
//		WORD colorAttribute = (static_cast<WORD>(background) << 4)
//			| static_cast<WORD>(foreground);
//
//		if (!SetConsoleTextAttribute(hConsole, colorAttribute))
//		{
//			std::cerr << "[ConsoleColorManager] 콘솔 색상을 설정하지 못했습니다.\n";
//		}
//	}
//
//	void SetDefaultColor()
//	{
//		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//		if (hConsole == INVALID_HANDLE_VALUE)
//		{
//			std::cerr << "[ConsoleColorManager] 콘솔 핸들을 가져오지 못했습니다.\n";
//			return;
//		}
//
//		// WinAPI의 SetConsoleTextAttribute:
//		// 배경색은 상위 4비트, 전경색은 하위 4비트를 사용합니다.
//		// 예) (background << 4) | foreground
//		WORD colorAttribute = (static_cast<WORD>(ConsoleColor::Black) << 4)
//			| static_cast<WORD>(ConsoleColor::White);
//
//		if (!SetConsoleTextAttribute(hConsole, colorAttribute))
//		{
//			std::cerr << "[ConsoleColorManager] 콘솔 색상을 설정하지 못했습니다.\n";
//		}
//	}
//
//private:
//	// 생성자를 private으로 만들어 외부에서 인스턴스를 생성하지 못하도록 합니다.
//	ConsoleColorManager() = default;
//	~ConsoleColorManager() = default;
//
//	// 복사나 대입을 방지하기 위해 삭제합니다.
//	ConsoleColorManager(const ConsoleColorManager&) = delete;
//	ConsoleColorManager& operator=(const ConsoleColorManager&) = delete;
//};
//

//#define SAMPLE_TEST 1
#ifdef SAMPLE_TEST // SAMPLE_TEST이 정의되어 있을 때만 컴파일

std::cout << "프로그램 시작\n";

// 싱글톤을 통해 콘솔 글자색: 녹색, 배경색: 검정색으로 설정
ConsoleColorManager::GetInstance().SetColor(ConsoleColor::Green, ConsoleColor::Black);
std::cout << "녹색 글자, 검정 배경 텍스트입니다.\n";

// 콘솔 글자색: 흰색, 배경색: 파란색으로 설정
ConsoleColorManager::GetInstance().SetColor(ConsoleColor::White, ConsoleColor::Blue);
std::cout << "흰색 글자, 파란 배경 텍스트입니다.\n";

// 다시 기본(흰색 글자, 검정 배경)으로 복귀
ConsoleColorManager::GetInstance().SetColor(ConsoleColor::White, ConsoleColor::Black);
std::cout << "기본 색상으로 돌아왔습니다.\n";

#endif


