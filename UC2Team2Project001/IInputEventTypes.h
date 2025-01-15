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
	IDisplayMenuEvent(const std::string& title, const std::vector<string>& options, const std::string& inputText) :title(title), options(options), inputText(inputText)
	{
	}
};

class IWrongInputEvent : public IEvent
{
public:
	IWrongInputEvent() {}
};