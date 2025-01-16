#pragma once

#include "pch.h"
#include "InputValidatorTypes.h"
#include "IInputEventTypes.h"
#include "GlobalEventManager.h"

class InputManagerSystem //선택지를 입력할 때 사용할 클래스
{
public:

	template<typename InputType, typename... Validators> //InputValidator.h 에 정의
	static InputType GetInput(const string& _title, const vector<string>& _options, Validators... _validators) //메뉴를 출력하고, 입력을 받은 다음, validator들도 검증 후 command 실행
	{
		auto displayEvent = make_shared<IDisplayMenuEvent>(_title, _options, "input🔽");
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
	
			// 가변 매개변수에 대해 올바르게 검증
			// C++17 폴드 표현식
			([&] {
				if (!_validators.IsValidate(input))
				{
					isValidate = false;
					Delay(0, 500);
				}
				}(), ...);
			if (isValidate) break;
		}
		
		return input;
	}

	template<typename... Validators> //InputValidator.h 에 정의
	static string GetInput(const string& _title, const vector<string>& _options, Validators... _validators) //메뉴를 출력하고, 입력을 받은 다음, validator들도 검증 후 command 실행
	{
		auto displayEvent = make_shared<IDisplayMenuEvent>(_title, _options, "input🔽");
		auto wrongInputEvent = make_shared<IWrongInputEvent>();
		string input;
		ClearInput();
	
		while (true)
		{
			GlobalEventManager::Get().Notify(displayEvent);
	
			getline(cin, input);
			
			if (cin.fail())
			{
				ClearInput();
				GlobalEventManager::Get().Notify(wrongInputEvent);
				continue;
			}
	
			bool isValidate = true;
	
			// 가변 매개변수에 대해 올바르게 검증
			// C++17 폴드 표현식
			([&] {
				if (!_validators.IsValidate(input))
				{
					isValidate = false;
					PauseUntilEnter();
				}
				}(), ...);
			if (isValidate) break;
		}
	
		return input;
	}

	static void ClearInput() //cin을 초기화
	{
		cin.clear();

		if (cin.rdbuf()->in_avail() > 0) // 버퍼에 읽을 수 있는 데이터가 있으면
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 버퍼에 있는 모든 입력을 무시
		};
	}

	static void PauseUntilEnter()
	{
		if (cin.rdbuf()->in_avail() > 0) // 버퍼에 읽을 수 있는 데이터가 있으면
		{
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');  // 버퍼에 있는 모든 입력을 무시
		};

		auto event = make_shared<IPauseEnterEvent>();
		GlobalEventManager::Get().Notify(event);
		
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');  // 엔터를 누를 때까지 대기
	}
};