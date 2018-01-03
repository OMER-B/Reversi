CC = g++
SERVER_H_FILES = *.h
SERVER_CPP_FILES = *.cpp
SERVER_O_FILES = ./obj/server_obj/*

create_all: obj server clean

server: $(SERVER_CPP_FILES) $(SERVER_H_FILES)
	$(CC) -c $(SERVER_CPP_FILES)
	mv *.o obj/server_obj
	$(CC) -pthread $(SERVER_O_FILES) -o ../../exe/server

obj:
	mkdir obj
	mkdir obj/server_obj

clean:	
	rm -rf obj/
