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

    int bank = atm.checkCard(A.cardId, A.password);
    ATMMessage mes;
    EXPECT_EQ(A.balance, atm.checkBalance(bank, A.cardId, A.password, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    bank = atm.checkCard(B.cardId, B.password);
    EXPECT_EQ(B.balance, atm.checkBalance(bank, B.cardId, B.password, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    bank = atm.checkCard(C.cardId, C.password);
    EXPECT_EQ(C.balance, atm.checkBalance(bank, C.cardId, C.password, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    bank = atm.checkCard(D.cardId, D.password);
    EXPECT_EQ(D.balance, atm.checkBalance(bank, D.cardId, D.password, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    std::string test("dddd2222");
    EXPECT_EQ(-1, atm.checkBalance(10, test, 1234, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);
}

TEST(ATMTest, Deposit) 
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

    int bank = atm.checkCard(C.cardId, C.password);
    ATMMessage mes;
    int amount = 1000;

    EXPECT_EQ(C.balance + amount, atm.deposit(bank, C.cardId, C.password, amount, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    EXPECT_EQ(-1, atm.deposit(bank, C.cardId, C.password, -1000, mes));
    EXPECT_EQ(ATMMessage::InvalidNumber, mes);

    std::string test("dddd2222");
    EXPECT_EQ(-1, atm.deposit(10, test, 1234, 300, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);
}

TEST(ATMTest, Withdraw) 
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
    ATMMain atm(interface, 2000);

    atm.addBank(bankA);
    atm.addBank(bankB);

    int bank = atm.checkCard(C.cardId, C.password);
    ATMMessage mes;
    int amount = 1500;

    EXPECT_EQ(C.balance, atm.withdraw(bank, C.cardId, C.password, amount, mes));
    EXPECT_EQ(ATMMessage::LackBalance, mes);

    amount = 1000;

    EXPECT_EQ(C.balance - amount, atm.withdraw(bank, C.cardId, C.password, amount, mes));
    EXPECT_EQ(ATMMessage::Success, mes);

    EXPECT_EQ(-1, atm.withdraw(bank, C.cardId, C.password, -1000, mes));
    EXPECT_EQ(ATMMessage::InvalidNumber, mes);

    EXPECT_EQ(-1, atm.withdraw(bank, C.cardId, C.password, 3000, mes));
    EXPECT_EQ(ATMMessage::LackCache, mes);

    std::string test("dddd2222");
    EXPECT_EQ(-1, atm.deposit(10, test, 1234, 300, mes));
    EXPECT_EQ(ATMMessage::UnknownCustommer, mes);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
