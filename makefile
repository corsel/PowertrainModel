CC=g++
CFLAGS=-Iinclude
BINFOLDER=bin

test: Powertrain.o Utilities.o Tester.o main.cpp
	if [ ! -d $(BINFOLDER) ]; then mkdir $(BINFOLDER); fi
	$(CC) -o $(BINFOLDER)/$@ $^ $(CFLAGS) -DTEST_MODE
	make clean
	
release: Powertrain.o Utilities.o main.cpp
	if [ ! -d $(BINFOLDER) ]; then mkdir $(BINFOLDER); fi
	$(CC) -o $(BINFOLDER)/$@ $^ $(CFLAGS)
	make clean
	
Powertrain.o: src/Powertrain.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
Utilities.o: src/Utilities.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
Tester.o: src/Tester.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
clean:
	rm *.o
	
reset:
	rm -r $(BINFOLDER)/*