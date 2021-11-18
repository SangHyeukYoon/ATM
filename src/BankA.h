#pragma once

#include "BankInterface.h"
#include "Customer.h"

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

    bool checkCard(const std::string& cardId, const int password);
    std::vector<Acount> getAccount(const std::string& cardId, const int password);
    int checkBalance(const std::string& cardId, const int password, const int account);
    int deposit(const std::string& cardId, const int password, const int amount, const int account, BankMessage& ret);
    int withdraw(const std::string& cardId, const int password, const int amount, const int account, BankMessage& ret);

};