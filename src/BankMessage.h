#pragma once

enum class BankMessage 
{ 
    Success = 1, 
    LackBalance = -1,
    UnknownCustomer = -2
};