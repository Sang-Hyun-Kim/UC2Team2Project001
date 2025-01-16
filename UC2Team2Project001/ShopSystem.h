#pragma once
#include "GameSystem.h"

class Item;
class Skill;
class SystemContext;
class ShopSystem : public GameSystem
{
public:
	ShopSystem() = default;
	virtual ~ShopSystem() = default;

	virtual void EnterSystem() override;
	//virtual void Update() override;

	inline SystemType GetSystemType() override
	{
		return SystemType::SHOP;
	}
	void OnEvent(const std::shared_ptr<IEvent> _event) override;
	void MainMenu();
	void DisplayInventory();
	void BuyItemMenu();
	void BuySkillMenu();
	void SellMenu();
private:
	void GetRandomItemsAndSkills();

	vector<shared_ptr<Item>> itemList;
	vector<shared_ptr<Skill>> skillList;
};
