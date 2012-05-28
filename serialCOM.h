#ifndef SERIAL_COMMUNICATION_TERMIOS
#define SERIAL_COMMUNICATION_TERMIOS

#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "serial.h"

#define SERIAL_OPEN_ERROR  -1
#define SERIAL_CLOSED      -2

class Cserial_termios: public Cserial
{
private:
  //!File descriptor for the port
  int fd;
public:
//! \todo [high] . \c last_message_written, \c last_message_readed (remove \c message).
//! \todo [medium] _ error handling: init fd to SERIAL_CLOSED (i.e. constructor), return code error in all functions but opens() (i.e. if(fd!=SERIAL_CLOSED) closes(); ).
//! \todo [next]   _ call closes in destructor (e.g. add also if(fd!=SERIAL_CLOSED) in closes).
//! \todo [low] move opens, writes, reads and closes to .cpp (i.e. need Makefile changes)
  Cserial_termios()
  {
#if cimg_debug>1
    class_name="Cserial_termios";
#endif
  }//constructor

  //! Open serial port
  /** 
   *
   * @param[in] port 
   *
   * @return 
   */
  bool opens()
  {
    fd=open((const char*)port_path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == SERIAL_OPEN_ERROR)
    {
      std::cerr<<"open_port: Unable to open "<<port_path<<" port.\n";//e.g. /dev/ttyUSB0
      return false;
    }
    fcntl(fd, F_SETFL, 0);
    std::cerr << "port is open"<<std::endl;
    return true;
  }//opens

  //! Open serial port
  /** 
   *
   * @param[in] port 
   *
   * @return 
   */
  bool opens(const std::string& port_path_name)
  {
    return Cserial::opens(port_path_name);
  }//opens
  
  //! write on serial port
  /** 
   *
   * @param[in] message= string to send to serial port  
   *
   * @return 
   */
  bool writes(std::string value,const int number_of_try=3,const int try_wait_time=10)
  {
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<"(\""<<value<<"\""<<","<<number_of_try<<" tries,"<<try_wait_time<<" ms)\n"<<std::flush;
#endif
    last_message_written=value;
    value.append("\r\n");
    int  tries=0;        /* Number of tries so far */
    while(write(fd,(const char*)value.c_str(),value.size()) <value.size())
      {
	tries++;
	if (tries > number_of_try)
	  {
	    std::cerr<<"error: write KO :( (with "<<--tries<<" tries)\n"<<std::flush;
	    return false;
	  }
	std::cerr<<"warning: rs232 not ready, retry\n"<<std::flush;
        cimg_library::cimg::wait(try_wait_time);
      }//try loop
    std::cerr << "write OK\n" << std::flush;
    return true;
  }//writes

  //! read on serial port
  /** 
   *
   * @param[out] value= value returned by serial port
   *
   * @return 
   */
  bool reads(std::string& value)
  {
#if cimg_debug>1
    std::cerr<<class_name<<"::"<<__func__<<"(get \""<<value<<"\")\n"<<std::flush;
#endif
    char buffer[255];  /* Input buffer */
    char *bufptr;      /* Current char in buffer */
    int  nbytes;       /* Number of bytes read */
    //std::string value;
//std::cerr<<__func__<<"/sizeof(buffer)="<<sizeof(buffer)<<"\n"<<std::flush;
    //initialisation
//    std::memset(buffer,0,255);
    //read loop
    bufptr = buffer;
    while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
      {
	std::cerr << "reading buffer" << std::endl;
//std::cerr<<"nbytes="<<nbytes<<"\n"<<std::flush;
	bufptr += nbytes;
	if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
	  break;
      }
    std::cerr << "read OK\n" << std::flush;
    buffer[bufptr-buffer-1]='\0';
//std::cerr<<__func__<<"/lenght(buffer)="<<strlen(buffer)<<"\n"<<std::flush;
    value=buffer;
    last_message_readed=value;//for information
#if cimg_debug>1
std::cerr<<class_name<<"::"<<__func__<<"(set \""<<value<<"\")\n"<<std::flush;
#endif
    return true;
  }//reads

  //! Close serial port
  /** 
   *
   * @return 
   */
  bool closes()
  {
    close(fd);
    fd=SERIAL_CLOSED;
    return true;
  }//closes

};//Cserial_termios class

#endif //SERIAL_COMMUNICATION_TERMIOSCserial_termios

