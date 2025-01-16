#pragma once
#include "Potion.h"
class HealthPotion : public Potion
{
public:
    HealthPotion(int _id);
    bool use(Character* _target) override;
    shared_ptr<Item> clone() const override;

};
