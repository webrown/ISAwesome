cacheTest: Cache.o CacheResult.o test.cpp
	g++ -g -o cacheTest Cache.o CacheResult.o test.cpp
test: cacheTest
	./cacheTest
%.o: %.cpp
	g++ -g -c $<
clean:
	rm -f *.o
	rm -f cacheTest
