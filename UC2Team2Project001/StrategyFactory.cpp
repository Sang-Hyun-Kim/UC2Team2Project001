#include "pch.h"
#include "StrategyFactory.h"




std::shared_ptr<IAttackStrategy> StrategyFactory::CreateAttackStrategy(const json& _strategyData) 
{
	std::string type = _strategyData.at("Type");
	if (type == "BasicAttack") 
	{
		return std::make_shared<BasicAttackStrategy>();
	}
	throw std::invalid_argument("알 수 없는 공격 전략 유형: " + type);
}

std::shared_ptr<IDefenseStrategy> StrategyFactory::CreateDefenseStrategy(const json& _strategyData) 
{
	std::string type = _strategyData.at("Type");
	if (type == "BlockDefense") 
	{
		return std::make_shared<BlockDefenseStrategy>();
	}
	throw std::invalid_argument("알 수 없는 방어 전략 유형: " + type);
}
