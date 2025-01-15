#pragma once
#include "Potion.h"
class HealthPotion : public Potion
{
public:
    HealthPotion();
    void use(Character* Target) override;
    shared_ptr<Item> clone() const override;

};
