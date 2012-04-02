PROGRAMS = rs232
DOCUMENTATIONS = doc

OPT = 
LIBCImg = -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr
CC = gcc
CPP = g++

all: $(PROGRAMS) $(DOCUMENTATIONS)

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


