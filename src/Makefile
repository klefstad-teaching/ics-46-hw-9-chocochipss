CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

# Default target builds both
all: ladder dijkstra

ladder: ladder.cpp ladder_main.cpp
	g++ $(CXXFLAGS) ladder.cpp ladder_main.cpp -o ladder

dijkstra: dijkstras.cpp dijkstras_main.cpp
	g++ $(CXXFLAGS) dijkstras.cpp dijkstras_main.cpp -o dijkstra

clean:
	rm -f ladder dijkstra
