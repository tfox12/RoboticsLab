server: main.cpp network.o
	g++ -o server main.cpp network.o
network.o: network.cpp network.h
	g++ -c network.cpp
clean:
	rm *.o
	rm server
