#pragma once

#include "ATMController.h"
#include "ATMInterface.h"
#include "BankInterface.h"
#include "Customer.h"

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

    int checkCard(const std::string& cardId, const int password);
    std::vector<Acount> getAccount(const int bank, const std::string& cardId, const int password, ATMMessage& ret);
    int checkBalance(const int bank, const std::string& cardId, const int password, const int account, ATMMessage& ret);
    int deposit(const int bank, const std::string& cardId, const int password, const int amount, const int account, ATMMessage& ret);
    int withdraw(const int bank, const std::string& cardId, const int password, const int amount, const int account, ATMMessage& ret);

};
