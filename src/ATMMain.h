#pragma once

#include "ATMController.h"
#include "ATMInterface.h"
#include "BankInterface.h"

#include <string>
#include <vector>

class ATMMain : public ATMController
{

private:
    ATMInterface* ux;
    std::vector<BankInterface*> banks;
    int cache;

public:

    ATMMain(ATMInterface* ux, int cache) : ux(ux), cache(cache) {}

    void start();

    void addBank(BankInterface* bank);

    int checkCard(std::string& cardId, int password);
    int checkBalance(int bank, std::string& cardId, int password, ATMMessage& ret);
    int deposit(int bank, std::string& cardId, int password, int amount, ATMMessage& ret);
    int withdraw(int bank, std::string& cardId, int password, int amount, ATMMessage& ret);

};
