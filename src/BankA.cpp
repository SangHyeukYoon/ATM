#include "BankA.h"

#include <string>
#include <vector>
#include <exception>

void BankA::addCustomer(Customer customer)
{
    customers.push_back(customer);
}

bool BankA::checkCard(std::string& cardId, int password)
{
    if (bankId.compare(cardId.substr(0, 4)) != 0)
    {
        return false;
    }

    for (auto it = customers.begin(); it < customers.end(); ++it)
    {
        if (it->cardId.compare(cardId) == 0 && it->password == password)
        {
            return true;
        }
    }

    return false;
}

int BankA::checkBalance(std::string& cardId, int password)
{
    for (auto it = customers.begin(); it < customers.end(); ++it)
    {
        if (it->cardId.compare(cardId) == 0 && it->password == password)
        {
            return it->balance;
        }
    }

    return -1;
}

int BankA::deposit(std::string& cardId, int password, int amount, BankMessage& ret)
{
    for (auto it = customers.begin(); it < customers.end(); ++it)
    {
        if (it->cardId.compare(cardId) == 0 && it->password == password)
        {
            ret = BankMessage::Success;
            it->balance += amount;
            return it->balance;
        }
    }

    ret = BankMessage::UnknownCustomer;

    return -1;
}

int BankA::withdraw(std::string& cardId, int password, int amount, BankMessage& ret)
{
    for (auto it = customers.begin(); it < customers.end(); ++it)
    {
        if (it->cardId.compare(cardId) == 0 && it->password == password)
        {
            if (it->balance < amount)
            {
                ret = BankMessage::LackBalance;
                return it->balance;
            }

            ret = BankMessage::Success;
            it->balance -= amount;
            return it->balance;
        }
    }

    ret = BankMessage::UnknownCustomer;

    return -1;
}
