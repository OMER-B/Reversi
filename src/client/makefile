CC = g++
VERSION = -std=c++98
CLIENT_H_FILES = *.h
CLIENT_CPP_FILES = *.cpp
CLIENT_O_FILES = ./obj/client_obj/*

create_all: obj client_exe clean

client_exe: $(CLIENT_CPP_FILES) $(CLIENT_H_FILES)
	$(CC) $(VERSION) -c $(CLIENT_CPP_FILES)
	mv *.o obj/client_obj
	$(CC) $(VERSION) $(CLIENT_O_FILES) -o ../../exe/client_exe

obj:
	mkdir obj
	mkdir obj/client_obj

clean:	
	rm -rf obj/
