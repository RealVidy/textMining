CXX = g++ -std=c++11
CPU_TYPE = native
CFLAGS = -O3 $(DEBUG) -march=$(CPU_TYPE)
OUT = ../

PT = patriciaTrie/

all: compile

compile: $(PT)patriciaTrie.o
	$(CXX) -o $(OUT)$@ $(PT)patriciaTrie.o


$(PT)%.o: $(PT)%.cpp
	$(CXX) -c $(CFLAGS) $<

clean:
	@cd ..; rm -f compile
	@rm -f *.o
