OBJECTS = character.o

game: $(OBJECTS) 
	g++ $(OBJECTS) -o game

character.o: character.cpp character.h
	g++  -c character.cpp -o character.o

test: 
	./game
clean:
	rm -f $(OBJECTS) game


.PHONY: clean
