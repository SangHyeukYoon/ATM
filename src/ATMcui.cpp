#include "ATMcui.h"
#include "Customer.h"

#include <string>
#include <iostream>
#include <exception>

int ATMcui::insertCard(std::string& cardId)
{
    int password;       // TODO: Need to crypto

    std::cout << "If you want to use our ATM\nPlease insert your card and type the password." << std::endl << std::endl;

    // Get card id
    std::cout << "Card ID: ";
    std::cin >> cardId;

    // Get password and return.
    std::cout << "Password: ";
    std::cin >> password;

    std::cout << std::endl;

    return password;
}

void ATMcui::insertCardRet(ATMMessage result)
{
    if (result == ATMMessage::Success)
    {
        std::cout << "Checked card." << std::endl << std::endl;
    }
    else if (result == ATMMessage::UnknownCustommer)
    {
        std::cout << "This is invalid card or invalid password." << std::endl;
        std::cout << "Or we are not support your bank." << std::endl << std::endl;
    }
    else
    {
        throw std::exception();
    }
}

int ATMcui::selectAccount(std::vector<Acount> accounts)
{
    std::cout << "Please select account." << std::endl << std::endl;

    for (auto it = accounts.begin(); it < accounts.end(); ++it)
    {
        std::cout << "Number: " << it->accountNum << std::endl;
        std::cout << "Name: " << it->name << std::endl << std::endl;
    }

    int num = -1;

    while (num < 0 || num > accounts.size() - 1)
    {
        std::cout << "Please enter the account number." << std::endl;
        std::cin >> num;
        std::cout << std::endl;
    }

    return num;
}

int ATMcui::selectMenu()
{
    int menu = -1;

    while (menu < 1 || menu > 4)
    {
        std::cout << std::string(32, '=') << std::endl;
        std::cout << "Please selete any memnu." << std::endl;

        std::cout << "1. Check balance" << std::endl;
        std::cout << "2. Deposit" << std::endl;
        std::cout << "3. Withdraw" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << std::string(32, '=') << std::endl << std::endl;

        std::cin >> menu;
        std::cout << std::endl;
    }

    return menu;
}

void ATMcui::checkBalance(int balance)
{
    std::cout << "Your balance is " << balance << "$." << std::endl << std::endl;
}

int ATMcui::deposit()
{
    int amount;

    std::cout << "Please enter the amount." << std::endl;
    std::cin >> amount;
    std::cout << std::endl;

    return amount;
}

void ATMcui::depositRet(ATMMessage result, int balance)
{
    if (result == ATMMessage::Success)
    {
        std::cout << "Deposit Success." << std::endl;
    }
    else if (result == ATMMessage::InvalidNumber)
    {
        std::cout << "Invalid number." << std::endl;
    }
    else
    {
        throw std::exception();
    }

    std::cout << "Your balance is now " << balance << "$." << std::endl << std::endl;
}

int ATMcui::withdraw()
{
    int amount;

    std::cout << "Please enter the amount." << std::endl;
    std::cin >> amount;
    std::cout << std::endl;

    return amount;
}

void ATMcui::withdrawRet(ATMMessage result, int balance)
{
    if (result == ATMMessage::Success)
    {
        std::cout << "Withdraw Success." << std::endl;
    }
    else if (result == ATMMessage::LackBalance)
    {
        std::cout << "Withdraw failed." << std::endl;
        std::cout << "You do not have enough moeny." << std::endl;
    }
    else if (result == ATMMessage::LackCache)
    {
        std::cout << "Withdraw failed." << std::endl;
        std::cout << "This ATM has not enough moeny." << std::endl;
    }
    else if (result == ATMMessage::InvalidNumber)
    {
        std::cout << "Invalid number." << std::endl;
    }
    else
    {
        throw std::exception();
    }

    std::cout << "Your balance is now " << balance << "$." << std::endl << std::endl;
}
