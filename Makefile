PROGRAMS = get put  
DOCUMENTATIONS = doc

OPT = -Dcimg_display=0
CC = gcc
CPP = g++

all: $(PROGRAMS) $(DOCUMENTATIONS)

prog:$(PROGRAMS)

get: serial.get.cpp  
	$(CPP) $(OPT) serial.get.cpp -o $@

put: serial.put.cpp  
	$(CPP) $(OPT) serial.put.cpp -o $@

doc: rs232.Doxygen serial.get.cpp 
	./doxIt.sh

clean:
	rm -rf $(DOCUMENTATIONS)
	rm -f *.o
	rm -rf .libs
	@list='$(PROGRAMS)'; for p in $$list; do \
	  rm -f $$p ; \
	done


