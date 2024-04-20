OBJECTS = character.o game.o moves.o main.o screen.o reward.o
FLAGS = "-std=c++11"

play: $(OBJECTS) 
	g++ $(FLAGS) $(OBJECTS) -o play

game.o: game.cpp game.hpp character.cpp character.hpp moves.cpp moves.hpp screen.cpp screen.hpp
	g++ $(FLAGS) -c game.cpp -o game.o

moves.o: moves.cpp moves.hpp
	g++ $(FLAGS) -c moves.cpp -o moves.o

main.o: main.cpp game.cpp game.hpp character.cpp character.hpp moves.cpp moves.hpp screen.cpp screen.hpp
	g++ $(FLAGS) -c main.cpp -o main.o

character.o: character.cpp character.hpp
	g++ $(FLAGS) -c character.cpp -o character.o

screen.o: screen.cpp screen.hpp textformat.hpp character.cpp character.hpp
	g++ $(FLAGS) -c screen.cpp -o screen.o

reward.o: character.hpp reward.hpp reward.cpp
	g++ $(FLAGS) -c reward.cpp -o reward.o

test: 
	./play
clean:
	rm -f $(OBJECTS) play


.PHONY: clean test
