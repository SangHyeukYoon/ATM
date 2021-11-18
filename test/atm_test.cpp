#include <iostream>

#include <gtest/gtest.h>

#include "../src/ATMcui.h"
#include "../src/ATMMessage.h"

#include "../src/BankA.h"
#include "../src/BankMessage.h"

#include "../src/ATMController.h"
#include "../src/ATMMain.h"

TEST(ATMTest, CheckCard) 
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
    
    EXPECT_EQ(0, atm.checkCard(A.cardId, A.password));
    EXPECT_EQ(0, atm.checkCard(B.cardId, B.password));
    EXPECT_EQ(1, atm.checkCard(C.cardId, C.password));
    EXPECT_EQ(1, atm.checkCard(D.cardId, D.password));

    std::string test("dddd2222");
    EXPECT_EQ(-1, atm.checkCard(test, 1234));
}

TEST(ATMTest, CheckBalance) 
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

    // Cusomer A
    int bank = atm.checkCard(A.cardId, A.password);
    ATMMessage mes;
    EXPECT_EQ(A.accounts[0].balance, atm.checkBalance(bank, A.cardId, A.password, 0, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    EXPECT_EQ(A.accounts[1].balance, atm.checkBalance(bank, A.cardId, A.password, 1, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    // Pass wrong account
    EXPECT_EQ(-1, atm.checkBalance(bank, A.cardId, A.password, 2, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);

    // Customer B
    bank = atm.checkCard(B.cardId, B.password);
    EXPECT_EQ(B.accounts[0].balance, atm.checkBalance(bank, B.cardId, B.password, 0, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    EXPECT_EQ(B.accounts[1].balance, atm.checkBalance(bank, B.cardId, B.password, 1, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    // Pass wrong account
    EXPECT_EQ(-1, atm.checkBalance(bank, B.cardId, B.password, 2, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);

    // Customer C
    bank = atm.checkCard(C.cardId, C.password);
    EXPECT_EQ(C.accounts[0].balance, atm.checkBalance(bank, C.cardId, C.password, 0, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    // Pass wrong account
    EXPECT_EQ(-1, atm.checkBalance(bank, C.cardId, C.password, 1, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);

    // Customer D
    bank = atm.checkCard(D.cardId, D.password);
    EXPECT_EQ(D.accounts[0].balance, atm.checkBalance(bank, D.cardId, D.password, 0, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    // Pass wrong account
    EXPECT_EQ(-1, atm.checkBalance(bank, D.cardId, D.password, -1, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);

    // Invalid customer
    std::string test("dddd2222");
    EXPECT_EQ(-1, atm.checkBalance(10, test, 1234, 0, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);
}

TEST(ATMTest, Deposit) 
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

    int bank = atm.checkCard(C.cardId, C.password);
    ATMMessage mes;
    int amount = 1000;

    // Zero test
    EXPECT_EQ(C.accounts[0].balance, atm.deposit(bank, C.cardId, C.password, 0, 0, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    // Deposit test
    EXPECT_EQ(C.accounts[0].balance + amount, atm.deposit(bank, C.cardId, C.password, amount, 0, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    // Invalid amount
    EXPECT_EQ(-1, atm.deposit(bank, C.cardId, C.password, -1000, 0, mes));
    EXPECT_EQ(ATMMessage::InvalidNumber, mes);
    
    // Invalid account
    EXPECT_EQ(-1, atm.deposit(bank, C.cardId, C.password, amount, 3, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);

    // Invalid customer
    std::string test("dddd2222");
    EXPECT_EQ(-1, atm.deposit(10, test, 1234, 300, 0, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);
}

TEST(ATMTest, Withdraw) 
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
    ATMMain atm(interface, 2000);

    atm.addBank(bankA);
    atm.addBank(bankB);

    int bank = atm.checkCard(C.cardId, C.password);
    ATMMessage mes;
    int amount = 1500;

    // zero test
    EXPECT_EQ(C.accounts[0].balance, atm.withdraw(bank, C.cardId, C.password, 0, 0, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    // Lack balance test
    EXPECT_EQ(C.accounts[0].balance, atm.withdraw(bank, C.cardId, C.password, amount, 0, mes));
    EXPECT_EQ(ATMMessage::LackBalance, mes);

    amount = 1000;

    EXPECT_EQ(C.accounts[0].balance - amount, atm.withdraw(bank, C.cardId, C.password, amount, 0, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    // Invalid amount test
    EXPECT_EQ(-1, atm.withdraw(bank, C.cardId, C.password, -1000, 0, mes));
    EXPECT_EQ(ATMMessage::InvalidNumber, mes);

    // Lack ATM cache bin test
    EXPECT_EQ(-1, atm.withdraw(bank, C.cardId, C.password, 3000, 0, mes));
    EXPECT_EQ(ATMMessage::LackCache, mes);

    // Invalid account test
    EXPECT_EQ(-1, atm.withdraw(bank, C.cardId, C.password, 100, 3, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);

    // Invalid customer test
    std::string test("dddd2222");
    EXPECT_EQ(-1, atm.deposit(10, test, 1234, 300, 0, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
