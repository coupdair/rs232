PROGRAMS = interactive get put ping pingpong
DOCUMENTATIONS = doc

version = v0.3.5.dev
OPT = -Dcimg_display=0 -Dcimg_debug=2 -Dcimg_use_vt100 -DRS232_VERSION=\"$(version)\"
CC = gcc
CPP = g++

all: $(PROGRAMS) $(DOCUMENTATIONS)

prog:$(PROGRAMS)

interactive: interactive_serial.c
	$(CPP) interactive_serial.c -o $@ $(OPT)

get: serial.get.cpp Makefile serial.h serialCOM.h
	$(CPP) serial.get.cpp -o $@ $(OPT)

put: serial.put.cpp Makefile serial.h serialCOM.h
	$(CPP) serial.put.cpp -o $@ $(OPT)

ping: serial.ping.cpp Makefile serial.h serialCOM.h
	$(CPP) serial.ping.cpp -o $@ $(OPT)

pingpong: serial.pingpong.cpp Makefile serial.h serialCOM.h
	$(CPP) serial.pingpong.cpp -o $@ $(OPT)

doc: rs232.Doxygen Makefile serial.h serial.get.cpp serial.put.cpp serial.ping.cpp serial.pingpong.cpp serialCOM.h
	echo ${version} > VERSION
	./doxIt.sh

clean:
	rm -rf $(DOCUMENTATIONS)/*
	rm -f *.o
	rm -rf .libs
	@list='$(PROGRAMS)'; for p in $$list; do \
	  rm -f $$p ; \
	done


