#pragma once
#include "Potion.h"
class HealthPotion : public Potion
{
public:
    HealthPotion();
    void use(Character& Target) override;
};
