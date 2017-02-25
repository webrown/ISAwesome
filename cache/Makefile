cacheTest: Cache.o CacheResult.o main.cpp
	g++ -o cacheTest Cache.o CacheResult.o main.cpp
%.o: %.cpp
	g++ -c $<
clean:
	rm -f *.o
