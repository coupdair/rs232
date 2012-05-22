PROGRAMS = get put  
DOCUMENTATIONS = doc

version = v0.2.0
OPT = -Dcimg_display=0 -Dcimg_debug=2 -Dcimg_use_vt100 -DVERSION=\"$(version)\"
CC = gcc
CPP = g++

all: $(PROGRAMS) $(DOCUMENTATIONS)

prog:$(PROGRAMS)

get: serial.get.cpp  
	$(CPP) $(OPT) serial.get.cpp -o $@

put: serial.put.cpp  
	$(CPP) $(OPT) serial.put.cpp -o $@

doc: rs232.Doxygen serial.get.cpp 
	echo ${version} > VERSION
	./doxIt.sh

clean:
	rm -rf $(DOCUMENTATIONS)
	rm -f *.o
	rm -rf .libs
	@list='$(PROGRAMS)'; for p in $$list; do \
	  rm -f $$p ; \
	done


