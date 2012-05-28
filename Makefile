PROGRAMS = get put ping pingpong
DOCUMENTATIONS = doc

version = v0.2.1
OPT = -Dcimg_display=0 -Dcimg_debug=2 -Dcimg_use_vt100 -DVERSION=\"$(version)\"
CC = gcc
CPP = g++

all: $(PROGRAMS) $(DOCUMENTATIONS)

prog:$(PROGRAMS)

get: serial.get.cpp serialCOM.h
	$(CPP) $(OPT) serial.get.cpp -o $@

put: serial.put.cpp serialCOM.h
	$(CPP) $(OPT) serial.put.cpp -o $@

ping: serial.ping.cpp serialCOM.h
	$(CPP) $(OPT) serial.ping.cpp -o $@

pingpong: serial.pingpong.cpp serialCOM.h
	$(CPP) $(OPT) serial.pingpong.cpp -o $@

doc: rs232.Doxygen serial.get.cpp serial.put.cpp serial.ping.cpp serial.pingpong.cpp serialCOM.h
	echo ${version} > VERSION
	./doxIt.sh

clean:
	rm -rf $(DOCUMENTATIONS)
	rm -f *.o
	rm -rf .libs
	@list='$(PROGRAMS)'; for p in $$list; do \
	  rm -f $$p ; \
	done


