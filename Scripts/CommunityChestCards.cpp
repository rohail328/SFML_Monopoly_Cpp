#include"GameCells.h"

bool ChestCard1::method(Player& obj)
{
    obj.setPos(Vector2f(118.0f, 118.0f));
    obj.incrementBalance(400);
    return false;
}

bool ChestCard2::method(Player& obj)
{

    obj.incrementBalance(200);
    return false;
}

bool ChestCard3::method(Player& obj)
{
    int amount = 200;
    if (obj.getBalance() >= amount) {
        obj.decrementBalance(amount);
    }
    else
    {
        if (obj.getNetWorth() >= amount) {
            obj.setdebt(amount);
        }
        else
        {
            obj.setStatus(1);
            Operator->Bankrupcy(nullptr, &obj);
        }
    }

    return false;
}

bool ChestCard4::method(Player& obj)
{

    obj.incrementBalance(50);
    return false;
}

bool ChestCard5::method(Player& obj)
{
    if (this->owner == nullptr) {

        this->setOwner(&obj);
        obj.setcmJailCard(true);
    }
    return false;
}

void ChestCard5::setOwner(Player* obj)
{
    owner = obj;
}

bool ChestCard6::method(Player& obj)
{

    obj.incrementBalance(150);
    return false;
}

bool ChestCard7::method(Player& obj)
{

    obj.incrementBalance(200);
    return false;
}

bool ChestCard8::method(Player& obj)
{
    int amount = 100;
    if (obj.getBalance() >= amount) {
        obj.decrementBalance(amount);
    }
    else
    {
        if (obj.getNetWorth() >= amount) {
            obj.setdebt(amount);
        }
        else
        {
            obj.setStatus(1);
            Operator->Bankrupcy(nullptr, &obj);
        }
    }
    return false;
}

bool ChestCard9::method(Player& obj)
{

    obj.incrementBalance(200);
    return false;
}

bool ChestCard10::method(Player& obj)
{

    obj.incrementBalance(50);
    return false;
}

bool ChestCard11::method(Player& obj)
{
    int amount = (obj.getHotelWealth() / 1000) * 125 + (obj.getHouseWealth() / 100) * 50;
    if (obj.getBalance() >= amount) {
        obj.decrementBalance(amount);
    }
    else
    {
        if (obj.getNetWorth() >= amount) {
            obj.setdebt(amount);
        }
        else
        {
            obj.setStatus(1);
            Operator->Bankrupcy(nullptr, &obj);
        }
    }
    return false;
}

bool ChestCard12::method(Player& obj)
{

    obj.incrementBalance(300);
    return false;
}

bool ChestCard13::method(Player& obj)
{
    int amount = 50;
    if (obj.getBalance() >= amount) {
        obj.decrementBalance(amount);
    }
    else
    {
        if (obj.getNetWorth() >= amount) {
            obj.setdebt(amount);
        }
        else
        {
            obj.setStatus(1);
            Operator->Bankrupcy(nullptr, &obj);
        }
    }
    return false;
}

bool ChestCard14::method(Player& obj)
{
    int amount = 80;
    if (obj.getBalance() >= amount) {
        obj.decrementBalance(amount);
    }
    else
    {
        if (obj.getNetWorth() >= amount) {
            obj.setdebt(amount);
        }
        else
        {
            obj.setStatus(1);
            Operator->Bankrupcy(nullptr, &obj);
        }
    }
    return false;
}

bool ChestCard15::method(Player& obj)
{
    int amount = 50;
    if (obj.getBalance() >= amount) {
        obj.decrementBalance(amount);
    }
    else
    {
        if (obj.getNetWorth() >= amount) {
            obj.setdebt(amount);
        }
        else
        {
            obj.setStatus(1);
            Operator->Bankrupcy(nullptr, &obj);
        }
    }
    return false;
}
