#include <iostream>
#include <string>

#include "ATMcui.h"
#include "ATMMessage.h"

#include "BankA.h"
#include "BankMessage.h"

#include "ATMController.h"
#include "ATMMain.h"

int main()
{
    // Bank A
    // customer A
    Customer A;
    A.name = "Yoon";
    A.cardId = "abcd1234";
    A.password = 1234;

    Acount account_A_0;
    account_A_0.name = "account 0";
    account_A_0.accountNum = 0;
    account_A_0.balance = 100;

    Acount account_A_1;
    account_A_1.name = "account 1";
    account_A_1.accountNum = 1;
    account_A_1.balance = 300;

    A.accounts.push_back(account_A_0);
    A.accounts.push_back(account_A_1);

    // Customer B
    Customer B;
    B.name = "Lee";
    B.cardId = "abcd5678";
    B.password = 2345;

    Acount account_B_0;
    account_B_0.name = "account 0";
    account_B_0.accountNum = 0;
    account_B_0.balance = 200;

    Acount account_B_1;
    account_B_1.name = "account 1";
    account_B_1.accountNum = 1;
    account_B_1.balance = 500;

    B.accounts.push_back(account_B_0);
    B.accounts.push_back(account_B_1);

    // add customer
    BankA* bankA = new BankA("BankA", "abcd");
    bankA->addCustomer(A);
    bankA->addCustomer(B);

    // Bank B
    // customer C
    Customer C;
    C.name = "Kang";
    C.cardId = "qwer1234";
    C.password = 3456;

    Acount account_C_0;
    account_C_0.name = "account 0";
    account_C_0.accountNum = 0;
    account_C_0.balance = 1000;

    C.accounts.push_back(account_C_0);

    Customer D;
    D.name = "Kim";
    D.cardId = "qwer5678";
    D.password = 4567;

    Acount account_D_0;
    account_D_0.name = "account 0";
    account_D_0.accountNum = 0;
    account_D_0.balance = 150;

    D.accounts.push_back(account_D_0);

    BankA* bankB = new BankA("BankB", "qwer");
    bankB->addCustomer(C);
    bankB->addCustomer(D);

    // ATM interface
    ATMcui* interface = new ATMcui();

    // Make ATM Object
    ATMMain atm(interface, 500);

    atm.addBank(bankA);
    atm.addBank(bankB);

    // start atm service
    atm.start();

    return 0;
}
