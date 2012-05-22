//serial get
/*-----------------------------------------------------------------------
  File        : serial_get.cpp
  Description : Particle Image Velocimetry program of the Laboratory of Mechanics in Lille (LML)
  Authors     : Caroline BRAUD, Sebastien COUDERT
-----------------------------------------------------------------------*/

//main doxygen page is in serial.put.cpp

//! \todo serial_get doxygen user page

//standard library
#include <iostream>
//CImg Library
#include "../CImg/CImg.h"
//RS232 library
#include "serialCOM.h"

int main(int argc, char *argv[])
{ 
//commmand line options
//! \todo add usage
  const int         verbose    = (cimg_option("-v",(const char*)NULL,"verbose option")!=NULL);
  const bool        show_info  = (cimg_option("--info",(const char*)NULL,"information")!=NULL);
  const bool        show_help  = (cimg_option("-h",(const char*)NULL,"information")!=NULL);
  const std::string SerialPath =  cimg_option("--path","/dev/ttyUSB0","Path serial device");
  const std::string Message =  cimg_option("--message","*IDN?","Message to send to the serial port (the example ask if IFA300 ready)");
//information and help
  if( cimg_option("-I",(const char*)NULL,"show compilation options") != NULL ) cimg_library::cimg::info();
  if (show_help|show_info) return 0; // program stops after printing the information
//serial object
  serialCOM serial;
// OPEN 
  if(!serial.opens(SerialPath)) return 1;
// WRITE 
  if(!serial.writes(Message))   return 1;
// READ
  std::string value;
  serial.reads(value);
  std::cout << value << std::endl;
//CLOSE
  serial.closes();
  return 0;
}//main

