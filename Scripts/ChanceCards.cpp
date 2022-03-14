#include"GameCells.h"

bool ChanceCard1::method(Player& obj)
{
    cout << "ch1\n";
    obj.setPos(Vector2f(118, 118));
    obj.MoveToken(0, 0, Vector2f(0, 0));
    obj.incrementBalance(300);
    return false;
}

bool ChanceCard2::method(Player& obj)
{
    cout << "ch2\n";

    Vector2f destination(Operator->GetCells()[26]->getPos().x, 825.0f);
    if (Operator->GetCells()[11]->reachedCell(obj.getPos()) || Operator->GetCells()[21]->reachedCell(obj.getPos())) {
        obj.setPos(destination);
        obj.MoveToken(0, 0, Vector2f(0, 0));
    }
    if (Operator->GetCells()[34]->reachedCell(obj.getPos())) {
        obj.incrementBalance(500);
        obj.setPos(destination);
        obj.MoveToken(0, 0, Vector2f(0, 0));
    }
    Operator->GetCells()[26]->Method(obj);
    return false;
}

bool ChanceCard3::method(Player& obj)
{
    cout << "ch3\n";

    Vector2f destination1(825, Operator->GetCells()[12]->getPos().y);
    Vector2f destination2(Operator->GetCells()[25]->getPos().x,825.0f);
    Vector2f destination3(117, Operator->GetCells()[36]->getPos().y);

    int amount = 5 * amountOnDice;
    if (Operator->GetCells()[11]->reachedCell(obj.getPos())) {
        obj.setPos(destination1);
        obj.MoveToken(0, 0, Vector2f(0, 0));
        if (Operator->GetCells()[12]->getOwner() != "BANK") {
            if (obj.getBalance() >= amount) {
                obj.decrementBalance(amount);
                Operator->GetCells()[12]->getItemOwner()->incrementBalance(5 * amountOnDice);
            }
            else
            {
                if (obj.getNetWorth() >= amount) {
                    obj.setdebt(amount);
                }
                else
                {
                    obj.setStatus(1);
                    Operator->Bankrupcy(Operator->GetCells()[12]->getItemOwner(), &obj);
                }
            }
        }
    }

    if (Operator->GetCells()[21]->reachedCell(obj.getPos())) {
        obj.setPos(destination2);
        obj.MoveToken(0, 0, Vector2f(0, 0));
        if (Operator->GetCells()[25]->getOwner() != "BANK") {
            if (obj.getBalance() >= amount) {
                obj.decrementBalance(amount);
                Operator->GetCells()[25]->getItemOwner()->incrementBalance(5 * amountOnDice);
            }
            else
            {
                if (obj.getNetWorth() >= amount) {
                    obj.setdebt(amount);
                }
                else
                {
                    obj.setStatus(1);
                    Operator->Bankrupcy(Operator->GetCells()[25]->getItemOwner(), &obj);
                }
            }
        }
    }

    if (Operator->GetCells()[34]->reachedCell(obj.getPos())) {
        obj.setPos(destination3);
        obj.MoveToken(0, 0, Vector2f(0, 0));
        if (Operator->GetCells()[36]->getOwner() != "BANK") {
            if (obj.getBalance() >= amount) {
                obj.decrementBalance(amount);
                Operator->GetCells()[36]->getItemOwner()->incrementBalance(5 * amountOnDice);
            }
            else
            {
                if (obj.getNetWorth() >= amount) {
                    obj.setdebt(amount);
                }
                else
                {
                    obj.setStatus(1);
                    Operator->Bankrupcy(Operator->GetCells()[36]->getItemOwner(), &obj);
                }
            }
        }
    }

    return false;
}

bool ChanceCard4::method(Player& obj)
{
    cout << "ch4\n";

    Vector2f destination1(825, Operator->GetCells()[15]->getPos().y);
    Vector2f destination2(Operator->GetCells()[24]->getPos().x, 825.0f);
    Vector2f destination3(Operator->GetCells()[36]->getPos().x,118.0f);

    if (Operator->GetCells()[11]->reachedCell(obj.getPos())) {
        obj.setPos(destination1);
        obj.MoveToken(0, 0, Vector2f(0, 0));
        if (Operator->GetCells()[15]->getOwner() != "BANK") {
            if (obj.getBalance() >= 2 * Operator->GetCells()[15]->getItemrent()) {
                obj.decrementBalance(2 * Operator->GetCells()[15]->getItemrent());
                Operator->GetCells()[15]->getItemOwner()->incrementBalance(2 * Operator->GetCells()[15]->getItemrent());
            }
            else
            {
                if (obj.getNetWorth() >= 2 * Operator->GetCells()[15]->getItemrent()) {
                    obj.setdebt(2 * Operator->GetCells()[15]->getItemrent());
                }
                else
                {
                    obj.setStatus(1);
                    Operator->Bankrupcy(Operator->GetCells()[15]->getItemOwner(), &obj);
                }
            }
        }
    }

    if (Operator->GetCells()[21]->reachedCell(obj.getPos())) {
        obj.setPos(destination2);
        obj.MoveToken(0, 0, Vector2f(0, 0));
        if (Operator->GetCells()[24]->getOwner() != "BANK") {
            if (obj.getBalance() >= 2 * Operator->GetCells()[24]->getItemrent()) {
                obj.decrementBalance(2 * Operator->GetCells()[24]->getItemrent());
                Operator->GetCells()[24]->getItemOwner()->incrementBalance(2 * Operator->GetCells()[15]->getItemrent());
            }
            else
            {
                if (obj.getNetWorth() >= 2 * Operator->GetCells()[24]->getItemrent()) {
                    obj.setdebt(2 * Operator->GetCells()[24]->getItemrent());
                }
                else
                {
                    obj.setStatus(1);
                    Operator->Bankrupcy(Operator->GetCells()[24]->getItemOwner(), &obj);
                }
            }
        }
    }

    if (Operator->GetCells()[34]->reachedCell(obj.getPos())) {
        obj.setPos(destination3);
        obj.MoveToken(0, 0, Vector2f(0, 0));

        if (Operator->GetCells()[5]->getOwner() != "BANK") {
            if (obj.getBalance() >= 2 * Operator->GetCells()[5]->getItemrent()) {
                obj.decrementBalance(2 * Operator->GetCells()[5]->getItemrent());
                Operator->GetCells()[5]->getItemOwner()->incrementBalance(2 * Operator->GetCells()[15]->getItemrent());
            }
            else
            {
                if (obj.getNetWorth() >= 2 * Operator->GetCells()[5]->getItemrent()) {
                    obj.setdebt(2 * Operator->GetCells()[15]->getItemrent());
                }
                else
                {
                    obj.setStatus(1);
                    Operator->Bankrupcy(Operator->GetCells()[5]->getItemOwner(), &obj);
                }
            }
        }
    }

    return false;
}

bool ChanceCard5::method(Player& obj)
{
    cout << "ch5\n";

    Vector2f destination(825, Operator->GetCells()[16]->getPos().y);
    if (Operator->GetCells()[11]->reachedCell(obj.getPos())) {
        obj.setPos(destination);
        obj.MoveToken(0, 0, Vector2f(0, 0));

    }
    if (Operator->GetCells()[21]->reachedCell(obj.getPos()) || Operator->GetCells()[34]->reachedCell(obj.getPos())) {
        obj.setPos(destination);
        obj.MoveToken(0, 0, Vector2f(0, 0));
        obj.incrementBalance(300);
    }
    Operator->GetCells()[16]->Method(obj);

    return false;
}

bool ChanceCard6::method(Player& obj)
{
    cout << "ch6\n";
    obj.incrementBalance(100);
    return false;
}

bool ChanceCard8::method(Player& obj)
{
    cout << "ch8\n";
    Vector2f destination1(Operator->GetCells()[7]->getPos().y,118.0f);
    Vector2f destination2(824.0f,Operator->GetCells()[17]->getPos().y);
    Vector2f destination3(Operator->GetCells()[30]->getPos().x,825.0f);
    if (Operator->GetCells()[11]->reachedCell(obj.getPos())) {
        obj.setPos(destination1);
        obj.MoveToken(0, 0, Vector2f(0, 0));
        Operator->GetCells()[7]->Method(obj);
    }
    if (Operator->GetCells()[21]->reachedCell(obj.getPos())) {
        obj.setPos(destination2);
        obj.MoveToken(0, 0, Vector2f(0, 0));
        Operator->GetCells()[17]->Method(obj);
    }
    if (Operator->GetCells()[34]->reachedCell(obj.getPos())) {
        obj.setPos(destination3);
        obj.MoveToken(0, 0, Vector2f(0, 0));
        Operator->GetCells()[30]->Method(obj);
    }

    return false;
}

bool ChanceCard9::method(Player& obj)
{
    cout << "ch9\n";

    int amount = (obj.getHotelWealth() / 1000) * 100 + (obj.getHouseWealth() / 100) * 50;
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

bool ChanceCard10::method(Player& obj)
{
    cout << "ch10\n";

    int amount = 25;
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

bool ChanceCard11::method(Player& obj)
{
    cout << "ch11\n";
    int amount = Operator->getnop() * 25;
    if (obj.getBalance() >= amount) {
        for (int i = 0; i < Operator->getnop(); i++) {
            if (Operator->GetPlayers()[i]->getplayername() != obj.getplayername()) {
                obj.decrementBalance(25);
                Operator->GetPlayers()[i]->incrementBalance(25);
            }
        }
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

bool ChanceCard12::method(Player& obj)
{
    cout << "ch12\n";
    obj.incrementBalance(150);

    return false;
}

bool ChanceCard13::method(Player& obj)
{
    cout << "ch13\n";
    Vector2f destination(Operator->GetCells()[24]->getPos().x, 825.0f);
    if (Operator->GetCells()[11]->reachedCell(obj.getPos()) || Operator->GetCells()[21]->reachedCell(obj.getPos())) {
        obj.setPos(destination);
        obj.MoveToken(0, 0, Vector2f(0, 0));
    }
    if (Operator->GetCells()[34]->reachedCell(obj.getPos())) {
        obj.incrementBalance(500);
        obj.setPos(destination);
        obj.MoveToken(0, 0, Vector2f(0, 0));
    }
    return false;
}

bool ChanceCard14::method(Player& obj)
{
    cout << "ch14\n";
    Vector2f destination(825.0f, Operator->GetCells()[15]->getPos().y);
    if (Operator->GetCells()[11]->reachedCell(obj.getPos())) {
        obj.setPos(destination);
        obj.MoveToken(0, 0, Vector2f(0, 0));
    }
    if (Operator->GetCells()[21]->reachedCell(obj.getPos()) || Operator->GetCells()[34]->reachedCell(obj.getPos())) {
        obj.setPos(destination);
        obj.incrementBalance(500);
        obj.MoveToken(0, 0, Vector2f(0, 0));
    }
    Operator->GetCells()[15]->Method(obj);
    return false;
}

bool ChanceCard7::method(Player& obj)
{
    cout << "ch7\n";
    if (this->owner == nullptr) {
        this->setOwner(&obj);
        obj.setchJailCard(true);
    }
    return false;
}

void ChanceCard7::setOwner(Player* obj)
{
    owner = obj;
}
