CC=g++
CFLAGS=-std=c++17
DIR=src/
OBJS=$(DIR)main.o $(DIR)ATMcui.o $(DIR)BankA.o $(DIR)ATMMain.o
TARGET=atm

all: $(TARGET)

clean:
	rm -f $(DIR)*.o
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)
