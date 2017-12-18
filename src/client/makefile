CC = g++
CLIENT_H_FILES = *.h
CLIENT_CPP_FILES = *.cpp
CLIENT_O_FILES = ./obj/client_obj/*

create_all: obj client clean

client: $(CLIENT_CPP_FILES) $(CLIENT_H_FILES)
	$(CC) -c $(CLIENT_CPP_FILES)
	mv *.o obj/client_obj
	$(CC) $(CLIENT_O_FILES) -o ../../exe/client

obj:
	mkdir obj
	mkdir obj/client_obj

clean:	
	rm -rf obj/
