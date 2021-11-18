#include "BankA.h"
#include "Customer.h"

#include <string>
#include <vector>
#include <exception>

void BankA::addCustomer(Customer customer)
{
    customers.push_back(customer);
}

bool BankA::checkCard(const std::string& cardId, const int password)
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

std::vector<Acount> BankA::getAccount(const std::string& cardId, const int password)
{
    for (auto it = customers.begin(); it < customers.end(); ++it)
    {
        if (it->cardId.compare(cardId) == 0 && it->password == password)
        {
            return it->accounts;
        }
    }

    return std::vector<Acount>();
}

int BankA::checkBalance(const std::string& cardId, const int password, const int account)
{
    // find customer, i know it is inefficient. 
    for (auto it = customers.begin(); it < customers.end(); ++it)
    {
        // find customer
        if (it->cardId.compare(cardId) == 0 && it->password == password)
        {
            // check account validation
            if (account < it->accounts.size())
                return it->accounts[account].balance;
        }
    }

    return -1;
}

int BankA::deposit(const std::string& cardId, const int password, const int amount, const int account, BankMessage& ret)
{
    // find customer, i know it is inefficient. 
    for (auto it = customers.begin(); it < customers.end(); ++it)
    {
        // find customer
        if (it->cardId.compare(cardId) == 0 && it->password == password)
        {
            // check amount and account validation
            if (amount >= 0 && account < it->accounts.size())
            {
                ret = BankMessage::Success;
                it->accounts[account].balance += amount;
                return it->accounts[account].balance;
            }
        }
    }

    // May be it is unkwown customer or unknown error.
    ret = BankMessage::UnknownCustomer;

    return -1;
}

int BankA::withdraw(const std::string& cardId, const int password, const int amount, const int account, BankMessage& ret)
{
    // find customer, i know it is inefficient. 
    for (auto it = customers.begin(); it < customers.end(); ++it)
    {
        // find customer
        if (it->cardId.compare(cardId) == 0 && it->password == password)
        {
            // check amount and account validation
            if (amount >= 0 && account < it->accounts.size())
            {
                if (it->accounts[account].balance < amount)
                {
                    ret = BankMessage::LackBalance;
                    return it->accounts[account].balance;
                }

                ret = BankMessage::Success;
                it->accounts[account].balance -= amount;
                return it->accounts[account].balance;
            }
        }
    }

    // May be it is unkwown customer or unknown error.
    ret = BankMessage::UnknownCustomer;

    return -1;
}
