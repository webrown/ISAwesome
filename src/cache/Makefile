cacheTest: Cache.o CacheResult.o main.cpp
	g++ -o cacheTest Cache.o CacheResult.o main.cpp
test: cacheTest
	./cacheTest
%.o: %.cpp
	g++ -c $<
clean:
	rm -f *.o
	rm -f cacheTest
