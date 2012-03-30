PROGRAMS = read_RS232.cpp
DOCUMENTATIONS = doc

OPT = 
LIBcomedi = 
LIBCImg = -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr
LIBNetCDF = -I../../NetCDF/include -lnetcdf_c++ -lnetcdf -L../../NetCDF/lib/
CC = gcc
CPP = g++

all: $(PROGRAMS) $(DOCUMENTATIONS)

rs232: read_RS232.cpp  
	$(CPP) $(OPT) read_RS232.cpp -o $@
doc: rs232.Doxygen read_RS232.cpp 
	./doxIt.sh

clean:
	rm -rf $(DOCUMENTATIONS)
	rm -f *.o
	rm -rf .libs
	@list='$(PROGRAMS)'; for p in $$list; do \
	  rm -f $$p ; \
	done


