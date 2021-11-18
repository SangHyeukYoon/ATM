#pragma once

#include "ATMInterface.h"
#include "ATMMessage.h"
#include "Customer.h"

#include <string>

class ATMcui : public ATMInterface
{

public:

    int insertCard(std::string& cardId);
    void insertCardRet(ATMMessage result);

    int selectAccount(std::vector<Acount> accounts);
    int selectMenu();
    void checkBalance(int balance);

    int deposit();
    void depositRet(ATMMessage result, int balance);

    int withdraw();
    void withdrawRet(ATMMessage result, int balance);

};
