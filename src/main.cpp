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
    Customer A;
    A.name = "Yoon";
    A.cardId = "abcd1234";
    A.password = 1234;
    A.balance = 100;

    Customer B;
    B.name = "Lee";
    B.cardId = "abcd5678";
    B.password = 2345;
    B.balance = 300;

    BankA* bankA = new BankA("BankA", "abcd");
    bankA->addCustomer(A);
    bankA->addCustomer(B);

    // Bank B
    Customer C;
    C.name = "Kang";
    C.cardId = "qwer1234";
    C.password = 3456;
    C.balance = 1000;

    Customer D;
    D.name = "Kim";
    D.cardId = "qwer5678";
    D.password = 4567;
    D.balance = 150;

    BankA* bankB = new BankA("BankB", "qwer");
    bankB->addCustomer(C);
    bankB->addCustomer(D);

    // ATM interface
    ATMcui* interface = new ATMcui();

    // Make ATM Object
    ATMMain atm(interface, 500);

    atm.addBank(bankA);
    atm.addBank(bankB);

    atm.start();

    return 0;
}
