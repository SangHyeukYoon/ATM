CC=g++
CFLAGS=-std=c++17

DIR=src/
TEST_DIR=test/

GTEST_LIB_DIR=/home/yoon/develope/googletest/build/lib/
GTEST_INC_DIR=/home/yoon/develope/googletest/googletest/include/

OBJS=$(DIR)main.o $(DIR)ATMcui.o $(DIR)BankA.o $(DIR)ATMMain.o
OBJS_TEST=$(TEST_DIR)atm_test.o $(DIR)ATMcui.o $(DIR)BankA.o $(DIR)ATMMain.o
TARGET=atm
TARGET_TESET=atm_test

all: $(TARGET)

test: $(TARGET_TESET)
	./$(TARGET_TESET)

clean:
	rm -f $(DIR)*.o
	rm -f $(TEST_DIR)*.o
	rm -f $(TARGET) $(TARGET_TESET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

$(TEST_DIR)atm_test.o:
	$(CC) -c -o $@ $(TEST_DIR)atm_test.cpp $(CFLAGS) -I$(GTEST_INC_DIR) -L${GTEST_LIB_DIR} -lgtest -lpthread

$(TARGET_TESET): $(OBJS_TEST)
	$(CC) -o $@ $(OBJS_TEST) $(CFLAGS) -I$(GTEST_INC_DIR) -L${GTEST_LIB_DIR} -lgtest -lpthread
