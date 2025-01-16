#pragma once
#include <iostream> 
#include <vector>
#include <random>
#include <unordered_map>
#include <memory> // 스마트 포인터
#include <sstream>

using namespace std;





// 캐릭터 이름 문자열 입력 및 검증 코드용 헤더
#include <string>
#include <ctype.h>
#include <cctype>
#include <algorithm>
#include "CharacterUtility.h"


#include <chrono>
#include <thread>

#define CLEAR system("cls");  //콘솔창 클리어 함수

static void Delay(int _sec, int _milliSec = 0)
{
	std::this_thread::sleep_for(std::chrono::seconds(_sec) + std::chrono::microseconds(_milliSec));
}
