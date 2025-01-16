#pragma once

#include "IEventTypes.h"
#include <string>

using namespace std;



class IDisplayMenuEvent : public IEvent
{
public:
	std::string title;
	std::vector<string> options;
	std::string inputText;

	IDisplayMenuEvent() {}
	IDisplayMenuEvent(const std::string& _title, const std::vector<string>& _options, const std::string& _inputText)
		: title(_title), options(_options), inputText(_inputText)
	{
	}
};

class IWrongInputEvent : public IEvent
{
public:
	IWrongInputEvent()
	{
	}
};