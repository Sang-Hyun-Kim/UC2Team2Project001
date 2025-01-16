#pragma once

#include "Potion.h"
class ManaPotion : public Potion
{
public:
    ManaPotion(int _id);
    bool use(Character* _target) override;
    shared_ptr<Item> clone() const override;

};
