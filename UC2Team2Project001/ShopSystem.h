#pragma once
#include "GameSystem.h"

class ShopSystem : public GameSystem
{
public:
	ShopSystem() {}
	virtual ~ShopSystem() {};
	virtual void EnterSystem();
	virtual void ExitSystem();
	virtual void Update(); 
	virtual void EnterSystem() override;
private:
	void MainMenu();
	void BuyMenu();
	void SellMenu();
	void GetRandomItems();

	/*vector<shared_ptr<Item>> itemList;*/
};

extern shared_ptr<ShopSystem> GShopSystem;
