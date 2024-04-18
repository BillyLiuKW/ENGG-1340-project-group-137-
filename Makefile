OBJECTS = character.o game.o moves.o main.o
FLAGS = "-std=c++11"

play: $(OBJECTS) 
	g++ $(FLAGS) $(OBJECTS) -o play

game.o: game.cpp game.hpp character.cpp character.hpp moves.cpp moves.hpp
	g++ $(FLAGS) -c game.cpp -o game.o

moves.o: moves.cpp moves.hpp
	g++ $(FLAGS) -c moves.cpp -o moves.o

main.o: main.cpp game.cpp game.hpp character.cpp character.hpp moves.cpp moves.hpp
	g++ $(FLAGS) -c main.cpp -o main.o

character.o: character.cpp character.hpp
	g++ $(FLAGS) -c character.cpp -o character.o

screen.o: screen.cpp screen.hpp textformat.hpp character.cpp character.hpp
	g++ $(FLAGS) -std=c++11 -c screen.cpp -o screen.o

test: 
	./play
clean:
	rm -f $(OBJECTS) play


.PHONY: clean test
