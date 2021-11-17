#pragma once

#include "BankMessage.h"

#include <string>

typedef struct
{
    std::string name;
    std::string cardId;
    int password;
    int balance;
} Customer;


class BankInterface
{

public:
    
    virtual bool checkCard(std::string& cardId, int password) = 0;
    virtual int checkBalance(std::string& cardId, int password) = 0;
    virtual int deposit(std::string& cardId, int password, int amount, BankMessage& ret) = 0;
    virtual int withdraw(std::string& cardId, int password, int amount, BankMessage& ret) = 0;

};