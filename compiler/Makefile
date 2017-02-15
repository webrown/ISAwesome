SOURCE=conversions.cpp MachineCode.cpp parsing.cpp utility.cpp main.cpp
OUT=pisaa

$(OUT): $(SOURCE)
	g++ $(SOURCE) -o $(OUT)

test: $(OUT) testfile
	cat testfile | ./$(OUT) > testout

clean:
	-rm $(OUT)
	-rm testout
