#pragma once

#include "BankMessage.h"
#include "Customer.h"

#include <string>
#include <vector>

class BankInterface
{

public:
    
    virtual bool checkCard(const std::string& cardId, const int password) = 0;
    virtual std::vector<Acount> getAccount(const std::string& cardId, const int password) = 0;
    virtual int checkBalance(const std::string& cardId, const int password, const int account) = 0;
    virtual int deposit(const std::string& cardId, const int password, const int amount, const int account, BankMessage& ret) = 0;
    virtual int withdraw(const std::string& cardId, const int password, const int amount, const int account, BankMessage& ret) = 0;

};