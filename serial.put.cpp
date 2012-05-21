//serial get

//standard library
#include <iostream>
//CImg Library
#include "../CImg/CImg.h"
//RS232 library
#include "serialCOM.h"

int main(int argc, char *argv[])
{ 
//commmand line options
  const int         verbose    = (cimg_option("-v",(const char*)NULL,"verbose option")!=NULL);
  const bool        show_info  = (cimg_option("--info",(const char*)NULL,"information")!=NULL);
  const bool        show_help  = (cimg_option("-h",(const char*)NULL,"information")!=NULL);
  const std::string SerialPath =  cimg_option("--path","/dev/ttyUSB0","Path serial device");
  const std::string Message =  cimg_option("--message","CONF:GAIN 1","Message to write to serial port (the example set the IFA300 gain to 1");
//information and help
  if( cimg_option("-I",(const char*)NULL,"show compilation options") != NULL ) cimg_library::cimg::info();
  if (show_help|show_info) return 0; // program stops after printing the information
//serial object
  serialCOM serial;
// OPEN 
  if(!serial.opens(SerialPath)) return 1;
// WRITE 
  std::cerr << "write:" << Message <<std::endl;
  if(!serial.writes(Message))   return 1;
//CLOSE
  serial.closes();
  return 0;
}//main

