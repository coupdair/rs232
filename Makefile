PROGRAMS = serialget
DOCUMENTATIONS = doc

OPT = 
LIBCImg = -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr
CC = gcc
CPP = g++

all: $(PROGRAMS) $(DOCUMENTATIONS)

rs232: serial.get.cpp  
	$(CPP) $(OPT) serial.get.cpp -o $@
doc: rs232.Doxygen serial.get.cpp 
	./doxIt.sh

clean:
	rm -rf $(DOCUMENTATIONS)
	rm -f *.o
	rm -rf .libs
	@list='$(PROGRAMS)'; for p in $$list; do \
	  rm -f $$p ; \
	done


