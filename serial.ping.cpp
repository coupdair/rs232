//serial ping pong
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
#include "serialCOM.h"

int main(int argc, char *argv[])
{ 
//commmand line options
 ///usage
  cimg_usage(std::string("serial_put a RS232 program of the Laboratory of Mechanics in Lille (LML), it is intended to receive a message through the serial cable from a RS232 device, \
it uses different GNU libraries (see --info option)\n\n \
usage: ./ping --path /dev/ttyUSB0\n \
       ./ping --path /dev/ttyUSB1 --pong\n \
version: "+std::string(VERSION)+"\n compilation date: " \
            ).c_str());//cimg_usage
  ///information and help
  const bool show_h   =cimg_option("-h",    false,NULL);//-h hidden option
        bool show_help=cimg_option("--help",show_h,"help (or -h option)");show_help=show_h|show_help;//same --help or -h option
  bool show_info=cimg_option("-I",false,NULL);//-I hidden option
  if( cimg_option("--info",show_info,"show compilation options (or -I option)") ) {show_info=true;cimg_library::cimg::info();}//same --info or -I option
  ///serial related variable
  const std::string SerialPath =  cimg_option("--path","/dev/ttyUSB0","Path serial device");
  const bool pong=cimg_option("--pong",false,"pong program (default ping).");
  std::string Message=(pong)?"pong":"ping";
  const int number=cimg_option("--number",5,"number of 2 side communications (i.e. ping<->pong number).");
  const int wait_time=cimg_option("--wait-time",10,"wait time in ms between write and read.");
  ///stop if help requested
  if(show_help) {/*print_help(std::cerr);*/return 0;}
//serial object
  serialCOM serial;
#if cimg_debug>1
  serial.class_name+=(pong)?"_in_pong":"_in_ping";
#endif
// OPEN 
  if(!serial.opens(SerialPath)) return 1;
/*
// FLUSH
  {
#if cimg_debug>1
  std::cerr<<"flush serial read buffer.\n"<<std::flush;
#endif
  std::string value;
  serial.reads(value);
  }
*/
///ping-pong loop
  for(int i=0;i<number;++i)
  {
// WRITE 
    if( (i>0)||(!pong) ) if(!serial.writes(Message+(char)('0'+i),10,100)) return 1;
//    cimg_library::cimg::wait(wait_time*i);
// READ
    std::string value;
    serial.reads(value);
    std::cout<<std::string((pong)?"pong":"ping")<<": read=\""<<value<<"\" @ i="<<(char)('0'+i)<<"\n"<<std::flush;
//    cimg_library::cimg::wait(wait_time*i*2);
  }
//CLOSE
  serial.closes();
  return 0;
}//main

