#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "IStrategy.h"

using json = nlohmann::json;

class StrategyFactory 
{
public:
	static std::shared_ptr<IAttackStrategy> CreateAttackStrategy(const json& strategyData);

	static std::shared_ptr<IDefenseStrategy> CreateDefenseStrategy(const json& strategyData);
};