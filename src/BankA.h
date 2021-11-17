#pragma once

#include "BankInterface.h"

#include <string>
#include <vector>

class BankA : public BankInterface
{

private:

    std::string bankName;
    std::string bankId;
    std::vector<Customer> customers;

public:

    BankA(std::string bankName, std::string bankId) : bankName(bankName), bankId(bankId) {}

    void addCustomer(Customer customer);

    bool checkCard(std::string& cardId, int password);
    int checkBalance(std::string& cardId, int password);
    int deposit(std::string& cardId, int password, int amount, BankMessage& ret);
    int withdraw(std::string& cardId, int password, int amount, BankMessage& ret);

};