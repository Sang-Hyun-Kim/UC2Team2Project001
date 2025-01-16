#pragma once
#include "EventManagerSystem.h"

class Item;

class URewardEventManagerSystem : public IEventManagerSystem
{
public:
	URewardEventManagerSystem() = default;
	~URewardEventManagerSystem() = default;

	void OnEvent(std::shared_ptr<IEvent> _event) override;

	struct Reward
	{
		int gold;
		int exp;
		shared_ptr<Item> item;
		vector<type_index> skillTypes;
	};
	
	void Initialize();

	Reward GetReward()
	{
		return reward; 
	}
private:
	Reward reward;
};

