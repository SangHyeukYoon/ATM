#pragma once

#include "ATMMessage.h"

#include <string>

class ATMInterface
{

public:

    virtual int insertCard(std::string& cardId) = 0;
    virtual void insertCardRet(ATMMessage result) = 0;

    virtual int selectMenu() = 0;
    virtual void checkBalance(int balance) = 0;

    virtual int deposit() = 0;
    virtual void depositRet(ATMMessage result, int balance) = 0;

    virtual int withdraw() = 0;
    virtual void withdrawRet(ATMMessage result, int balance) = 0;

    virtual ~ATMInterface() = default;

};
