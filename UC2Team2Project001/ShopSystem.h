#pragma once
#include "GameSystem.h"

class Item;
class SystemContext;
class ShopSystem : public GameSystem
{
	friend class SystemContext;

	enum ShopState
	{
		MAIN = 0,
		INVENTORY = 1,
		BUY = 2,
		SELL = 3,
		EXIT = 4
	};

	ShopSystem() 
	{
	}
	virtual ~ShopSystem() 
	{
	}
public:

	virtual void EnterSystem() override;
	//virtual void Update() override;

	inline SystemType GetSystemType() override { return SystemType::SHOP; }
	void OnEvent(const std::shared_ptr<IEvent> ev) override;
	void MainMenu();
	void DisplayInventory();
	void BuyMenu();
	void SellMenu();
private:
	void GetRandomItems();

	vector<shared_ptr<Item>> itemList;

};
