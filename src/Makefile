CC = g++

# compiler flags:
CFLAGS  = -g -Wall -Werror -Wpedantic -std=c++17 -pthread

server: main.o server.o path_register.o http_request.o http_response.o http.o static_content_register.o utility.o
	$(CC) $(CFLAGS) -o server main.o server.o path_register.o http_request.o http_response.o http.o static_content_register.o utility.o

main.o:
	$(CC) $(CFLAGS) -c main.cpp

server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp

path_register.o: path_register.cpp
	$(CC) $(CFLAGS) -c path_register.cpp

http.o: http.cpp
	$(CC) $(CFLAGS) -c http.cpp

http_request.o: http_request.cpp
	$(CC) $(CFLAGS) -c http_request.cpp

http_response.o: http_response.cpp
	$(CC) $(CFLAGS) -c http_response.cpp

static_content_register.o: static_content_register.cpp
	$(CC) $(CFLAGS) -c static_content_register.cpp

utility.o: utility.cpp
	$(CC) $(CFLAGS) -c utility.cpp

clean:
	rm -rf main.o server.o path_register.o http_request.o http_response.o http.o static_content_register.o utility.o server