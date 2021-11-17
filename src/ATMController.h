#pragma once

#include "ATMMessage.h"

#include <string>

class ATMController
{

public:

    virtual void start() = 0;

    virtual int checkCard(std::string& cardId, int password) = 0;
    virtual int checkBalance(int bank, std::string& cardId, int password, ATMMessage& ret) = 0;
    virtual int deposit(int bank, std::string& cardId, int password, int amount, ATMMessage& ret) = 0;
    virtual int withdraw(int bank, std::string& cardId, int password, int amount, ATMMessage& ret) = 0;

};
