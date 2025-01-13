#pragma once
#include "GameSystem.h"

struct Item
{
	Item() {}
	Item(string name, string description, int cost) :name(name), description(description), cost(cost) {}

	string name;
	string description;
	int cost;
};

class ShopSystem : public GameSystem
{
public:
	ShopSystem() {}
	virtual ~ShopSystem() {};

	virtual void EnterSystem() override;
private:
	void MainMenu();
	void BuyMenu();
	void SellMenu();
	void GetRandomItems();

	vector<shared_ptr<Item>> itemList;
};

extern shared_ptr<ShopSystem> GShopSystem;
