CC = /usr/bin/g++ #path to g++
SOURCES = bridge.cpp port.cpp main.cpp #source files
EXE = spanning_tree #executable name
OBJS = $(SOURCES:.cpp = .o)

$(EXE): $(OBJS) 
	$(CC) -o $(EXE) $(OBJS)
%.o: %.cpp
	$(CC) $(FLAGS) -c $(.SOURCE)

clean:
	rm -i $(OBJS) $(EXE)

