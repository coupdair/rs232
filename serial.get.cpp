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
#include "serial_factory.h"

int main(int argc, char *argv[])
{ 
//commmand line options
 ///usage
  cimg_usage(std::string("serial_put a RS232 program of the Laboratory of Mechanics in Lille (LML), it is intended to receive a message through the serial cable from a RS232 device, \
it uses different GNU libraries (see --info option)\n\n \
usage: ./get --message \"*IDN?\"\n \
       ./put --message \"CONF:GAIN 5\"\n \
       ./get --message \"READ:GAIN?\"\n \
version: "+std::string(VERSION)+"\n compilation date: " \
            ).c_str());//cimg_usage
  ///information and help
  const bool show_h   =cimg_option("-h",    false,NULL);//-h hidden option
        bool show_help=cimg_option("--help",show_h,"help (or -h option)");show_help=show_h|show_help;//same --help or -h option
  bool show_info=cimg_option("-I",false,NULL);//-I hidden option
  if( cimg_option("--info",show_info,"show compilation options (or -I option)") ) {show_info=true;cimg_library::cimg::info();}//same --info or -I option
  ///serial related variable
  const std::string SerialType =  cimg_option("--type","serial_termios","Type of serial device (i.e. serial_termios or serial_system)");
  const std::string SerialPath =  cimg_option("--path","/dev/ttyUSB0","Path serial device");
  const std::string Message =  cimg_option("--message","*IDN?","Message to send to the serial port (the example ask if IFA300 ready)");
  ///stop if help requested
  if(show_help) {/*print_help(std::cerr);*/return 0;}
//serial object
  Cserial_factory serial_factory;
  Cserial *pSerial=serial_factory.create(SerialType);
// OPEN 
  if(!pSerial->opens(SerialPath)) return 1;
// WRITE 
  if(!pSerial->writes(Message))   return 1;
// READ
  std::string value;
  pSerial->reads(value);
  std::cout << value << std::endl;
//CLOSE
  pSerial->closes();
  return 0;
}//main

