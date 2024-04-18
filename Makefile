OBJECTS = character.o game.o moves.o main.o

play: $(OBJECTS) 
	g++ $(OBJECTS) -o play

game.o: game.cpp game.hpp character.cpp character.hpp moves.cpp moves.hpp
	g++ -c game.cpp -o game.o

moves.o: moves.cpp moves.hpp
	g++ -c moves.cpp -o moves.o

main.o: main.cpp game.cpp game.hpp character.cpp character.hpp moves.cpp moves.hpp
	g++ -c main.cpp -o main.o

character.o: character.cpp character.hpp
	g++ -c character.cpp -o character.o

screen.o: screen.cpp screen.hpp textformat.hpp
	g++ -std=c++11 -c screen.cpp -o screen.o

test: 
	./play
clean:
	rm -f $(OBJECTS) play


.PHONY: clean test
