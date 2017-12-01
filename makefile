# OMER BARAK        313264053
# HODAYA KOSLOWSKY  313377673

a.out: compileAll
	g++ *.o 
	rm -f *.o

compileAll: *.h *.cpp
	g++ -c *.cpp
