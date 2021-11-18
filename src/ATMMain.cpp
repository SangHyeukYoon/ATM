#include "ATMMain.h"
#include "ATMInterface.h"
#include "BankInterface.h"
#include "ATMMessage.h"
#include "BankMessage.h"
#include "Customer.h"

#include <string>
#include <vector>

void ATMMain::start()
{
    while(true)
    {
        // Insert Card
        std::string cardId;
        int password, bank;
        ATMMessage ret;

        password = ux->insertCard(cardId);

        if ((bank = checkCard(cardId, password)) == -1)
        {
            ux->insertCardRet(ATMMessage::UnknownCustommer);
            continue;
        }

        ux->insertCardRet(ATMMessage::Success);

        // Select account
        std::vector<Acount> accounts = getAccount(bank, cardId, password, ret);

        if (ret == ATMMessage::UnknownCustommer)
        {
            continue;
        }

        int account = ux->selectAccount(accounts);

        // check menu
        int menu = -1;
        int balance;

        while (menu != 4)
        {
            menu = ux->selectMenu();

            // check balance
            if (menu == 1)
            {
                balance = checkBalance(bank, cardId, password, account, ret);

                // Unknown error 
                if (balance == -1)
                {
                    continue;
                }

                ux->checkBalance(balance);
            }
            // deposit
            else if (menu == 2)
            {
                int amount = ux->deposit();
                balance = deposit(bank, cardId, password, amount, account, ret);
                ux->depositRet(ret, balance);
            }
            // withdraw
            else if (menu == 3)
            {
                int amount = ux->withdraw();
                balance = withdraw(bank, cardId, password, amount, account, ret);
                ux->withdrawRet(ret, balance);
            }
        }
    }
}

void ATMMain::addBank(BankInterface* bank)
{
    banks.push_back(bank);
}

int ATMMain::checkCard(const std::string& cardId, const int password)
{
    // find user through registered banks.
    for (auto it = banks.begin(); it < banks.end(); ++it)
    {
        if ((*it)->checkCard(cardId, password))
        {
            return (it - banks.begin());
        }
    }

    return -1;
}

std::vector<Acount> ATMMain::getAccount(const int bank, const std::string& cardId, const int password, ATMMessage& ret)
{
    // bank value validation
    if (bank < 0 || bank > banks.size())
    {
        ret = ATMMessage::UnknownCustommer;
        return std::vector<Acount>();
    }

    // get account
    std::vector<Acount> accounts = banks[bank]->getAccount(cardId, password);

    // if accounts are empty, something is wrong. 
    if (accounts.empty())
    {
        ret = ATMMessage::UnknownCustommer;
        return std::vector<Acount>();
    }

    ret = ATMMessage::Success;
    return accounts;
}

int ATMMain::checkBalance(const int bank, const std::string& cardId, const int password, const int account, ATMMessage& ret)
{
    // bank value validation
    if (bank < 0 || bank > banks.size())
    {
        ret = ATMMessage::UnknownCustommer;
        return -1;
    }

    int balance = banks[bank]->checkBalance(cardId, password, account);

    if (balance != -1)
    {
        ret = ATMMessage::Success;
        return balance;
    }

    ret = ATMMessage::UnknownCustommer;
    return -1;
}

int ATMMain::deposit(const int bank, const std::string& cardId, const int password, const int amount, const int account, ATMMessage& ret)
{
    // bank value validation
    if (bank < 0 || bank > banks.size())
    {
        ret = ATMMessage::UnknownCustommer;
        return -1;
    }

    // amount value validation
    if (amount < 0)
    {
        ret = ATMMessage::InvalidNumber;
        return -1;
    }

    BankMessage mes;
    int balance = banks[bank]->deposit(cardId, password, amount, account, mes);

    if (mes == BankMessage::Success)
    {
        ret = ATMMessage::Success;
        cache += amount;
        return balance;
    }

    ret = ATMMessage::UnknownCustommer;
    return -1;
}

int ATMMain::withdraw(const int bank, const std::string& cardId, const int password, const int amount, const int account, ATMMessage& ret)
{
    // bank value validation
    if (bank < 0 || bank > banks.size())
    {
        return -1;
    }

    // amount value validation
    if (amount < 0)
    {
        ret = ATMMessage::InvalidNumber;
        return -1;
    }

    // check ATM cache bin
    if (amount > cache)
    {
        ret = ATMMessage::LackCache;
        return -1;
    }

    BankMessage mes;
    int balance = banks[bank]->withdraw(cardId, password, amount, account, mes);

    if (mes == BankMessage::Success)
    {
        ret = ATMMessage::Success;
        cache -= amount;
        return balance;
    }
    // user's balance is less then amount
    else if (mes == BankMessage::LackBalance)
    {
        ret = ATMMessage::LackBalance;
        return balance;
    }

    ret = ATMMessage::UnknownCustommer;
    return -1;
}
