#pragma once
#include "Potion.h"
class HealthPotion : public Potion
{
public:
    HealthPotion();
    void use(Character* _target) override;
    shared_ptr<Item> clone() const override;

};
