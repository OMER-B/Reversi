CC = g++
VERSION = -std=c++98
SERVER_H_FILES = *.h
SERVER_CPP_FILES = *.cpp
SERVER_O_FILES = ./obj/server_obj/*

create_all: obj server_exe clean

server_exe: $(SERVER_CPP_FILES) $(SERVER_H_FILES)
	$(CC) $(VERSION) -c $(SERVER_CPP_FILES)
	mv *.o obj/server_obj
	$(CC) $(VERSION) $(SERVER_O_FILES) -o ../../exe/server_exe

obj:
	mkdir obj
	mkdir obj/server_obj

clean:	
	rm -rf obj/
