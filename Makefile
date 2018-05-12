CC = g++
CFLAGS = -std=c++11 -g
OBJECTS = main.o pid.o model.o
EXECUTABLE = main
VPATH = src
DOXYGENFILE = Doxyfile
DOXYGEN = doxygen

main: $(OBJECTS)
	# $(CC) $(CFLAGS) $(LLVMFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	

%.o : %.cpp
	# $(CC) $(CFLAGS) $(LLVMFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: docs clean

docs:
	$(DOXYGEN) $(DOXYGENFILE)

clean:
	rm $(OBJECTS) $(EXECUTABLE)