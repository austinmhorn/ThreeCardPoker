CC:= g++ -std=c++11

CFLAGS := -Wall -c

TARGET := ThreeCardPoker

$(TARGET): main.o Gameboard.o PokerHand.o
	@echo "Creating target..."
	@$(CC) main.o Gameboard.o PokerHand.o -o $(TARGET)
	@echo "Target created successfully."

main.o: main.cpp Gameboard.hpp PokerHand.hpp
	@echo "Creating main.o..."
	@$(CC) $(CFLAGS) main.cpp
	@echo "Complete."

Gameboard.o: Gameboard.cpp Gameboard.hpp
	@echo "Creating Gameboard.o..."
	@$(CC) $(CFLAGS) Gameboard.cpp
	@echo "Complete."

PokerHand.o: PokerHand.cpp PokerHand.hpp
	@echo "Creating PokerHand.o..."
	@$(CC) $(CFLAGS) PokerHand.cpp
	@echo "Complete."

clean:
	@rm *.o
	@rm ThreeCardPoker

run:
	@./ThreeCardPoker
