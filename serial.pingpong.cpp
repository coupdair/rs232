//serial pingpong
/*-----------------------------------------------------------------------
  File        : serial_ping.cpp
  Description : Particle Image Velocimetry program of the Laboratory of Mechanics in Lille (LML)
  Authors     : Sebastien COUDERT
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
usage: ./pingpong --path-ping /dev/ttyUSB0 --path-pong /dev/ttyUSB1\n \
version: "+std::string(VERSION)+"\n compilation date: " \
            ).c_str());//cimg_usage
  ///information and help
  const bool show_h   =cimg_option("-h",    false,NULL);//-h hidden option
        bool show_help=cimg_option("--help",show_h,"help (or -h option)");show_help=show_h|show_help;//same --help or -h option
  bool show_info=cimg_option("-I",false,NULL);//-I hidden option
  if( cimg_option("--info",show_info,"show compilation options (or -I option)") ) {show_info=true;cimg_library::cimg::info();}//same --info or -I option
  ///serial related variable
  const std::string SerialTypePing=cimg_option("--type-ping","serial_termios","Type of serial device used as ping (i.e. serial_termios or serial_system)");
  const std::string SerialTypePong=cimg_option("--type-pong","serial_termios","Type of serial device used as pong (i.e. serial_termios or serial_system)");
  const std::string SerialPathPing=cimg_option("--path-ping","/dev/ttyUSB0","Path serial device used as ping");
  const std::string SerialPathPong=cimg_option("--path-pong","/dev/ttyUSB1","Path serial device used as pong");
  const int number=cimg_option("--number",5,"number of 2 side communications (i.e. ping<->pong number).");
  const int wait_time=cimg_option("--wait-time",10,"wait time in ms between write and read.");
  ///stop if help requested
  if(show_help) {/*print_help(std::cerr);*/return 0;}
//serial object
  Cserial_factory serial_factory;
  Cserial *pSerial_ping=serial_factory.create(SerialTypePing);
  Cserial *pSerial_pong=serial_factory.create(SerialTypePong);
#if cimg_debug>1
  pSerial_ping->class_name+="ping";
  pSerial_pong->class_name+="pong";
#endif
// OPEN 
  if(!pSerial_ping->opens(SerialPathPing)) return 1;
  if(!pSerial_pong->opens(SerialPathPong)) return 1;
///ping-pong loop
//  std::string Message="ping";
  std::string Message="0123456789ABCDEFIJKLMNOPQRSTUVWXYZ";
  for(int i=0;i<number;++i)
  {
// WRITE 
    std::cout<<"ping: write=\""<<Message+(char)('0'+i)<<"\" @ i="<<(char)('0'+i)<<"\n"<<std::flush;
    if(!pSerial_ping->writes(Message+(char)('0'+i),10,100)) return 1;
    cimg_library::cimg::wait(wait_time);
// READ
    std::string value;
    pSerial_pong->reads(value);
    std::cout<<"pong: read=\""<<value<<"\" @ i="<<(char)('0'+i)<<"\n"<<std::flush;
    cimg_library::cimg::wait(wait_time);
  }
//CLOSE
  pSerial_ping->closes();
  pSerial_pong->closes();
  return 0;
}//main

