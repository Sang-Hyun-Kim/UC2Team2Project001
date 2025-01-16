#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 콘솔에서 사용할 색상을 관리하기 위한 열거형입니다.
// 필요에 따라 색상 값을 추가하거나 수정할 수 있습니다.
enum class ConsoleColor : WORD
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class ConsoleColorManager
{
public:
	// 싱글톤 인스턴스를 반환합니다.
	static ConsoleColorManager& GetInstance()
	{
		static ConsoleColorManager instance;
		return instance;
	}

	// 콘솔 텍스트 및 배경 색상을 설정하는 함수입니다.
	// foreground : 텍스트(글자) 색상
	// background : 배경 색상
	void SetColor(ConsoleColor foreground, ConsoleColor background)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConsole == INVALID_HANDLE_VALUE)
		{
			std::cerr << "[ConsoleColorManager] 콘솔 핸들을 가져오지 못했습니다.\n";
			return;
		}

		// WinAPI의 SetConsoleTextAttribute:
		// 배경색은 상위 4비트, 전경색은 하위 4비트를 사용합니다.
		// 예) (background << 4) | foreground
		WORD colorAttribute = (static_cast<WORD>(background) << 4)
			| static_cast<WORD>(foreground);

		if (!SetConsoleTextAttribute(hConsole, colorAttribute))
		{
			std::cerr << "[ConsoleColorManager] 콘솔 색상을 설정하지 못했습니다.\n";
		}
	}

	void SetDefaultColor()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConsole == INVALID_HANDLE_VALUE)
		{
			std::cerr << "[ConsoleColorManager] 콘솔 핸들을 가져오지 못했습니다.\n";
			return;
		}

		// WinAPI의 SetConsoleTextAttribute:
		// 배경색은 상위 4비트, 전경색은 하위 4비트를 사용합니다.
		// 예) (background << 4) | foreground
		WORD colorAttribute = (static_cast<WORD>(ConsoleColor::Black) << 4)
			| static_cast<WORD>(ConsoleColor::White);

		if (!SetConsoleTextAttribute(hConsole, colorAttribute))
		{
			std::cerr << "[ConsoleColorManager] 콘솔 색상을 설정하지 못했습니다.\n";
		}
	}

private:
	// 생성자를 private으로 만들어 외부에서 인스턴스를 생성하지 못하도록 합니다.
	ConsoleColorManager() = default;
	~ConsoleColorManager() = default;

	// 복사나 대입을 방지하기 위해 삭제합니다.
	ConsoleColorManager(const ConsoleColorManager&) = delete;
	ConsoleColorManager& operator=(const ConsoleColorManager&) = delete;
};



//--------------------------------------
// (1) 열거형으로 콘솔 영역 구분
//--------------------------------------
enum class ConsoleRegionType
{
	LeftTop,
	LeftBottom,
	RightTop,
	RightBottom
};


//-----------------------------------------------------
// (1) 'AppendableRegion' : 줄 단위 로그를 관리하는 영역
//-----------------------------------------------------
class AppendableRegion
{
private:
	int startX;     // 영역 시작 X (절대 콘솔 좌표)
	int startY;     // 영역 시작 Y (절대 콘솔 좌표)
	int width;      // 영역 너비
	int height;     // 영역 높이
	HANDLE hConsole;

	// 이미 출력된 로그/라인들
	std::vector<std::string> lines;

public:
	AppendableRegion(int x, int y, int w, int h) : startX(x), startY(y), width(w), height(h)
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	// 1) 영역 전체 Clear (공백으로 채움)
	void ClearScreen() const
	{
		for (int row = 0; row < height; ++row)
		{
			SetCursorPosition(0, row);
			std::cout << std::string(width, ' ');
		}
	}

	// (A) 현재 "몇 줄"을 저장(출력)하고 있는지 확인
	int GetLineCount() const
	{
		return static_cast<int>(lines.size());
	}

	// (B) "현재 라인 수"를 기반으로 다음 줄 위치(=새로 텍스트 출력할 줄)를 구함
	//     영역 높이를 넘어가면 마지막 줄로 처리(간단화)
	int GetNextEmptyLineIndex() const
	{
		int lineCount = GetLineCount();
		if (lineCount >= height)
		{
			// 이미 영역 높이 이상이면, 마지막 줄( height - 1 )로 제한
			return height - 1;
		}
		return lineCount;  // 예: lines.size() == 3 이면, 다음 빈줄 = 3번째 줄
	}

	// (C) 실제로 “다음 빈 줄”에 커서를 이동하는 함수
	void SetCursorToNextEmptyLine()
	{
		int nextLine = GetNextEmptyLineIndex();
		SetCursorPosition(0, nextLine);
	}


	// 2) 새 줄을 추가(Append)
	//    - 맨 아래에 붙임
	void AppendLine(const std::string& newLine, bool useColor = false, ConsoleColor fg = ConsoleColor::White, ConsoleColor bg = ConsoleColor::Black)
	{
		if (useColor)
		{
			// 1) 원하는 색 적용
			ConsoleColorManager::GetInstance().SetColor(fg, bg);
		}

		// 2) 라인 추가 + Redraw
		lines.push_back(newLine);
		Redraw();

		// 3) 기본색 복귀
		if (useColor)
		{
			ConsoleColorManager::GetInstance().SetDefaultColor();
		}
	}

	// 3) 특정 줄 삭제
	//    - 범위 체크 후 제거
	void RemoveLine(int index)
	{
		if (index >= 0 && index < (int)lines.size())
		{
			lines.erase(lines.begin() + index);
			Redraw();
		}
	}

	// 4) 특정 줄 내용 수정
	//    - 범위 체크 후 내용 교체
	void UpdateLine(int index, const std::string& newLine, bool useColor = false, ConsoleColor fg = ConsoleColor::White, ConsoleColor bg = ConsoleColor::Black)
	{
		if (index < 0 || index >= (int)lines.size())
			return;

		if (useColor)
		{
			// 1) 원하는 색 적용
			ConsoleColorManager::GetInstance().SetColor(fg, bg);
		}

		lines[index] = newLine;
		Redraw();

		// 3) 기본색 복귀
		if (useColor)
		{
			ConsoleColorManager::GetInstance().SetDefaultColor();
		}
	}

	// 5) 모든 로그 삭제
	void ClearAll()
	{
		lines.clear();
		Redraw();
	}

	// 6) 영역 다시 그리기
	//    - Clear -> lines 내용을 위에서부터 한 줄씩 출력
	//    - 영역 높이보다 많으면 그 뒤는 생략 (스크롤 미구현)
	void Redraw()
	{
		ClearScreen();

		int row = 0;
		for (const auto& txt : lines)
		{
			if (row >= height) break;  // 영역을 벗어나면 출력 중단
			Print(0, row, txt);
			row++;
		}
	}

	// 7) 즉시 원하는 좌표에 출력 (lines와 상관없이)
	//    - 필요하다면 공개 메서드로 써도 되고, private로 둬도 됩니다.
	void Print(int x, int y, const std::string& text) const
	{
		if (x < 0 || y < 0 || x >= width || y >= height) return;
		SetCursorPosition(x, y);
		std::cout << text;
	}

private:
	// 콘솔 커서 이동(영역 상대 좌표)
	void SetCursorPosition(int x, int y) const
	{
		COORD pos;
		pos.X = (SHORT)(startX + x);
		pos.Y = (SHORT)(startY + y);
		SetConsoleCursorPosition(hConsole, pos);
	}

private:
	void SetStartCursorPosition()
	{
		COORD pos;
		pos.X = (SHORT)(startX);
		pos.Y = (SHORT)(startY);
		SetConsoleCursorPosition(hConsole, pos);
	}
public:
	int GetStartX() { return startX; }
	int GetStartY() { return startY; }
};


//-----------------------------------------------------
// (2) 콘솔 전체 레이아웃 관리 (크기, 4등분 라인 등)
//-----------------------------------------------------
class ConsoleLayout
{
private:
	HANDLE hConsole;
	int consoleWidth;
	int consoleHeight;

	// 싱글톤 인스턴스
	static ConsoleLayout* s_instance;

	// 4개 영역
	std::shared_ptr<AppendableRegion> leftTop;
	std::shared_ptr<AppendableRegion> leftBottom;
	std::shared_ptr<AppendableRegion> rightTop;
	std::shared_ptr<AppendableRegion> rightBottom;

private:
	ConsoleLayout() : consoleWidth(160), consoleHeight(40)
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		InitializeConsoleSize(consoleWidth, consoleHeight);
		system("cls"); // 콘솔 초기화

		// 4개 영역 생성
		int halfW = consoleWidth / 2;
		int halfH = consoleHeight / 2;

		leftTop = std::make_shared<AppendableRegion>(0, 0, halfW, halfH);
		leftBottom = std::make_shared<AppendableRegion>(0, halfH, halfW, halfH);
		rightTop = std::make_shared<AppendableRegion>(halfW, 0, halfW, halfH);
		rightBottom = std::make_shared<AppendableRegion>(halfW, halfH, halfW, halfH);
	}

	ConsoleLayout(int width, int height) : consoleWidth(width), consoleHeight(height)
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		InitializeConsoleSize(consoleWidth, consoleHeight);
		system("cls"); // 콘솔 초기화

		// 4개 영역 생성
		int halfW = consoleWidth / 2;
		int halfH = consoleHeight / 2;

		leftTop = std::make_shared<AppendableRegion>(0, 0, halfW, halfH);
		leftBottom = std::make_shared<AppendableRegion>(0, halfH, halfW, halfH);
		rightTop = std::make_shared<AppendableRegion>(halfW, 0, halfW, halfH);
		rightBottom = std::make_shared<AppendableRegion>(halfW, halfH, halfW, halfH);
	}

public:
	// 싱글톤 전역 접근 함수
	//  - 이미 인스턴스가 있으면 재사용, 없으면 (140,50)로 생성
	static ConsoleLayout& GetInstance()
	{
		static ConsoleLayout instance = ConsoleLayout(160, 40);
		return instance;
	}

	// 소멸자
	~ConsoleLayout()
	{
		// 필요시 리소스 해제
	}


	// Windows 콘솔 창을 cols=xxx, lines=yyy로 강제 설정
	// 그 뒤 WinAPI로도 버퍼,창 크기를 맞춤
	void InitializeConsoleSize(int width, int height)
	{
		// 1) mode con 명령어
		{
			char cmd[64];
			sprintf_s(cmd, "mode con cols=%d lines=%d", width, height);
			system(cmd);
		}

		// 2) WinAPI 버퍼 크기 설정
		COORD bufferSize;
		bufferSize.X = (SHORT)width;
		bufferSize.Y = (SHORT)height;
		SetConsoleScreenBufferSize(hConsole, bufferSize);

		// 3) WinAPI 창 크기 설정
		SMALL_RECT windowSize;
		windowSize.Left = 0;
		windowSize.Top = 0;
		windowSize.Right = (SHORT)(width - 1);
		windowSize.Bottom = (SHORT)(height - 1);
		SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
	}

	// 화면을 4등분하는 구분선(가운데 가로/세로줄) 그리기
	void DrawFourSplit()
	{
		int midX = consoleWidth / 2;
		int midY = consoleHeight / 2;

		// 가로줄
		for (int x = 0; x < consoleWidth; x++)
		{
			SetCursorPosAbsolute(x, midY);
			std::cout << "-";
		}

		// 세로줄
		for (int y = 0; y < consoleHeight; y++)
		{
			SetCursorPosAbsolute(midX, y);
			std::cout << "|";
		}
	}

	//-------------------------------------------------
	//  (A) 좌상,좌하,우상 각 영역에 AppendLine 시,
	//      우하단 SetCursorToNextEmptyLine() 자동 호출
	//-------------------------------------------------

	// 한 줄 추가
	void AppendLine(ConsoleRegionType region, const std::string& text, bool useColor = false, ConsoleColor fg = ConsoleColor::White, ConsoleColor bg = ConsoleColor::Black)
	{
		auto regPtr = GetRegionPtr(region);
		if (regPtr)
		{
			regPtr->AppendLine(text, useColor, fg, bg);

			rightBottom->SetCursorToNextEmptyLine();
		}
	}

	// 특정 줄 수정
	void UpdateLine(ConsoleRegionType region, int index, const std::string& newLine, bool useColor = false, ConsoleColor fg = ConsoleColor::White, ConsoleColor bg = ConsoleColor::Black)
	{
		auto regPtr = GetRegionPtr(region);
		if (regPtr)
		{
			regPtr->UpdateLine(index, newLine, useColor, fg, bg);

			// 좌상, 좌하, 우상 업데이트 후에도 우하 커서 이동
			if (region != ConsoleRegionType::RightBottom)
			{
				rightBottom->SetCursorToNextEmptyLine();
			}
		}
	}

	// 특정 줄 삭제
	void RemoveLine(ConsoleRegionType region, int index)
	{
		auto regPtr = GetRegionPtr(region);
		if (regPtr)
		{
			regPtr->RemoveLine(index);

			if (region != ConsoleRegionType::RightBottom)
			{
				rightBottom->SetCursorToNextEmptyLine();
			}
		}
	}

	// 전체 삭제
	void SelectClear(ConsoleRegionType region)
	{
		auto regPtr = GetRegionPtr(region);
		if (regPtr)
		{
			regPtr->ClearAll();

			if (region != ConsoleRegionType::RightBottom)
			{
				rightBottom->SetCursorToNextEmptyLine();
			}
		}
	}

	void AllClear()
	{
		leftTop->ClearAll();
		leftBottom->ClearAll();
		rightTop->ClearAll();
		rightBottom->ClearAll();
	}


	std::shared_ptr<AppendableRegion> GetLeftTop() { return leftTop; }
	std::shared_ptr<AppendableRegion> GetLeftBottom() { return leftBottom; }
	std::shared_ptr<AppendableRegion> GetRightTop() { return rightTop; }
	std::shared_ptr<AppendableRegion> GetRightBottom() { return rightBottom; }

private:
	// (d) 내부적으로 열거형에 맞게 영역 포인터 반환
	std::shared_ptr<AppendableRegion> GetRegionPtr(ConsoleRegionType region)
	{
		switch (region)
		{
		case ConsoleRegionType::LeftTop:
			return leftTop;
		case ConsoleRegionType::LeftBottom:
			return leftBottom;
		case ConsoleRegionType::RightTop:
			return rightTop;
		case ConsoleRegionType::RightBottom:
			return rightBottom;
		default:
			return nullptr;
		}
	}

	// 콘솔의 '절대좌표'로 커서 이동
	void SetCursorPosAbsolute(int x, int y)
	{
		COORD pos;
		pos.X = (SHORT)x;
		pos.Y = (SHORT)y;
		SetConsoleCursorPosition(hConsole, pos);
	}
};



#pragma region 예시 코드
// 싱글톤 객체 획득 (140×50)
//auto& layout = ConsoleLayout::GetInstance(180, 50);
//
//// 4등분 라인
//layout.DrawFourSplit();
//
//// 좌상에 한 줄 추가
//layout.AppendLine(ConsoleRegionType::LeftTop, "[좌상] Hello World");
//// 좌하에 한 줄 추가
//layout.AppendLine(ConsoleRegionType::LeftBottom, "[좌하] 전투 로그 시작");
//// 우상에 한 줄 추가
//layout.AppendLine(ConsoleRegionType::RightTop, "[우상] 몬스터 정보");
//// 우하에 한 줄 추가
//layout.AppendLine(ConsoleRegionType::RightBottom, "[우하] 시스템 메세지");
//
//
//std::cin.get();
//
//// 좌상 0번 줄 수정
//layout.UpdateLine(ConsoleRegionType::LeftTop, 0, "[좌상] 업데이트된 텍스트");
//// 우상 0번 줄 삭제
//layout.RemoveLine(ConsoleRegionType::RightTop, 0);
//
//
//
//std::cin.get();
//
//// 우하단 ClearAll
//layout.SelectClear(ConsoleRegionType::RightBottom);
//
//// 1) 기본 AppendLine (흰색, 검정)
//layout.AppendLine(ConsoleRegionType::LeftTop, "기본색 텍스트(색상 안 지정)");
//
//// 2) 색상 지정 AppendLine (연두색 LightGreen=10, 배경=Black=0)
//layout.AppendLine(ConsoleRegionType::LeftTop, "이 라인은 녹색!",
//	true,
//	ConsoleColor::LightGreen,
//	ConsoleColor::Black);
//
//// 3) 또 다른 라인(빨강, 검정)
//layout.AppendLine(ConsoleRegionType::RightTop, "이 라인은 빨강!",
//	true,
//	ConsoleColor::LightRed,
//	ConsoleColor::Black);
//
//// 4) 다시 기본색
//layout.AppendLine(ConsoleRegionType::RightBottom, "다시 기본색(매개변수 생략)");
//
//
//
//std::cin.get();
//return 0;
#pragma endregion 예시 코드