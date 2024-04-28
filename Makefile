OBJECTS = character.o game.o moves.o main.o screen.o enemymoves.o
FLAGS = "-std=c++11"

all: dungeons

dungeons: $(OBJECTS) 
	g++ $(FLAGS) $(OBJECTS) -o dungeons

game.o: game.cpp game.hpp character.o moves.o screen.o enemymoves.o
	g++ $(FLAGS) -c game.cpp -o game.o

moves.o: moves.cpp moves.hpp
	g++ $(FLAGS) -c moves.cpp -o moves.o

enemymoves.o: enemymoves.cpp enemymoves.hpp character.o
	g++ $(FLAGS) -c enemymoves.cpp -o enemymoves.o

main.o: main.cpp game.o character.o moves.o screen.o
	g++ $(FLAGS) -c main.cpp -o main.o

character.o: character.cpp character.hpp
	g++ $(FLAGS) -c character.cpp -o character.o

screen.o: screen.cpp screen.hpp textformat.hpp character.o
	g++ $(FLAGS) -c screen.cpp -o screen.o


play: 
	./dungeons
clean:
	rm -f $(OBJECTS) dungeons

.PHONY: clean play all
