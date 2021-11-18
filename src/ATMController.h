#pragma once

#include "ATMMessage.h"
#include "BankInterface.h"
#include "Customer.h"

#include <string>
#include <vector>

class ATMController
{

public:

    virtual void start() = 0;

    virtual int checkCard(const std::string& cardId, const int password) = 0;
    virtual std::vector<Acount> getAccount(const int bank, const std::string& cardId, const int password, ATMMessage& ret) = 0;
    virtual int checkBalance(const int bank, const std::string& cardId, const int password, const int account, ATMMessage& ret) = 0;
    virtual int deposit(const int bank, const std::string& cardId, const int password, const int amount, const int account, ATMMessage& ret) = 0;
    virtual int withdraw(const int bank, const std::string& cardId, const int password, const int amount, const int account, ATMMessage& ret) = 0;

};
