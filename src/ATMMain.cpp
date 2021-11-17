#include "ATMMain.h"
#include "ATMInterface.h"
#include "BankInterface.h"
#include "ATMMessage.h"
#include "BankMessage.h"

#include <string>
#include <vector>

void ATMMain::start()
{
    while(true)
    {
        // Insert Card
        std::string cardId;
        int password, bank;

        password = ux->insertCard(cardId);

        if ((bank = checkCard(cardId, password)) == -1)
        {
            ux->insertCardRet(ATMMessage::UnknownCustommer);
            continue;
        }

        ux->insertCardRet(ATMMessage::Success);

        // check menu
        int menu = -1;
        int balance;
        ATMMessage ret;

        while (menu != 4)
        {
            menu = ux->selectMenu();

            if (menu == 1)
            {
                balance = checkBalance(bank, cardId, password, ret);

                // Unknown error 
                if (balance == -1)
                {
                    continue;
                }

                ux->checkBalance(balance);
            }
            else if (menu == 2)
            {
                int amount = ux->deposit();
                balance = deposit(bank, cardId, password, amount, ret);
                ux->depositRet(ret, balance);
            }
            else if (menu == 3)
            {
                int amount = ux->withdraw();
                balance = withdraw(bank, cardId, password, amount, ret);
                ux->withdrawRet(ret, balance);
            }
        }
    }
}

void ATMMain::addBank(BankInterface* bank)
{
    banks.push_back(bank);
}

int ATMMain::checkCard(std::string& cardId, int password)
{
    for (auto it = banks.begin(); it < banks.end(); ++it)
    {
        if ((*it)->checkCard(cardId, password))
        {
            return (it - banks.begin());
        }
    }

    return -1;
}

int ATMMain::checkBalance(int bank, std::string& cardId, int password, ATMMessage& ret)
{
    if (bank < 0 || bank > banks.size())
    {
        ret = ATMMessage::UnknownCustommer;
        return -1;
    }

    ret = ATMMessage::Success;
    return banks[bank]->checkBalance(cardId, password);
}

int ATMMain::deposit(int bank, std::string& cardId, int password, int amount, ATMMessage& ret)
{
    if (bank < 0 || bank > banks.size())
    {
        ret = ATMMessage::UnknownCustommer;
        return -1;
    }

    if (amount < 0)
    {
        ret = ATMMessage::InvalidNumber;
        return -1;
    }

    BankMessage mes;
    int balance = banks[bank]->deposit(cardId, password, amount, mes);

    if (mes == BankMessage::Success)
    {
        ret = ATMMessage::Success;
        cache += amount;
        return balance;
    }

    ret = ATMMessage::UnknownCustommer;
    return -1;
}

int ATMMain::withdraw(int bank, std::string& cardId, int password, int amount, ATMMessage& ret)
{
    if (bank < 0 || bank > banks.size())
    {
        return -1;
    }

    if (amount < 0)
    {
        ret = ATMMessage::InvalidNumber;
        return -1;
    }

    if (amount > cache)
    {
        ret = ATMMessage::LackCache;
        return -1;
    }

    BankMessage mes;
    int balance = banks[bank]->withdraw(cardId, password, amount, mes);

    if (mes == BankMessage::Success)
    {
        ret = ATMMessage::Success;
        cache -= amount;
        return balance;
    }
    else if (mes == BankMessage::LackBalance)
    {
        ret = ATMMessage::LackBalance;
        return balance;
    }

    ret = ATMMessage::UnknownCustommer;
    return -1;
}
