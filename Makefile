PROGRAMS = rs232
DOCUMENTATIONS = doc

OPT = 
LIBCImg = -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr
CC = gcc
CPP = g++

all: $(PROGRAMS) $(DOCUMENTATIONS)

rs232: serialCOM_v2.cpp  
	$(CPP) $(OPT) serialCOM_v2.cpp -o $@
doc: rs232.Doxygen serialCOM_v2.cpp 
	./doxIt.sh

clean:
	rm -rf $(DOCUMENTATIONS)
	rm -f *.o
	rm -rf .libs
	@list='$(PROGRAMS)'; for p in $$list; do \
	  rm -f $$p ; \
	done


