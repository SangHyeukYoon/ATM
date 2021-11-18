#pragma once

#include <string>
#include <vector>

typedef struct
{
    std::string name;
    int accountNum;
    int balance;
} Acount;

typedef struct
{
    std::string name;
    std::string cardId;
    int password;
    std::vector<Acount> accounts;
} Customer;
