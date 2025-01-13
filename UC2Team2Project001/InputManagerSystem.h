#pragma once

#include "pch.h"
#include "InputValidatorTypes.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"

class InputManagerSystem //선택지를 입력할 때 사용할 클래스
{
public:

	template<typename InputType, typename... Validators> //InputValidator.h 에 정의
	static InputType GetInput(const string& title, const vector<string>& options, Validators... validators) //메뉴를 출력하고, 입력을 받은 다음, validator들도 검증 후 command 실행
	{
		auto displayEvent = make_shared<IDisplayMenuEvent>(title, options);
		auto wrongInputEvent = make_shared<IWrongInputEvent>();
		InputType input;
			
		ClearInput();

		while (true)
		{
			GlobalEventManager::Get().Notify(displayEvent);

			cin >> input;
			
			if (cin.fail())
			{
				ClearInput();
				GlobalEventManager::Get().Notify(wrongInputEvent);
				continue;
			}

			bool isValidate = true;

			for (const auto& validator : {validators...})
			{
				if (!validator.IsValidate(input))
				{
					isValidate = false;
					break;
				}
			}

			if (isValidate) break;
		}
		
		return input;
	}

private:

	static void ClearInput() //cin을 초기화
	{
		cin.clear();

		if (cin.rdbuf()->in_avail() > 0) // 버퍼에 읽을 수 있는 데이터가 있으면
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 버퍼에 있는 모든 입력을 무시
		};
	}
};